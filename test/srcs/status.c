/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 00:32:48 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/29 17:15:01 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	usleep_(long int duration)
{
	long int	start;

	start = -1;
	start = get_time();
	if (start == -1)
		printf("usleep_ \033[2;1;33mUnable to get time...\033[22m\033[0m\n");
	else
	{
		while ((get_time() - start) < duration)
			usleep(duration / 10);
	}
}

void	sleep_(t_philo *philo)
{
	status_update(philo->data, philo, "is sleeping");
	usleep_(philo->data->sleep);
	status_update(philo->data, philo, "is thinking");
}

void	eat2_(t_data *data, t_philo *philo)
{
	printf("before \033[1;42mLock\033[0m LEFT\n");
	pthread_mutex_lock(philo->right);
	printf("After \033[1;41mLock\033[0m LEFT\n");
	status_update(data, philo, "has taken a fork");
	if (!&philo->left)
	{
		usleep_(philo->data->die * 2);
		pthread_mutex_unlock(&philo->left);
		return ;
	}
	printf("before \033[1;42mLock\033[0m RIGHT\n");
	pthread_mutex_lock(&philo->left);
	printf("After \033[1;41mLock\033[0m RIGHT\n");
	status_update(data, philo, "has taken a fork");
	status_update(data, philo, "is eating");
	usleep_(philo->data->eat);
	pthread_mutex_lock(&data->check);
	philo->total++;
	philo->meal = get_time();
	printf("before \033[1;43mUnlock\033[0m LEFT\n");
	pthread_mutex_unlock(&data->check);
	printf("after \033[1;44mUnlock\033[0m LEFT\n");
	pthread_mutex_unlock(philo->right);
	printf("before \033[1;43mUnlock\033[0m RIGHT\n");
	pthread_mutex_unlock(&philo->left);
	printf("after \033[1;44mUnlock\033[0m RIGHT\n");
}

void	eat_(t_data *data, t_philo *philo)
{
	printf("before \033[1;42mLock\033[0m LEFT\n");
	pthread_mutex_lock(&philo->left);
	printf("After \033[1;41mLock\033[0m LEFT\n");
	status_update(data, philo, "has taken a fork");
	if (!philo->right)
	{
		usleep_(philo->data->die * 2);
		pthread_mutex_unlock(&philo->left);
		return ;
	}
	printf("before \033[1;42mLock\033[0m RIGHT\n");
	pthread_mutex_lock(philo->right);
	printf("After \033[1;41mLock\033[0m RIGHT\n");
	status_update(data, philo, "has taken a fork");
	status_update(data, philo, "is eating");
	usleep_(philo->data->eat);
	pthread_mutex_lock(&data->check);
	philo->total++;
	philo->meal = get_time();
	printf("before \033[1;43mUnlock\033[0m LEFT\n");
	pthread_mutex_unlock(&data->check);
	printf("after \033[1;44mUnlock\033[0m LEFT\n");
	pthread_mutex_unlock(&philo->left);
	printf("before \033[1;43mUnlock\033[0m RIGHT\n");
	pthread_mutex_unlock(philo->right);
	printf("after \033[1;44mUnlock\033[0m RIGHT\n");
}

void	print_activity(t_data *data, t_philo *philo, char *status, long int t)
{
	if (ft_strcmp(status, "has taken a fork") == 0)
		printf("【%ld】Philo[%d]\033[1;33m %s\033[0m\n",
			t - data->start, philo->id, status);
	else if (ft_strcmp(status, "is eating") == 0)
		printf("【%ld】Philo[%d]\033[1;32m %s\033[0m : n_meal = %d\n",
			t - data->start, philo->id, status, philo->total);
	else if (ft_strcmp(status, "is sleeping") == 0)
	{
		printf("【%ld】Philo[%d]\033[1;34m %s\033[0m\n",
			t - data->start, philo->id, status);
	}
	else if (ft_strcmp(status, "is thinking") == 0)
		printf("【%ld】Philo[%d]\033[1;35m %s\033[0m\n",
			t - data->start, philo->id, status);
	else
		printf("【%ld】Philo[%d]\033[3;1;31m %s\033[25m\033[0m\n",
			t - data->start, philo->id, status);
}

int	status_update(t_data *data, t_philo *philo, char *status)
{
	long int	time;

	time = get_time();
	if (check_win(data) || check_death(data))
		return (1);
	pthread_mutex_lock(&data->print);
	if (time == -1)
		printf("Philo[%d]\033[2;1;33m Unable to get time...\033[22m\033[0m\n",
			philo->id);
	else
		print_activity(data, philo, status, time);
	pthread_mutex_unlock(&data->print);
	return (0);
}
