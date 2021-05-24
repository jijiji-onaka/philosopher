/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:10:59 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/24 19:38:44 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void	*eat_spaghetti(t_philosopher *philosopher)
{
	if (philosopher->info->status == DEATH)
		return (NULL);
	if (pthread_mutex_lock(&philosopher->info->forks[philosopher->right_fork]) != 0)
		return (wrap(error_exit(ERR_MUTEX_LOCK)));
	take_fork(philosopher);
	if (pthread_mutex_lock(&philosopher->info->forks[philosopher->left_fork]) != 0)
		return (wrap(error_exit(ERR_MUTEX_LOCK)));
	take_fork(philosopher);
	print_action(philosopher->number + 1, EAT);
	philosopher->eat_count++;
	philosopher->last_eat_time = get_cur_time();
	usleep(philosopher->info->time_to_eat * 950);
	if (pthread_mutex_unlock(&philosopher->info->forks[philosopher->left_fork]) != 0)
		return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
	if (pthread_mutex_unlock(&philosopher->info->forks[philosopher->right_fork]) != 0)
		return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
	return ("OK");
}

void	*sleep_after_eating(t_philosopher *philosopher)
{
	if (philosopher->info->status == DEATH)
		return (NULL);
	print_action(philosopher->number + 1, SLEEP);
	usleep(philosopher->info->time_to_sleep * 950);
	return ("OK");
}

void	*deep_thought(t_philosopher *philosopher)
{
	if (philosopher->info->status == DEATH)
		return (NULL);
	print_action(philosopher->number + 1, THINK);
	return ("OK");
}

void	*take_fork(t_philosopher *philosopher)
{
	if (philosopher->info->status == DEATH)
		return (NULL);
	print_action(philosopher->number + 1, TAKE_FORK);
	return ("OK");
}
