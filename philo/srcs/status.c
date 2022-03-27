/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 00:32:48 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/27 04:37:51 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	sleep_(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	status_update(philo, "is sleeping");
	pthread_mutex_unlock(&philo->data->print);
	usleep_(philo->data->sleep);
	pthread_mutex_lock(&philo->data->print);
	status_update(philo, "is thinking");
	pthread_mutex_unlock(&philo->data->print);
}

void	eat_(t_philo *philo)
{
	pthread_mutex_lock(&philo->left);
	pthread_mutex_lock(&philo->data->print);
	status_update(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->data->print);
	if (!philo->right)
	{
		usleep_(philo->data->die * 2);
		return ;
	}
	pthread_mutex_lock(philo->right);
	pthread_mutex_lock(&philo->data->print);
	status_update(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_lock(&philo->data->print);
	status_update(philo, "is eating");
	pthread_mutex_unlock(&philo->data->print);
	philo->meal = get_time();


}
