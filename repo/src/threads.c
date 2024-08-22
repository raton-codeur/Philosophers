/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:14:10 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/22 17:02:20 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	launch_threads(t_data *data)
{
	int		i;
	t_philo	*philos;

	philos = data->philos;
	i = 0;
	while (i < data->philos_count)
	{
		pthread_create(&philos[i].thread_id, NULL, routine, &philos[i]);
		i += 2;
	}
	usleep(1000);
	i = 1;
	while (i < data->philos_count)
	{
		pthread_create(&philos[i].thread_id, NULL, routine, &philos[i]);
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
