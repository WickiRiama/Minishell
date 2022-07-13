/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-huec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:08:27 by sle-huec          #+#    #+#             */
/*   Updated: 2022/07/13 15:08:31 by sle-huec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int	ft_run_builtin(char **cmd, t_env *env, t_dlist **blocks,
t_dlist **pipes)
{
	if (ft_strcmp(cmd[0], "cd") == 0)
		return (ft_cd(cmd, &env));
	else if (ft_strcmp(cmd[0], "echo") == 0)
		return (ft_echo(cmd));
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (display_env(env));
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (ft_exit(cmd, blocks, pipes, &env));
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

void	ft_close_fd_parent(t_dlist *blocks, t_dlist *pipes)
{
	if (((t_exec *)blocks->cont)->outfile != -2)
		((t_exec *)blocks->cont)->outfile \
			= close(((t_exec *)blocks->cont)->outfile) -2;
	if (((t_exec *)blocks->cont)->infile != -2)
		((t_exec *)blocks->cont)->infile \
			= close(((t_exec *)blocks->cont)->infile) -2;
	if (((t_pipe *)pipes->cont)->pipe_to_read_from != -2)
		((t_pipe *)pipes->cont)->pipe_to_read_from \
			= close(((t_pipe *)pipes->cont)->pipe_to_read_from) -2;
	if (((t_pipe *)pipes->cont)->pipe_to_write_to != -2)
		((t_pipe *)pipes->cont)->pipe_to_write_to \
			= close(((t_pipe *)pipes->cont)->pipe_to_write_to) -2;
}

void	ft_child(t_dlist *blocks, t_dlist *pipes, t_env *env, char **envp)
{
	int	status;

	if (((t_exec *)blocks->cont)->outfile == -1
		|| ((t_exec *)blocks->cont)->infile == -1)
	{
		ft_close_fd_parent(blocks, pipes);
		fprintf("free a faire\n");
		exit(1);
	}
	if (((t_exec *)blocks->cont)->outfile >= 0)
		dup2(((t_exec *)blocks->cont)->outfile, STDOUT_FILENO);
	else if (((t_pipe *)pipes->cont)->pipe_to_write_to >= 0)
		dup2(((t_pipe *)pipes->cont)->pipe_to_write_to, STDOUT_FILENO);

	if (((t_exec *)blocks->cont)->infile >= 0)
		dup2(((t_exec *)blocks->cont)->infile, STDIN_FILENO);
	else if (((t_pipe *)pipes->cont)->pipe_to_read_from >= 0)
		dup2(((t_pipe *)pipes->cont)->pipe_to_read_from, STDIN_FILENO);
	ft_close_fd_parent(blocks, pipes);

	if (ft_is_builtin(((t_exec *)blocks->cont)->cmd))
	{
		status = ft_run_builtin(((t_exec *)blocks->cont)->cmd,
				env, blocks, pipes);
		exit(status);
	}
	if (execve(((t_exec *)blocks->cont)->cmd[0], ((t_exec *)blocks->cont)->cmd,
			envp) == -1)
	{
		fprintf("error a gerer\n");
		fprintf("free a faire\n");
		exit(1);
	}
}

int	ft_exec(t_dlist	*blocks, t_dlist *pipes, t_env *env, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		fprintf("error a gerer\n");
	else if (pid == 0)
		ft_child(blocks, pipes, env, envp);
	ft_close_fd_parent(blocks, pipes);
	return (pid);
}

int	ft_executor(t_dlist	*blocks, t_dlist *pipes, t_env *env, char **envp)
{
	pid_t	pid;
	int		i;
	int		status;
	int		result;

	if (pipes == NULL && ft_is_builtin(((t_exec *)blocks->cont)->cmd))
		result = ft_exec_one_builtin();
	else
	{
		while (blocks)
		{
			pid = ft_exec(blocks, pipes, env, envp);
			blocks = blocks->next;
			if (pipes)
				pipes = pipes->next;
		}
		i = wait(&status);
		while (i > 0)
		{
			if (i == pid)
				result = status;
			i = wait(&status);
		}
	}
	return (WEXITSTATUS(result));
}
