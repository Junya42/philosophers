/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_last.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:46:47 by anremiki          #+#    #+#             */
/*   Updated: 2022/06/05 12:08:11 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	eat2_(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->right);
	status_update(data, philo, "has taken a fork");
	pthread_mutex_lock(&philo->left);
	status_update(data, philo, "has taken a fork");
	status_update(data, philo, "is eating");
	pthread_mutex_lock(&data->check);
	philo->meal = get_time();
	pthread_mutex_lock(&data->c_total);
	philo->total++;
	pthread_mutex_unlock(&data->c_total);
	pthread_mutex_unlock(&data->check);
	usleep_(philo->data->eat, data);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(&philo->left);
}

void	start_death(t_philo *philo, t_data *data, int i)
{
	status_update(data, &philo[i], "is dead");
	pthread_mutex_lock(&data->c_death);
	data->death = 1;
	pthread_mutex_unlock(&data->c_death);
}

int	destroy_data_mutex(t_data *data)
{
	if (pthread_mutex_destroy(&data->c_win) != 0)
		return (0);
	if (pthread_mutex_destroy(&data->c_win) != 0)
		return (0);
	if (pthread_mutex_destroy(&data->c_death) != 0)
		return (0);
	if (pthread_mutex_destroy(&data->check) != 0)
		return (0);
	if (pthread_mutex_destroy(&data->print) != 0)
		return (0);
	return (1);
}

int	check_death(t_data *data)
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
	pthread_mutex_lock(&data->c_win);
	if (data->win == 1)
	{
		pthread_mutex_unlock(&data->c_win);
		return (1);
	}
	pthread_mutex_unlock(&data->c_win);
	return (0);
}
