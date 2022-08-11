# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mriant <mriant@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/14 13:49:10 by mriant            #+#    #+#              #
#    Updated: 2022/08/08 17:07:34 by mriant           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = libft/libft.a

SRCS = ${addprefix srcs/, \
	minishell.c \
	utils.c}
SRCS += ${addprefix srcs/builtins/, \
	cd.c \
	echo.c \
	env.c \
	exit.c \
	export.c \
	pwd.c \
	unset.c}
SRCS += ${addprefix srcs/exec/, \
	exec_builtin.c \
	exec_clean.c \
	exec_utils.c \
	executor.c}
SRCS += ${addprefix srcs/lists/, \
	list_env_utils.c \
	list_env.c \
	list_utils.c \
	list.c}
SRCS += ${addprefix srcs/parsing/, \
	blocks_list.c \
	parsing.c \
	pipes_list.c \
	redir.c}
SRCS += ${addprefix srcs/parsing/here_doc/, \
	here_doc.c}
SRCS += ${addprefix srcs/parsing/tokenisation/, \
	is_token.c \
	token_types.c \
	token_utils.c \
	tokenisation.c}
SRCS += ${addprefix srcs/parsing/word_expansion/, \
	word_expansion_utils.c \
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
	mkdir -p ${dir $@}
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

.PHONY: grind
grind: ${NAME}
	valgrind --suppressions=.ignore_readline --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all ./minishell

.PHONY: malloc_test
malloc_test: $(OBJS) ${LIBFT}
	$(CC) $(CFLAGS) -fsanitize=undefined -rdynamic -o $@ ${OBJS} -L. -lmallocator -ldl $(LFLAGS)

-include ${DEP}
