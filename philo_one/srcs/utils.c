/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 20:42:41 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/31 18:22:10 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int64_t	ft_atoi(char *str)
{
	int		sign;
	int64_t	res;

	res = 0;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	sign = 1;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = 44 - *(str - 1);
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		if ((INT_MAX < res && sign == 1)
			|| (res == (int64_t)INT_MAX + 2 && sign == -1))
			return (-1);
		str++;
	}
	return (res * sign);
}

bool	is_valid_arg(t_philo_one *info)
{
	if (info->number_of_philosophers <= 1)
		return (error_exit(OOR_NUM_PHI));
	if (info->time_to_die <= 0)
		return (error_exit(OOR_TIME_DIE));
	if (info->time_to_eat <= 0)
		return (error_exit(OOR_TIME_EAT));
	if (info->time_to_sleep <= 0)
		return (error_exit(OOR_TIME_SLEEP));
	if (info->number_of_times_each_philosopher_must_eat < -1)
		return (error_exit(OOR_NUM_MUST_EAT));
	return (true);
}

bool	get_arg(t_philo_one *info, int argc, char **argv)
{
	info->number_of_philosophers = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		info->number_of_times_each_philosopher_must_eat = -1;
	printf("1 : %lld\n", ft_atoi(argv[1]));
	printf("2 : %lld\n", ft_atoi(argv[2]));
	printf("3 : %lld\n", ft_atoi(argv[3]));
	printf("4 : %lld\n", ft_atoi(argv[4]));
	if (argc == 6)
		printf("5 : %lld\n", ft_atoi(argv[5]));
	if (is_valid_arg(info) == false)
		return (false);
	info->status = ALIVE;
	info->all_eat = false;
	return (true);
}

time_t	get_cur_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return ((tv.tv_usec / 1000) + (tv.tv_sec * 1000));
}
