/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-huec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:13:00 by sle-huec          #+#    #+#             */
/*   Updated: 2022/07/12 16:13:09 by sle-huec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

t_env	*ft_lstnew_env(char *env_var)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->var = ft_strdup(env_var);
	if (!env_var)
	{	
		free(new);
		return (NULL);
	}
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_env	*ft_lstlast_env(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_env(t_env **alst, t_env *new)
{
	t_env	*last;

	if (!new)
		return ;
	if (!(*alst))
		*alst = new;
	else
	{
		last = ft_lstlast_env(*alst);
		last->next = new;
		new->prev = last;
	}
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
