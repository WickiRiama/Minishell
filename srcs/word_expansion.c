/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:32:25 by mriant            #+#    #+#             */
/*   Updated: 2022/06/25 10:57:46 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "minishell.h"
#include "libft.h"

char	*ft_find_var(char *var, char **envp)
{
	int		i;
	int		j;
	char	*result;

	if (!envp)
		result = ft_calloc(sizeof(char), 1);
	else
	{
		i = 0;
		while (envp[i])
		{
			j = 0;
			while (var[j] == envp[i][j])
				j++;
			if (var[j] == '\0' && envp[i][j] == '=')
			{
				result = ft_substr(envp[i], j + 1, ft_strlen(envp[i]));
				if (!result)
					ft_fprintf(2, "System error. Malloc failed.\n");
				break;
			}
			i++;
		}
		if (!envp[i])
			result = ft_calloc(sizeof(char), 1);
	}
	free(var);
	return (result);
}

int	ft_is_name(char	c, t_state *state)
{
	if (state->i != state->start && (ft_isalnum(c) || c == '_'))
		return (1);
	else if (ft_isalpha(c) || c == '_')
		return (1);
	return (0);
}

char	*ft_isenv(char *src, t_state *state, char **envp)
{
	char	*result;
	char	*env_var;
	size_t	len;

	len = ft_strlen(src);
	state->i++;
	state->start = state->i;
	while (ft_is_name(src[state->i], state))
		state->i++;
	env_var = ft_substr(src, state->start, state->i - state->start);
	if (!env_var)
	{
		free(src);
		ft_fprintf(2, "System error. Malloc failed.\n");
		return (NULL);
	}
	env_var = ft_find_var(env_var, envp);
	if (!env_var)
	{
		free(src);
		return (NULL);
	}
	len += ft_strlen(env_var);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
	{
		free(src);
		ft_fprintf(2, "System error. Malloc failed.\n");
		return (NULL);
	}
	ft_strlcpy(result, src, state->start);
	ft_strlcpy(result + state->start - 1, env_var, ft_strlen(env_var) + 1);
	ft_strlcpy(result + state->start + ft_strlen(env_var) - 1, src + state->i, len);
	ft_printf("result= %s\n", result);
	free(env_var);
	free(src);
	return (result = env_var);
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
			token = ft_isenv(token, &state, envp);
		state.i ++;
	}
	return (NULL);
}

void	ft_wexpanse(t_token **tokens, char **envp)
{
	t_token	*temp;

	temp = *tokens;
	while (temp)
	{
		// temp->token = ft_excode_expanse
		temp->token = ft_env_expanse(temp->token, envp);
		temp = temp->next;		
	}
}