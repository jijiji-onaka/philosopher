/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:01:46 by tjinichi          #+#    #+#             */
/*   Updated: 2021/06/06 22:44:02 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

int	print_action(int number, int act, bool status, time_t begin_time)
{
	char	*act_message;
	time_t	cur_time;

	act_message = NULL;
	if (status == DEATH)
		return (-1);
	else if (act == TAKE_FORK)
		act_message = "has taken a fork";
	else if (act == EAT)
		act_message = "is eating";
	else if (act == SLEEP)
		act_message = "is sleeping";
	else if (act == THINK)
		act_message = "is thinking";
	else if (act == DIED)
		act_message = "died";
	cur_time = get_cur_time();
	if (cur_time == -1)
		return (error_exit(ERR_GETTIMEOFDAY));
	if (printf("%5li %d %s\n", cur_time
			- begin_time, number, act_message) < 0)
		return (error_exit(ERR_PRINTF));
	return (EXIT_SUCCESS);
}
