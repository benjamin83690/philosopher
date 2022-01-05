/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:49:42 by bfichot           #+#    #+#             */
/*   Updated: 2022/01/05 17:59:56 by bfichot          ###   ########.fr       */
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
	long	nbr_must_eat;
	long	last_eat;
	long	time;
	struct	timeval start, end;
	t_data	*d;
}	t_philo;

struct s_data
{
	pthread_t *thread;
	t_philo *p;
	pthread_mutex_t *mutex;
};

void	*ft_routine(void *arg);
void	init_thread(t_data *data, char **av);
void	init_mutex(t_data *data, char **av);
void	eat(t_philo *philo);
long	ft_time(t_philo *philo);
int		ft_atoi(const char *str);

#endif
