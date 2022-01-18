/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:49:42 by bfichot           #+#    #+#             */
/*   Updated: 2022/01/17 14:22:40 by bfichot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/types.h>

typedef struct s_data	t_data;
typedef struct s_philo
{
	int				id;
	int				res;
	int				pid;
	int				nbr_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nbr_must_eat;
	long			last_eat;
	int				eat;
	long			time;
	int				death;
	struct timeval	start;
	t_data			*d;
}	t_philo;

struct s_data
{
	pthread_t		*thread;
	t_philo			*p;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	talk;
	sem_t			*dead;
	sem_t			*sem;
};

void	*ft_routine(void *arg);
void	*check_death(void *param);
void	ft_usleep(int ms);
void	init_thread(t_data *data, char **av, int ac);
void	init_sema(t_data *data, char **av, int i);
void	init_mutex(t_data *data, char **av);
void	print_philo(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	think(t_philo *philo);
long	print_time(t_philo *philo);
long	ft_time(void);
int		ft_atoi(const char *str);
int		eat(t_philo *philo);
int		is_death2(t_philo *philo);
int		is_death(t_philo *philo, int i);
int		check_eat(t_philo *philo);
int		one_philo(t_philo *philo);
int		check_error(int ac, char **av);
int		is_digit(char c);

#endif
