/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 13:25:07 by sle-huec          #+#    #+#             */
/*   Updated: 2022/07/27 14:20:26 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "libft.h"
#include "minishell.h"

int	len_arg_tab(char **input)
{
	int	i;

	i = 0;
	while (input && input[i])
	{
		i++;
	}
	return (i);
}

int	is_pos_or_neg(char c)
{
	if (c == '+' || c == '-')
		return (1);
	else
		return (0);
}

int	check_arg_and_get_status(char **input)
{
	int	i;
	int	len;

	i = 0;
	len = len_arg_tab(input);
	if (len > 2)
	{
		ft_fprintf(2, "%s: too many arguments\n", input[0]);
		// g_exitcode = 1;
		return (1);
	}
	else if (input[1])
	{
		if (is_pos_or_neg(input[1][i]))
			i++;
		while (input[1][i])
		{
			if (!ft_isdigit(input[1][i]))
			{
				ft_fprintf(2, "%s: %s: numeric argument required\n", input[0],
					input[1]);
				return (2);
			}
			i++;
		}
		return (ft_atoi(input[1]));
	}
	else
		return (g_exitcode);
}

int	ft_exit(char **cmd, t_dlist **blocks, t_dlist **pipes, t_env **env)
{
	int	status;

	(void)env;
	ft_printf("exit\n");
	status = check_arg_and_get_status(cmd);
	ft_lstclear_msh(blocks, &ft_del_blocks);
	ft_lstclear_msh(pipes, ft_del_pipes);
	ft_lstclear_env(env, &free);
	rl_clear_history();
	//close fd?
	
	//PSEUDO CODE
	// if (status !=1)
		exit(status);
	// else
		// printf too many argument
	//FIN DU PSEUDO CODE
}
