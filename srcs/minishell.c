/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-huec <sle-huec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:06:41 by mriant            #+#    #+#             */
/*   Updated: 2022/07/06 13:28:37 by sle-huec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Use with --suppressions=.ignore_readline to ignore readline leaks

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
		ft_pwd();
		ft_cd(input);
		ft_pwd();
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
