/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:32:25 by mriant            #+#    #+#             */
/*   Updated: 2022/07/04 16:27:02 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "minishell.h"
#include "libft.h"

static void	ft_clean(char *error, void *ptr1, void *ptr2, void *ptr3)
{
	if (error)
		ft_fprintf(2, "%s\n", error);
	free (ptr1);
	free (ptr2);
	free (ptr3);
}

char	*ft_exp_env(char *src, t_state *state, char **envp)
{
	char	*result;
	char	*env_var;

	state->i++;
	state->start = state->i;
	while (ft_is_name(src[state->i], state))
		state->i++;
	env_var = ft_substr(src, state->start, state->i - state->start);
	if (!env_var)
	{
		ft_clean("System error. Malloc failed.", src, NULL, NULL);
		return (NULL);
	}
	env_var = ft_find_var(env_var, envp);
	if (!env_var)
	{
		ft_clean("System error. Malloc failed.", src, NULL, NULL);
		return (NULL);
	}
	result = ft_extd_token(src, env_var, state->start, state->i);
	state->i = state->start - 1 + ft_strlen(env_var) - 1;
	ft_clean(NULL, src, env_var, NULL);
	return (result);
}

char	*ft_exp_exitcode(char *src, t_state *state)
{
	char	*result;
	char	*exit_code;

	state->start = state->i + 1;
	state->i += 2;
	exit_code = ft_itoa(g_exitcode);
	result = ft_extd_token(src, exit_code, state->start, state->i);
	state->i = state->start - 1 + ft_strlen(exit_code) - 1;
	ft_clean(NULL, src, exit_code, NULL);
	return (result);
}

char	*ft_token_expanse(char *token, char **envp)
{
	t_state	state;

	ft_init_state(&state);
	while (token[state.i])
	{
		if (token[state.i] == '\'' || token[state.i] == '"')
			ft_isquoted(token[state.i], &state);
		else if (state.squoted == 0 && token[state.i] == '$')
		{
			if (token[state.i + 1] == '?')
				token = ft_exp_exitcode(token, &state);
			else if (ft_isalpha(token[state.i + 1]) 
				|| token[state.i + 1] == '_')
				token = ft_exp_env(token, &state, envp);
		}
		if (!token)
			return (NULL);
		state.i++;
	}
	return (token);
}

int	ft_wexpanse(t_token **tokens, char **envp)
{
	t_token	*temp;

	temp = *tokens;
	while (temp)
	{
		temp->token = ft_token_expanse(temp->token, envp);
		if (!temp->token)
		{
			ft_lstclear_msh(tokens, &free);
			return (1);
		}
		temp = temp->next;
	}
	*tokens = ft_trim_empty_token(*tokens);
	return (0);
}
