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

int	is_pos_or_neg(char c)
{
	if (c == '+' || c == '-')
		return (1);
	else
		return (0);
}

int	check_digit(char **input, int i)
{
	while (input[1][i])
	{
		if (!ft_isdigit(input[1][i]) || (ft_strlen(input[1]) > 19))
		{
			ft_fprintf(2, "%s: %s: numeric argument required\n", input[0],
				input[1]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_arg_and_get_status(char **input)
{
	int	len;
	int	i;

	i = 0;
	len = len_arg_tab(input);
	if (input[1])
	{
		if (is_pos_or_neg(input[1][i]))
			i++;
		if (check_digit(input, i))
			return (2);
		if (len > 2)
			return (-1);
		else
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
	if (status == -1)
	{
		ft_fprintf(2, "%s: too many arguments\n", cmd[0]);
		return (1);
	}
	else
	{
		ft_lstclear_msh(blocks, &ft_del_blocks);
		ft_lstclear_msh(pipes, ft_del_pipes);
		ft_lstclear_env(env, &free);
		rl_clear_history();
		g_exitcode = status;
		exit(status);
	}
}
