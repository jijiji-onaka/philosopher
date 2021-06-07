/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 22:52:22 by tjinichi          #+#    #+#             */
/*   Updated: 2021/06/07 02:25:41 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

bool	initialize_philosophers(t_philo_two *info)
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
		philosophers[i].last_eat_time = get_cur_time();
		if (philosophers[i].last_eat_time == -1)
			return (error_exit(ERR_GETTIMEOFDAY));
		philosophers[i].eat_count = 0;
		philosophers[i].info = info;
	}
	info->philosophers = philosophers;
	return (true);
}

bool	initialize_semaphore(t_philo_two *info)
{
	info->forks = sem_open(MY_FORK_NAME, O_CREAT | O_EXCL, S_IRWXU,
			info->number_of_philosophers);
	if (info->forks == SEM_FAILED)
	{
		sem_unlink(MY_FORK_NAME);
		info->forks = sem_open(MY_FORK_NAME, O_CREAT | O_EXCL, S_IRWXU,
				info->number_of_philosophers);
		if (info->forks == SEM_FAILED)
			return (error_exit(ERR_SEM_OPEN));
	}
	info->semaphore = sem_open(MY_SEMA_NAME, O_CREAT | O_EXCL, S_IRWXU, 1);
	if (info->semaphore == SEM_FAILED)
	{
		sem_unlink(MY_SEMA_NAME);
		info->semaphore = sem_open(MY_SEMA_NAME, O_CREAT | O_EXCL, S_IRWXU, 1);
		if (info->semaphore == SEM_FAILED)
			return (error_exit(ERR_SEM_OPEN));
	}
	return (true);
}
