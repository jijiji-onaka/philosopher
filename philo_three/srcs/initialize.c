/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 22:52:22 by tjinichi          #+#    #+#             */
/*   Updated: 2021/06/07 22:00:10 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

bool	initialize_philosophers(t_philo_three *info)
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

bool	initialize_semaphore(t_philo_three *info)
{
	info->forks = my_sem_open(MY_FORK_NAME, O_CREAT | O_EXCL, S_IRWXU,
			info->number_of_philosophers);
	info->semaphore = my_sem_open(MY_SEMA_NAME, O_CREAT | O_EXCL, S_IRWXU, 1);
	info->dead_sem = my_sem_open(MY_DEAD_NAME, O_CREAT | O_EXCL, S_IRWXU, 1);
	return (true);
}
