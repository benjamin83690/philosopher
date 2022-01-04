/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:49:42 by bfichot           #+#    #+#             */
/*   Updated: 2022/01/04 18:50:10 by bfichot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_thread t_thread;

typedef struct s_data
{
	int		nbr_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_must_eat;
	long	last_eat;
	long	time;
	struct timeval start, end;
}	t_data;

struct s_thread
{
	int id;
	pthread_t *thread;
	pthread_mutex_t *mutex;
	t_data *d;
};

void	*ft_routine(void *arg);
void	init_thread(t_thread *tab, char **av);
void	init_data(t_data *data);
int		ft_atoi(const char *str);

#endif
