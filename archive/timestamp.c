/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:51:56 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/14 22:42:14 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(void)
{
	struct timeval	tv;
	long long		timestamp;
	int				i;

	i = 0;
	while (i < 100)
	{
		if (gettimeofday(&tv, NULL) == -1)
		{
			perror("gettimeofday");
			return (1);
		}
		timestamp = (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
		usleep(1 * 1000 * 1000);
		printf("timestamp : %lld\n", timestamp);
		i++;
	}
}
