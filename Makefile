# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mriant <mriant@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/14 13:49:10 by mriant            #+#    #+#              #
#    Updated: 2022/06/27 11:36:00 by mriant           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = libft/libft.a

SRCS = ${addprefix srcs/, \
	list.c \
	list_utils.c \
	minishell.c \
	token_types.c \
	token_utils.c \
	tokenisation.c \
	pwd.c \
	cd.c \
	word_expansion.c}

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

.PHONY: clean
clean:
	rm -rf ${OBJS} ${DEPS} build

.PHONY: fclean
fclean: clean
	rm -rf ${NAME}

.PHONY: re
re: fclean
	make -C. 