/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:51:16 by bfichot           #+#    #+#             */
/*   Updated: 2022/01/17 15:13:16 by bfichot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	check_error(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (ac < 5 || ac > 6)
		return (0);
	while (i < ac)
	{
		while (av[i][j])
		{
			if (!is_digit(av[i][j]))
				return (0);
			else
				j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	one_philo(t_philo *philo)
{
	if (philo->nbr_philo == 1)
	{
		sem_wait(philo->d->dead);
		printf("temps:[%ld], philo: [%d],has taken a fork ==>|||\n",
			print_time(philo), philo->id);
		ft_usleep(philo->time_to_eat);
		printf("temps:[%ld], philo: [%d] is dead\n", print_time(&philo[0]),
			philo[0].id);
		sem_post(philo->d->dead);
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	isneg;
	int	numb;

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
