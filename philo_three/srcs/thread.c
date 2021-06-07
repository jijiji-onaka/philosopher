/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 02:11:09 by tjinichi          #+#    #+#             */
/*   Updated: 2021/06/07 22:06:10 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

static int	death_from_starvation(t_philo_three *info,
					t_philosopher *philosopher)
{
	time_t	cur_time;

	if (sem_wait(info->semaphore) == -1)
		return (error_exit(ERR_SEM_WAIT));
	cur_time = get_cur_time();
	if (cur_time == -1)
	{
		if (sem_post(info->semaphore) == -1)
			return (error_exit(ERR_SEM_POST));
		return (error_exit(ERR_GETTIMEOFDAY));
	}
	if (die_check(philosopher, cur_time) == NULL)
		return (EXIT_FAILURE);
	if (sem_post(info->semaphore) == -1)
		return (error_exit(ERR_SEM_POST));
	if (info->status == DEATH)
		return (-1);
	return (EXIT_SUCCESS);
}

// when the philosopher dies, it exit.
// but when all the philosophers has finished eating, it return .
void	*death_monitor(void *philo_info)
{
	int64_t			must_eat;
	t_philosopher	*philosopher;
	t_philo_three	*info;

	philosopher = (t_philosopher *)philo_info;
	info = philosopher->info;
	must_eat = info->number_of_times_each_philosopher_must_eat;
	while (info->all_eat == false)
	{
		if (death_from_starvation(info, philosopher) != EXIT_SUCCESS)
		{
			if (sem_wait(info->dead_sem) == -1)
				return (wrap(error_exit(ERR_SEM_WAIT)));
			exit(EXIT_FAILURE);
		}
		if (must_eat != -1 && philosopher->eat_count >= must_eat)
			return (NULL);
	}
	return (NULL);
}

static void	philosopher_act_prepare(t_philosopher **philo,
				t_philo_three **info, pthread_t *death, void *philo_info)
{
	*philo = (t_philosopher *)philo_info;
	*info = (*philo)->info;
	(*philo)->last_eat_time = get_cur_time();
	if ((*philo)->last_eat_time == -1)
		exit(error_exit(ERR_GETTIMEOFDAY));
	if (pthread_create(death, NULL, death_monitor, philo_info) != 0)
		exit(error_exit(ERR_PTHREAD_CREATE));
	if (((*philo)->number % 2) == 1)
	{
		if (deep_thought((*philo)) == NULL)
			exit(EXIT_FAILURE);
		if (usleep((*philo)->info->time_to_eat) == -1)
			exit(error_exit(ERR_USLEEP));
	}
}

void	*philosopher_act(void *philo_info)
{
	t_philosopher	*philosopher;
	t_philo_three	*info;
	pthread_t		death;

	philosopher_act_prepare(&philosopher, &info, &death, philo_info);
	while (info->status == ALIVE)
	{
		if (info->all_eat == true || eat_spaghetti(philosopher) == NULL)
			break ;
		if (info->all_eat == true || sleep_after_eating(philosopher) == NULL)
			break ;
		if (info->all_eat == true || deep_thought(philosopher) == NULL)
			break ;
	}
	if (pthread_join(death, NULL) != 0)
		exit(error_exit(ERR_PTHREAD_JOIN));
	if (info->status == DEATH)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

bool	create_thread(t_philo_three *info)
{
	int64_t			i;
	t_philosopher	*philosophers;

	info->begin_time = get_cur_time();
	if (info->begin_time == -1)
		return (error_exit(ERR_GETTIMEOFDAY));
	philosophers = info->philosophers;
	i = -1;
	while (++i < info->number_of_philosophers)
	{
		philosophers[i].pid = fork();
		if (philosophers[i].pid == -1)
			exit_kill_process(philosophers, i, ERR_FORK);
		if (philosophers[i].pid == 0)
			philosopher_act(philosophers + i);
	}
	wait_process(info, philosophers);
	return (true);
}
