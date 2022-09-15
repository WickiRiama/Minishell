/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:22:56 by mriant            #+#    #+#             */
/*   Updated: 2022/09/15 16:12:18 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <errno.h>

#include "minishell.h"
#include "libft.h"

void	ft_handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n🐱 minishell 🐈 $> ");
		g_exitcode = 130;
	}
	else if (sig == SIGQUIT)
		ft_printf("\b\b  \b\b");
}

void	ft_handle_here_doc(int sig)
{
	if (sig == SIGQUIT)
		ft_printf("\b\b  \b\b");
	if (sig == SIGINT)
	{
		g_exitcode = 130;
		close(STDIN_FILENO);
		rl_replace_line("", 1);
		ft_printf("\n");
	}
	return ;
}

void	ft_set_sa(t_sig *new_sa, void (*f)(int))
{
	sigemptyset(&new_sa->sa_mask);
	new_sa->sa_flags = SA_RESTART;
	new_sa->sa_handler = f;
	if (sigaction(SIGINT, new_sa, NULL) == -1)
		ft_fprintf(2, "sigaction %s\n", strerror(errno));
	if (sigaction(SIGQUIT, new_sa, NULL) == -1)
		ft_fprintf(2, "sigaction %s\n", strerror(errno));
}
