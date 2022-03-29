/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 21:06:45 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/29 21:18:40 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
			return (-1);
		res = res * 10 + *(nptr++) - 48;
	}
	if (res == 0 || (res * sign) > INT_MAX || (res * sign) < INT_MIN)
		return (-1);
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

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] && s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
