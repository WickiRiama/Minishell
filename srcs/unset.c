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

int	ft_unset(char **cmd, t_env **env)
{
	ft_lstdelone_env(ft_get_ptr_env_var(cmd[1], *env), &free);
	return (0);
}
