/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-huec <sle-huec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:06:41 by mriant            #+#    #+#             */
/*   Updated: 2022/07/07 15:30:07 by sle-huec         ###   ########.fr       */
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

void	found_and_run_cmd(t_token **tokens, char *input, char **env)
{
	char	**path = ft_split(input, ' ');

	if (!path)
		return ;
	if (ft_strcmp(path[0], "cd") == 0)
		ft_cd(path);
	else if (ft_strcmp(path[0], "echo") == 0)
		ft_echo(path);
	else if (ft_strcmp(path[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(path[0], "env") == 0)
		display_env(env);
	else if (ft_strcmp(path[0], "exit") == 0)
	{
		free_tab(path);
		ft_exit(tokens, input, env);
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	**env;
	t_token	*tokens;

	if (ac != 1)
		return (1);
	(void) av;
	env = copy_envp_in_tab(envp);
	if (!env)
		return (1);
	while (1)
	{
		input = readline("$>");
		if (input && input[0] == '\0')
		{
			free(input);
			continue ;
		}
		tokens = ft_tokenisation(input);
		if (!tokens)
		{
			ft_lstclear_msh(&tokens, &free);
			free(input);
			free_tab(env);
			return (1);
		}
		if (ft_token_types(tokens))
		{
			ft_lstclear_msh(&tokens, &free);
			free(input);
			continue ;
		}
		if (ft_wexpanse(&tokens, env))
		{
			ft_lstclear_msh(&tokens, &free);
			free(input);
			free_tab(env);
			return (1);
		}
		found_and_run_cmd(&tokens, input, env);
		// ft_print_list(tokens);
		free(input);
		ft_lstclear_msh(&tokens, &free);
	}
	free_tab(env);
	return (0);
}
