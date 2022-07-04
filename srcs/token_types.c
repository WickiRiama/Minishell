/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:22:11 by mriant            #+#    #+#             */
/*   Updated: 2022/07/04 13:17:50 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_isquoted(char c, t_state *state)
{
	if (c == '\'')
	{
		if (state->squoted + state->dquoted == 0)
			state->squoted = 1;
		else if (state->squoted == 1)
			state->squoted = 0;
	}
	else
	{
		if (state->squoted + state->dquoted == 0)
			state->dquoted = 1;
		else if (state->dquoted == 1)
			state->dquoted = 0;
	}
}

int	ft_is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	ft_is_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

void	ft_redirin_type(t_token *tokens)
{
	if (tokens->token[1] == '\0')
	{
		tokens->type = LESS;
		if (tokens->next && tokens->next->type != OPERATOR)
			tokens->next->type = INFILE;
	}
	else if (tokens->token[1] == '<')
	{
		tokens->type = DLESS;
		if (tokens->next && tokens->next->type != OPERATOR)
			tokens->next->type = DELIM;
	}
	if (!tokens->next || tokens->next->type == OPERATOR)
		ft_error("Syntax error");
}

void	ft_redirout_type(t_token *tokens)
{
	if (tokens->token[1] == '\0')
	{
		tokens->type = GREAT;
		if (tokens->next && tokens->next->type != OPERATOR)
			tokens->next->type = OUTFILE;
	}
	else if (tokens->token[1] == '>')
	{
		tokens->type = DGREAT;
		if (tokens->next && tokens->next->type != OPERATOR)
			tokens->next->type = APP_FILE;
	}
	if (!tokens->next || tokens->next->type == OPERATOR)
		ft_error("Syntax error");
}

void	ft_token_types(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->token[0] == '<')
			ft_redirin_type(tokens);
		if (tokens->token[0] == '>')
			ft_redirout_type(tokens);
		else
			ft_word_type();
		tokens = tokens->next;
	}
}
