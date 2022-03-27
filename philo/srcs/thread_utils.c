/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:42:29 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/27 04:31:11 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long int	get_time()
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == -1)
		return (-1);
	return (current_time.tv_usec / 1000);

}

void	status_update(t_philo *philo, char *status)
{
	long int	time;

	time = get_time();
	if (time == -1)
		printf("Philo[%d]\033[2;1;33m Unable to get time...\033[22m\033[0m\n",
			philo->id);
	else
	{
		time -= philo->data->start;
		if (ft_strcmp(status, "has taken a fork") == 0)
			printf("⎩%ld⎫Philo[%d]\033[1;33m %s\033[0m\n",
				time, philo->id, status);
		else if (ft_strcmp(status, "is eating") == 0)
			printf("⎩%ld⎫Philo[%d]\033[1;32m %s\033[0m\n",
				time, philo->id, status);
		else if (ft_strcmp(status, "is sleeping") == 0)
			printf("⎩%ld⎫Philo[%d]\033[1;34m %s\033[0m\n",
				time, philo->id, status);
		else if (ft_strcmp(status, "is thinking") == 0)
			printf("⎩%ld⎫Philo[%d]\033[1;35m %s\033[0m\n",
				time, philo->id, status);
		else
			printf("⎩%ld⎫Philo[%d]\033[3;1;31m %s\033[25m\033[0m\n",
				time, philo->id, status);
	}
}

int	create_mutex(t_core	*core)
{
	int	i;

	i = 0;
	core->data->start = get_time();
	if (pthread_mutex_init(&core->data->print, NULL) != 0 ||
			core->data->start == -1)
		return (0);
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
