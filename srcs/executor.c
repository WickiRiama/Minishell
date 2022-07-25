/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:08:27 by sle-huec          #+#    #+#             */
/*   Updated: 2022/07/25 14:18:57 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

#include "minishell.h"
#include "libft.h"

int	ft_run_builtin(char **cmd, t_env *env, t_dlist **blocks, t_dlist **pipes)
{
	if (ft_strcmp(cmd[0], "cd") == 0)
	{
		ft_cd(cmd, &env);
		// return (ft_cd(cmd, &env));
		return (133);
	}
	else if (ft_strcmp(cmd[0], "echo") == 0)
	{
		ft_echo(cmd);
		// return (ft_echo(cmd));
		return (133);
	}
	else if (ft_strcmp(cmd[0], "pwd") == 0)
	{
		ft_pwd();
		// return (ft_pwd());
		return (133);
	}
	else if (ft_strcmp(cmd[0], "env") == 0)
	{
		display_env(env);
		// return (display_env(env));
		return (133);
	}
	else if (ft_strcmp(cmd[0], "exit") == 0)
	{
		ft_exit(cmd, blocks, pipes, &env);
		// return (ft_exit(cmd, blocks, pipes, &env));
		return (133);
	}
	return (133);
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
	if (blocks)
	{
		if (((t_exec *)blocks->cont)->outfile != -2)
			((t_exec *)blocks->cont)->outfile \
				= close(((t_exec *)blocks->cont)->outfile) -2;
		if (((t_exec *)blocks->cont)->infile != -2)
			((t_exec *)blocks->cont)->infile \
				= close(((t_exec *)blocks->cont)->infile) -2;
	}
	if (pipes)
	{
		if (((t_pipe *)pipes->cont)->pipe_to_read_from != -2)
			((t_pipe *)pipes->cont)->pipe_to_read_from \
				= close(((t_pipe *)pipes->cont)->pipe_to_read_from) -2;
		if (((t_pipe *)pipes->cont)->pipe_to_write_to != -2)
			((t_pipe *)pipes->cont)->pipe_to_write_to \
				= close(((t_pipe *)pipes->cont)->pipe_to_write_to) -2;
	}
}

void	ft_close_fd_all(t_dlist *blocks, t_dlist *pipes)
{
	while (blocks && blocks->prev)
		blocks = blocks->prev;
	while (blocks)
	{
		if (((t_exec *)blocks->cont)->outfile != -2)
			((t_exec *)blocks->cont)->outfile \
				= close(((t_exec *)blocks->cont)->outfile) -2;
		if (((t_exec *)blocks->cont)->infile != -2)
			((t_exec *)blocks->cont)->infile \
				= close(((t_exec *)blocks->cont)->infile) -2;
		blocks = blocks->next;
	}
	while (pipes && pipes->prev)
		pipes = pipes->prev;
	while (pipes)
	{
		if (((t_pipe *)pipes->cont)->pipe_to_read_from != -2)
			((t_pipe *)pipes->cont)->pipe_to_read_from \
				= close(((t_pipe *)pipes->cont)->pipe_to_read_from) -2;
		if (((t_pipe *)pipes->cont)->pipe_to_write_to != -2)
			((t_pipe *)pipes->cont)->pipe_to_write_to \
				= close(((t_pipe *)pipes->cont)->pipe_to_write_to) -2;
		pipes = pipes->next;
	}
}

int	ft_get_cmdpath(char **cmd, char **paths)
{
	int		i;
	char	*s;

	i = 0;
	while (paths && paths[i])
	{
		s = ft_strjoin(paths[i], cmd[0], "/");
		if (!s)
			return (1);
		if (access(s, X_OK) == 0)
		{
			free(cmd[0]);
			cmd[0] = s;
			return (0);
		}
		free(s);
		i++;
	}
	if (!ft_strchr(cmd[0], '/') || access(cmd[0], X_OK) == -1)
	{
		ft_fprintf(2, "%s: %s\n", "command not found", cmd[0]);
		cmd[0][0] = '\0';
	}
	return (0);
}

int	ft_get_path(t_env *env, char **cmd)
{
	char	**paths;

	if (!env)
		return (1);
	while (env && ft_strncmp(env->var, "PATH=", 5) != 0)
		env = env->next;
	if (env)
	{
		paths = ft_split(env->var + 5, ':');
		if (!paths)
		{
			ft_fprintf(2, "System error. Malloc failed.\n");
			return (1);
		}
	}
	else
		paths = NULL;
	if (ft_get_cmdpath(cmd, paths))
	{
		free_tab(paths);
		ft_fprintf(2, "System error. Malloc failed.\n");
		return (1);
	}
	return (0);
}

void	ft_free_lists(t_dlist *blocks, t_dlist *pipes, t_env *env)
{
	while (blocks && blocks->prev)
		blocks = blocks->prev;
	ft_lstclear_msh(&blocks, &ft_del_blocks);
	while (pipes && pipes->prev)
		pipes = pipes->prev;
	ft_lstclear_msh(&pipes, &ft_del_pipes);
	while (env && env->prev)
		env = env->prev;
	ft_lstclear_env(&env, &free);
}

void	ft_redir(t_dlist *blocks, t_dlist *pipes)
{
	if (((t_exec *)blocks->cont)->outfile >= 0)
		dup2(((t_exec *)blocks->cont)->outfile, STDOUT_FILENO);
	else if (pipes && ((t_pipe *)pipes->cont)->pipe_to_write_to >= 0)
		dup2(((t_pipe *)pipes->cont)->pipe_to_write_to, STDOUT_FILENO);
	if (((t_exec *)blocks->cont)->infile >= 0)
		dup2(((t_exec *)blocks->cont)->infile, STDIN_FILENO);
	else if (pipes && ((t_pipe *)pipes->cont)->pipe_to_read_from >= 0)
		dup2(((t_pipe *)pipes->cont)->pipe_to_read_from, STDIN_FILENO);
	ft_close_fd_all(blocks, pipes);
}

int	ft_run_one_builtin(t_dlist *blocks, t_dlist *pipes, t_env *env)
{
	int	status;

	if (!blocks
		|| ((t_exec *)blocks->cont)->outfile == -1
		|| ((t_exec *)blocks->cont)->infile == -1)
	{
		ft_close_fd_all(blocks, pipes);
		ft_free_lists(blocks, pipes, env);
		return (1);
	}
	ft_redir(blocks, pipes);
	status = ft_run_builtin(((t_exec *)blocks->cont)->cmd,
			env, &blocks, &pipes);
	return (status);
}
void	ft_exit_free(t_dlist *blocks, t_dlist *pipes, t_env *env, int status)
{
	ft_free_lists(blocks, pipes, env);
	exit(status);
}

char	**ft_list_to_tab(t_env *list)
{
	int		size;
	char	**env;

	size = ft_lstsize_env(list);
	env = malloc(sizeof(char *) * (size + 1));
	if (!env)
	{
		ft_fprintf(2, "System error. Malloc failed.\n");
		return (NULL);
	}
	size = 0;
	while (list)
	{
		env[size] = ft_strdup(list->var);
		if (!env[size])
		{
			ft_fprintf(2, "System error. Malloc failed.\n");
			free_tab(env);
			return (NULL);
		}
		size++;
		list = list->next;
	}
	env[size] = NULL;
	return (env);
}

void	ft_child(t_dlist *blocks, t_dlist *pipes, t_env *env, char **env_tab)
{
	int	status;

	if (!blocks || ((t_exec *)blocks->cont)->outfile == -1
		|| ((t_exec *)blocks->cont)->infile == -1)
	{
		ft_close_fd_all(blocks, pipes);
		ft_exit_free(blocks, pipes, env, 1);
	}
	ft_redir(blocks, pipes);
	if (ft_is_builtin(((t_exec *)blocks->cont)->cmd))
	{
		status = ft_run_builtin(((t_exec *)blocks->cont)->cmd,
				env, &blocks, &pipes);
		ft_exit_free(blocks, pipes, env, status);
	}
	if (ft_get_path(env, ((t_exec *)blocks->cont)->cmd))
		ft_exit_free(blocks, pipes, env, 1);
	if (((t_exec *)blocks->cont)->cmd[0][0] == '\0')
		ft_exit_free(blocks, pipes, env, 127);
	if (execve(((t_exec *)blocks->cont)->cmd[0], ((t_exec *)blocks->cont)->cmd,
			env_tab) == -1)
	{
		ft_fprintf(2, "%s: %s\n", strerror(errno), ((t_exec *)blocks->cont)->cmd[0]);
		ft_exit_free(blocks, pipes, env, 1);
	}
}

int	ft_exec(t_dlist	*blocks, t_dlist *pipes, t_env *env)
{
	pid_t	pid;
	char	**env_tab;

	env_tab = ft_list_to_tab(env);
	if (!env_tab)
		return (-1);
	pid = fork();
	if (pid == -1)
		ft_fprintf(2, "Fork error: %s\n", strerror(errno));
	else if (pid == 0)
		ft_child(blocks, pipes, env, env_tab);
	ft_close_fd_parent(blocks, pipes);
	free_tab(env_tab);
	return (pid);
}

int	ft_executor(t_dlist	*blocks, t_dlist *pipes, t_env *env)
{
	pid_t	pid;
	int		i;
	int		status;
	int		result;

	if (pipes == NULL && ft_is_builtin(((t_exec *)blocks->cont)->cmd))
		result = ft_run_one_builtin(blocks, pipes, env);
	else
	{
		while (blocks)
		{
			pid = ft_exec(blocks, pipes, env);
			if (pid == -1)
			{
				ft_close_fd_all(blocks, pipes);
				ft_free_lists(blocks, pipes, env);
				exit(1);
			}
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
	g_exitcode = WEXITSTATUS(result);
	return (WEXITSTATUS(result));
}
