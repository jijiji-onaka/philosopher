/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 20:42:59 by tjinichi          #+#    #+#             */
/*   Updated: 2021/06/06 22:44:02 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

void	*wrap(int exit_status)
{
	if (exit_status == EXIT_FAILURE)
		return (NULL);
	else
		return ("OK");
}

int	error_exit(char *message)
{
	write(STDERR_FILENO, BOLD""RED"Error: "RESET, 20);
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
	return (EXIT_FAILURE);
}
