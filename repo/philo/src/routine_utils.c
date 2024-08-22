/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:36:07 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/22 17:36:31 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_fork(t_data *data, int i)
{
	pthread_mutex_lock(&data->forks[i]);
}

void	unlock_fork(t_data *data, int i)
{
	pthread_mutex_unlock(&data->forks[i]);
}

void	increment_meals_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->meals_count++;
	pthread_mutex_unlock(&philo->mutex);
}

void	set_last_meal_time(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&philo->mutex);
	philo->last_meal_time = get_timestamp(data);
	pthread_mutex_unlock(&philo->mutex);
}

void	philo_alone(t_philo *philo, t_data *data)
{
	unlock_fork(data, philo->id - 1);
	while (get_simulation_stop(data) == 0)
		;
}
