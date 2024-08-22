/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:53:48 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/22 13:31:39 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_arrays(t_data *data)
{
	free(data->forks);
	free(data->philos);
}

// static void	unlock_all_forks(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->philos_count)
// 	{
// 		pthread_mutex_unlock(&(data->forks[i]));
// 		i++;
// 	}
// }

// static void	destroy_mutexes(t_data *data)
// {
// 	int	i;

// 	unlock_all_forks(data);
// 	i = 0;
// 	while (i < data->philos_count)
// 	{
// 		pthread_mutex_destroy(&(data->forks[i].mutex));
// 		i++;
// 	}
// }

void	free_all(t_data *data)
{
	// destroy_mutexes(data);
	free_arrays(data);
}
