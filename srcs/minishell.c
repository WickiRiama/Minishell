/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:06:41 by mriant            #+#    #+#             */
/*   Updated: 2022/07/13 10:37:48 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Use with --suppressions=.ignore_readline to ignore readline leaks

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
		ft_printf("pipe read :%d\n", ((t_pipe *)pipes->cont)->pipe_to_read_from);
		ft_printf("pipe write :%d\n", ((t_pipe *)pipes->cont)->pipe_to_write_to);
		pipes = pipes->next;
	}
}

void	found_and_run_cmd(t_token **tokens, char *input, t_env *env)
{
	char	**path = ft_split(input, ' ');

	if (!path)
		return ;
	if (ft_strcmp(path[0], "cd") == 0)
		ft_cd(path, &env);
	else if (ft_strcmp(path[0], "echo") == 0)
		ft_echo(path);
	else if (ft_strcmp(path[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(path[0], "env") == 0)
		display_env(env);
	else if (ft_strcmp(path[0], "exit") == 0)
	{
		ft_exit(tokens, path, &env);
		// free_tab(path);
	}
	free_tab(path);
}

nt	main(int ac, char **av, char **envp)
{
	t_env	**env;
	t_dlist	*blocks;
	t_dlist	*pipes;

	if (ac != 1)
		return (1);
	(void) av;
	get_env_var(envp, &env);
	// if (!env)
	// 	return (1);
	while (1)
	{
		pipes = NULL;
		blocks = ft_parsing(&pipes, env);
		if (!blocks)
		{
			ft_lstclear_msh(&pipes, &ft_del_pipes);
			free_tab(env);
			return (1);
		}
		// found_and_run_cmd(&tokens, input, env);
		ft_print_list(blocks, pipes);
		ft_lstclear_msh(&blocks, &ft_del_blocks);
		ft_lstclear_msh(&pipes, &ft_del_pipes);
	}
	free_tab(env);
	return (0);
}

/*
int	main(int ac, char **av, char **envp)
{
	t_dlist	*blocks;
	t_dlist	*pipes;
	t_env	*env;

	if (ac != 1)
		return (1);
	(void) av;
	get_env_var(envp, &env);
	if (!env)
		return (1);
	while (1)
	{
		pipes = NULL;
		blocks = ft_parsing(&pipes, env);
		if (!blocks)
		{
			ft_lstclear_msh(&pipes, &ft_del_pipes);
			ft_lstclear_env(&env, &free);
			return (1);
		}
		// found_and_run_cmd(&tokens, input, env);
		ft_print_list(blocks, pipes);
		ft_lstclear_msh(&blocks, &ft_del_blocks);
		ft_lstclear_msh(&pipes, &ft_del_pipes);
	}
	ft_lstclear_env(&env, &free);
	return (0);
}
*/