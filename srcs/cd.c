/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-huec <sle-huec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:03:57 by sle-huec          #+#    #+#             */
/*   Updated: 2022/06/24 11:57:49 by sle-huec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "libft.h"
#include "minishell.h"

int	ft_cd(char *path)
{
	if (chdir(path) < 0)
	{
		ft_fprintf(2, strerror(errno));
		return (1);
	}
	return (0);
}