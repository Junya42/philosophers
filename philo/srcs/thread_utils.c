/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:42:29 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/29 21:02:08 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long int	get_time(void)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == -1)
		return (-1);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

int	init_data_mutex(t_core *core)
{
	if (pthread_mutex_init(&core->data->print, NULL) != 0
		|| core->data->start == -1)
		return (0);
	if (pthread_mutex_init(&core->data->check, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&core->data->c_total, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&core->data->c_win, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&core->data->c_death, NULL) != 0)
		return (0);
	return (1);
}

int	create_mutex(t_core	*core)
{
	int	i;

	i = 0;
	if (!init_data_mutex(core))
		return (0);
	core->data->start = get_time();
	while (i < core->data->total)
	{
		if (pthread_mutex_init(&core->philo[i].left, NULL) != 0)
			return (0);
		if (core->data->total == 1)
			return (-1);
		if (i == core->data->total - 1)
			core->philo[i].right = &core->philo[0].left;
		else
			core->philo[i].right = &core->philo[i + 1].left;
		i++;
	}
	return (-1);
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
		pthread_mutex_lock(&data->c_total);
		if (philo[i].total >= (unsigned int)required)
			check++;
		pthread_mutex_unlock(&data->c_total);
		i++;
	}
	return (win_(check, data));
}
