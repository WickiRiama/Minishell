# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sam <sam@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/14 13:49:10 by mriant            #+#    #+#              #
#    Updated: 2022/07/04 21:10:14 by sam              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = libft/libft.a

SRCS = ${addprefix srcs/, \
	is_token.c \
	list.c \
	list_utils.c \
	minishell.c \
	token_types.c \
	token_utils.c \
	tokenisation.c \
	pwd.c \
	cd.c \
	exit.c \
	word_expansion.c \
	word_expansion_utils.c}

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