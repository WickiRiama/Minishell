/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 13:25:07 by sle-huec          #+#    #+#             */
/*   Updated: 2022/09/14 16:00:52 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "minishell.h"

int	ft_checknum(char *s)
{
	char	*max;

	max = "9223372036854775807";
	if (!s)
		return (1);
	while (ft_isspace(*s))
		s++;
	if (*s == '+' && *(s + 1) != '\0')
		s++;
	else if (*s == '-' && *(s + 1) != '\0')
	{
		max = "9223372036854775808";
		s++;
	}
	while (*s == '0')
		s ++;
	if (ft_strlen(s) > 19 || (ft_strlen(s) == 19 && ft_strncmp(s, max, 19) > 0))
		return (1);
	while (*s)
	{
		if (ft_isdigit(*s) == 0)
			return (1);
		s++;
	}
	return (0);
}

int	check_arg_and_get_status(char **input)
{
	int	len;

	len = len_arg_tab(input);
	if (!input || !input[0])
		return (4);
	if (input[1])
	{
		if (ft_checknum(input[1]))
		{
			ft_fprintf(2, "%s: %s: numeric argument required\n", input[0],
				input[1]);
			return (2);
		}
		if (len > 2)
			return (-1);
		else
			return (ft_atoi(input[1]));
	}
	else
		return (g_exitcode);
}

int	ft_exit(char **cmd, t_dlist **blocks, t_env **env, int temp_std[2])
{
	int	status;

	(void)env;
	if (isatty(STDIN_FILENO) == 1 && isatty(STDERR_FILENO) == 1)
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
		ft_lstclear_env(env, &free);
		if (temp_std)
		{
			close(temp_std[0]);
			close(temp_std[1]);
		}
		rl_clear_history();
		exit(status);
	}
}

void	ft_exit_ctrld(t_dlist **blocks, t_env **env)
{
	char	*cmd_tab[2];
	char	cmd[5];

	ft_strlcpy(cmd, "exit", 5);
	cmd_tab[0] = cmd;
	cmd_tab[1] = NULL;
	ft_exit(cmd_tab, blocks, env, NULL);
}
