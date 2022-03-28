/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 04:38:03 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/28 04:58:31 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*philosophers(void *thread)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)thread;
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep_(philo->data->eat / 10);
	while (!data->death)
	{
		eat_(data, philo);
		if (data->win)
			return (NULL);
		if (!data->death)
			sleep_(philo);
	}
	return (NULL);
}

int	check_philos_count(t_philo *philo, int required, int i)
{
	int	check;

	check = 0;
	while (i < philo->data->total)
	{
		if (philo[i].total >= (unsigned int)required)
			check++;
		i++;
	}
	if (check == philo->data->total)
		return (1);
	return (0);
}

int	reaper(t_philo *philo, t_data *data, int i)
{
	long int	lifespan;

	while (42)
	{
		i = 0;
		while (i < data->total && !data->death)
		{
			pthread_mutex_lock(&data->check);
			lifespan = get_time() - philo[i].meal;
			if (lifespan >= data->die)
			{
				status_update(data, &philo[i], "is dead");
				data->death = 1;
			}
			pthread_mutex_unlock(&data->check);
			if (data->death)
				break ;
			i++;
		}
		if (data->death)
			return (0);
		if (data->min != -1)
			if (check_philos_count(philo, data->min, 0))
				return (1);
	}
}

int	threading(t_core *core, t_philo	*philo, int i)
{
	while (i < core->data->total)
	{
		if (pthread_create(&philo[i].t_id, NULL, philosophers, &philo[i]))
			return (-1);
		philo[i].meal = get_time();
		i++;
	}
	return (reaper(philo, core->data, 0));
}
