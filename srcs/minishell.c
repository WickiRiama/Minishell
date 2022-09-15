/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:06:41 by mriant            #+#    #+#             */
/*   Updated: 2022/09/15 16:13:23 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Use with --suppressions=.ignore_readline to ignore readline leaks

#include <readline/readline.h>

#include "minishell.h"
#include "libft.h"

int	g_exitcode;

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	t_dlist	*blocks;
	t_sig	new_sa;

	if (ac != 1)
		return (1);
	(void) av;
	env = NULL;
	if (get_env_var(envp, &env) == 1)
		return (1);
	while (1)
	{
		blocks = ft_parsing(&env, &new_sa);
		if (!blocks)
			ft_exit_ctrld(NULL, &env);
		if (ft_check_last_infile(blocks) == 1)
			ft_executor(blocks, &env, &new_sa);
		ft_lstclear_msh(&blocks, &ft_del_blocks);
	}
	ft_lstclear_env(&env, &free);
	rl_clear_history();
	return (0);
}
