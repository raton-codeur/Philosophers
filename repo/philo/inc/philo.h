/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:53:46 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/23 14:57:06 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;
	int				meals_count;
	long long		last_meal_time;
	pthread_mutex_t	mutex;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				philos_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_max;
	long long		start_time;
	int				simulation_stop;
	pthread_mutex_t	mutex;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}					t_data;

/* utils.c */
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *s);
int			ft_strcmp(const char *s1, const char *s2);
long long	get_absolute_timestamp(void);
long long	get_timestamp(t_data *data);

/* check_args.c */
int			check_args(int argc, char **argv);

/* init.c */
int			init(t_data *data, int argc, char **argv);

/* free.c */
void		free_arrays(t_data *data);
void		destroy_philos(t_data *data, int max);
void		destroy_forks(t_data *data, int max);
void		free_all(t_data *data);

/* threads.c */
int			launch_threads(t_data *data);
void		wait_for_threads(t_data *data);

/* check_simulation_stop.c */
int			get_simulation_stop(t_data *data);
void		set_simulation_stop(t_data *data);
void		check_simulation_stop(t_data *data);

/* routine.c */
void		*routine(void *arg);

/* routine_utils.c */
void		lock_fork(t_data *data, int i);
void		unlock_fork(t_data *data, int i);
void		increment_meals_count(t_philo *philo);
void		set_last_meal_time(t_philo *philo, t_data *data);
void		philo_alone(t_philo *philo, t_data *data);

#endif
