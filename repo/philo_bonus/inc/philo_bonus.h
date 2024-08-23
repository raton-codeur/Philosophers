/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:53:46 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/23 15:31:11 by qhauuy           ###   ########.fr       */
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
# include <signal.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/types.h>

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
	sem_t			*forks;
	int				simulation_stop;
	pthread_mutex_t	mutex;
}					t_data;

/* utils.c */
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *s);
int			ft_strcmp(const char *s1, const char *s2);
long long	get_absolute_timestamp(void);
long long	get_timestamp(t_data *data);

/* check_args.c */
void	check_args(int argc, char **argv);

/* init.c */
void	init(t_data *data, int argc, char **argv);

/* free.c */
void	free_all(t_data *data);

#endif
