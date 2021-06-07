/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 16:55:55 by tjinichi          #+#    #+#             */
/*   Updated: 2021/06/06 22:44:31 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

void	*my_usleep(int64_t sleep_time, t_philo_two *info)
{
	int64_t	begin_time;
	int64_t	cur_time;

	begin_time = get_cur_time();
	if (begin_time == -1)
		return (NULL);
	while (info->status == ALIVE)
	{
		cur_time = get_cur_time();
		if (cur_time == -1)
			return (NULL);
		if (cur_time - begin_time >= sleep_time)
			return ("OK");
	}
	return ("OK");
}
