/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:08:27 by sle-huec          #+#    #+#             */
/*   Updated: 2022/08/04 10:36:04 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "minishell.h"
#include "libft.h"

void	ft_child_bis(t_dlist *blocks, t_dlist *pipes, t_env *env,
	char **env_tab)
{
	int	status;

	ft_redir(blocks, pipes);
	if (ft_is_builtin(((t_exec *)blocks->cont)->cmd))
	{
		status = ft_run_builtin(((t_exec *)blocks->cont)->cmd,
				env, &blocks, &pipes);
		ft_free_lists(blocks, pipes, env, env_tab);
		rl_clear_history();
		exit(status);
	}
	if (ft_get_path(env, ((t_exec *)blocks->cont)->cmd))
	{
		ft_free_lists(blocks, pipes, env, env_tab);
		rl_clear_history();
		exit(1);
	}
}

void	ft_child(t_dlist *blocks, t_dlist *pipes, t_env *env, char **env_tab)
{
	int	status;

	status = 127;
	if (!blocks || ((t_exec *)blocks->cont)->outfile == -1
		|| ((t_exec *)blocks->cont)->infile == -1)
	{
		ft_close_fd_all(blocks, pipes);
		ft_free_lists(blocks, pipes, env, env_tab);
		rl_clear_history();
		exit(1);
	}
	ft_child_bis(blocks, pipes, env, env_tab);
	if (((t_exec *)blocks->cont)->cmd[0][0] != '\0')
	{
		execve(((t_exec *)blocks->cont)->cmd[0], ((t_exec *)blocks->cont)->cmd,
			env_tab);
		ft_fprintf(2, "%s: %s\n",
			strerror(errno), ((t_exec *)blocks->cont)->cmd[0]);
		status = 1;
	}
	ft_free_lists(blocks, pipes, env, env_tab);
	rl_clear_history();
	exit(status);
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
				ft_free_lists(blocks, pipes, env, NULL);
				rl_clear_history();
				exit(1);
			}
			blocks = blocks->next;
			if (pipes)
				pipes = pipes->next;
		}
		result = ft_wait(pid);
	}
	g_exitcode = result;
	// return (WEXITSTATUS(result));
	return (result);
}
