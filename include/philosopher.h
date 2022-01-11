/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:49:42 by bfichot           #+#    #+#             */
/*   Updated: 2022/01/11 21:07:33 by bfichot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data t_data;
typedef struct s_philo
{
	int		id;
	int		nbr_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		nbr_must_eat;
	long	last_eat;
	int		eat;
	long	time;
	int		death;
	struct	timeval start, end;
	t_data	*d;
}	t_philo;

struct s_data
{
	pthread_t		*thread;
	t_philo			*p;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	talk;
};

void	*ft_routine(void *arg);
void	*check_death(void *param);
void	ft_usleep(int ms);
void	init_thread(t_data *data, char **av, int ac);
void	init_mutex(t_data *data, char **av);
void	print_philo(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	think(t_philo *philo);
void	print_drop(t_philo *philo);
long	print_time(t_philo *philo);
long	ft_time(void);
int		ft_atoi(const char *str);
int		eat(t_philo *philo);
int		is_death(t_philo *philo, int i);
int		check_eat(t_philo *philo);

#endif
