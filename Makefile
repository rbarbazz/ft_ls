# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbarbazz <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/31 11:02:43 by rbarbazz          #+#    #+#              #
#    Updated: 2018/03/07 12:05:26 by rbarbazz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

LIB = libft/libft.a

CC = clang

SRCS = main.c\
	   srcs/create.c\
	   srcs/long_format.c\
	   srcs/parsing.c\
	   srcs/printing.c\
	   srcs/printing_no_args.c\
	   srcs/recursion.c\
	   srcs/sort_delete.c\
	   srcs/tools.c

CFLAGS = -Wall -Wextra -Werror

LFLAGS = -lft -L libft

IFLAGS = -I includes -I libft/includes

OBJ = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) $(IFLAGS) $< -o $@

$(LIB):
	make -C libft

$(NAME): $(LIB) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) $(IFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all re fclean clean
