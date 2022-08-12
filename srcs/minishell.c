/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:06:41 by mriant            #+#    #+#             */
/*   Updated: 2022/08/12 14:25:56 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Use with --suppressions=.ignore_readline to ignore readline leaks

#include <readline/readline.h>
#include <readline/history.h>

#include "minishell.h"
#include "libft.h"

int	g_exitcode;

void	ft_print_list(t_dlist *list)
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
		ft_printf("pipe write :%d\n", ((t_exec *)list->cont)->pipe_to_write_to);
		ft_printf("pipe read :%d\n", ((t_exec *)list->cont)->pipe_to_read_from);
		list = list->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	t_dlist	*blocks;

	if (ac != 1)
		return (1);
	(void) av;
	env = NULL;
	if (get_env_var(envp, &env) == 1)
		return (1);
	if (!env)
		return (1);
	while (1)
	{
		blocks = ft_parsing(&env);
		if (!blocks)
			ft_exit_ctrld(NULL, &env);
		ft_executor(blocks, env);
		ft_lstclear_msh(&blocks, &ft_del_blocks);
	}
	ft_lstclear_env(&env, &free);
	rl_clear_history();
	return (0);
}
