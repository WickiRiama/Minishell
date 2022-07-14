/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:06:41 by mriant            #+#    #+#             */
/*   Updated: 2022/07/14 15:15:38 by mriant           ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	t_dlist	*blocks;
	t_dlist	*pipes;

	if (ac != 1)
		return (1);
	(void) av;
	env = NULL;
	get_env_var(envp, &env);
	if (!env)
		return (1);
	while (1)
	{
		pipes = NULL;
		blocks = ft_parsing(&pipes, &env);
		if (!blocks)
		{
			ft_lstclear_msh(&pipes, &ft_del_pipes);
			ft_lstclear_env(&env, &free);
			return (1);
		}
		// found_and_run_cmd(((t_exec *)blocks->cont)->cmd, 
					// env, &blocks, &pipes);
		// ft_print_list(blocks, pipes);
		ft_executor(blocks, pipes, env, envp);
		ft_lstclear_msh(&blocks, &ft_del_blocks);
		ft_lstclear_msh(&pipes, &ft_del_pipes);
	}
	ft_lstclear_env(&env, &free);
	return (0);
}
