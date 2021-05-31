/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:10:59 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/31 21:32:15 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

long long	time_diff(long long past, long long pres)
{
	if (pres == -1 || past == -1)
		exit(1);
	return (pres - past);
}


void		smart_sleep(long long time, t_philo_one *info)
{
	long long i;

	i = get_cur_time();
	if (i == -1)
		exit(1);
	(void)info;
	while (info->status == ALIVE)
	{
		if (time_diff(i, get_cur_time()) >= time)
			break ;
		usleep(10);
	}
}

void	*eat_spaghetti(t_philosopher *philo)
{
	// if (philo->eat_count
	// 	== philo->info->number_of_times_each_philosopher_must_eat)
	// 	return (NULL);
	// if (pthread_mutex_lock(&philo->info->forks[philo->right_fork]) != 0)
	// 	return (wrap(error_exit(ERR_MUTEX_LOCK)));
	// if (take_fork(philo, RIGHT) == NULL)
	// 	return (NULL);
	// if (pthread_mutex_lock(&philo->info->forks[philo->left_fork]) != 0)
	// 	return (wrap(error_exit(ERR_MUTEX_LOCK)));
	// if (take_fork(philo, LEFT) == NULL)
	// 	return (NULL);
	// if (pthread_mutex_lock(&(philo->info->eat_mutex)) != 0)
	// 	return (wrap(error_exit(ERR_MUTEX_LOCK)));
	// if (print_action(philo->number + 1,
	// 		EAT, philo->info->status) == EXIT_FAILURE)
	// {
	// 	if (pthread_mutex_unlock(&(philo->info->eat_mutex)) != 0)
	// 		return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
	// 	if (pthread_mutex_unlock(&philo->info->forks[philo->left_fork]) != 0)
	// 		return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
	// 	if (pthread_mutex_unlock(&philo->info->forks[philo->right_fork]) != 0)
	// 		return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
	// 	return (NULL);
	// }
	// return (eat_spaghetti_2(philo));
	if (philo->eat_count
		== philo->info->number_of_times_each_philosopher_must_eat)
		return (NULL);
	pthread_mutex_lock(&philo->info->forks[philo->right_fork]);
	take_fork(philo, RIGHT);
	pthread_mutex_lock(&philo->info->forks[philo->left_fork]);
	take_fork(philo, LEFT);
	pthread_mutex_lock(&(philo->info->eat_mutex));
	print_action(philo->number + 1,
			EAT, philo->info->status);
	// if (print_action(philo->number + 1,
	// 		EAT, philo->info->status) == false)
	// 	return (NULL);
	philo->last_eat_time = get_cur_time();
	pthread_mutex_unlock(&(philo->info->eat_mutex));
	philo->eat_count++;
	smart_sleep(philo->info->time_to_eat, philo->info);
	// usleep(philo->info->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->info->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->info->forks[philo->right_fork]);
	return ("OK");
}

// bool	print_action_2(int number, char *message, bool status)
// {
// 	// char	*act_message;

// 	if (status == DEATH)
// 		return (EXIT_FAILURE);
// 	// else if (act == TAKE_FORK)
// 	// 	act_message = "has taken a fork";
// 	// else if (act == EAT)
// 	// 	act_message = "is eating";
// 	// else if (act == SLEEP)
// 	// 	act_message = "is sleeping";
// 	// else if (act == THINK)
// 	// 	act_message = "is thinking";
// 	// else if (act == DIED)
// 	// 	act_message = "died";
// 	printf("%ld %d %s\n", get_cur_time(), number, message);
// 	// if (printf("%ld %d %s\n", get_cur_time(), number, act_message) < 0)
// 	// 	return (error_exit(ERR_PRINTF));
// 	return (EXIT_SUCCESS);
// }

void	*sleep_after_eating(t_philosopher *philo)
{
	if (philo->eat_count
		== philo->info->number_of_times_each_philosopher_must_eat)
		return (NULL);
	if (philo->info->status == DEATH)
		return (NULL);
	smart_sleep(philo->info->time_to_sleep, philo->info);
	// if (print_action(philo->number + 1, SLEEP,
	// 		philo->info->status) == false)
	// 	return (NULL);
	// philo->last_eat_time++;
	print_action(philo->number + 1, SLEEP, philo->info->status);
	return ("OK");
}

void	*deep_thought(t_philosopher *philo)
{
	if (philo->eat_count
		== philo->info->number_of_times_each_philosopher_must_eat)
		return (NULL);
	if (philo->info->status == DEATH)
		return (NULL);
	// if (print_action(philo->number + 1,
	//		THINK, philo->info->status) == EXIT_FAILURE)
	//	return (NULL);
	print_action(philo->number + 1, THINK, philo->info->status);
	return ("OK");
}

void	*take_fork(t_philosopher *phil, int l_or_r)
{
	void	*res;

	res = "OK";
	if (phil->eat_count
		== phil->info->number_of_times_each_philosopher_must_eat)
		res = NULL;
	if (phil->info->status == DEATH)
		res = NULL;
	if (print_action(phil->number + 1,
			TAKE_FORK, phil->info->status) == EXIT_FAILURE)
		res = NULL;
	// if (res == NULL)
	// {
	// 	if (l_or_r == RIGHT || l_or_r == LEFT)
	// 		if (pthread_mutex_unlock(&phil->info->forks[phil->right_fork]) != 0)
	// 			return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
	// 	if (l_or_r == LEFT)
	// 		if (pthread_mutex_unlock(&phil->info->forks[phil->left_fork]) != 0)
	// 			return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
	// 	return (NULL);
	// }
	// return ("OK");
	(void)l_or_r;
	return (res);
}
