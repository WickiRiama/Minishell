/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:38:12 by mriant            #+#    #+#             */
/*   Updated: 2022/06/22 16:30:29 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

int	ft_isquoted(int squoted, int dquoted)
{
	if (squoted == 1 || dquoted == 1)
		return (1);
	return (0);
void	ft_trim_empty_token(t_token *tokens)
{
	t_token	*temp;
	
	while (tokens)
	{
		if (tokens->token[0] == '\0')
		{	temp = tokens;
			tokens = tokens->next;
			ft_lstdelone_msh(temp, &free);
		}
		else
			tokens = tokens->next;
	}
}