/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:42:29 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/29 16:28:36 by anremiki         ###   ########.fr       */
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

int	create_mutex(t_core	*core)
{
	int	i;

	i = 0;
	core->data->start = get_time();
	if (pthread_mutex_init(&core->data->print, NULL) != 0
		|| core->data->start == -1)
		return (0);
	if (pthread_mutex_init(&core->data->check, NULL) != 0)
		return (i);
	if (pthread_mutex_init(&core->data->c_total, NULL) != 0)
		return (i);
	if (pthread_mutex_init(&core->data->c_win, NULL) != 0)
		return (i);
	if (pthread_mutex_init(&core->data->c_death, NULL) != 0)
		return (i);
	while (i < core->data->total)
	{
		if (pthread_mutex_init(&core->philo[i].left, NULL) != 0)
			return (i);
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
