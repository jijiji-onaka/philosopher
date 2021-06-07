/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:10:59 by tjinichi          #+#    #+#             */
/*   Updated: 2021/06/07 21:54:28 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	*eat_spaghetti(t_philosopher *philo)
{
	if (philo->eat_count
		== philo->info->number_of_times_each_philosopher_must_eat)
		return (NULL);
	if (sem_wait(philo->info->forks) == -1)
		return (wrap(error_exit(ERR_SEM_WAIT)));
	if (take_fork(philo, RIGHT) == NULL)
		return (NULL);
	if (sem_wait(philo->info->forks) == -1)
	{
		if (sem_post(philo->info->forks) == -1)
			return (wrap(error_exit(ERR_SEM_POST)));
		return (wrap(error_exit(ERR_SEM_WAIT)));
	}
	if (take_fork(philo, LEFT) == NULL)
		return (NULL);
	return (eat_spaghetti_2(philo));
}

void	*sleep_after_eating(t_philosopher *philo)
{
	if (philo->eat_count
		== philo->info->number_of_times_each_philosopher_must_eat)
		return (NULL);
	if (philo->info->status == DEATH)
		return (NULL);
	if (sem_wait(philo->info->semaphore) == -1)
		return (wrap(error_exit(ERR_SEM_WAIT)));
	if (print_action(philo->number + 1, SLEEP,
			philo->info->status, philo->info->begin_time) == EXIT_FAILURE)
	{
		if (sem_post(philo->info->semaphore) == -1)
			return (wrap(error_exit(ERR_SEM_POST)));
		return (wrap(error_exit(ERR_PRINTF)));
	}
	if (sem_post(philo->info->semaphore) == -1)
		return (wrap(error_exit(ERR_SEM_POST)));
	if (my_usleep(philo->info->time_to_sleep, philo->info) == NULL)
		return (wrap(error_exit(ERR_GETTIMEOFDAY)));
	return ("OK");
}

void	*deep_thought(t_philosopher *philo)
{
	if (philo->eat_count
		== philo->info->number_of_times_each_philosopher_must_eat)
		return (NULL);
	if (philo->info->status == DEATH)
		return (NULL);
	if (sem_wait(philo->info->semaphore) == -1)
		return (wrap(error_exit(ERR_SEM_WAIT)));
	if (print_action(philo->number + 1,
			THINK, philo->info->status,
			philo->info->begin_time) == EXIT_FAILURE)
	{
		if (sem_post(philo->info->semaphore) == -1)
			return (wrap(error_exit(ERR_SEM_POST)));
		return (wrap(error_exit(ERR_PRINTF)));
	}
	if (sem_post(philo->info->semaphore) == -1)
		return (wrap(error_exit(ERR_SEM_POST)));
	return ("OK");
}

void	*take_fork(t_philosopher *philo, int l_or_r)
{
	void	*res;

	res = "OK";
	if (philo->eat_count
		== philo->info->number_of_times_each_philosopher_must_eat)
		res = NULL;
	if (philo->info->status == DEATH)
		res = NULL;
	if (print_action(philo->number + 1,
			TAKE_FORK, philo->info->status,
			philo->info->begin_time) == EXIT_FAILURE)
		res = NULL;
	if (res == NULL)
	{
		if (l_or_r == RIGHT || l_or_r == LEFT)
			if (sem_post(philo->info->semaphore) == -1)
				return (wrap(error_exit(ERR_SEM_POST)));
		if (l_or_r == LEFT)
			if (sem_post(philo->info->semaphore) == -1)
				return (wrap(error_exit(ERR_SEM_POST)));
		if (philo->info->status == DEATH)
			return (NULL);
		return (wrap(error_exit(ERR_PRINTF)));
	}
	return (res);
}

void	*die_check(t_philosopher *philo, time_t cur_time)
{
	if (sem_wait(philo->info->dead_sem) == -1)
		return (wrap(error_exit(ERR_SEM_WAIT)));
	if (philo->info->time_to_die + philo->last_eat_time < cur_time)
	{
		if (print_action(philo->number + 1,
				DIED, philo->info->status,
				philo->info->begin_time) == EXIT_FAILURE)
		{
			if (sem_post(philo->info->semaphore) == -1)
				return (wrap(error_exit(ERR_SEM_POST)));
			if (sem_post(philo->info->dead_sem) == -1)
				return (wrap(error_exit(ERR_SEM_POST)));
			return (wrap(error_exit(ERR_PRINTF)));
		}
		philo->info->status = DEATH;
	}
	if (sem_post(philo->info->dead_sem) == -1)
		return (wrap(error_exit(ERR_SEM_POST)));
	return ("OK");
}
