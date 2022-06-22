/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:02:57 by mriant            #+#    #+#             */
/*   Updated: 2022/06/22 11:42:37 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_token
{
	char			*type;
	char			*token;
	struct s_token	*prev;
	struct s_token	*next;
}			t_token;

//==============================================================================
// Lists
//==============================================================================

void	ft_lstadd_back_msh(t_token **alst, t_token *new);
void	ft_lstclear_msh(t_token **lst, void (*del)(void *));
t_token	*ft_lstlast_msh(t_token *lst);
t_token	*ft_lstnew_msh(char *type, char *token);

//==============================================================================
// Tokenisation
//==============================================================================

int	ft_isquoted(int squoted, int dquoted);
t_token	*ft_tokenisation(char *input);

#endif