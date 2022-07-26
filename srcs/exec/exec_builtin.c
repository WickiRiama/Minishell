/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:41:31 by mriant            #+#    #+#             */
/*   Updated: 2022/07/25 16:38:29 by mriant           ###   ########.fr       */
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
		ft_cd(cmd, &env);
		// result =  return (ft_cd(cmd, &env));
	}
	else if (ft_strcmp(cmd[0], "echo") == 0)
	{
		ft_echo(cmd);
		// result = return (ft_echo(cmd));
	}
	else if (ft_strcmp(cmd[0], "pwd") == 0)
	{
		ft_pwd();
		// result = return (ft_pwd());
	}
	else if (ft_strcmp(cmd[0], "env") == 0)
	{
		display_env(env);
		// result = return (display_env(env));
	}
	else if (ft_strcmp(cmd[0], "exit") == 0)
	{
		ft_exit(cmd, blocks, pipes, &env);
		// result = return (ft_exit(cmd, blocks, pipes, &env));
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

	if (!blocks
		|| ((t_exec *)blocks->cont)->outfile == -1
		|| ((t_exec *)blocks->cont)->infile == -1)
	{
		ft_close_fd_all(blocks, pipes);
		ft_free_lists(blocks, pipes, env, NULL);
		return (1);
	}
	ft_redir(blocks, pipes);
	status = ft_run_builtin(((t_exec *)blocks->cont)->cmd,
			env, &blocks, &pipes);
	return (status);
}
