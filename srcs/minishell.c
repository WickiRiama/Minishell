/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:06:41 by mriant            #+#    #+#             */
/*   Updated: 2022/07/12 16:44:47 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Use with --suppressions=.ignore_readline to ignore readline leaks

#include <readline/readline.h>
#include <readline/history.h>

#include "minishell.h"
#include "libft.h"

int	g_exitcode;

void	ft_print_list(t_dlist *list, t_dlist *pipes)
{
	int	i;

	while (list)
	{
		i = 0;
		ft_printf("command :\n");
		while (((t_exec *)list->cont)->cmd[i])
		{
			ft_printf("   %s\n", ((t_exec *)list->cont)->cmd[i]);
			i++;
		}
		ft_printf("infile :%d\n", ((t_exec *)list->cont)->infile);
		ft_printf("outfile :%d\n", ((t_exec *)list->cont)->outfile);
		list = list->next;
	}
	while (pipes)
	{
		ft_printf("pipein :%d\n", ((t_pipe *)pipes->cont)->pipe_in);
		ft_printf("pipeout :%d\n", ((t_pipe *)pipes->cont)->pipe_out);
		pipes = pipes->next;
	}
}

void	found_and_run_cmd(t_dlist **tokens, char *input, char **env)
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
		ft_exit(tokens, path, env);
		// free_tab(path);
	}
	free_tab(path);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	**env;
	t_dlist	*tokens;
	t_dlist	*blocks;
	t_dlist	*pipes;

	if (ac != 1)
		return (1);
	(void) av;
	env = copy_envp_in_tab(envp);
	if (!env)
		return (1);
	while (1)
	{
		input = readline("$> ");
		if (!input)
			break ;
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		tokens = ft_tokenisation(input);
		if (!tokens)
		{
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
		pipes = NULL;
		blocks = ft_cmd_orga(tokens, &pipes);
		if (!blocks)
		{
			ft_lstclear_msh(&tokens, &free);
			free(input);
			free_tab(env);
			return (1);
		}
		// found_and_run_cmd(&tokens, input, env);
		ft_print_list(blocks, pipes);
		free(input);
		ft_lstclear_msh(&tokens, &ft_del_token);
		ft_lstclear_msh(&blocks, &ft_del_blocks);
		ft_lstclear_msh(&pipes, &ft_del_pipes);
	}
	free_tab(env);
	return (0);
}
