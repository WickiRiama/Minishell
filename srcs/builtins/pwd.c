/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:15:00 by sle-huec          #+#    #+#             */
/*   Updated: 2022/09/15 15:51:33 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>

#include "libft.h"
#include "minishell.h"

int	ft_pwd(char **input)
{
	char	*ft_pwd;

	if (is_invalid_option(input))
		return (2);
	ft_pwd = getcwd(NULL, 0);
	if (!ft_pwd)
	{
		ft_fprintf(2, "getcwd in pwd: %s\n", strerror(errno));
		return (1);
	}
	ft_fprintf(1, "%s\n", ft_pwd);
	free (ft_pwd);
	return (0);
}
