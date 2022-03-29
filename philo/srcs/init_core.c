/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 22:38:01 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/29 21:08:30 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_core	*core_elem(t_core *core, int ac, char **av)
{
	core->data = data_init(ac, av);
	if (!core->data)
	{
		free(core);
		return (NULL);
	}
	core->philo = philo_init(core->data);
	if (!core->philo)
	{
		free(core->data);
		free(core);
		return (NULL);
	}
	return (core);
}

t_core	*core_init(int ac, char **av)
{
	t_core	*core;

	if (ac < 5 || ac > 6)
	{
		printf("Found %d arguments, required 5 or 6 only\n", ac);
		return (NULL);
	}
	core = NULL;
	core = (t_core *)malloc(sizeof(t_core) * 1);
	if (!core)
	{
		printf("Core malloc failed\n");
		return (NULL);
	}
	core->data = NULL;
	core->philo = NULL;
	return (core_elem(core, ac, av));
}
