/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:51:44 by bfichot           #+#    #+#             */
/*   Updated: 2022/01/04 18:49:49 by bfichot          ###   ########.fr       */
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

void *ft_routine(void* param)
{
	t_thread *tab;
	tab = (t_thread *) param;
    pthread_mutex_lock(tab->mutex);
	printf("id : [%d]\n", tab->id);
    for (int i = 0; i < 10000; ++i)
        shared += 1;
    pthread_mutex_unlock(tab->mutex);
    return 0;
}

long ft_time(t_data *data)
{
	gettimeofday(&data->start, NULL);
	return (data->start.tv_sec * 1000 + data->start.tv_usec / 1000);
}

void init_thread(t_thread *tab, char **av)
{
	int i;
	
	i = -1;
	tab = malloc(sizeof(t_thread));
	tab->thread = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	tab->mutex = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	tab->d->time = ft_time(tab->d);
	tab->d->nbr_philo = ft_atoi(av[1]);
	tab->d->time_to_die = ft_atoi(av[2]);
	tab->d->time_to_eat = ft_atoi(av[3]);
	tab->d->time_to_sleep = ft_atoi(av[4]);
	tab->d->nbr_must_eat = ft_atoi(av[5]);
	pthread_mutex_init(tab->mutex, NULL);
	while (++i < ft_atoi(av[1]))
	{
		tab[i].id = i + 1;
		//printf("id : [%d]\n", tab[i].id);
		pthread_create(&tab->thread[i], NULL, ft_routine, &tab[i]);
	}
	i = 0;
	while (++i < ft_atoi(av[1]))
        pthread_join(tab->thread[i], NULL);
}

int main(int ac, char **av)
{
    t_thread tab;
	if (ac < 5 || ac > 6)
		return (0);

	init_thread(&tab, av);	
    printf("%d\n", shared);
    exit(EXIT_SUCCESS);
}
