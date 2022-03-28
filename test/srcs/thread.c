/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 04:38:03 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/28 23:12:31 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int		check_death(t_data *data)
{
	pthread_mutex_lock(&data->c_death);
	if (data->death == 1)
	{
		pthread_mutex_unlock(&data->c_death);
		return (1);
	}
	pthread_mutex_unlock(&data->c_death);
	return (0);
}

int	check_win(t_data *data)
{
	pthread_mutex_lock(&data->c_death);
	if (data->death == 1)
	{
		pthread_mutex_unlock(&data->c_death);
		return (1);
	}
	pthread_mutex_unlock(&data->c_death);
	return (0);
}

void	*philosophers(void *thread)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)thread;
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep_(philo->data->eat / 10);
	while (!check_death(data))
	{
		//if (data->win != 1 && data->death != 1)
		eat_(data, philo);
		//printf("DATA WIN = %d ID = %d\n", data->win, philo->id);
		if (check_win(data))
			return (NULL);
		//if (data->win != 1 && data->death != 1)
		sleep_(philo);
		//if (data->win == 1)
		//break ;
	}
	return (NULL);
}

int	win_(int check, t_data *data)
{
	if (check == data->total)
	{
		pthread_mutex_lock(&data->c_win);
		data->win = 1;
		pthread_mutex_unlock(&data->c_win);
		return (1);
	}
	return (0);
}

int	check_philos_count(t_philo *philo, int required, int i, t_data *data)
{
	int	check;

	check = 0;
	while (i < philo->data->total)
	{
		if (philo[i].total >= (unsigned int)required)
			check++;
		i++;
	}
	return (win_(check, data));
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
			if (lifespan >= data->die)
			{
				status_update(data, &philo[i], "is dead");
				pthread_mutex_lock(&data->c_death);
				data->death = 1;
				pthread_mutex_unlock(&data->c_death);
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
			printf("JOIN FAIL\n");
			return (0);
		}
		i++;
	}
	(void)i;
	//	sleep(1);
	while (j < data->total)
	{
		if (pthread_mutex_destroy(&philo[j].left) != 0)
		{
			printf("FORK destroy fail > philo[%d]\n", philo[j].id);
			return (0);
		}
		j++;
	}
	if (pthread_mutex_destroy(&data->c_win) != 0)
	{
		printf("C_WIN destroy fail\n");
		return (0);
	}
	if (pthread_mutex_destroy(&data->c_death) != 0)
	{
		printf("C_DEATH destroy fail\n");
		return (0);
	}
	if (pthread_mutex_destroy(&data->check) != 0)
	{
		printf("CHECK destroy fail\n");
		return (0);
	}
	if (pthread_mutex_destroy(&data->print) != 0)
	{
		printf("PRINT destroy fail\n");
		return (0);
	}
	return (1);
}

int	threading(t_core *core, t_philo	*philo, int i)
{
	int	check;

	while (i < core->data->total)
	{
		if (pthread_create(&philo[i].t_id, NULL, philosophers, &philo[i]))
			return (-1);
		philo[i].meal = get_time();
		i++;
	}
	check = reaper(philo, core->data, 0, 0);
	if (!join_and_destroy(philo, core->data, 0, 0))
		return (-2);
	return (check);
}
