/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 21:16:47 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/28 18:00:13 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	clean_memory(t_core *core)
{
	free(core->philo);
	free(core->data);
	free(core);
}

int	main(int ac, char **av)
{
	t_core	*core;
	int		value;

	core = core_init(ac, ++av);
	if (!core)
		return (1);
	if (create_mutex(core) == -1)
	{
		value = threading(core, core->philo, 0);
		if (value == -1)
			printf("pthread_create failed\n");
		else if (value == -2)
			printf("pthread_join or pthread_mutex_destroy failed\n");
	}
	else
		printf("pthread_mutex_init failed\n");
	clean_memory(core);
	return (0);
}
