/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:14:10 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/22 14:30:31 by qhauuy           ###   ########.fr       */
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

static int	is_dead(t_philo *philo, t_data *data)
{
	return (get_timestamp(data) - philo->last_meal_time >= data->time_to_die);
}

int	get_sim_stop(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->sim_stop_mut);
	result = data->simulation_stop;
	pthread_mutex_unlock(&data->sim_stop_mut);
	return (result);
}

void	check_simulation_stop(t_data *data)
{
	int		all_meals_completed;
	int		i;
	t_philo	*philo;

	while (get_sim_stop(data) == 0)
	{
		all_meals_completed = data->meals_max;
		i = 0;
		while (i < data->philos_count && get_sim_stop(data) == 0)
		{
			philo = &data->philos[i];
			if (is_dead(philo, data))
			{
				printf("%06lld %d died\n", get_timestamp(data), philo->id);
				pthread_mutex_lock(&data->sim_stop_mut);
				data->simulation_stop = 1;
				pthread_mutex_unlock(&data->sim_stop_mut);
			}
			if (philo->meals_count < data->meals_max)
				all_meals_completed = 0;
			i++;
		}
		if (all_meals_completed)
		{
			pthread_mutex_lock(&data->sim_stop_mut);
			data->simulation_stop = 1;
			pthread_mutex_unlock(&data->sim_stop_mut);
		}
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
