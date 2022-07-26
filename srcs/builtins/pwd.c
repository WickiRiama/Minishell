/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-huec <sle-huec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:15:00 by sle-huec          #+#    #+#             */
/*   Updated: 2022/07/06 10:19:12 by sle-huec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "libft.h"
#include "minishell.h"

int	ft_pwd(void)
{
	char	*ft_pwd;

	ft_pwd = getcwd(NULL, 0);
	if (!ft_pwd)
	{
		ft_fprintf(2, "pwd : %s, errno: %d\n", strerror(errno), errno);
		return (1);
	}
	ft_fprintf(2, "%s\n", ft_pwd);
	free (ft_pwd);
	return (0);
}
