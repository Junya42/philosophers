/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 04:38:03 by anremiki          #+#    #+#             */
/*   Updated: 2022/06/08 14:53:41 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*philosophers(void *thread)
{
	t_philo			*philo;
	t_data			*data;
	unsigned int	checker;

	philo = (t_philo *)thread;
	data = philo->data;
	checker = (unsigned int)(data->total - 1);
	if (philo->id % 2 == 0)
		usleep_(philo->data->eat / 10, data);
	while (!check_death(data))
	{
		if (philo->id == checker && data->total > 1)
			eat2_(data, philo);
		else
			eat_(data, philo);
		if (check_win(data))
			return (NULL);
		sleep_(philo);
	}
	return (NULL);
}

int	reaper(t_philo *philo, t_data *data, int i, int checker)
{
	long int	lifespan;

	while (42)
	{
		i = 0;
		while (i < data->total)
		{
			pthread_mutex_lock(&data->check);
			lifespan = get_time() - philo[i].meal;
			if (lifespan > data->die)
			{
				start_death(philo, data, i);
				checker = 1;
			}
			pthread_mutex_unlock(&data->check);
			if (checker)
				break ;
			i++;
		}
		if (checker)
			return (0);
		if (data->min != -1)
			if (check_philos_count(philo, data->min, 0, data))
				return (1);
	}
}

int	join_and_destroy(t_philo *philo, t_data *data, int i, int j)
{
	while (i < data->total)
	{
		if (pthread_join(philo[i].t_id, NULL) != 0)
		{
			printf("Pthread_join failed\n");
			return (0);
		}
		i++;
	}
	while (j < data->total)
	{
		if (pthread_mutex_destroy(&philo[j].left) != 0)
		{
			printf("Pthread_mutex_destroy failed\n");
			return (0);
		}
		j++;
	}
	if (!destroy_data_mutex(data))
	{
		printf("Pthread_mutex_destroy failed\n");
		return (0);
	}
	return (1);
}

int	threading(t_core *core, t_philo	*philo, int i)
{
	int	check;

	while (i < core->data->total)
	{
		philo[i].meal = get_time();
		if (pthread_create(&philo[i].t_id, NULL, philosophers, &philo[i]))
			return (-1);
		i++;
	}
	check = reaper(philo, core->data, 0, 0);
	if (!join_and_destroy(philo, core->data, 0, 0))
		return (-2);
	return (check);
}
