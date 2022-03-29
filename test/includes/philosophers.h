/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:57:27 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/29 17:14:02 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*../srcs*/
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <semaphore.h>
# include <pthread.h>

typedef struct s_data
{
	int					total;
	int					die;
	int					eat;
	int					sleep;
	int					min;
	int					death;
	int					win;
	long int			start;
	pthread_mutex_t		c_win;
	pthread_mutex_t		c_death;
	pthread_mutex_t		check;
	pthread_mutex_t		print;
}				t_data;

typedef struct s_philo
{
	t_data				*data;
	unsigned int		id;
	unsigned int		total;
	unsigned int		end;
	unsigned long int	timer;
	unsigned long int	meal;
	pthread_t			t_id;
	pthread_mutex_t		left;
	pthread_mutex_t		*right;
}				t_philo;

typedef struct s_core
{
	t_data		*data;
	t_philo		*philo;
}				t_core;

int			ft_atoi(const char *nptr);
size_t		ft_strlen(const char *s);
void		ft_putchar_fd(char c, int fd);
void		ft_putnbr_fd(int n, int fd);
int			ft_strcmp(char *s1, char *s2);

t_philo		*philo_init(t_data *data);
t_data		*data_init(int ac, char **av);
t_core		*core_init(int ac, char **av);

long int	get_time(void);
int			status_update(t_data *data, t_philo *philo, char *status);
int			create_mutex(t_core	*core);
int			threading(t_core *core, t_philo *philo, int i);
void		usleep_(long int duration);
void		sleep_(t_philo *philo);
void		eat_(t_data *data, t_philo *philo);
void		eat2_(t_data *data, t_philo *philo);
int			check_win(t_data *data);
int			check_death(t_data *data);

#endif
