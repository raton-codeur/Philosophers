/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:53:46 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/22 15:27:29 by qhauuy           ###   ########.fr       */
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
	struct s_data	*data;
	pthread_mutex_t	philo_mutex;
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
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	data_mutex;
}					t_data;

/* utils.c */
int			ft_atoi(const char *str);
long long	get_absolute_timestamp(void);
long long	get_timestamp(t_data *data);

/* check_args.c */
int			check_args(int argc, char **argv);

/* init.c */
int			init_data(t_data *data, int argc, char **argv);

/* free.c */
void		free_arrays(t_data *data);
void		free_all(t_data *data);

/* main_thread.c */
void		launch_threads(t_data *data);
int			get_sim_stop(t_data *data);
void		check_simulation_stop(t_data *data);
void		wait_for_threads(t_data *data);

/* routine.c */
void		*routine(void *arg);

#endif