/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 03:00:25 by tjinichi          #+#    #+#             */
/*   Updated: 2021/06/07 21:00:25 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

bool	exit_kill_process(t_philosopher *philosophers,
			int64_t fail_index, char *err_message)
{
	int64_t	i;

	i = 0;
	while (i < fail_index)
	{
		if (kill(philosophers[i].pid, SIGKILL) == -1)
			exit(error_exit(ERR_KILL));
		i++;
	}
	if (err_message == NULL)
		exit(EXIT_FAILURE);
	exit(error_exit(err_message));
}

bool	kill_process(t_philosopher *philosophers, int64_t fail_index)
{
	int64_t	i;
	int64_t	philo_num;

	i = 0;
	philo_num = philosophers->info->number_of_philosophers;
	while (i < philo_num)
	{
		if (philosophers[i].pid != fail_index)
		{
			if (kill(philosophers[i].pid, SIGKILL) == -1)
				return (error_exit(ERR_KILL));
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
