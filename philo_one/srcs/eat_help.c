/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 18:24:56 by tjinichi          #+#    #+#             */
/*   Updated: 2021/06/07 01:02:46 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

static void	*eat_spaghetti_4(t_philosopher *philo)
{
	philo->eat_count++;
	if (my_usleep(philo->info->time_to_eat, philo->info) == NULL)
	{
		if (pthread_mutex_unlock(&philo->info->forks[philo->left_fork]) != 0)
			return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
		if (pthread_mutex_unlock(&philo->info->forks[philo->right_fork]) != 0)
			return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
		return (wrap(error_exit(ERR_GETTIMEOFDAY)));
	}
	if (pthread_mutex_unlock(&philo->info->forks[philo->left_fork]) != 0)
	{
		if (pthread_mutex_unlock(&philo->info->forks[philo->right_fork]) != 0)
			return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
		return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
	}
	if (pthread_mutex_unlock(&philo->info->forks[philo->right_fork]) != 0)
		return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
	return ("OK");
}

static void	*eat_spaghetti_3(t_philosopher *philo)
{
	philo->last_eat_time = get_cur_time();
	if (philo->last_eat_time == -1)
	{
		if (pthread_mutex_unlock(&(philo->info->mutex)) != 0)
			return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
		if (pthread_mutex_unlock(&philo->info->forks[philo->left_fork]) != 0)
			return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
		if (pthread_mutex_unlock(&philo->info->forks[philo->right_fork]) != 0)
			return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
		return (wrap(error_exit(ERR_GETTIMEOFDAY)));
	}
	if (pthread_mutex_unlock(&(philo->info->mutex)) != 0)
	{
		if (pthread_mutex_unlock(&philo->info->forks[philo->left_fork]) != 0)
			return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
		if (pthread_mutex_unlock(&philo->info->forks[philo->right_fork]) != 0)
			return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
		return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
	}
	return (eat_spaghetti_4(philo));
}

void	*eat_spaghetti_2(t_philosopher *philo)
{
	if (pthread_mutex_lock(&(philo->info->mutex)) != 0)
	{
		if (pthread_mutex_unlock(&philo->info->forks[philo->left_fork]) != 0)
			return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
		if (pthread_mutex_unlock(&philo->info->forks[philo->right_fork]) != 0)
			return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
		return (wrap(error_exit(ERR_MUTEX_LOCK)));
	}
	if (print_action(philo->number + 1,
			EAT, philo->info->status, philo->info->begin_time) == EXIT_FAILURE)
	{
		if (pthread_mutex_unlock(&(philo->info->mutex)) != 0)
			return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
		if (pthread_mutex_unlock(&philo->info->forks[philo->left_fork]) != 0)
			return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
		if (pthread_mutex_unlock(&philo->info->forks[philo->right_fork]) != 0)
			return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
		return (wrap(error_exit(ERR_PRINTF)));
	}
	return (eat_spaghetti_3(philo));
}
