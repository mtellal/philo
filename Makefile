# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/19 16:37:18 by mtellal           #+#    #+#              #
#    Updated: 2022/03/09 15:57:06 by mtellal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GCC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = philo

SRC = src/main.c src/init.c src/routine.c src/threads.c src/utils.c src/parse.c  

HEADER = -I ./

OBJ = $(SRC:.c=.o) 

all: $(NAME)

%.o:%.c
	$(GCC) -g $(CFLAGS) -pthread -o $@ -c $< $(HEADER)

$(NAME): $(OBJ)
	$(GCC) -g $(CFLAGS) -pthread -o $(NAME) $(OBJ) $(HEADER)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
