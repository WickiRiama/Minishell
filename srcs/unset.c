/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-huec <sle-huec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:17:13 by sle-huec          #+#    #+#             */
/*   Updated: 2022/07/06 14:17:14 by sle-huec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/* TEST DE DELONE*/

void	ft_unset(char **cmd, t_env **env)
{
	(void)cmd;
	t_env *tmp;
	tmp = *env;
	tmp = tmp->next;
	display_env(*env);
	ft_printf("\n////////////////////////////////////////////////////////\n\n");
	ft_lstdelone_env(tmp, &free);
	display_env(*env);
}
