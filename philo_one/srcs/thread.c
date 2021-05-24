/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 02:11:09 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/24 19:45:03 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void	*philosopher_act(void *philo_info)
{
	t_philosopher	*philosopher;
	char			*error_message;

	philosopher = (t_philosopher *)philo_info;
	philosopher->last_eat_time = get_cur_time();
	if ((philosopher->number % 2) == 1)
	{
		deep_thought(philosopher);
		usleep(200);
	}
	while (1)
	{
		error_message = eat_spaghetti(philosopher);
		if (error_message == NULL)
			return (NULL);
		error_message = sleep_after_eating(philosopher);
		if (error_message == NULL)
			return (NULL);
		deep_thought(philosopher);
	}
	return ("OK");
}

void	*death_monitor(void *philo_info)
{
	t_philosopher	*philosopher;
	// char			*error_message;
	// bool			is_must_eat;
	// int64_t			must_eat_cnt;

	philosopher = (t_philosopher *)philo_info;
	// if (philosopher->info->number_of_times_each_philosopher_must_eat > 0)
	// 	is_must_eat = true;
	// else
	// 	is_must_eat = false;
	// must_eat_cnt = philosopher->info->number_of_times_each_philosopher_must_eat;
	int i = 0;
	while (1)
	{
		i++;
		pthread_mutex_lock(&philosopher->info->status_mutex);
		if (philosopher->info->time_to_die
			+ philosopher->last_eat_time < get_cur_time())
		{
			philosopher->info->status = DEATH;

			print_action(philosopher->number + 1, DIED);
			// printf("%d\n", philosopher->info->time_to_die
			// + philosopher->last_eat_time < get_cur_time());
			// printf("%d\n", (is_must_eat && philosopher->eat_count == must_eat_cnt));
			if (pthread_mutex_unlock(&philosopher->info->artist) != 0)
				return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
			// exit(puts("\n\n\nfinish"));
			return (NULL);
		}
		pthread_mutex_unlock(&philosopher->info->status_mutex);
		// if (is_must_eat && philosopher->eat_count == must_eat_cnt)
		// {
		// 	print_action(philosopher->number + 1, DIED);
		// 	if (pthread_mutex_unlock(&philosopher->info->artist) != 0)
		// 		return (wrap(error_exit(ERR_MUTEX_UNLOCK)));
		// 	return (NULL);
		// }


		// printf("1 : %lld\n", philosopher->info->time_to_die);
		// printf("2 : %ld\n", philosopher->last_eat_time);
		// printf("3 : %ld\n", get_cur_time());
		// printf("4 : %d\n", philosopher->info->time_to_die
		// 	+ philosopher->last_eat_time < get_cur_time());
		// if (i == 3) exit(1);
		usleep(10000);
	}
}

bool	create_thread(t_philo_one *info)
{
	int64_t		i;
	pthread_t	*tid;

	tid = malloc(sizeof(pthread_t) * info->number_of_philosophers);
	if (tid == NULL)
		return (error_exit(ERR_MALLOC));
	// i = -1;
	// while (++i < info->number_of_times_each_philosopher_must_eat)
	i = -1;
	while (++i < info->number_of_philosophers)
	{
		if (pthread_create(&(tid[i]), NULL, philosopher_act,
				 info->philosophers + i) != 0)
			return (error_exit(ERR_PTHREAD_CREATE));
		pthread_detach(tid[i]);
		if (pthread_create(&(tid[i]), NULL, death_monitor,
				 info->philosophers + i) != 0)
			return (error_exit(ERR_PTHREAD_CREATE));
		pthread_detach(tid[i]);
		// pthread_create(&tid, NULL, life_monitor, info->philosophers + i);
	}

	//  == pthread_join ==

	i = -1;
	while (++i < info->number_of_philosophers)
	{
		pthread_join(tid[i], NULL);
		// pthread_create(&tid, NULL, life_monitor, info->philosophers + i);
	}
	return (true);
}
