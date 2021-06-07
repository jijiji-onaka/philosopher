# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/22 20:47:24 by tjinichi          #+#    #+#              #
#    Updated: 2021/06/07 21:05:41 by tjinichi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_two

CC = gcc

CFLAGS = -Wall -Werror -Wextra -I includes   -g #-fsanitize=address

SRCS =	./srcs/exit.c \
		./srcs/philo_two.c \
		./srcs/utils.c \
		./srcs/initialize.c \
		./srcs/thread.c \
		./srcs/print.c \
		./srcs/action.c \
		./srcs/eat_help.c \
		./srcs/my_usleep.c \

OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lpthread

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
