/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 22:43:32 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/29 21:11:38 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_philo	*philo_init(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = NULL;
	philo = (t_philo *)malloc(sizeof(t_philo) * data->total);
	if (!philo)
	{
		printf("Philo malloc failed\n");
		return (NULL);
	}
	i = 0;
	while (i < data->total)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].total = 0;
		philo[i].end = 0;
		philo[i].timer = 0;
		philo[i].meal = 0;
		philo[i].right = NULL;
		i++;
	}
	return (philo);
}
