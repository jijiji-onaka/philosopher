/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 22:52:22 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/31 17:59:57 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

bool	initialize_philosophers(t_philo_one *info)
{
	int64_t			i;
	t_philosopher	*philosophers;

	philosophers = malloc(sizeof(t_philosopher) * info->number_of_philosophers);
	if (philosophers == NULL)
		return (error_exit(ERR_MALLOC));
	i = -1;
	while (++i < info->number_of_philosophers)
	{
		philosophers[i].number = i;
		philosophers[i].left_fork = i;
		philosophers[i].right_fork = (i + 1) % info->number_of_philosophers;
		philosophers[i].last_eat_time = get_cur_time();
		philosophers[i].eat_count = 0;
		philosophers[i].info = info;
	}
	info->philosophers = philosophers;
	return (true);
}

bool	initialize_mutex_fork(t_philo_one *info)
{
	int64_t	i;

	info->forks = malloc(sizeof(pthread_mutex_t)
			* info->number_of_philosophers);
	if (info->forks == NULL)
		return (error_exit(ERR_MALLOC));
	i = -1;
	while (++i < info->number_of_philosophers)
		if (pthread_mutex_init(&(info->forks[i]), NULL) != 0)
			return (error_exit(ERR_MUTEX_INIT));
	if (pthread_mutex_init(&(info->artist), NULL) != 0)
		return (error_exit(ERR_MUTEX_INIT));
	if (pthread_mutex_init(&(info->eat_mutex), NULL) != 0)
		return (error_exit(ERR_MUTEX_INIT));
	return (true);
}
