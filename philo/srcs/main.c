/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 21:16:47 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/28 03:53:27 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*void	clean_memory(t_core *core, t_data *data, t_philo *philo)
{

}*/

int main(int ac, char **av)
{
	t_core	*core;

	core = core_init(ac, ++av);
	if (!core)
		return (1);
	if (create_mutex(core) == -1)
	{
		if (threading(core, core->philo, 0) == -1)
			printf("pthread_create failed\n");
	}
	else
		printf("pthread_mutex_init failed\n");
	//clean_memory(core, core->data, core->philo);
	return (0);
}
