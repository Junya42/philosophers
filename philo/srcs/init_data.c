/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 22:11:51 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/29 21:20:27 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	parse_data(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[i])
	{
		j = 0;
		if (!av[i][j])
			return (0);
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9' || ft_atoi(av[i]) == -1)
			{
				printf("Wrong types of arguments\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_data_values(t_data *data, int ac)
{
	int	check;

	check = 1;
	if (data->total == -1)
		check = 0;
	if (data->die == -1)
		check = 0;
	if (data->eat == -1)
		check = 0;
	if (data->sleep == -1)
		check = 0;
	if (data->min == -1 && ac == 6)
		check = 0;
	return (check);
}

void	get_data_values(t_data *data, int ac, char **av)
{
	data->total = ft_atoi(av[0]);
	data->die = ft_atoi(av[1]);
	data->eat = ft_atoi(av[2]);
	data->sleep = ft_atoi(av[3]);
	if (ac == 6)
		data->min = ft_atoi(av[4]);
	else
		data->min = -1;
	data->death = 0;
	data->win = 0;
}

t_data	*data_init(int ac, char **av)
{
	t_data	*data;

	if (!parse_data(av))
		return (NULL);
	data = NULL;
	data = (t_data *)malloc(sizeof(t_data) * 1);
	if (!data)
	{
		printf("data malloc failed\n");
		return (NULL);
	}
	get_data_values(data, ac, av);
	if (!check_data_values(data, ac))
	{
		printf("Wrong types of arguments\n");
		free(data);
		return (NULL);
	}
	return (data);
}
