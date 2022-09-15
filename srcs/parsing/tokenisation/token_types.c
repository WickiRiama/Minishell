/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:22:11 by mriant            #+#    #+#             */
/*   Updated: 2022/09/15 16:06:32 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	ft_synt_err(char *token)
{
	ft_fprintf(2, "Syntax error near unexpected token '%s'\n", token);
	g_exitcode = 2;
}

int	ft_redirin_type(t_dlist *tokens)
{
	if (((t_token *)tokens->cont)->text[1] == '\0'
		&& tokens->next && ((t_token *)tokens->next->cont)->type != OPERATOR)
	{
		((t_token *)tokens->cont)->type = LESS;
		((t_token *)tokens->next->cont)->type = INFILE;
		return (0);
	}
	else if (((t_token *)tokens->cont)->text[1] == '<'
		&& tokens->next && ((t_token *)tokens->next->cont)->type != OPERATOR)
	{
		((t_token *)tokens->cont)->type = DLESS;
		((t_token *)tokens->next->cont)->type = DELIM;
		return (0);
	}
	if (!tokens->next)
		ft_synt_err("newline");
	else if (((t_token *)tokens->next->cont)->type == OPERATOR)
		ft_synt_err(((t_token *)tokens->next->cont)->text);
	return (1);
}

int	ft_redirout_type(t_dlist *tokens)
{
	if (((t_token *)tokens->cont)->text[1] == '\0'
		&& tokens->next && ((t_token *)tokens->next->cont)->type != OPERATOR)
	{
		((t_token *)tokens->cont)->type = GREAT;
		((t_token *)tokens->next->cont)->type = OUTFILE;
		return (0);
	}
	else if (((t_token *)tokens->cont)->text[1] == '>'
		&& tokens->next && ((t_token *)tokens->next->cont)->type != OPERATOR)
	{
		((t_token *)tokens->cont)->type = DGREAT;
		((t_token *)tokens->next->cont)->type = APP_FILE;
		return (0);
	}
	if (!tokens->next)
		ft_synt_err("newline");
	else if (((t_token *)tokens->next->cont)->type == OPERATOR)
		ft_synt_err(((t_token *)tokens->next->cont)->text);
	return (1);
}

int	ft_pipe_type(t_dlist *tokens)
{
	((t_token *)tokens->cont)->type = PIPE;
	if (!tokens->prev
		|| ((t_token *)tokens->prev->cont)->type == PIPE
		|| !tokens->next)
	{
		ft_synt_err(((t_token *)tokens->cont)->text);
		return (1);
	}
	return (0);
}

int	ft_token_types(t_dlist *tokens)
{
	int	ret;

	ret = 0;
	if (((t_token *)tokens->cont)->type == QUOTE_ERR
		|| ((t_token *)tokens->cont)->text[0] == '\0')
		return (1);
	while (tokens)
	{
		if (((t_token *)tokens->cont)->text[0] == '<')
			ret = ft_redirin_type(tokens);
		if (((t_token *)tokens->cont)->text[0] == '>')
			ret = ft_redirout_type(tokens);
		if (((t_token *)tokens->cont)->text[0] == '|')
			ret = ft_pipe_type(tokens);
		if (ret == 1)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}
