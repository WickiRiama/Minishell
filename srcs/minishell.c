/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-huec <sle-huec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:06:41 by mriant            #+#    #+#             */
/*   Updated: 2022/07/06 13:35:17 by sle-huec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Use with --suppressions=.ignore_readline to ignore readline leaks

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "minishell.h"
#include "libft.h"

int	g_exitcode;

void	ft_print_list(t_token *list)
{
	while (list)
	{
		ft_printf("token: %s, type: %d\n", list->token, list->type);
		list = list->next;
	}
}

void	found_and_run_cmd(t_token **tokens, char *input)
{
	int		i;
	char	**path = ft_split(input, ' ');

	if (!path)
		return ;
	if (ft_strcmp(path[0], "cd") == 0)
		ft_cd(path);
	else if (ft_strcmp(path[0], "echo") == 0)
		ft_echo(path);
	else if (ft_strcmp(path[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(path[0], "exit") == 0)
	{
		i = 0;
		while (path[i])
		{
			free(path[i]);
			i++;
		}
		free(path);
		ft_exit(tokens, input);
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_token	*tokens;

	if (ac != 1)
		return (1);
	(void) av;
	while (1)
	{
		input = readline("$>");
		tokens = ft_tokenisation(input);
		if (!tokens)
		{
			ft_lstclear_msh(&tokens, &free);
			free(input);
			return (1);
		}
		if (ft_token_types(tokens))
		{
			ft_lstclear_msh(&tokens, &free);
			free(input);
			continue ;
		}
		if (ft_wexpanse(&tokens, envp))
		{
			ft_lstclear_msh(&tokens, &free);
			free(input);
			return (1);
		}
		found_and_run_cmd(&tokens, input);
		// ft_print_list(tokens);
		free(input);
		ft_lstclear_msh(&tokens, &free);
	}
	return (0);
}
