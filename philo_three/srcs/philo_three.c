/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 22:05:44 by tjinichi          #+#    #+#             */
/*   Updated: 2021/06/07 22:05:46 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

bool	clean_up(t_philo_three *info)
{
	if (sem_close(info->forks) == -1)
		return (error_exit(ERR_SEM_CLOSE));
	if (sem_unlink(MY_FORK_NAME) == -1)
		return (error_exit(ERR_SEM_UNLINK));
	free(info->philosophers);
	if (sem_close(info->semaphore) == -1)
		return (error_exit(ERR_SEM_CLOSE));
	if (sem_unlink(MY_SEMA_NAME) == -1)
		return (error_exit(ERR_SEM_UNLINK));
	if (sem_close(info->dead_sem) == -1)
		return (error_exit(ERR_SEM_CLOSE));
	if (sem_unlink(MY_DEAD_NAME) == -1)
		return (error_exit(ERR_SEM_UNLINK));
	return (true);
}

int	main(int argc, char **argv)
{
	t_philo_three	info;

	setbuf(stdout, NULL);
	if (argc < 5 || argc > 6)
		return (error_exit(ERR_ARG));
	if (get_arg(&info, argc, argv) == false)
		return (EXIT_FAILURE);
	if (initialize_semaphore(&info) == false)
		return (EXIT_FAILURE);
	if (initialize_philosophers(&info) == false)
		return (EXIT_FAILURE);
	if (create_thread(&info) == false)
		return (EXIT_FAILURE);
	if (clean_up(&info) == false)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
