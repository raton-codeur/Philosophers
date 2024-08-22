/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:53:48 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/22 15:52:29 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_arrays(t_data *data)
{
	free(data->forks);
	free(data->philos);
}

void	destroy_mutexes(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philos_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&data->mutex);
}
