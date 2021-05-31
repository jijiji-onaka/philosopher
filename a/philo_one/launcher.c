/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:19:34 by gsmets            #+#    #+#             */
/*   Updated: 2021/05/31 20:19:55 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eats(t_philosopher *philo)
{
	t_rules *rules;

	rules = philo->rules;
	if (pthread_mutex_lock(&(rules->forks[philo->left_fork_id])) != 0)
		exit(1);
	action_print(rules, philo->id, "has taken a fork");
	if (pthread_mutex_lock(&(rules->forks[philo->right_fork_id])) != 0)
		exit(1);
	action_print(rules, philo->id, "has taken a fork");
	if (pthread_mutex_lock(&(rules->meal_check)) != 0)
		exit(1);
	action_print(rules, philo->id, "is eating");
	philo->t_last_meal = timestamp();
	if (philo->t_last_meal == -1)
		exit(1);
	if (pthread_mutex_unlock(&(rules->meal_check)) != 0)
		exit(1);
	smart_sleep(rules->time_eat, rules);
	(philo->x_ate)++;
	if (pthread_mutex_unlock(&(rules->forks[philo->left_fork_id])) != 0)
		exit(1);
	if (pthread_mutex_unlock(&(rules->forks[philo->right_fork_id])) != 0)
		exit(1);
}

void	*p_thread(void *void_philosopher)
{
	int				i;
	t_philosopher	*philo;
	t_rules			*rules;

	i = 0;
	philo = (t_philosopher *)void_philosopher;
	rules = philo->rules;
	if (philo->id % 2)
		if (usleep(15000) == -1)
			exit(1);
	while (!(rules->dieded))
	{
		philo_eats(philo);
		if (rules->all_ate)
			break ;
		action_print(rules, philo->id, "is sleeping");
		smart_sleep(rules->time_sleep, rules);
		action_print(rules, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}

void	exit_launcher(t_rules *rules, t_philosopher *philos)
{
	int i;

	i = -1;
	while (++i < rules->nb_philo)
		if (pthread_join(philos[i].thread_id, NULL) != 0)
			exit(1);
	i = -1;
	while (++i < rules->nb_philo)
		if (pthread_mutex_destroy(&(rules->forks[i])) != 0)
			exit(1);
	if (pthread_mutex_destroy(&(rules->writing)) != 0)
		exit(1);
}

void	death_checker(t_rules *r, t_philosopher *p)
{
	int i;

	while (!(r->all_ate))
	{
		i = -1;
		while (++i < r->nb_philo && !(r->dieded))
		{
			pthread_mutex_lock(&(r->meal_check));
			if (time_diff(p[i].t_last_meal, timestamp()) > r->time_death)
			{
				action_print(r, i, "died");
				r->dieded = 1;
			}
			pthread_mutex_unlock(&(r->meal_check));
			usleep(100);
		}
		if (r->dieded)
			break ;
		i = 0;
		while (r->nb_eat != -1 && i < r->nb_philo && p[i].x_ate >= r->nb_eat)
			i++;
		if (i == r->nb_philo)
			r->all_ate = 1;
	}
}

int		launcher(t_rules *rules)
{
	int				i;
	t_philosopher	*phi;

	i = 0;
	phi = rules->philosophers;
	rules->first_timestamp = timestamp();
	if (rules->first_timestamp == -1)
		exit(1);
	while (i < rules->nb_philo)
	{
		if (pthread_create(&(phi[i].thread_id), NULL, p_thread, &(phi[i])))
			return (1);
		phi[i].t_last_meal = timestamp();
		if (phi[i].t_last_meal == -1)
			exit(1);
		i++;
	}
	death_checker(rules, rules->philosophers);
	exit_launcher(rules, phi);
	return (0);
}
