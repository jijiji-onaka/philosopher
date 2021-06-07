/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 18:36:17 by tjinichi          #+#    #+#             */
/*   Updated: 2021/06/07 21:04:41 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	wait_process(t_philo_three *info, t_philosopher *philosophers)
{
	int64_t	i;
	int		status;
	pid_t	now_pid;

	i = 0;
	while (i < info->number_of_philosophers)
	{
		now_pid = waitpid(-1, &status, 0);
		if (now_pid == -1)
			exit(error_exit(ERR_WAITPID));
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			if (kill_process(philosophers, now_pid) == EXIT_FAILURE)
				exit(EXIT_FAILURE);
		}
		i++;
	}
}
