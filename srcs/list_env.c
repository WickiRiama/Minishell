/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:13:00 by sle-huec          #+#    #+#             */
/*   Updated: 2022/07/25 13:53:22 by mriant           ###   ########.fr       */
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
	if (!new->var)
	{
		free(new);
		return (NULL);
	}
	new->prev = NULL;
	new->next = NULL;
	return (new);
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
