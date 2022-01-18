/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:50:25 by bfichot           #+#    #+#             */
/*   Updated: 2022/01/17 14:22:46 by bfichot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	ft_usleep(int ms)
{
	long int	time;

	time = ft_time();
	while ((ft_time() - time) * 1000 < ms)
		usleep(200);
}

void	print_philo(t_philo *philo)
{
	if (philo->death == 1)
		return ;
	else
	{
		pthread_mutex_lock(&philo->d->talk);
		printf("temps:[%ld], philo: [%d],has taken a fork ==>|||\n",
			print_time(philo), philo->id);
		printf("temps:[%ld], philo: [%d],has taken a fork ==>|||\n",
			print_time(philo), philo->id);
		printf("temps:[%ld], philo: [%d],is eating ( )\n",
			print_time(philo), philo->id);
		pthread_mutex_unlock(&philo->d->talk);
	}
}

long	print_time(t_philo *philo)
{
	return (ft_time() - philo->time);
}

long	ft_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}
