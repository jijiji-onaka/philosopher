/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 18:24:56 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/31 18:53:18 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

static void	*eat_spaghetti_3(t_philosopher *philo)
{
	philo->eat_count++;
	if (usleep(1000) == -1)
	{
		if (pthread_mutex_unlock(&philo->info->forks[philo->left_fork]) != 0)
			return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
		if (pthread_mutex_unlock(&philo->info->forks[philo->right_fork]) != 0)
			return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
		return (wrap(error_exit(ERR_USLEEP)));
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

void	*eat_spaghetti_2(t_philosopher *philo)
{
	philo->last_eat_time = get_cur_time();
	if (philo->last_eat_time == -1)
	{
		if (pthread_mutex_unlock(&(philo->info->eat_mutex)) != 0)
			return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
		if (pthread_mutex_unlock(&philo->info->forks[philo->left_fork]) != 0)
			return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
		if (pthread_mutex_unlock(&philo->info->forks[philo->right_fork]) != 0)
			return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
		return (wrap(error_exit(ERR_GETTIMEOFDAY)));
	}
	if (pthread_mutex_unlock(&(philo->info->eat_mutex)) != 0)
	{
		if (pthread_mutex_unlock(&philo->info->forks[philo->left_fork]) != 0)
			return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
		if (pthread_mutex_unlock(&philo->info->forks[philo->right_fork]) != 0)
			return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
		return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
	}
	return (eat_spaghetti_3(philo));
}
