/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:34:10 by bfichot           #+#    #+#             */
/*   Updated: 2022/01/17 16:18:29 by bfichot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	eat(t_philo *philo)
{
	if (philo->death == 1)
		return (1);
	if (philo->id == 0)
		pthread_mutex_lock(&philo->d->mutex[philo->nbr_philo - 1]);
	else
		pthread_mutex_lock(&philo->d->mutex[philo->id - 1]);
	pthread_mutex_lock(&philo->d->mutex[philo->id]);
	print_philo(philo);
	philo->eat++;
	philo->last_eat = ft_time() - philo->time;
	ft_usleep(philo->time_to_eat);
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
		printf("temps:[%ld], philo: [%d], is sleeping |----| \n",
			print_time(philo), philo->id);
		pthread_mutex_unlock(&philo->d->talk);
		ft_usleep(philo->time_to_sleep);
	}
}

void	think(t_philo *philo)
{
	if (philo->death == 1)
		return ;
	else
	{
		pthread_mutex_lock(&philo->d->talk);
		printf("temps:[%ld], philo: [%d], is thinking ??? \n",
			print_time(philo), philo->id);
		pthread_mutex_unlock(&philo->d->talk);
	}
}

int	is_death(t_philo *philo, int i)
{
	int	j;

	j = -1;
	if (print_time(&philo[i]) - philo[i].last_eat > philo[i].time_to_die / 1000)
	{
		while (++j < philo->nbr_philo)
			philo[j].death = 1;
		printf("temps:[%ld], philo: [%d] is dead\n",
			print_time(&philo[i]), philo[i].id);
		pthread_mutex_destroy(philo->d->mutex);
		pthread_mutex_destroy(&philo->d->talk);
		return (1);
	}
	return (0);
}

void	*check_death(void *param)
{
	t_philo	*philo;
	int		i;

	philo = param;
	if (philo->nbr_philo == 1)
		return (NULL);
	while (1)
	{
		i = 0;
		while (i < philo->nbr_philo)
		{
			if (is_death(philo, i))
				return (NULL);
			if (philo[i].eat == philo[i].nbr_must_eat)
				i++;
			else
				continue ;
		}
		if (philo->eat == philo->nbr_must_eat || philo->nbr_philo == 1)
			return (NULL);
	}
}
