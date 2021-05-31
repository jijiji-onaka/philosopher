# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/22 20:47:24 by tjinichi          #+#    #+#              #
#    Updated: 2021/05/31 19:37:15 by tjinichi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_one

CC = gcc

CFLAGS = -Wall -Werror -Wextra -I includes    -fsanitize=address

SRCS =	./srcs/exit.c \
		./srcs/philo_one.c \
		./srcs/utils.c \
		./srcs/initialize.c \
		./srcs/thread.c \
		./srcs/print.c \
		./srcs/action.c \
		./srcs/eat_help.c \

MANDATORY_OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(MANDATORY_OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(MANDATORY_OBJS) -lpthread

$(LIBS): FORCE
	make -C utils/Libft

FORCE:

clean:
	rm -f $(MANDATORY_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re FORCE
