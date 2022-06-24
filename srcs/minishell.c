/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-huec <sle-huec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:06:41 by mriant            #+#    #+#             */
/*   Updated: 2022/06/24 15:10:20 by sle-huec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Compile with --suppressions=.ignore_readline to ignore readline leaks

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "minishell.h"
#include "libft.h"

void	ft_print_list(t_token *list)
{
	while (list)
	{
		ft_printf("token: %s, type: %s\n", list->token, list->type);
		list = list->next;
	}
}

int	main(void)
{
	char	*input;
	// t_token	*tokens;

	input = readline("$>");
	// tokens = ft_tokenisation(input);
	// ft_print_list(tokens);
	ft_pwd();
	ft_cd(input);
	ft_pwd();
	free(input);
	// ft_lstclear_msh(&tokens, &free);
	return (0);
}
