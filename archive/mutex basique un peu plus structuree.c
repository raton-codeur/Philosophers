/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:51:56 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/16 18:42:41 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct s_data
{
	int				n; // la data utilisee dans la routine du thread
	pthread_mutex_t	mutex_n; // mutex qui protege la data
}	t_data;

void	*routine(void *arg)
{
	t_data	*data;
	int		*n;

	data = (t_data *)arg;
	printf("debut de routine\n");

	pthread_mutex_lock(&data->mutex_n);
	n = &data->n;
	printf("n = %d\n", *n);
	printf("n passe a %d\n", *n + 1);
	(*n)++;
	pthread_mutex_unlock(&data->mutex_n);

	printf("fin de routine\n");
	return (NULL);
}

int	main(void)
{
	t_data		data;
	pthread_t	pthread[2];

	printf("debut du programme\n");

	data.n = 0;
	pthread_mutex_init(&data.mutex_n, NULL);

	pthread_create(&pthread[0], NULL, routine, &data);
	pthread_create(&pthread[1], NULL, routine, &data);

	pthread_join(pthread[0], NULL);
	pthread_join(pthread[1], NULL);

	pthread_mutex_destroy(&data.mutex_n);

	printf("fin du programme\n");
}
