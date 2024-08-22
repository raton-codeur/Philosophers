/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:53:48 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/22 18:39:40 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_arrays(t_data *data)
{
	free(data->forks);
	free(data->philos);
}

void	destroy_philos(t_data *data, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&data->philos[j].mutex);
		j++;
	}
}

void	destroy_forks(t_data *data, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&data->forks[j]);
		j++;
	}
}

void	free_all(t_data *data)
{
	destroy_philos(data, data->philos_count);
	destroy_forks(data, data->philos_count);
	pthread_mutex_destroy(&data->mutex);
	free_arrays(data);
}
