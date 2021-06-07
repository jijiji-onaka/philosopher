/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 18:24:56 by tjinichi          #+#    #+#             */
/*   Updated: 2021/06/07 10:53:14 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

static void	*eat_spaghetti_4(t_philosopher *philo)
{
	philo->eat_count++;
	if (my_usleep(philo->info->time_to_eat, philo->info) == NULL)
	{
		if (sem_post(philo->info->forks) == -1)
			return (wrap(error_exit(ERR_SEM_POST)));
		if (sem_post(philo->info->forks) == -1)
			return (wrap(error_exit(ERR_SEM_POST)));
		return (wrap(error_exit(ERR_GETTIMEOFDAY)));
	}
	if (sem_post(philo->info->forks) == -1)
	{
		if (sem_post(philo->info->forks) == -1)
			return (wrap(error_exit(ERR_SEM_POST)));
		return (wrap(error_exit(ERR_SEM_POST)));
	}
	if (sem_post(philo->info->forks) == -1)
		return (wrap(error_exit(ERR_SEM_POST)));
	return ("OK");
}

static void	*eat_spaghetti_3(t_philosopher *philo)
{
	philo->last_eat_time = get_cur_time();
	if (philo->last_eat_time == -1)
	{
		if (sem_post(philo->info->semaphore) == -1)
			return (wrap(error_exit(ERR_SEM_POST)));
		if (sem_post(philo->info->forks) == -1)
			return (wrap(error_exit(ERR_SEM_POST)));
		if (sem_post(philo->info->forks) == -1)
			return (wrap(error_exit(ERR_SEM_POST)));
		return (wrap(error_exit(ERR_GETTIMEOFDAY)));
	}
	if (sem_post(philo->info->semaphore) == -1)
	{
		if (sem_post(philo->info->forks) == -1)
			return (wrap(error_exit(ERR_SEM_POST)));
		if (sem_post(philo->info->forks) == -1)
			return (wrap(error_exit(ERR_SEM_POST)));
		return (wrap(error_exit(ERR_SEM_WAIT)));
	}
	return (eat_spaghetti_4(philo));
}

void	*eat_spaghetti_2(t_philosopher *philo)
{
	if (sem_wait(philo->info->semaphore) == -1)
	{
		if (sem_post(philo->info->forks) == -1)
			return (wrap(error_exit(ERR_SEM_POST)));
		if (sem_post(philo->info->forks) == -1)
			return (wrap(error_exit(ERR_SEM_POST)));
		return (wrap(error_exit(ERR_SEM_WAIT)));
	}
	if (print_action(philo->number + 1,
			EAT, philo->info->status, philo->info->begin_time) == EXIT_FAILURE)
	{
		if (sem_post(philo->info->semaphore) == -1)
			return (wrap(error_exit(ERR_SEM_POST)));
		if (sem_post(philo->info->forks) == -1)
			return (wrap(error_exit(ERR_SEM_POST)));
		if (sem_post(philo->info->forks) == -1)
			return (wrap(error_exit(ERR_SEM_POST)));
		return (wrap(error_exit(ERR_PRINTF)));
	}
	return (eat_spaghetti_3(philo));
}
