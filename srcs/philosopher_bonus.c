/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:48:05 by bfichot           #+#    #+#             */
/*   Updated: 2022/01/17 13:47:00 by bfichot          ###   ########.fr       */
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
		data->p[i].pid = 0;
		if (one_philo(data->p))
			exit(EXIT_FAILURE);
	}
}

void	init_sema(t_data *data, char **av, int i)
{
	data->sem = sem_open("sem_routine", O_CREAT | O_EXCL, 0660, ft_atoi(av[1]));
	data->dead = sem_open("dead", O_CREAT | O_EXCL, 0660, 1);
	if (data->sem == SEM_FAILED && data->dead == SEM_FAILED)
	{
		sem_unlink("sem_routine");
		sem_unlink("dead");
		data->dead = sem_open("dead", O_CREAT | O_EXCL, 0660, 1);
		data->sem = sem_open("sem_routine",
				O_CREAT | O_EXCL, 0660, ft_atoi(av[1]));
	}
	while (++i < ft_atoi(av[1]))
	{
		data->p[i].pid = fork();
		if (data->p[i].pid == 0)
		{
			pthread_create(data->thread, NULL, check_death, &data->p[i]);
			ft_routine(&data->p[i]);
			exit(EXIT_SUCCESS);
		}
	}
	waitpid(0, NULL, 0);
	i = -1;
	while (++i < ft_atoi(av[1]))
		kill(data->p[i].pid, SIGINT);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	i = -1;
	if (!check_error(ac, av))
	{
		printf("Arguments invalide!\n");
		return (0);
	}
	data.thread = malloc(sizeof(pthread_t));
	data.p = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	pthread_mutex_init(&data.talk, NULL);
	init_thread(&data, av, ac);
	init_sema(&data, av, i);
	sem_post(data.dead);
	sem_close(data.dead);
	sem_close(data.sem);
	free(data.p);
}
