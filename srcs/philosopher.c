/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:51:44 by bfichot           #+#    #+#             */
/*   Updated: 2022/01/05 17:59:58 by bfichot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int shared = 0;
int		ft_atoi(const char *str)
{
	int i;
	int isneg;
	int numb;

	i = 0;
	isneg = 1;
	numb = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			isneg = isneg * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		numb = numb * 10 + (str[i] - '0');
		i++;
	}
	return (isneg * numb);
}

void	*ft_routine(void* param)
{
	t_philo *philo;
	philo = param;
    
	eat(philo);
	return (0);
}

void	eat(t_philo *philo)
{
	if (philo->id == 1)
    	pthread_mutex_lock(&philo->d->mutex[philo->nbr_philo - 1]);
	else
    	pthread_mutex_lock(&philo->d->mutex[philo->id - 1]);
    pthread_mutex_lock(&philo->d->mutex[philo->id]);
    for (int i = 0; i < 10000; ++i)
        shared += 1;

	if (philo->id == 1)
    	pthread_mutex_unlock(&philo->d->mutex[philo->nbr_philo - 1]);
	else
		pthread_mutex_unlock(&philo->d->mutex[philo->id - 1]);
	pthread_mutex_unlock(&philo->d->mutex[philo->id]);
}

long	ft_time(t_philo *philo)
{
	gettimeofday(&philo->start, NULL);
	return (philo->start.tv_sec * 1000 + philo->start.tv_usec / 1000);
}

void	init_thread(t_data *data, char **av)
{
	int	i;
	
	i = -1;
	data->thread = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	while (++i < ft_atoi(av[1]))
	{
		data->p[i].time = ft_time(data->p);
		data->p[i].nbr_philo = ft_atoi(av[1]);
		data->p[i].time_to_die = ft_atoi(av[2]);
		data->p[i].time_to_eat = ft_atoi(av[3]);
		data->p[i].time_to_sleep = ft_atoi(av[4]);
		data->p[i].nbr_must_eat = ft_atoi(av[5]);
		data->p[i].id = i;
		data->p[i].d = data;
		pthread_create(&data->thread[i], NULL, ft_routine, &data->p[i]);
	}
	i = 0;
	while (++i < ft_atoi(av[1]))
       pthread_join(data->thread[i], NULL);
}

void	init_mutex(t_data *data, char **av)
{
	int	i;
	
	i = -1;
	data->p = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	data->mutex = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	while (++i < ft_atoi(av[1]))
		pthread_mutex_init(&data->mutex[i], NULL);
}

int main(int ac, char **av)
{
    t_data data;
	if (ac < 5 || ac > 6)
		return (0);
	init_mutex(&data, av);
	init_thread(&data, av);	
    printf("%d\n", shared);
    exit(EXIT_SUCCESS);
}
