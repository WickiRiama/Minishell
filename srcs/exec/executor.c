/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:08:27 by sle-huec          #+#    #+#             */
/*   Updated: 2022/09/15 15:58:50 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <readline/readline.h>
#include <signal.h>

#include "minishell.h"
#include "libft.h"
#include "get_next_line.h"

void	ft_check_dir(t_dlist *blocks, t_env *env, char **env_tab)
{
	int	fd;

	fd = open(((t_exec *)blocks->cont)->cmd[0], O_DIRECTORY);
	if (fd != -1)
	{
		ft_fprintf(2, "%s: Is a directory\n", ((t_exec *)blocks->cont)->cmd[0]);
		close(fd);
		ft_free_lists(blocks, env, env_tab);
		rl_clear_history();
		exit(126);
	}
}

void	ft_child_bis(t_dlist *blocks, t_env **env, char **env_tab)
{
	int	status;

	ft_redir(blocks);
	if (ft_is_builtin(((t_exec *)blocks->cont)->cmd))
	{
		status = ft_run_builtin(((t_exec *)blocks->cont)->cmd, env, &blocks,
				NULL);
		ft_free_lists(blocks, *env, env_tab);
		rl_clear_history();
		exit(status);
	}
	if (ft_get_path(*env, ((t_exec *)blocks->cont)->cmd))
	{
		ft_free_lists(blocks, *env, env_tab);
		rl_clear_history();
		exit(1);
	}
	ft_check_dir(blocks, *env, env_tab);
}

void	ft_child(t_dlist *blocks, t_env **env, char **env_tab, t_sig *new_sa)
{
	int	status;

	ft_set_sa(new_sa, SIG_DFL);
	status = 127;
	if (!blocks || ((t_exec *)blocks->cont)->outfile == -1
		|| ((t_exec *)blocks->cont)->infile == -1)
	{
		ft_close_fd_all(blocks);
		ft_free_lists(blocks, *env, env_tab);
		rl_clear_history();
		exit(1);
	}
	ft_child_bis(blocks, env, env_tab);
	if (((t_exec *)blocks->cont)->cmd[0][0] != '\0')
	{
		execve(((t_exec *)blocks->cont)->cmd[0], ((t_exec *)blocks->cont)->cmd,
			env_tab);
		ft_fprintf(2, "%s: %s\n",
			strerror(errno), ((t_exec *)blocks->cont)->cmd[0]);
		status = 1;
	}
	ft_free_lists(blocks, *env, env_tab);
	rl_clear_history();
	exit(status);
}

int	ft_exec(t_dlist	*blocks, t_env **env, t_sig *new_sas)
{
	pid_t	pid;
	char	**env_tab;

	if (!((t_exec *)blocks->cont)->cmd)
	{
		ft_close_fd_parent(blocks);
		return (-2);
	}
	env_tab = ft_list_to_tab(*env);
	if (!env_tab)
		return (-1);
	pid = fork();
	if (pid == -1)
		ft_fprintf(2, "Fork error: %s\n", strerror(errno));
	else if (pid == 0)
	{
		if (isatty(STDIN_FILENO) == 0 || isatty(STDERR_FILENO) == 0)
			get_next_line(-1);
		ft_child(blocks, env, env_tab, new_sas);
	}
	ft_close_fd_parent(blocks);
	free_tab(env_tab);
	return (pid);
}

int	ft_executor(t_dlist	*blocks, t_env **env, t_sig *new_sa)
{
	pid_t	pid;
	int		result;

	ft_set_sa(new_sa, SIG_IGN);
	if (blocks->next == NULL && ft_is_builtin(((t_exec *)blocks->cont)->cmd))
		result = ft_run_one_builtin(blocks, env);
	else
	{
		while (blocks)
		{
			pid = ft_exec(blocks, env, new_sa);
			if (pid == -1)
			{
				ft_close_fd_all(blocks);
				ft_free_lists(blocks, *env, NULL);
				rl_clear_history();
				exit(1);
			}
			blocks = blocks->next;
		}
		result = ft_wait(pid);
	}
	g_exitcode = (result);
	return ((result));
}
