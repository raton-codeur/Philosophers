/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:51:56 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/16 19:05:04 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct s_data
{
	int				n; // la data utilisee dans la routine du thread
	pthread_mutex_t	mutex_n; // mutex qui protege la data
}	t_data;

typedef struct s_thread
{
	pthread_t		id;
	int				i;
	t_data			*data;
}	t_thread;

void	*routine(void *arg)
{
	t_thread	*thread;

	thread = (t_thread *)arg;

	pthread_mutex_lock(&thread->data->mutex_n);
	printf("debut de routine pour le thread %d\n", thread->i);
	printf("n = %d\n", thread->data->n);
	printf("n passe a %d\n", thread->data->n + 1);
	thread->data->n++;
	printf("fin de routine pour le thread %d\n", thread->i);
	pthread_mutex_unlock(&thread->data->mutex_n);

	return (NULL);
}

void	init_data(t_data *data)
{
	data->n = 0;
	pthread_mutex_init(&data->mutex_n, NULL);
}

void	free_data(t_data *data)
{
	pthread_mutex_destroy(&data->mutex_n);
}

void	init_threads(t_thread *array, int size, t_data *data)
{
	int	i;

	i = 0;
	while (i < size)
	{
		array[i].i = i;
		array[i].data = data;
		i++;
	}
}

void	launch_threads(t_thread *array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_create(&array[i].id, NULL, routine, &array[i]);
		i++;
	}
}

void	wait_for_threads(t_thread *array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_join(array[i].id, NULL);
		i++;
	}
}

int	main(void)
{
	t_data		data;
	t_thread	threads[5];

	printf("debut du programme\n");
	init_data(&data);
	init_threads(threads, 5, &data);
	launch_threads(threads, 5);
	wait_for_threads(threads, 5);
	free_data(&data);
	printf("fin du programme\n");
}
