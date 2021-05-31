/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 02:11:09 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/31 19:27:14 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void	*philosopher_act(void *philo_info)
{
	t_philosopher	*philosopher;
	t_philo_one		*info;

	philosopher = (t_philosopher *)philo_info;
	info = philosopher->info;
	philosopher->last_eat_time = get_cur_time();
	if (philosopher->last_eat_time == -1)
		return (wrap(error_exit(ERR_GETTIMEOFDAY)));
	if ((philosopher->number % 2) == 1)
	{
		// if (deep_thought(philosopher) == NULL)
		// 	return (NULL);
		if (usleep(200) == -1)
			return (wrap(error_exit(ERR_USLEEP)));
	}
	while (info->status == ALIVE)
	{
		if (eat_spaghetti(philosopher) == NULL || info->all_eat == true)
			return (NULL);
		if (sleep_after_eating(philosopher) == NULL || info->all_eat == true)
			return (NULL);
		if (deep_thought(philosopher) == NULL || info->all_eat == true)
			return (NULL);
	}
	return ("OK");
}

int	death_monitor(t_philo_one *info, t_philosopher *philosopher)
{
	int		i;
	time_t	cur_time;

	while (info->all_eat == false)
	{
		i = -1;
		while (++i < info->number_of_philosophers && info->status == ALIVE)
		{
			if (pthread_mutex_lock(&(info->eat_mutex)) != 0)
				return (error_exit(ERR_MUTEX_LOCK));
			cur_time = get_cur_time();
			if (cur_time == -1)
			{
				if (pthread_mutex_unlock(&(info->eat_mutex)) != 0)
					return (error_exit(ERR_MUTEX_LOCK));
				return (error_exit(ERR_GETTIMEOFDAY));
			}
			if (philosopher[i].info->time_to_die
				+ philosopher[i].last_eat_time < get_cur_time())
			{
				// printf("%lld\n", philosopher[i].info->time_to_die + philosopher[i].last_eat_time + 2);
				// printf("%ld\n", cur_time);
				// printf("%d\n", philosopher[0].);
				if (print_action(philosopher[i].number + 1, DIED, philosopher->info->status) == EXIT_FAILURE)
					return (EXIT_FAILURE);
				info->status = DEATH;
			}
			if (pthread_mutex_unlock(&(info->eat_mutex)) != 0)
				return (error_exit(ERR_MUTEX_LOCK));
			if (usleep(100) == -1)
				return (error_exit(ERR_USLEEP));
		}
		if (info->status == DEATH)
			break ;
		i = 0;
		while (info->number_of_times_each_philosopher_must_eat != -1
			&& ++i < info->number_of_philosophers
			&& philosopher[i].eat_count
				>= info->number_of_times_each_philosopher_must_eat)
			i++;
		if (i == info->number_of_philosophers)
			info->all_eat = true;
	}
	return (EXIT_SUCCESS);
}

bool	create_thread(t_philo_one *info)
{
	int64_t		i;
	pthread_t	*tid;

	tid = malloc(sizeof(pthread_t) * info->number_of_philosophers);
	if (tid == NULL)
		return (error_exit(ERR_MALLOC));
	i = -1;
	while (++i < info->number_of_philosophers)
	{
		if (pthread_create(&(tid[i]), NULL, philosopher_act,
				info->philosophers + i) != 0)
			return (error_exit(ERR_PTHREAD_CREATE));
	}
	if (death_monitor(info, info->philosophers) == EXIT_FAILURE)
		return (false);
	i = -1;
	while (++i < info->number_of_philosophers)
		if (pthread_join(tid[i], NULL) != 0)
			return (error_exit(ERR_PTHREAD_JOIN));
	free(tid);
	tid = NULL;
	return (true);
}
