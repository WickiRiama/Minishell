/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:32:25 by mriant            #+#    #+#             */
/*   Updated: 2022/09/19 14:03:51 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*ft_exp_env(char *src, t_state *state, t_env **envp)
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
	env_var = ft_find_var(env_var, *envp);
	if (!env_var)
	{
		ft_clean("System error. Malloc failed.", src, NULL, NULL);
		return (NULL);
	}
	result = ft_extd_token(src, env_var, state->start, state->i);
	state->i = state->start - 1 + ft_strlen(env_var) - 1;
	free(env_var);
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
	free(exit_code);
	return (result);
}

char	*ft_token_expanse(char *token, t_env **envp)
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

int	ft_wexpanse(t_dlist **tokens, t_env	**envp)
{
	t_dlist	*temp;
	t_token	*content;

	temp = *tokens;
	while (temp)
	{
		content = (t_token *)temp->cont;
		if (content->type != DELIM)
			content->text = ft_token_expanse(content->text, envp);
		if (!content->text
			|| (content->type == WORD && ft_split_token(temp) == 1))
		{
			ft_lstclear_msh(tokens, &ft_del_token);
			return (1);
		}
		content->text = ft_rm_quote(content);
		if (!content->text)
		{
			ft_lstclear_msh(tokens, &ft_del_token);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}
