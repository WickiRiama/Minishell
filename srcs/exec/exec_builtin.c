/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:41:31 by mriant            #+#    #+#             */
/*   Updated: 2022/09/15 15:52:28 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	ft_run_builtin(char **cmd, t_env **env, t_dlist **blocks, int tmp_std[2])
{
	int	result;

	result = 133;
	if (ft_strcmp(cmd[0], "cd") == 0)
		result = (ft_cd(cmd, env));
	else if (ft_strcmp(cmd[0], "echo") == 0)
		result = (ft_echo(cmd));
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		result = (ft_pwd(cmd));
	else if (ft_strcmp(cmd[0], "env") == 0)
		result = (display_env(cmd, *env, 0));
	else if (ft_strcmp(cmd[0], "exit") == 0)
		result = ft_exit(cmd, blocks, env, tmp_std);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		result = (ft_unset(cmd, env));
	else if (ft_strcmp(cmd[0], "export") == 0)
		result = (ft_export(cmd, env));
	if (result == 15)
		ft_exit_ctrld(blocks, env);
	return (result);
}

int	ft_is_builtin(char **cmd)
{
	if (!cmd)
		return (0);
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

int	ft_run_one_builtin(t_dlist *blocks, t_env **env)
{
	int	status;
	int	temp_std[2];

	if (!blocks || ((t_exec *)blocks->cont)->outfile == -1
		|| ((t_exec *)blocks->cont)->infile == -1)
	{
		ft_close_fd_all(blocks);
		return (1);
	}
	temp_std[0] = dup(0);
	temp_std[1] = dup(1);
	ft_redir(blocks);
	status = ft_run_builtin(((t_exec *)blocks->cont)->cmd, env, &blocks,
			temp_std);
	dup2(temp_std[0], 0);
	dup2(temp_std[1], 1);
	close(temp_std[0]);
	close(temp_std[1]);
	return (status);
}
