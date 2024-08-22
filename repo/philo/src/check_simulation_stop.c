/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_simulation_stop.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:24:16 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/22 21:47:37 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_simulation_stop(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->mutex);
	result = data->simulation_stop;
	pthread_mutex_unlock(&data->mutex);
	return (result);
}

void	set_simulation_stop(t_data *data)
{
	pthread_mutex_lock(&data->mutex);
	data->simulation_stop = 1;
	pthread_mutex_unlock(&data->mutex);
}

static int	is_dead(t_philo *philo, t_data *data)
{
	int	result;

	pthread_mutex_lock(&philo->mutex);
	result = get_timestamp(data) - philo->last_meal_time >= data->time_to_die;
	pthread_mutex_unlock(&philo->mutex);
	return (result);
}

static int	meals_not_finished(t_philo *philo, t_data *data)
{
	int	result;

	pthread_mutex_lock(&philo->mutex);
	result = philo->meals_count < data->meals_max;
	pthread_mutex_unlock(&philo->mutex);
	return (result);
}

void	check_simulation_stop(t_data *data)
{
	int		all_meals_finished;
	int		i;
	t_philo	*philo;

	while (get_simulation_stop(data) == 0)
	{
		all_meals_finished = data->meals_max;
		i = 0;
		while (i < data->philos_count && get_simulation_stop(data) == 0)
		{
			philo = &data->philos[i];
			if (is_dead(philo, data))
			{
				printf("%6lld %d died\n", get_timestamp(data), philo->id);
				set_simulation_stop(data);
			}
			if (meals_not_finished(philo, data))
				all_meals_finished = 0;
			i++;
		}
		if (all_meals_finished)
			set_simulation_stop(data);
	}
}
