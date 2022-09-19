/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 11:13:46 by mriant            #+#    #+#             */
/*   Updated: 2022/09/19 14:04:31 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*ft_find_var(char *var, t_env *envp)
{
	int		j;
	char	*result;

	result = ft_calloc(sizeof(char), 1);
	while (envp)
	{
		j = 0;
		while (var[j] == envp->var[j])
			j++;
		if (var[j] == '\0' && envp->var[j] == '=')
		{
			free(result);
			result = ft_substr(envp->var, j + 1, ft_strlen(envp->var));
			break ;
		}
		envp = envp->next;
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

char	*ft_extd_token(char *src, char *env_var, int start_var, int end_var)
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
	free(src);
	return (result);
}

char	*ft_rm_quote(t_token *token)
{
	t_state	state;
	char	*text;

	text = token->text;
	if (text[0] == '\0')
		token->type = TO_IGNORE;
	ft_init_state(&state);
	while (text && text[state.i])
	{
		if (text[state.i] == '"' || text[state.i] == '\'')
		{
			ft_isquoted(text[state.i], &state);
			text = ft_extd_token(text, "\0", state.i + 1, state.i + 1);
			state.i--;
			while (text && state.dquoted && text[state.i + 1]
				&& text[state.i + 1] != '"')
				state.i++;
			while (text && state.squoted && text[state.i + 1]
				&& text[state.i + 1] != '\'')
				state.i++;
		}
		state.i++;
	}
	return (text);
}
