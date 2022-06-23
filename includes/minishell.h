/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:02:57 by mriant            #+#    #+#             */
/*   Updated: 2022/06/23 18:27:45 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//==============================================================================
// Lists
//==============================================================================

typedef struct s_token
{
	char			*type;
	char			*token;
	struct s_token	*prev;
	struct s_token	*next;
}			t_token;
void	ft_lstadd_back_msh(t_token **alst, t_token *new);
void	ft_lstclear_msh(t_token **lst, void (*del)(void *));
void	ft_lstdelone_msh(t_token *lst, void (*del)(void *));
t_token	*ft_lstlast_msh(t_token *lst);
t_token	*ft_lstnew_msh(char *type, char *token);

//==============================================================================
// Tokenisation
//==============================================================================

typedef struct s_state
{
	int				squoted;
	int				dquoted;
	unsigned int	i;
	unsigned int	start;
}			t_state;
void	ft_init_state(t_state *state);
void	ft_isquoted(char c, t_state *state);
t_token	*ft_tokenisation(char *input);
void	ft_trim_empty_token(t_token *tokens);

#endif