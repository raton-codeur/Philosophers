/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:51:56 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/22 16:31:42 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv) || init(&data, argc, argv))
		return (1);
	launch_threads(&data);
	check_simulation_stop(&data);
	wait_for_threads(&data);
	destroy_mutexes(&data);
	free_arrays(&data);
	return (0);
}
