/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-huec <sle-huec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 13:25:07 by sle-huec          #+#    #+#             */
/*   Updated: 2022/07/06 13:25:16 by sle-huec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

int	ft_exit(t_token **tokens, char *input)
{
	ft_lstclear_msh(tokens, &free);
	free(input);
	exit(EXIT_SUCCESS);
}
