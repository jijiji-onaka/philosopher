/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 02:11:09 by tjinichi          #+#    #+#             */
/*   Updated: 2021/06/07 01:25:25 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

void	*philosopher_act(void *philo_info)
{
	t_philosopher	*philosopher;
	t_philo_two		*info;

	philosopher = (t_philosopher *)philo_info;
	info = philosopher->info;
	philosopher->last_eat_time = get_cur_time();
	if (philosopher->last_eat_time == -1)
		return (wrap(error_exit(ERR_GETTIMEOFDAY)));
	if ((philosopher->number % 2) == 1)
	{
		if (deep_thought(philosopher) == NULL)
			return (NULL);
		if (usleep(philosopher->info->time_to_eat) == -1)
			return (wrap(error_exit(ERR_USLEEP)));
	}
	while (info->status == ALIVE)
	{
		if (info->all_eat == true || eat_spaghetti(philosopher) == NULL)
			return (NULL);
		if (info->all_eat == true || sleep_after_eating(philosopher) == NULL)
			return (NULL);
		if (info->all_eat == true || deep_thought(philosopher) == NULL)
			return (NULL);
	}
	return ("OK");
}

static int	death_from_starvation(t_philo_two *info, t_philosopher *philosopher)
{
	int64_t	i;
	time_t	cur_time;

	i = -1;
	while (++i < info->number_of_philosophers && info->status == ALIVE)
	{
		if (sem_wait(info->semaphore) == -1)
			return (error_exit(ERR_SEM_WAIT));
		cur_time = get_cur_time();
		if (cur_time == -1)
		{
			if (sem_post(info->semaphore) == -1)
				return (error_exit(ERR_SEM_POST));
			return (error_exit(ERR_GETTIMEOFDAY));
		}
		if (die_check(&(philosopher[i]), cur_time) == NULL)
			return (EXIT_FAILURE);
		if (sem_post(info->semaphore) == -1)
			return (error_exit(ERR_SEM_POST));
		if (info->status == DEATH)
			return (-1);
	}
	return (EXIT_SUCCESS);
}

int	death_monitor(t_philo_two *info, t_philosopher *philosopher)
{
	int64_t	i;
	int64_t	finish_eat_philo_num;
	int64_t	must_eat;
	int		ret;

	must_eat = info->number_of_times_each_philosopher_must_eat;
	while (info->all_eat == false)
	{
		ret = death_from_starvation(info, philosopher);
		if (ret == EXIT_FAILURE || ret == -1)
			return (ret);
		i = -1;
		finish_eat_philo_num = 0;
		while (must_eat != -1 && ++i < info->number_of_philosophers)
			if (philosopher[i].eat_count >= must_eat)
				finish_eat_philo_num++;
		if (finish_eat_philo_num == info->number_of_philosophers)
			return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

bool	create_thread(t_philo_two *info)
{
	int64_t		i;
	pthread_t	*tid;

	tid = malloc(sizeof(pthread_t) * info->number_of_philosophers);
	if (tid == NULL)
		return (error_exit(ERR_MALLOC));
	info->begin_time = get_cur_time();
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
