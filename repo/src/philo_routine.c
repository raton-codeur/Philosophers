/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:16:52 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/22 16:49:17 by qhauuy           ###   ########.fr       */
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

static void	eat_routine(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->forks[philo->id - 1]);
	if (get_simulation_stop(data))
	{
		pthread_mutex_unlock(&data->forks[philo->id - 1]);
		return ;
	}
	printf("%06lld %d has taken a fork\n", get_timestamp(data), philo->id);
	if (data->philos_count == 1)
	{
		pthread_mutex_unlock(&data->forks[philo->id - 1]);
		while (get_simulation_stop(data) == 0)
			;
		return ;
	}
	pthread_mutex_lock(&data->forks[philo->id % data->philos_count]);
	if (get_simulation_stop(data))
	{
		pthread_mutex_unlock(&data->forks[philo->id - 1]);
		pthread_mutex_unlock(&data->forks[philo->id % data->philos_count]);
		return ;
	}
	printf("%06lld %d has taken a fork\n", get_timestamp(data), philo->id);
	printf("%06lld %d is eating\n", get_timestamp(data), philo->id);
	set_last_meal_time(philo, data);
	increment_meals_count(philo);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&data->forks[philo->id - 1]);
	pthread_mutex_unlock(&data->forks[philo->id % data->philos_count]);
}

static void	sleep_routine(t_philo *philo, t_data *data)
{
	if (get_simulation_stop(data))
		return ;
	printf("%06lld %d is sleeping\n", get_timestamp(data), philo->id);
	usleep(data->time_to_sleep * 1000);
}

static void	think_routine(t_philo *philo, t_data *data)
{
	if (get_simulation_stop(data))
		return ;
	printf("%06lld %d is thinking\n", get_timestamp(data), philo->id);
}

void	*philo_routine(void *arg)
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
