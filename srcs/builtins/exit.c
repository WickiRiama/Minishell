/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 13:25:07 by sle-huec          #+#    #+#             */
/*   Updated: 2022/08/08 17:14:54 by mriant           ###   ########.fr       */
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

int	check_arg_and_get_status(char **input)
{
	int	i;
	int	len;

	i = 0;
	while (input[1])
	{
		if (!ft_isdigit(input[1][i]))
		{
			ft_fprintf(2, "%s: %s: numeric argument required\n", input[0],
				input[1]);
			return (2);
		}
		else
		{
			len = len_arg_tab(input);
			if (len > 2)
			{
				ft_fprintf(2, "%s: too many arguments\n", input[0]);
				return (1);
			}
			return (ft_atoi(input[1]));
		}
		i++;
	}
	return (0);
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
	exit(status);
}

void	ft_exit_ctrld(t_dlist **pipes, t_env **env)
{
	char	*cmd_tab[2];
	char	cmd[5];

	ft_strlcpy(cmd, "exit", 5);
	cmd_tab[0] = cmd;
	cmd_tab[1] = NULL;
	ft_exit(cmd_tab, NULL, pipes, env);
}
