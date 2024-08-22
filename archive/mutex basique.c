/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:51:56 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/16 18:09:43 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// long long	get_timestamp(void)
// {
// 	struct timeval	tv;

// 	if (gettimeofday(&tv, NULL) == -1)
// 	{
// 		write(2, "timestamp error\n", 16);
// 		return (-1);
// 	}
// 	return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
// }

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

typedef struct s_data
{
	int				n;
	pthread_mutex_t	mutex;
}					t_data;

void	*routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	pthread_mutex_lock(&data->mutex);
	printf("debut de routine\n");
	int *n = &data->n;
	printf("n = %d\n", *n);
	printf("n passe a %d\n", *n + 1);
	(*n)++;
	printf("fin de routine\n");
	pthread_mutex_unlock(&data->mutex);
	return (NULL);
}

int	main(void)
{
	t_data		data;
	pthread_t	pthread[2];

	printf("debut du programme\n");
	data.n = 0;
	pthread_mutex_init(&data.mutex, NULL);
	pthread_create(&pthread[0], NULL, routine, &data);
	pthread_create(&pthread[1], NULL, routine, &data);
	pthread_join(pthread[0], NULL);
	pthread_join(pthread[1], NULL);
	pthread_mutex_destroy(&data.mutex);
	printf("fin du programme\n");
}
