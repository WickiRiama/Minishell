/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:03:34 by mriant            #+#    #+#             */
/*   Updated: 2022/06/16 16:20:46 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	ft_lstdelone_minishell(t_token *lst, void (*del)(void *))
{
	if (del)
	{
		del(lst->type);
		del(lst->token);
	}
	free(lst);
}

void	ft_lstclear_minishell(t_token **lst, void (*del)(void *))
{
	t_token	*temp1;
	t_token	*temp2;

	temp2 = *lst;
	while (temp2)
	{
		temp1 = temp2->next;
		ft_lstdelone(temp2, del);
		temp2 = temp1;
	}
	*lst = NULL;
}

t_token	*ft_lstlast_minishell(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	ft_lstsize_minishell(t_token *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (i);
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}