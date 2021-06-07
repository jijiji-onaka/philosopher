/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 20:06:10 by tjinichi          #+#    #+#             */
/*   Updated: 2021/06/06 23:26:59 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

# define RESET "\033[0m"
# define BOLD "\033[1m"
# define RED "\033[31m"
# define MY_FORK_NAME "/tjinichi_forks"
# define MY_SEMA_NAME "/tjinichi_semaphore"
# define ALIVE 0
# define DEATH 1
# define LEFT 0
# define RIGHT 1
# define ERR_MALLOC "malloc error"
# define ERR_PRINTF "printf error"
# define ERR_USLEEP "usleep error"
# define ERR_GETTIMEOFDAY "gettimeofday error"
# define ERR_PTHREAD_CREATE "pthread_create error"
# define ERR_PTHREAD_JOIN "pthread_join error"
# define ERR_SEM_OPEN "sem_open error"
# define ERR_SEM_WAIT "sem_wait error"
# define ERR_SEM_POST "sem_post error"
# define ERR_SEM_CLOSE "sem_close error"
# define ERR_SEM_UNLINK "sem_unlink error"
// # define ERR_MUTEX_INIT "pthread_mutex_init error"
// # define ERR_MUTEX_LOCK "pthread_mutex_lock error"
// # define ERR_MUTEX_UNLOCK "pthread_mutex_unlock error"
// # define ERR_MUTEX_DESTORY "pthread_mutex_destory error"
# define ERR_ARG "usage: ./philo_two number_of_philosophers \
time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]"
# define OOR_NUM_PHI "number of philosophers is out of range"
# define OOR_TIME_DIE "time to die is out of range"
# define OOR_TIME_EAT "time to eat is out of range"
# define OOR_TIME_SLEEP "time to sleep is out of range"
# define OOR_NUM_MUST_EAT "number of times each philosopher must eat \
is out of range"

struct	s_philo_two;

typedef struct s_philosopher
{
	int64_t				number;
	time_t				last_eat_time;
	int64_t				eat_count;
	struct s_philo_two	*info;
}	t_philosopher;

typedef struct s_philo_two
{
	int64_t				number_of_philosophers;
	int64_t				time_to_die;
	int64_t				time_to_eat;
	int64_t				time_to_sleep;
	int64_t				number_of_times_each_philosopher_must_eat;
	t_philosopher		*philosophers;
	sem_t				*forks;
	sem_t				*semaphore;
	bool				all_eat;
	bool				status;
	int64_t				begin_time;
}	t_philo_two;

enum	e_action
{
	TAKE_FORK,
	EAT,
	SLEEP,
	THINK,
	DIED,
};

/*
** EXIT_C
*/
int		error_exit(char *message);
void	*wrap(int exit_status);
/*
** UTILS_C
*/
size_t	ft_strlen(char *str);
bool	get_arg(t_philo_two *info, int argc, char **argv);
time_t	get_cur_time(void);
/*
** INITIALIZE_C
*/
bool	initialize_philosophers(t_philo_two *info);
bool	initialize_semaphore(t_philo_two *info);
/*
** THREAD_C
*/
bool	create_thread(t_philo_two *info);
/*
** PRINT_C
*/
int		print_action(int number, int act, bool status, time_t begin_time);
/*
** ACTION_C
*/
void	*sleep_after_eating(t_philosopher *philosopher);
void	*eat_spaghetti(t_philosopher *philosopher);
void	*take_fork(t_philosopher *philosopher, int l_or_r);
void	*deep_thought(t_philosopher *philosopher);
void	*die_check(t_philosopher *philo, time_t cur_time);
/*
** EAT_HELP
*/
void	*eat_spaghetti_2(t_philosopher *philosopher);
/*
** MY_USLEEP
*/
void	*my_usleep(int64_t sleep_time, t_philo_two *info);

#endif
