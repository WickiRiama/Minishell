/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:41:31 by mriant            #+#    #+#             */
/*   Updated: 2022/08/04 10:27:02 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	ft_run_builtin(char **cmd, t_env *env, t_dlist **blocks, t_dlist **pipes)
{
	int	result;

	result = 133;
	if (ft_strcmp(cmd[0], "cd") == 0)
	{
		result = (ft_cd(cmd, &env));
	}
	else if (ft_strcmp(cmd[0], "echo") == 0)
	{
		result = (ft_echo(cmd));
	}
	else if (ft_strcmp(cmd[0], "pwd") == 0)
	{
		ft_pwd();
		// result =  (ft_pwd());
	}
	else if (ft_strcmp(cmd[0], "env") == 0)
	{
		display_env(env);
		// result =  (display_env(env));
	}
	else if (ft_strcmp(cmd[0], "exit") == 0)
	{
		result = ft_exit(cmd, blocks, pipes, &env);
	}
	return (result);
}

int	ft_is_builtin(char **cmd)
{
	if (ft_strcmp(cmd[0], "cd") == 0
		|| ft_strcmp(cmd[0], "echo") == 0
		|| ft_strcmp(cmd[0], "pwd") == 0
		|| ft_strcmp(cmd[0], "env") == 0
		|| ft_strcmp(cmd[0], "exit") == 0
		|| ft_strcmp(cmd[0], "unset") == 0
		|| ft_strcmp(cmd[0], "export") == 0)
		return (1);
	else
		return (0);
}

int	ft_run_one_builtin(t_dlist *blocks, t_dlist *pipes, t_env *env)
{
	int	status;
	int	temp_stdin;
	int	temp_stdout;

	if (!blocks || ((t_exec *)blocks->cont)->outfile == -1
		|| ((t_exec *)blocks->cont)->infile == -1)
	{
		ft_close_fd_all(blocks, pipes);
		return (1);
	}
	temp_stdin = dup(0);
	temp_stdout = dup(1);
	if (ft_strcmp("exit", ((t_exec *)blocks->cont)->cmd[0]) == 0
		&& len_arg_tab(((t_exec *)blocks->cont)->cmd) < 2)
	{
		close(temp_stdin);
		close(temp_stdout);
	}
	ft_redir(blocks, pipes);
	status = ft_run_builtin(((t_exec *)blocks->cont)->cmd,
			env, &blocks, &pipes);
	dup2(temp_stdin, 0);
	dup2(temp_stdout, 1);
	close(temp_stdin);
	close(temp_stdout);
	return (status);
}
