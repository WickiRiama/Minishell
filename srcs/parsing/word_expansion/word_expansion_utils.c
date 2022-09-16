/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 11:13:46 by mriant            #+#    #+#             */
/*   Updated: 2022/09/16 14:43:04 by mriant           ###   ########.fr       */
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

int	ft_split_token(t_dlist *token)
{
	t_state	state;
	t_token	*content;
	t_token	*new_token;
	t_dlist	*new_link;

	if (!token)
		return (0);
	ft_init_state(&state);
	content = (t_token *)token->cont;
	while (content->text[state.i])
	{
		if (content->text[state.i] == '"' || content->text[state.i] == '\'')
		{
			ft_isquoted(content->text[state.i], &state);
			state.i++;
		}
		else if (ft_is_blank(content->text[state.i])
			&& state.dquoted + state.squoted == 0)
		{
			content->text[state.i] = '\0';
			state.i++;
			while (ft_is_blank(content->text[state.i]))
				state.i++;
			if (content->text[state.i])
			{
				new_token = ft_init_token(0, ft_strlen(content->text + state.i),
					content->text + state.i);
				if (!new_token)
					return (1);
				new_link = ft_lstnew_msh(new_token);
				if (!new_link)
				{
					ft_del_token(new_token);
					return (1);
				}
				((t_token *)new_link->cont)->type = WORD;
				ft_lstinsert_msh(token, new_link);
				if (ft_split_token(token->next) == 1)
					return (1);
				content->text[state.i] = '\0';
			}
		}
		else
			state.i++;
	}
	return (0);
}

char	*ft_rm_quote(char *token)
{
	t_state	state;

	ft_init_state(&state);
	while (token && token[state.i])
	{
		if (token[state.i] == '"' || token[state.i] == '\'')
		{
			ft_isquoted(token[state.i], &state);
			token = ft_extd_token(token, "\0", state.i + 1, state.i + 1);
			state.i--;
			while (token && state.dquoted && token[state.i + 1]
				&& token[state.i + 1] != '"')
				state.i++;
			while (token && state.squoted && token[state.i + 1]
				&& token[state.i + 1] != '\'')
				state.i++;
		}
		state.i++;
	}
	return (token);
}
