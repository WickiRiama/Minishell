/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 11:13:46 by mriant            #+#    #+#             */
/*   Updated: 2022/07/07 13:59:26 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*ft_find_var(char *var, t_env **envp)
{
	// int		i;
	// int		j;
	(void)var;
	(void)envp;
	
	char	*result;

	result = ft_calloc(sizeof(char), 1);
	// ICI FAIRE PARCOURT DE LIST AVEC T_ENV

	// while (envp && envp[i])
	// {
	// 	j = 0;
	// 	while (var[j] == envp[i][j])
	// 		j++;
	// 	if (var[j] == '\0' && envp[i][j] == '=')
	// 	{
	// 		free(result);
	// 		result = ft_substr(envp[i], j + 1, ft_strlen(envp[i]));
	// 		break ;
	// 	}
	// 	i++;
	// }
	// free(var);
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

char	*ft_rm_quote(char *token)
{
	int	i;

	i = 0;
	while (token && token[i])
	{
		if (token[i] == '"')
		{
			token = ft_extd_token(token, "\0", i + 1, i + 1);
			i--;
			while (token && token[i + 1] && token[i + 1] != '"')
				i++;
		}
		else if (token[i] == '\'')
		{
			token = ft_extd_token(token, "\0", i + 1, i + 1);
			i--;
			while (token && token[i + 1] && token[i + 1] != '\'')
				i++;
		}
		i++;
	}
	return (token);
}
