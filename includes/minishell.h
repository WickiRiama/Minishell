/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-huec <sle-huec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:02:57 by mriant            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/06/24 15:20:05 by sle-huec         ###   ########.fr       */
=======
/*   Updated: 2022/06/25 09:54:49 by mriant           ###   ########.fr       */
>>>>>>> Add a functionnal environment variable expansion
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef unsigned int	t_ui;

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
int		ft_add_token(t_token **tokens, t_ui start, t_ui i, char *input);
int		ft_cut_blank(t_token **tokens, t_state *state, char *input);
int		ft_cut_operator(t_token **tokens, t_state *state, char *input);
void	ft_init_state(t_state *state);
int		ft_is_blank(char c);
int		ft_is_operator(char c);
void	ft_isquoted(char c, t_state *state);
t_token	*ft_tokenisation(char *input);
t_token	*ft_trim_empty_token(t_token *tokens);

//==============================================================================
// builtins
//==============================================================================

int	ft_pwd(void);
int	ft_cd(char *path);

//==============================================================================
// Word expansion
//==============================================================================

void	ft_wexpanse(t_token **tokens, char **envp);

#endif