/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:06:41 by mriant            #+#    #+#             */
/*   Updated: 2022/07/05 21:36:50 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Compile with --suppressions=.ignore_readline to ignore readline leaks

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "minishell.h"
#include "libft.h"

int	g_exitcode;

void	ft_print_list(t_token *list)
{
	while (list)
	{
		ft_printf("token: %s, type: %d\n", list->token, list->type);
		list = list->next;
	}
}

void	found_and_run_cmd(t_token *tokens)
{
	int	nl;

	nl = 0;
	if (ft_strcmp(tokens->token, "cd"))
		ft_cd(&tokens->next->token);
	else if (ft_strcmp(tokens->token, "echo"))
	{
		if (ft_strcmp(tokens->next->token, "-n"))
			nl = 1;
		ft_echo(&tokens->next->token, nl);
	}
	else if (ft_strcmp(tokens->token, "pwd"))
		ft_pwd();
	if (ft_strcmp(tokens->token, "exit"))
		ft_exit();
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_token	*tokens;

	if (ac != 1)
		return (1);
	(void) av;
	while (1)
	{
		input = readline("$>");
		found_and_run_cmd(tokens);
		tokens = ft_tokenisation(input);
		if (!tokens)
		{
			ft_lstclear_msh(&tokens, &free);
			free(input);
			return (1);
		}
		if (ft_token_types(tokens))
		{
			ft_lstclear_msh(&tokens, &free);
			free(input);
			continue ;
		}
		if (ft_wexpanse(&tokens, envp))
		{
			ft_lstclear_msh(&tokens, &free);
			free(input);
			return (1);
		}
		ft_print_list(tokens);
		free(input);
		ft_lstclear_msh(&tokens, &free);
	}
	return (0);
}
