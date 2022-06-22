/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:03:34 by mriant            #+#    #+#             */
/*   Updated: 2022/06/22 15:30:01 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	ft_lstdelone_msh(t_token *lst, void (*del)(void *))
{
	if (del)
	{
		// del(lst->type);
		del(lst->token);
	}
	if (lst->prev)
		lst->prev->next = lst->next;
	if (lst->next)
		lst->next->prev = lst->prev;
	free(lst);
}

void	ft_lstclear_msh(t_token **lst, void (*del)(void *))
{
	t_token	*temp1;
	t_token	*temp2;

	temp2 = *lst;
	while (temp2)
	{
		temp1 = temp2->next;
		ft_lstdelone_msh(temp2, del);
		temp2 = temp1;
	}
	*lst = NULL;
}

t_token	*ft_lstlast_msh(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	ft_lstsize_msh(t_token *lst)
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