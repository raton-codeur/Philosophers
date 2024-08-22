/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:51:56 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/16 16:26:50 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_timestamp(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		write(2, "timestamp error\n", 16);
		return (-1);
	}
	return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	*routine(void *arg)
{
	(void)arg;
	printf("routine\n");
	return (NULL);
}

int main()
{
	pthread_t	pthread;
	pthread_create(&pthread, NULL, routine, NULL);
	usleep(1 * 1000 * 1000);
}

// tester get timestamp
// int	main(void)
// {
// 	long long	timestamp;

// 	while (1)
// 	{
// 		timestamp = get_timestamp();
// 		if (timestamp == -1)
// 			return (1);
// 		printf("timestamp : %lld\n", timestamp);
// 		usleep(1 * 1000 * 1000);
// 	}
// }

