/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:22:56 by mriant            #+#    #+#             */
/*   Updated: 2022/09/01 14:23:08 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <readline/readline.h>

#include "minishell.h"
#include "libft.h"

void	ft_handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n$> ");
	}
	else if (sig == SIGQUIT)
		ft_printf("\b\b  \b\b");
}

void	ft_handle_ignore(int sig)
{
	if (sig == SIGQUIT)
	{
		g_exitcode = 131;
		ft_printf("Quit (core dumped)");
	}
	if (sig == SIGINT)
		g_exitcode = 130;
	ft_printf("\n");
	return ;
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

void	ft_set_sa(t_sigaction *new_sa, t_sigaction *old_sigint,
	t_sigaction *old_sigquit)
{
	sigaction(SIGINT, new_sa, old_sigint);
	sigaction(SIGQUIT, new_sa, old_sigquit);
}

void	ft_init_all_sas(t_sas *all_sa)
{
	ft_memset(&all_sa->new_sa, 0, sizeof (all_sa->new_sa));
	ft_memset(&all_sa->old_sigint, 0, sizeof (all_sa->old_sigint));
	ft_memset(&all_sa->old_sigquit, 0, sizeof (all_sa->old_sigquit));
}
