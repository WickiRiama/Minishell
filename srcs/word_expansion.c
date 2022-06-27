/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:32:25 by mriant            #+#    #+#             */
/*   Updated: 2022/06/27 11:00:50 by mriant           ###   ########.fr       */
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

char	*ft_find_var(char *var, char **envp)
{
	int		i;
	int		j;
	char	*result;

	result = ft_calloc(sizeof(char), 1);
	i = 0;
	while (envp && envp[i])
	{
		j = 0;
		while (var[j] == envp[i][j])
			j++;
		if (var[j] == '\0' && envp[i][j] == '=')
		{
			free(result);
			result = ft_substr(envp[i], j + 1, ft_strlen(envp[i]));
			break ;
		}
		i++;
	}
	free(var);
	return (result);
}

int	ft_is_name(char c, t_state *state)
{
	if (state->i != state->start && (ft_isalnum(c) || c == '_'))
		return (1);
	else if (ft_isalpha(c) || c == '_')
		return (1);
	return (0);
}

char	*ft_extended_token(char *src, char *env_var, int start_var, int end_var)
{
	size_t	res_len;
	size_t	var_len;
	char	*result;

	var_len = ft_strlen(env_var);
	res_len = ft_strlen(src) + var_len;
	result = ft_calloc(sizeof(char), (res_len + 1));
	if (!result)
	{
		ft_fprintf(2, "System error. Malloc failed.");
		return (NULL);
	}
	ft_strlcpy(result, src, start_var);
	ft_strlcpy(result + start_var - 1, env_var, var_len + 1);
	ft_strlcpy(result + start_var + var_len - 1, src + end_var, res_len);
	return (result);
}

char	*ft_isenv(char *src, t_state *state, char **envp)
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
	result = ft_extended_token(src, env_var, state->start, state->i);
	state->i = state->start - 1 + ft_strlen(env_var) - 1;
	ft_clean(NULL, src, env_var, NULL);
	return (result);
}

char	*ft_isexitcode(char *src, t_state *state)
{
	char	*result;
	char	*exit_code;

	state->start = state->i + 1;
	state->i += 2;
	exit_code = ft_itoa(g_exitcode);
	result = ft_extended_token(src, exit_code, state->start, state->i);
	state->i = state->start - 1 + ft_strlen(exit_code) - 1;
	ft_clean(NULL, src, exit_code, NULL);
	return (result);
}

char	*ft_env_expanse(char *token, char **envp)
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
				token = ft_isexitcode(token, &state);
			else
				token = ft_isenv(token, &state, envp);
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
		temp->token = ft_env_expanse(temp->token, envp);
		if (!temp->token)
		{
			ft_lstclear_msh(tokens, &free);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}
