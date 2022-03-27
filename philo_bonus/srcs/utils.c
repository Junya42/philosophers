/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 21:06:45 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/21 21:13:18 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

int	ft_atoi(const char *nptr)
{
	int			sign;
	long int	res;

	res = 0;
	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*(nptr++) == '-')
			sign = -sign;
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (res * sign > INT_MAX)
			return (-1);
		if (res * sign < INT_MIN)
			return (0);
		res = res * 10 + *(nptr++) - 48;
	}
	return (res * sign);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n >= 0)
		n = -n;
	else
		ft_putchar_fd('-', fd);
	if (n < -9)
		ft_putnbr_fd(-n / 10, fd);
	ft_putchar_fd(-(n % 10) + '0', fd);
}
