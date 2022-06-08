# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anremiki <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/27 05:01:17 by anremiki          #+#    #+#              #
#    Updated: 2022/06/08 17:59:22 by anremiki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =		./srcs/init_core.c ./srcs/init_data.c ./srcs/init_philo.c	\
	   		./srcs/main.c ./srcs/status.c ./srcs/thread.c ./srcs/thread_utils.c \
	   		./srcs/status_last.c ./srcs/utils.c	

INCLUDES =  ./includes/

OBJS = 		$(SRCS:.c=.o)

CC = 		@cc

RM =		rm -rf

CFLAGS_THREAD = -Wall -Wextra -Werror -pthread -g3 -fsanitize=thread -fPIE -pie -I $(INCLUDES)
CFLAGS = 	-Wall -Wextra -Werror -pthread -I $(INCLUDES)

PTHREAD =	-pthread

NAME = 		philo

NAMEEXIST = $(shell ls | grep -F $(NAME) | wc -l)

TOTAL = $(shell ls ./srcs/ | grep -F .c | wc -l)

CURRENT = $(shell ls ./srcs/ | grep -F .o | wc -l | xargs expr 1 +)

COMPARE = $(shell expr $(TOTAL) + 1)

all:		$(NAME)

thread: all

.c.o:		
			@echo "Building $< $(CURRENT)/$(TOTAL)"
ifeq ($(MAKECMDGOALS), thread)
				${CC} ${CFLAGS_THREAD} -c $< -o ${<:.c=.o}
else
				${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
endif

$(NAME):	$(OBJS)
			@echo
			@echo "\033[1;32mBuilding executable $(NAME)\033[0m"
			@echo
ifeq ($(MAKECMDGOALS), thread)
			$(CC) $(CFLAGS_THREAD) $(PTHREAD) $(OBJS) -o $(NAME)
else
			$(CC) $(CFLAGS) $(PTHREAD) $(OBJS) -o $(NAME)
endif
			@echo "\033[5;1;34mPhilo : done\033[0m"

clean:
ifeq ($(CURRENT), $(COMPARE))
				@echo "\033[1;33mClean philo objs\033[0m"
else
				@echo "\033[1;31mNo philo objs to clean\033[0m"
endif
			$(RM) $(OBJS)

fclean:		clean
ifeq ($(NAMEEXIST), 1)
			@echo "\033[1;33mClean $(NAME)\033[0m"
else
			@echo "\033[1;31m$(NAME) does not exist yet\033[0m"
endif
			$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re

.SILENT:	all clean fclean re
