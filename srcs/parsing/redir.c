/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:19:18 by mriant            #+#    #+#             */
/*   Updated: 2022/09/15 16:11:26 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include "minishell.h"
#include "libft.h"

void	ft_close_old_redir(t_dlist *tokens, t_exec *blocks)
{
	if (((t_token *)tokens->cont)->type == INFILE && blocks->infile >= 0)
		blocks->infile = close(blocks->infile) - 2;
	else if (((t_token *)tokens->cont)->type == OUTFILE && blocks->outfile >= 0)
		blocks->outfile = close(blocks->outfile) - 2;
	else if (((t_token *)tokens->cont)->type == APP_FILE
		&& blocks->outfile >= 0)
		blocks->outfile = close(blocks->outfile) - 2;
	else if (((t_token *)tokens->cont)->type == DELIM && blocks->infile >= 0)
		blocks->infile = close(blocks->infile) - 2;
}

void	ft_open_redir(t_dlist *tokens, t_exec *blocks, t_env **env,
	t_sig *new_sa)
{
	if (((t_token *)tokens->cont)->type == INFILE)
		blocks->infile = open(((t_token *)tokens->cont)->text, O_RDONLY);
	else if (((t_token *)tokens->cont)->type == OUTFILE)
		blocks->outfile = open(((t_token *)tokens->cont)->text, \
			O_WRONLY | O_CREAT | O_TRUNC, 00644);
	else if (((t_token *)tokens->cont)->type == APP_FILE)
		blocks->outfile = open(((t_token *)tokens->cont)->text, \
			O_WRONLY | O_CREAT | O_APPEND, 00644);
	else if (((t_token *)tokens->cont)->type == DELIM)
		blocks->infile = ft_here_doc(tokens, env, new_sa);
	if (blocks->infile == -1 || blocks->outfile == -1)
		ft_fprintf(2, "%s: %s\n", \
			strerror(errno), ((t_token *)tokens->cont)->text);
}
