/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:42:00 by mriant            #+#    #+#             */
/*   Updated: 2022/09/15 15:55:23 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	ft_get_cmdpath(char **cmd, char **paths)
{
	int		i;
	char	*s;

	if (!paths && access(cmd[0], X_OK) == 0)
		return (0);
	i = 0;
	while (paths && paths[i] && cmd[0][0] && ft_strchr(cmd[0], '/') == 0)
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
	if (ft_strchr(cmd[0], '/') != 0 && access(cmd[0], X_OK) == 0)
		return (0);
	ft_fprintf(2, "%s: '%s'\n", "command not found", cmd[0]);
	cmd[0][0] = '\0';
	return (0);
}

int	ft_get_path(t_env *env, char **cmd)
{
	char	**paths;

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
	if (cmd && cmd[0] && ft_get_cmdpath(cmd, paths))
	{
		free_tab(paths);
		ft_fprintf(2, "System error. Malloc failed.\n");
		return (1);
	}
	free_tab(paths);
	return (0);
}

void	ft_redir(t_dlist *blocks)
{
	if (((t_exec *)blocks->cont)->outfile >= 0)
		dup2(((t_exec *)blocks->cont)->outfile, STDOUT_FILENO);
	else if (((t_exec *)blocks->cont)->pipe_to_write_to >= 0)
		dup2(((t_exec *)blocks->cont)->pipe_to_write_to, STDOUT_FILENO);
	if (((t_exec *)blocks->cont)->infile >= 0)
		dup2(((t_exec *)blocks->cont)->infile, STDIN_FILENO);
	else if (((t_exec *)blocks->cont)->pipe_to_read_from >= 0)
		dup2(((t_exec *)blocks->cont)->pipe_to_read_from, STDIN_FILENO);
	ft_close_fd_all(blocks);
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

int	ft_wait(pid_t pid)
{
	int	i;
	int	status;
	int	result;

	result = -15;
	if (pid == -2)
		return (0);
	i = wait(&status);
	while (i > 0)
	{
		if (i == pid)
			result = status;
		i = wait(&status);
	}
	if (result >= 0 && WIFSIGNALED(result) == 1)
	{
		result = 128 + WTERMSIG(status);
		if (result == 131)
			ft_printf("Quit (core dumped)");
		ft_printf("\n");
		return (result);
	}
	else if (result >= 0)
		return (WEXITSTATUS(result));
	return (result);
}
