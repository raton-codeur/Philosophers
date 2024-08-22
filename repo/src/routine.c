/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:16:52 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/22 15:03:49 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat_routine(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->forks[philo->id - 1]);
	if (get_sim_stop(data))
	{
		pthread_mutex_unlock(&data->forks[philo->id - 1]);
		return ;
	}
	printf("%06lld %d has taken a fork\n", get_timestamp(data), philo->id);
	if (data->philos_count == 1)
	{
		pthread_mutex_unlock(&data->forks[philo->id - 1]);
		while (get_sim_stop(data) == 0)
			;
	}
	if (get_sim_stop(data))
		return ;
	pthread_mutex_lock(&data->forks[philo->id % data->philos_count]);
	if (get_sim_stop(data))
		return ;
	printf("%06lld %d has taken a fork\n", get_timestamp(data), philo->id);
	printf("%06lld %d is eating\n", get_timestamp(data), philo->id);
	philo->last_meal_time = get_timestamp(data);
	philo->meals_count++;
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&data->forks[philo->id - 1]);
	pthread_mutex_unlock(&data->forks[philo->id % data->philos_count]);
}

static void	sleep_routine(t_philo *philo, t_data *data)
{
	if (get_sim_stop(data))
		return ;
	printf("%06lld %d is sleeping\n", get_timestamp(data), philo->id);
	usleep(data->time_to_sleep * 1000);
}

static void	think_routine(t_philo *philo, t_data *data)
{
	if (get_sim_stop(data))
		return ;
	printf("%06lld %d is thinking\n", get_timestamp(data), philo->id);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (get_sim_stop(data) == 0)
	{
		eat_routine(philo, data);
		sleep_routine(philo, data);
		think_routine(philo, data);
	}
	return (NULL);
}
