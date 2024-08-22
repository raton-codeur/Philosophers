/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:35:21 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/22 14:26:20 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_count = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].data = data;
		i++;
	}
}

static void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

int	init_data(t_data *data, int argc, char **argv)
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
		return (write(2, "gettimeofday error\n", 19), 1);
	data->simulation_stop = 0;
	data->philos = malloc(sizeof(t_philo) * data->philos_count);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philos_count);
	if (data->philos == NULL || data->forks == NULL)
		return (free_arrays(data), write(2, "malloc error\n", 13), 1);
	init_philos(data);
	init_forks(data);
	pthread_mutex_init(&data->sim_stop_mut, NULL);
	return (0);
}
