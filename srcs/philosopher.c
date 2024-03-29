/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:51:44 by bfichot           #+#    #+#             */
/*   Updated: 2022/01/17 16:11:53 by bfichot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	*ft_routine(void *param)
{
	t_philo	*philo;

	philo = param;
	while (1)
	{
		if (eat(philo))
			break ;
		if (!philo->death)
			ft_sleep(philo);
		else
			break ;
		if (!philo->death)
			think(philo);
		else
			break ;
	}
	free(philo->d->mutex);
	free(philo->d->thread);
	return (0);
}

void	init_thread(t_data *data, char **av, int ac)
{
	int	i;

	i = -1;
	while (++i < ft_atoi(av[1]))
	{
		data->p[i].time = ft_time();
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
		if (one_philo(&data->p[i]))
			return ;
		pthread_create(&data->thread[i], NULL, ft_routine, &data->p[i]);
		pthread_detach(data->thread[i]);
	}
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

int	main(int ac, char **av)
{
	t_data	data;

	if (!check_error(ac, av))
	{
		printf("Arguments invalide!\n");
		return (0);
	}
	data.thread = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	init_mutex(&data, av);
	init_thread(&data, av, ac);
	check_death(data.p);
	pthread_mutex_destroy(data.mutex);
	pthread_mutex_destroy(&data.talk);
	free(data.thread);
	free(data.mutex);
	free(data.p);
	return (0);
}
