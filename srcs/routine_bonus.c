/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:49:36 by bfichot           #+#    #+#             */
/*   Updated: 2022/01/17 14:03:17 by bfichot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	eat(t_philo *philo)
{
	if (philo->death == 1)
		return (1);
	sem_wait(philo->d->sem);
	sem_wait(philo->d->sem);
	print_philo(philo);
	philo->eat++;
	philo->last_eat = ft_time() - philo->time;
	ft_usleep(philo->time_to_eat);
	sem_post(philo->d->sem);
	sem_post(philo->d->sem);
	return (0);
}

void	ft_sleep(t_philo *philo)
{
	if (philo->death == 1)
		return ;
	else
	{
		sem_wait(philo->d->dead);
		printf("temps:[%ld], philo: [%d], is sleeping |----| \n",
			print_time(philo), philo->id);
		sem_post(philo->d->dead);
		ft_usleep(philo->time_to_sleep);
	}
}

void	think(t_philo *philo)
{
	if (philo->death == 1)
		return ;
	else
	{
		sem_wait(philo->d->dead);
		printf("temps:[%ld], philo: [%d], is thinking ??? \n",
			print_time(philo), philo->id);
		sem_post(philo->d->dead);
	}
}

int	is_death(t_philo *philo, int i)
{
	int	j;

	(void)i;
	j = -1;
	if (print_time(philo) - philo->last_eat > philo->time_to_die / 1000)
	{
		while (++j < philo->nbr_philo)
			philo[j].death = 1;
		sem_wait(philo->d->dead);
		printf("temps:[%ld], philo: [%d] is dead\n",
			print_time(philo), philo->id);
		exit(EXIT_SUCCESS);
		return (1);
	}
	return (0);
}

void	*check_death(void *param)
{
	t_philo	*philo;
	int		i;

	philo = param;
	i = 0;
	while (1)
	{
		while (i < philo->nbr_philo)
		{
			if (philo[i].eat == philo[i].nbr_must_eat)
				i++;
			if (is_death(philo, i))
				return (NULL);
			else
				continue ;
		}
		if (philo->eat == philo->nbr_must_eat)
			exit(EXIT_SUCCESS);
	}
}
