/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:35:21 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/22 18:57:49 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_count = 0;
		data->philos[i].last_meal_time = 0;
		if (pthread_mutex_init(&data->philos[i].mutex, NULL))
		{
			write(2, "pthread_mutex_init: error", 25);
			destroy_philos(data, i);
			return (1);
		}
		data->philos[i].data = data;
		i++;
	}
	return (0);
}

static int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			write(2, "pthread_mutex_init: error", 25);
			destroy_forks(data, i);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	last_mutex_error(t_data *data)
{
	write(2, "pthread_mutex_init: error", 25);
	destroy_philos(data, data->philos_count);
	destroy_forks(data, data->philos_count);
	free_arrays(data);
	return (1);
}

int	init(t_data *data, int argc, char **argv)
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
		return (write(2, "gettimeofday: error\n", 20), 1);
	data->simulation_stop = 0;
	data->philos = malloc(sizeof(t_philo) * data->philos_count);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philos_count);
	if (data->philos == NULL || data->forks == NULL)
		return (free_arrays(data), write(2, "malloc: error\n", 14), 1);
	if (init_philos(data))
		return (free_arrays(data), 1);
	if (init_forks(data))
		return (destroy_philos(data, data->philos_count), free_arrays(data), 1);
	if (pthread_mutex_init(&data->mutex, NULL))
		return (last_mutex_error(data));
	return (0);
}
