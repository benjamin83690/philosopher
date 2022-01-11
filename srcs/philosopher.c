/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:51:44 by bfichot           #+#    #+#             */
/*   Updated: 2022/01/11 21:05:48 by bfichot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

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
		if (!philo->death)
			ft_sleep(philo);
		else
			break;
		if (!philo->death)
			think(philo);
		else
			break;
	}
	return (0);
}

int	is_death(t_philo *philo, int i)
{
	int j = -1;
	if (print_time(&philo[i]) - philo[i].last_eat > philo[i].time_to_die / 1000)
	{
		while (++j < philo->nbr_philo)
			philo[j].death = 1;
		printf("temps:[%ld], philo: [%d] is dead\n", print_time(&philo[i]), philo[i].id);
		return (1);
	}
	return (0);
}

void	*check_death(void *param)
{
	t_philo *philo;
	philo = param;
	int i;
	
	i = -1;
	while (1)
	{
		if (philo->eat == philo->nbr_must_eat)
			return (NULL);
		while (++i < philo->nbr_philo)
			if (is_death(philo, i))
				return (NULL);
		i = 0;
		ft_usleep(philo, 2000);
	}
}

int	eat(t_philo *philo)
{
	if (philo->death == 1)
		return (1);
	if (philo->eat == philo->nbr_must_eat)
		return (-1);
	if (philo->id == 0)
		pthread_mutex_lock(&philo->d->mutex[philo->nbr_philo - 1]);
	else
		pthread_mutex_lock(&philo->d->mutex[philo->id - 1]);
	pthread_mutex_lock(&philo->d->mutex[philo->id]);
	print_philo(philo);
	philo->eat++;
	philo->last_eat = ft_time(philo) - philo->time;
	ft_usleep(philo, philo->time_to_eat);
	if (philo->id == 0)
		pthread_mutex_unlock(&philo->d->mutex[philo->nbr_philo - 1]);
	else
		pthread_mutex_unlock(&philo->d->mutex[philo->id - 1]);
	pthread_mutex_unlock(&philo->d->mutex[philo->id]);
	return (0);
}

void	ft_sleep(t_philo *philo)
{
	if (philo->death == 1)
		return ;
	else
	{
		pthread_mutex_lock(&philo->d->talk);
		printf("temps:[%ld], philo: [%d], is sleeping |----| \n",print_time(philo), philo->id);
		pthread_mutex_unlock(&philo->d->talk);
		ft_usleep(philo, philo->time_to_sleep);
	}
}

void	think(t_philo *philo)
{
	if (philo->death == 1)
		return ;
	else
	{
		pthread_mutex_lock(&philo->d->talk);
		printf("temps:[%ld], philo: [%d], is thinking ??? \n",print_time(philo), philo->id);
		pthread_mutex_unlock(&philo->d->talk);
	}
}

long	ft_time(t_philo *philo)
{
	struct timeval now;
	(void)philo;
	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

long	print_time(t_philo *philo)
{
	return (ft_time(philo) - philo->time);
}

void	print_philo(t_philo *philo)
{
	if (philo->death == 1)
		return ;
	else
	{
		pthread_mutex_lock(&philo->d->talk);
		printf("temps:[%ld], philo: [%d],has taken a fork |||\n",print_time(philo), philo->id);
		printf("temps:[%ld], philo: [%d],has taken a fork |||\n",print_time(philo), philo->id);
		printf("temps:[%ld], philo: [%d],is eating ( )\n", print_time(philo), philo->id);
		pthread_mutex_unlock(&philo->d->talk);
	}
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
		else
			data->p[i].nbr_must_eat = -1;
		data->p[i].id = i;
		data->p[i].d = data;
		data->p[i].death = 0;
		data->p[i].last_eat = 0;
		data->p[i].eat = 0;
		pthread_create(&data->thread[i], NULL, ft_routine, &data->p[i]);
		pthread_detach(data->thread[i]);
	}
}

void	ft_usleep(t_philo *philo, int ms)
{
	long int	time;
	
	time = ft_time(philo);
	while ((ft_time(philo) - time) * 1000 < ms)
		usleep(100);
}

void	init_mutex(t_data *data, char **av)
{
	int	i;
	
	i = -1;
	data->p = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	pthread_mutex_init(&data->talk, NULL);
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
	check_death(data.p);
}
