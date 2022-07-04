/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:22:11 by mriant            #+#    #+#             */
/*   Updated: 2022/07/04 15:50:55 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	ft_synt_err(char *token)
{
	ft_fprintf(2, "Syntax error near unexpected token '%s'\n", token);
}

int	ft_redirin_type(t_token *tokens)
{
	if (tokens->token[1] == '\0'
		&& tokens->next && tokens->next->type != OPERATOR)
	{
		tokens->type = LESS;
		tokens->next->type = INFILE;
		return (0);
	}
	else if (tokens->token[1] == '<'
		&& tokens->next && tokens->next->type != OPERATOR)
	{
		tokens->type = DLESS;
		tokens->next->type = DELIM;
		return (0);
	}
	if (!tokens->next)
		ft_synt_err("newline");
	else if (tokens->next->type == OPERATOR)
		ft_synt_err(tokens->next->token);
	return (1);
}

int	ft_redirout_type(t_token *tokens)
{
	if (tokens->token[1] == '\0'
		&& tokens->next && tokens->next->type != OPERATOR)
	{
		tokens->type = GREAT;
		tokens->next->type = OUTFILE;
		return (0);
	}
	else if (tokens->token[1] == '>'
		&& tokens->next && tokens->next->type != OPERATOR)
	{
		tokens->type = DGREAT;
		tokens->next->type = APP_FILE;
		return (0);
	}
	if (!tokens->next)
		ft_synt_err("newline");
	else if (tokens->next->type == OPERATOR)
		ft_synt_err(tokens->next->token);
	return (1);
}

int	ft_pipe_type(t_token *tokens)
{
	tokens->type = PIPE;
	if (!tokens->prev || tokens->prev->type == PIPE || !tokens->next)
	{
		ft_synt_err(tokens->token);
		return (1);
	}
	return (0);
}

int	ft_token_types(t_token *tokens)
{
	int	ret;

	if (tokens->type == QUOTE_ERR)
		return (1);
	while (tokens)
	{
		if (tokens->token[0] == '<')
			ret = ft_redirin_type(tokens);
		if (tokens->token[0] == '>')
			ret = ft_redirout_type(tokens);
		if (tokens->token[0] == '|')
			ret = ft_pipe_type(tokens);
		if (ret == 1)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}
