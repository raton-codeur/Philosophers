/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:51:56 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/23 19:48:23 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_routine(t_data *data)
{
	(void)data;
}

void	launch_simulation(t_data *data)
{
	pid_t	pid;
	int		i;

	while (i < data->philos_count)
	{
		pid = fork();
		if (pid == 0)
		{
			philo_routine(data);
			exit(0);
		}
		else if (pid < 0)
		{
			write(2, "fork: error\n", 12);
			exit(1);
		}
		i++;
	}
}

void	check_simulation_stop(t_data *data)
{
	(void)data;
}

void	finish_program(t_data *data)
{
	sem_close(data->forks);
	sem_unlink("/forks");
}

int	main(int argc, char **argv)
{
	t_data	data;

	check_args(argc, argv);
	init(&data, argc, argv);
	launch_simulation(&data);
	check_simulation_stop(&data);
	finish_program(&data);
	return (0);
}
