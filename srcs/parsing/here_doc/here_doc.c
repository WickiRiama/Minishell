/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:24:59 by mriant            #+#    #+#             */
/*   Updated: 2022/08/05 10:54:31 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "minishell.h"
#include "libft.h"

void	ft_find_here_name(char *s1, char name[11])
{
	int		i;

	i = 0;
	while (i < 10 && s1[i])
	{
		name[i] = s1[i];
		i++;
	}
	name[i] = '\0';
	i = 1;
	while (i < 100 && access(name, F_OK) == 0)
	{
		name[8] = '0' + i / 10;
		name[9] = '0' + i % 10;
		i++;
	}
}

void	ft_write_here_doc(int fd, t_dlist *tokens, t_env **env)
{
	char	*input;

	input = readline("here_doc > ");
	while (input && ft_strcmp(input, ((t_token *)tokens->cont)->text) != 0)
	{
		input = ft_token_expanse(input, env);
		if (!input)
			return ;
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
		input = readline("here_doc > ");
	}
	if (!input)
		ft_fprintf(2,
			"\rwarning: here-document delimited by end-of-file (wanted '%s')\n",
			((t_token *)tokens->cont)->text);
	free(input);
}

int	ft_here_doc(t_dlist *tokens, t_env **env)
{
	char	name[11];
	int		fd;

	ft_find_here_name("here_doc00", name);
	fd = open(name, O_WRONLY | O_CREAT, 00644);
	if (fd == -1)
		return (fd);
	ft_write_here_doc(fd, tokens, env);
	close(fd);
	fd = open(name, O_RDONLY);
	unlink(name);
	return (fd);
}
