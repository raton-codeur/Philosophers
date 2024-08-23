/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:35:21 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/23 19:29:43 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init(t_data *data, int argc, char **argv)
{
	data->philos_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->meals_max = ft_atoi(argv[5]);
	else
		data->meals_max = 0;
	data->start_time = get_absolute_timestamp();
	if (data->start_time == -1)
		return (write(2, "gettimeofday: error\n", 20), exit(1));
	data->simulation_stop = 0;
	if (pthread_mutex_init(&data->mutex, NULL))
		return (write(2, "pthread_mutex_init: error", 25), exit(1));
	sem_unlink("/forks");
	data->forks = \
		sem_open("/forks", O_CREAT | O_EXCL, 0644, data->philos_count);
	if (data->forks == SEM_FAILED)
		return (write(2, "sem_open: error\n", 16), exit(1));
}
 