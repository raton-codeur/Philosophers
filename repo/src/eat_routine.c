/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:29:30 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/22 17:29:35 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	increment_meals_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->meals_count++;
	pthread_mutex_unlock(&philo->mutex);
}

static void	set_last_meal_time(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&philo->mutex);
	philo->last_meal_time = get_timestamp(data);
	pthread_mutex_unlock(&philo->mutex);
}

static void	lock_fork(t_data *data, int i)
{
	pthread_mutex_lock(&data->forks[i]);
}

static void	unlock_fork(t_data *data, int i)
{
	pthread_mutex_unlock(&data->forks[i]);
}

void	eat_routine(t_philo *philo, t_data *data)
{
	lock_fork(data, philo->id - 1);
	if (get_simulation_stop(data))
		return (unlock_fork(data, philo->id - 1));
	printf("%06lld %d has taken a fork\n", get_timestamp(data), philo->id);
	if (data->philos_count == 1)
	{
		while (get_simulation_stop(data) == 0)
			;
		return (unlock_fork(data, philo->id - 1));
	}
	lock_fork(data, philo->id % data->philos_count);
	if (get_simulation_stop(data))
	{
		unlock_fork(data, philo->id - 1);
		unlock_fork(data, philo->id % data->philos_count);
		return ;
	}
	printf("%06lld %d has taken a fork\n", get_timestamp(data), philo->id);
	printf("%06lld %d is eating\n", get_timestamp(data), philo->id);
	set_last_meal_time(philo, data);
	increment_meals_count(philo);
	usleep(data->time_to_eat * 1000);
	unlock_fork(data, philo->id - 1);
	unlock_fork(data, philo->id % data->philos_count);
}
