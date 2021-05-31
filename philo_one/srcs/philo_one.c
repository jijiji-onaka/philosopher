/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 20:07:10 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/31 18:33:51 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

bool	clean_up(t_philo_one *info)
{
	int64_t	i;

	i = -1;
	while (++i < info->number_of_philosophers)
		if (pthread_mutex_destroy(&info->forks[i]) != 0)
			return (error_exit(ERR_MUTEX_DESTORY"(forks)"));
	free(info->forks);
	free(info->philosophers);
	if (pthread_mutex_destroy(&(info->artist)) != 0)
		return (error_exit(ERR_MUTEX_DESTORY"(artist)"));
	if (pthread_mutex_destroy(&(info->eat_mutex)) != 0)
		return (error_exit(ERR_MUTEX_DESTORY"(eat_mutex)"));
	return (true);
}

int	main(int argc, char **argv)
{
	t_philo_one	info;

	if (argc < 5 || argc > 6)
		return (error_exit(ERR_ARG));
	if (get_arg(&info, argc, argv) == false)
		return (EXIT_FAILURE);
	if (initialize_mutex_fork(&info) == false)
		return (EXIT_FAILURE);
	if (initialize_philosophers(&info) == false)
		return (EXIT_FAILURE);
	if (create_thread(&info) == false)
		return (EXIT_FAILURE);
	if (clean_up(&info) == false)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
