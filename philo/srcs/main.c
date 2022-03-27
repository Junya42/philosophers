/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 21:16:47 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/27 04:41:40 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int main(int ac, char **av)
{
	t_core	*core;

	core = core_init(ac, av);
	if (!core)
		return (1);
	if (!create_mutex(core) || !threading(core, core->philo, 0))
	{

	}
	return (0);
}
