/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:15:00 by sle-huec          #+#    #+#             */
/*   Updated: 2022/07/04 19:46:20 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

int	ft_pwd(void)
{
	char	*ft_pwd;

	ft_pwd = getcwd(NULL, 0);
	if (!ft_pwd)
		return (1);
	ft_fprintf(2, "%s\n", ft_pwd);
	free (ft_pwd);
	return (0);
}
