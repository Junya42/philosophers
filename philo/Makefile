# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anremiki <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/27 05:01:17 by anremiki          #+#    #+#              #
#    Updated: 2022/03/27 06:34:29 by anremiki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =		./srcs/init_core.c ./srcs/init_data.c ./srcs/init_philo.c	\
	   		./srcs/main.c ./srcs/status.c ./srcs/thread.c ./srcs/thread_utils.c \
	   		./srcs/utils.c	\

INCLUDES =  ./includes/

OBJS = 		$(SRCS:.c=.o)

CC = 		@gcc

RM =		rm -rf

CFLAGS = 	-Wall -Wextra -Werror -I $(INCLUDES)

PTHREAD =	-pthread

NAME = 		philo

.c.o:
			@echo "Building $<"
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(PTHREAD) $(OBJS) -o $(NAME)
			@echo "\033[5;1;35mPhilo : done\033[0m"

clean:
			$(RM) $(OBJS)
			@echo "\033[1;33mClean philo objs\033[0m"

fclean:		clean
			$(RM) $(NAME)
			@echo "\033[1;33mClean philo\033[0m"

re:			fclean $(NAME)

.PHONY:		all clean fclean re

.SILENT:	all clean fclean re
