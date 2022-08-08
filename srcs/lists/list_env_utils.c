/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:13:00 by sle-huec          #+#    #+#             */
/*   Updated: 2022/08/08 16:59:23 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

int	ft_lstsize_env(t_env *lst)
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

t_env	*ft_lstlast_env(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstclear_env(t_env **lst, void (*del)(void *))
{
	t_env	*temp1;
	t_env	*temp2;

	temp2 = *lst;
	while (temp2)
	{
		temp1 = temp2->next;
		ft_lstdelone_env(temp2, del);
		temp2 = temp1;
	}
	*lst = NULL;
}

void	ft_lstdelone_env(t_env *lst, void (*del)(void *))
{
	if (del)
		del(lst->var);
	if (lst->prev)
		lst->prev->next = lst->next;
	if (lst->next)
		lst->next->prev = lst->prev;
	free(lst);
}
