/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:14:10 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/22 21:28:32 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_for_threads_half(t_data *data, int start, int max)
{
	int	i;

	i = start;
	while (i < max)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i += 2;
	}
}

static int	pthread_create_error(t_data *data, int i, int first_half)
{
	write(2, "pthread_create: error\n", 22);
	set_simulation_stop(data);
	if (first_half)
		wait_for_threads_half(data, 0, i);
	else
	{
		wait_for_threads_half(data, 0, data->philos_count);
		wait_for_threads_half(data, 1, i);
	}
	free_all(data);
	return (1);
}

int	launch_threads(t_data *data)
{
	int		i;
	t_philo	*philos;

	philos = data->philos;
	i = 0;
	while (i < data->philos_count)
	{
		if (pthread_create(&philos[i].thread_id, NULL, routine, &philos[i]))
			return (pthread_create_error(data, i, 1));
		i += 2;
	}
	usleep(1000);
	i = 1;
	while (i < data->philos_count)
	{
		if (pthread_create(&philos[i].thread_id, NULL, routine, &philos[i]))
			return (pthread_create_error(data, i, 0));
		i += 2;
	}
	return (0);
}

void	wait_for_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
}
