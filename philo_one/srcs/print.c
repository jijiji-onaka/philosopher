/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:01:46 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/24 16:07:04 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void	print_action(int number, int act)
{
	char	*act_message;

	if (act == TAKE_FORK)
		act_message = "has taken a fork";
	else if (act == EAT)
		act_message = "is eating";
	else if (act == SLEEP)
		act_message = "is sleeping";
	else if (act == THINK)
		act_message = "is thinking";
	else if (act == DIED)
		act_message = "died";
	printf("%ld %d %s\n", get_cur_time(), number, act_message);
}
