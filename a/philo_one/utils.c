/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:59:07 by gsmets            #+#    #+#             */
/*   Updated: 2021/05/31 20:21:03 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			ft_atoi(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(n * sign));
}

long long	timestamp(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
		return (-1);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long past, long long pres)
{
	if (pres == -1 || past == -1)
		exit(1);
	return (pres - past);
}

void		smart_sleep(long long time, t_rules *rules)
{
	long long i;

	i = timestamp();
	if (i == -1)
		exit(1);
	while (!(rules->dieded))
	{
		if (time_diff(i, timestamp()) >= time)
			break ;
		usleep(50);
	}
}

void		action_print(t_rules *rules, int id, char *string)
{
	if (pthread_mutex_lock(&(rules->writing)) != 0)
		exit(1);
	if (!(rules->dieded))
	{
		if (printf("%lli ", timestamp() - rules->first_timestamp) < 0)
			exit(1);
		if (printf("%i ", id + 1) < 0)
			exit(1);
		if (printf("%s\n", string) < 0)
			exit(1);
	}
	if (pthread_mutex_unlock(&(rules->writing)) != 0)
		exit(1);
	return ;
}
