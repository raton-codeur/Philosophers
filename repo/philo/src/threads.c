/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:14:10 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/22 19:16:20 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pthread_create_error(t_data *data, int i)
{
	int	j;

	write(2, "pthread_create: error\n", 22);
	if (i % 2 == 0)
	{
		j = 0;
		pthread_join(
	}
	else
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
			return (pthread_create_error(data, i));
		i += 2;
	}
	usleep(1000);
	i = 1;
	while (i < data->philos_count)
	{
		if (pthread_create(&philos[i].thread_id, NULL, routine, &philos[i]))
			return (pthread_create_error(data, i));
		i += 2;
	}
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
