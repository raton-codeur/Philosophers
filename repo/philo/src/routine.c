/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:16:52 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/22 18:08:40 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat_routine(t_philo *philo, t_data *data)
{
	lock_fork(data, philo->id - 1);
	if (get_simulation_stop(data))
		return (unlock_fork(data, philo->id - 1));
	printf("%6lld %d has taken a fork\n", get_timestamp(data), philo->id);
	if (data->philos_count == 1)
		return (philo_alone(philo, data));
	lock_fork(data, philo->id % data->philos_count);
	if (get_simulation_stop(data))
	{
		unlock_fork(data, philo->id - 1);
		unlock_fork(data, philo->id % data->philos_count);
		return ;
	}
	printf("%6lld %d has taken a fork\n", get_timestamp(data), philo->id);
	printf("%6lld %d is eating\n", get_timestamp(data), philo->id);
	set_last_meal_time(philo, data);
	increment_meals_count(philo);
	usleep(data->time_to_eat * 1000);
	unlock_fork(data, philo->id - 1);
	unlock_fork(data, philo->id % data->philos_count);
}

static void	sleep_routine(t_philo *philo, t_data *data)
{
	if (get_simulation_stop(data))
		return ;
	printf("%6lld %d is sleeping\n", get_timestamp(data), philo->id);
	usleep(data->time_to_sleep * 1000);
}

static void	think_routine(t_philo *philo, t_data *data)
{
	if (get_simulation_stop(data))
		return ;
	printf("%6lld %d is thinking\n", get_timestamp(data), philo->id);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (get_simulation_stop(data) == 0)
	{
		eat_routine(philo, data);
		sleep_routine(philo, data);
		think_routine(philo, data);
	}
	return (NULL);
}
