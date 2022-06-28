/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:22:11 by mriant            #+#    #+#             */
/*   Updated: 2022/06/28 18:23:26 by mriant           ###   ########.fr       */
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
	if (ft_strcmp(tokens->token, "<") == 0)
	{
		ft_strlcpy(tokens->type, "redir_from", ft_strlen("redir_from") + 1);
		if (tokens->next)
			ft_strlcpy(tokens->next->type, "infile", ft_strlen("infile") + 1);
	}
	else if (ft_strcmp(tokens->token, "<<") == 0)
	{
		ft_strlcpy(tokens->type, "here_doc", ft_strlen("here_doc") + 1);
		if (tokens->next)
			ft_strlcpy(tokens->next->type, "delim", ft_strlen("delim") + 1);
	}
	if (!tokens->next)
		ft_error("Syntax error");
}

void	ft_redirout_type(t_token *tokens)
{
	else if (ft_strcmp(tokens->token, ">") == 0)
	{
		ft_strlcpy(tokens->type, "redir_to", ft_strlen("redir_to") + 1);
		if (tokens->next)
			ft_strlcpy(tokens->next->type, "outfile", ft_strlen("outfile") + 1);
	}
	else if (ft_strcmp(tokens->token, ">>") == 0)
	{
		ft_strlcpy(tokens->type, "append", ft_strlen("append") + 1);
		if (tokens->next)
			ft_strlcpy(tokens->next->type, "app_file", ft_strlen("app_file") + 1);
	}
	if (!tokens->next)
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
