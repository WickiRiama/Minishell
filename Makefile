# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mriant <mriant@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/14 13:49:10 by mriant            #+#    #+#              #
#    Updated: 2022/06/16 16:05:31 by mriant           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = libft/libft.a

SRCS = ${addprefix srcs/, \
	list.c \
	list_utils.c \
	minishell.c \
	parsing.c}

OBJS = ${SRCS:srcs/%.c=build/%.o}
DEPS = ${SRCS:srcs/%.c=build/%.d}

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
IFLAGS = -I./includes -I./libft -MMD
LFLAGS = -L./libft -lft -lreadline

${NAME}: ${LIBFT} ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME} ${LFLAGS}

${LIBFT}:
	make -C libft

build/%.o: srcs/%.c
	mkdir -p build
	${CC} ${CFLAGS} -c $< -o $@ ${IFLAGS}

clean:
	rm -rf ${OBJS} ${DEPS} build

fclean: clean
	rm -rf ${NAME}

re: fclean
	make -C. 