/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:33:25 by mriant            #+#    #+#             */
/*   Updated: 2022/06/14 18:44:22 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	ft_parse_cmd(char *input, t_token *token_list)
{

}

int	ft_parse_env(char *input, t_token *token_list)
{

}

int	ft_parse_dquotes(char *input, t_token *token_list)
{

}

int	ft_parse_squotes(char *input, t_token *token_list)
{

}

int	ft_parse_file(char *input, t_token *token_list)
{
	
}

int	ft_parse(char *input, t_token *token_list)
{
	int		i;
	t_token	*token_list;

	i= 0;
	token_list = NULL;
	while (input[i])
	{
		if (input[i] == '>' && input[i + 1] == '>')
			i += ft_parse_file(input + i + 2, token_list);
		else if (input[i] == '>')
			i += ft_parse_file(input + 1, token_list);
		if (input[i] == '<' && input[i + 1] == '<')
			i += ft_parse_file(input + i + 2, token_list);
		else if (input[i] == '<')
			i += ft_parse_file(input + 1, token_list);
		else if (input[i] == '$')
			i += ft_parse_env(input + 1, token_list);
		else if (input[i] == '\'')
			i += ft_parse_squotes(input + 1, token_list)
		else if (input == '\"')
			i += ft_parse_dquotes(input + 1, token_list);
		else
			i += ft_parse_cmd(input, token_list);
	}
}