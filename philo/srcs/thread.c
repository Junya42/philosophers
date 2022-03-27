/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 04:38:03 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/27 04:53:15 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*philosophers(void *thread)
{
	t_philo	*philo;

	philo = (t_philo *)thread;
	if (philo->id % 2 == 0)
		usleep_(philo->data->eat / 10);
	return (NULL);
}

int	threading(t_core *core, t_philo	*philo, int i)
{
	while (i < core->data->total)
	{
		if (pthread_create(&philo[i].t_id, NULL, philosophers, &philo[i]))
			return (0);
		philo[i].meal = get_time();
	}
	return (0);
}
