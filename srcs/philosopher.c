/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:51:44 by bfichot           #+#    #+#             */
/*   Updated: 2022/01/08 18:05:55 by bfichot          ###   ########.fr       */
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
   
   	while (1)
	{
		if (eat(philo))
			break;
		ft_sleep(philo);
		think(philo);
	}
	return (0);
}

int	eat(t_philo *philo)
{
	if (philo->eat == philo->nbr_must_eat)
		return (1);
	if (philo->id % 2 == 0)
		usleep(philo->time_to_eat);
	if (philo->id == 0)
    	pthread_mutex_lock(&philo->d->mutex[philo->nbr_philo - 1]);
	else
    	pthread_mutex_lock(&philo->d->mutex[philo->id - 1]);
    pthread_mutex_lock(&philo->d->mutex[philo->id]);
	print_philo(philo);
	philo->eat++;
	usleep(philo->time_to_eat);
	if (philo->id == 0)
    	pthread_mutex_unlock(&philo->d->mutex[philo->nbr_philo - 1]);
	else
		pthread_mutex_unlock(&philo->d->mutex[philo->id - 1]);
	pthread_mutex_unlock(&philo->d->mutex[philo->id]);
	print_drop(philo);
	return (0);
}

void	ft_sleep(t_philo *philo)
{
    pthread_mutex_lock(&philo->d->talk[philo->id]);
	printf("temps:[%ld], philo: [%d], is sleeping |----| \n",print_time(philo), philo->id);
	usleep(philo->time_to_sleep);
    pthread_mutex_unlock(&philo->d->talk[philo->id]);
}

void	think(t_philo *philo)
{
    pthread_mutex_lock(&philo->d->talk[philo->id]);
	printf("temps:[%ld], philo: [%d], is thinking ??? \n",print_time(philo), philo->id);
    pthread_mutex_unlock(&philo->d->talk[philo->id]);
}

long	ft_time(t_philo *philo)
{
	gettimeofday(&philo->start, NULL);
	return (philo->start.tv_sec * 1000 + philo->start.tv_usec / 1000);
}

long	print_time(t_philo *philo)
{
	return (ft_time(philo) - philo->time);
}

void	print_philo(t_philo *philo)
{
	philo->d->talk = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->d->talk, NULL);
    pthread_mutex_lock(&philo->d->talk[philo->id]);
	printf("temps:[%ld], philo: [%d],has taken a fork |||\n",print_time(philo), philo->id);
	printf("temps:[%ld], philo: [%d],has taken a fork |||\n",print_time(philo), philo->id);
	printf("philo: [%d],is eating ( )\n",philo->id);
    pthread_mutex_unlock(&philo->d->talk[philo->id]);
}

void	print_drop(t_philo *philo)
{
	printf("temps:[%ld], philo: [%d],has drop a fork |||\n",print_time(philo), philo->id);
	printf("temps:[%ld], philo: [%d],has drop a fork |||\n",print_time(philo), philo->id);
}

void	init_thread(t_data *data, char **av, int ac)
{
	int	i;
	
	i = -1;
	data->thread = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	while (++i < ft_atoi(av[1]))
	{
		data->p[i].time = ft_time(data->p);
		data->p[i].nbr_philo = ft_atoi(av[1]);
		data->p[i].time_to_die = ft_atoi(av[2]) * 1000;
		data->p[i].time_to_eat = ft_atoi(av[3]) * 1000;
		data->p[i].time_to_sleep = ft_atoi(av[4]) * 1000;
		if (ac > 5)
			data->p[i].nbr_must_eat = ft_atoi(av[5]);
		data->p[i].id = i;
		data->p[i].d = data;
		data->p[i].death = 0;
		data->p[i].eat = 0;
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
	init_thread(&data, av, ac);	
    exit(EXIT_SUCCESS);
}
