/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 20:07:10 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/25 02:07:22 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

bool	clean_up(t_philo_one *info)
{
	int64_t	i;

	i = -1;
	int ret = 0;
	while (++i < info->number_of_philosophers)
		// pthread_mutex_destroy(&(info->forks[i]));
		if (pthread_mutex_destroy(&(info->forks[i])) != 0)
		{
			errno = ret;
			printf("i = %lld\n", i);
			perror(RED"perror"RESET);
			return (error_exit(ERR_MUTEX_DESTORY"1"));
			// perror("error");
			// exit(1);
		}
	free(info->forks);
	free(info->philosophers);
	pthread_mutex_destroy(&(info->artist));
	// if (pthread_mutex_destroy(&(info->artist)) != 0)
	// 	return (error_exit(ERR_MUTEX_DESTORY"2"));
	return (true);

	// int	i;

	// i = 0;
	// while (i < state->amount)
	// 	if (pthread_mutex_destroy(&state->forks[i++]) != 0)
	// free(state->forks);
	// free(state->philos);
	// pthread_mutex_destroy(&state->life);
	// pthread_mutex_destroy(&state->status);

}

int	main(int argc, char **argv)
{
	t_philo_one	info;

	if (argc < 5 || argc > 6)
		return (error_exit(ERR_ARG));
	if (get_arg(&info, argc, argv) == false)
		return (EXIT_FAILURE);
	if (initialize_philosophers(&info) == false)
		return (EXIT_FAILURE);
	if (initialize_mutex_fork(&info) == false)
		return (EXIT_FAILURE);
	// int i = -1;
	// int ret = 0;
	// while (++i < info.number_of_philosophers)
	// 	if ((ret = pthread_mutex_destroy(&(info.forks[i]))) != 0)
	// 	{
	// 		errno = ret;
	// 		printf("i = %d\n", i);
	// 		perror(RED"perror"RESET);
	// 		return (error_exit(ERR_MUTEX_DESTORY"1"));
	// 	}
	// exit(1);
	if (create_thread(&info) == false)
		return (EXIT_FAILURE);
	puts(RED"in1"RESET);
	if (pthread_mutex_lock(&(info.artist)) != 0)
		return (error_exit(ERR_MUTEX_LOCK));
	puts(RED"in2"RESET);
	if (pthread_mutex_unlock(&(info.artist)) != 0)
		return (error_exit(ERR_MUTEX_UNLOCK));
	puts(RED"in3"RESET);
	if (clean_up(&info) == false)
		return (EXIT_FAILURE);
	// while (1) ;
	return (EXIT_SUCCESS);
}
