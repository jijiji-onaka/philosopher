/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_sem_open.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 21:55:02 by tjinichi          #+#    #+#             */
/*   Updated: 2021/06/07 21:58:40 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

sem_t	*my_sem_open(const char *name, int oflag,
			mode_t mode, unsigned int value)
{
	sem_t	*res;

	res = sem_open(name, oflag, mode, value);
	if (res == SEM_FAILED)
	{
		if (sem_unlink(name) == -1)
			exit(error_exit(ERR_SEM_UNLINK));
		res = sem_open(name, oflag, mode, value);
		if (res == SEM_FAILED)
			exit(error_exit(ERR_SEM_OPEN));
	}
	return (res);
}
