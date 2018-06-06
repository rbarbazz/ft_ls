# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbarbazz <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 16:41:38 by rbarbazz          #+#    #+#              #
#    Updated: 2018/03/04 10:10:23 by rbarbazz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = srcs/ft_atoi.c \
	   srcs/ft_itoa.c \
	   srcs/boolean/ft_isalpha.c \
	   srcs/boolean/ft_isdigit.c \
	   srcs/boolean/ft_isalnum.c \
	   srcs/boolean/ft_isascii.c \
	   srcs/boolean/ft_isprint.c \
	   srcs/display/ft_putchar.c \
	   srcs/display/ft_putendl.c \
	   srcs/display/ft_putnbr.c \
	   srcs/display/ft_putstr.c \
	   srcs/display/ft_putchar_fd.c \
	   srcs/display/ft_putstr_fd.c \
	   srcs/display/ft_putendl_fd.c \
	   srcs/display/ft_putnbr_fd.c \
	   srcs/mem/ft_memset.c \
	   srcs/mem/ft_bzero.c \
	   srcs/mem/ft_memdel.c \
	   srcs/mem/ft_memcpy.c \
	   srcs/mem/ft_memccpy.c \
	   srcs/mem/ft_memmove.c \
	   srcs/mem/ft_memchr.c \
	   srcs/mem/ft_memcmp.c \
	   srcs/mem/ft_memalloc.c \
	   srcs/lists/ft_lstnew.c \
	   srcs/lists/ft_lstdelone.c \
	   srcs/lists/ft_lstdel.c \
	   srcs/strings/ft_strlen.c \
	   srcs/strings/ft_strcat.c \
	   srcs/strings/ft_strncat.c \
	   srcs/strings/ft_strdup.c \
	   srcs/strings/ft_strcpy.c \
	   srcs/strings/ft_strncpy.c \
	   srcs/strings/ft_strstr.c \
	   srcs/strings/ft_strcmp.c \
	   srcs/strings/ft_strncmp.c \
	   srcs/strings/ft_strnstr.c \
	   srcs/strings/ft_strchr.c \
	   srcs/strings/ft_strnew.c \
	   srcs/strings/ft_strrchr.c \
	   srcs/strings/ft_strdel.c \
	   srcs/strings/ft_strclr.c \
	   srcs/strings/ft_striter.c \
	   srcs/strings/ft_striteri.c \
	   srcs/strings/ft_strmap.c \
	   srcs/strings/ft_strlcat.c \
	   srcs/strings/ft_strmapi.c \
	   srcs/strings/ft_strequ.c \
	   srcs/strings/ft_strnequ.c \
	   srcs/strings/ft_strsub.c \
	   srcs/strings/ft_strjoin.c \
	   srcs/strings/ft_strtrim.c \
	   srcs/strings/ft_strsplit.c \
	   srcs/strings/ft_toupper.c \
	   srcs/strings/ft_tolower.c \
	   srcs/strings/ft_strjoinchar.c \
	   srcs/strings/ft_reverse.c \
	   srcs/get_next_line.c \
	   srcs/ft_printf/ft_printf.c \
	   srcs/ft_printf/apply_flags.c \
	   srcs/ft_printf/convert_c.c \
	   srcs/ft_printf/convert_s.c \
	   srcs/ft_printf/convert_p.c \
	   srcs/ft_printf/convert_int_long.c \
	   srcs/ft_printf/convert_wchar.c \
	   srcs/ft_printf/handle_arg.c \
	   srcs/ft_printf/handle_arg2.c

CFLAGS = -Wall -Wextra -Werror

HEADERS = -I includes

OBJ = $(SRCS:.c=.o)

%.o: %.c
	clang $(CFLAGS) -c $< -o $@ $(HEADERS)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
