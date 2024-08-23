/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 20:00:22 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/22 18:59:02 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_usage(void)
{
	write(2, "invalid number of arguments\n", 28);
	printf("./philo number_of_philosophers time_to_die ");
	printf("time_to_eat time_to_sleep ");
	printf("[number_of_times_each_philosopher_must_eat]\n");
}

static int	is_valid_arg(char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	i = 0;
	while (s[i] == '0')
		i++;
	if (!s[i])
		return (0);
	if (ft_strlen(s + i) < 10)
		return (1);
	else if (ft_strlen(s + i) > 10)
		return (0);
	else
		return (ft_strcmp(s + i, "2147483647") <= 0);
}

int	check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (print_usage(), 1);
	i = 1;
	while (i < argc)
	{
		if (!is_valid_arg(argv[i]))
			return (write(2, "invalid argument\n", 17), 1);
		i++;
	}
	return (0);
}
