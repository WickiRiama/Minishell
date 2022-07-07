/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-huec <sle-huec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:02:57 by mriant            #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2022/07/07 12:11:58 by sle-huec         ###   ########.fr       */
=======
/*   Updated: 2022/07/07 09:56:45 by mriant           ###   ########.fr       */
>>>>>>> Add a structure to hold all informations about one command and a structure to hold informations about pipes
=======
/*   Updated: 2022/07/07 12:16:50 by mriant           ###   ########.fr       */
>>>>>>> Start to modify lists functions to be able to use them on different double lists.
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef unsigned int	t_ui;
extern int				g_exitcode;

//==============================================================================
// Lists
//==============================================================================

typedef struct s_dlist
{
	void			*cont;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}			t_dlist;
void	ft_lstadd_back_msh(t_dlist **alst, t_dlist *new);
void	ft_lstclear_msh(t_dlist **lst, void (*del)(void *));
void	ft_lstdelone_msh(t_dlist *lst, void (*del)(void *));
t_dlist	*ft_lstlast_msh(t_dlist *lst);
t_dlist	*ft_lstnew_msh(void *content);

//==============================================================================
// Tokenisation
//==============================================================================

typedef enum e_types
{
	WORD,
	OPERATOR,
	QUOTE_ERR,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
	INFILE,
	OUTFILE,
	DELIM,
	APP_FILE,
	PIPE
}			t_types;
typedef struct s_token
{
	t_types			type;
	char			*text;
}			t_token;
typedef struct s_state
{
	int				squoted;
	int				dquoted;
	unsigned int	i;
	unsigned int	start;
}			t_state;
int		ft_add_token(t_dlist **tokens, t_ui start, t_ui i, char *input);
int		ft_cut_blank(t_dlist **tokens, t_state *state, char *input);
int		ft_cut_operator(t_dlist **tokens, t_state *state, char *input);
void	ft_del_token(void *content);
void	ft_init_state(t_state *state);
int		ft_is_blank(char c);
int		ft_is_operator(char c);
void	ft_isquoted(char c, t_state *state);
t_dlist	*ft_dlistisation(char *input);
int		ft_dlist_types(t_dlist *tokens);
t_dlist	*ft_trim_empty_token(t_dlist *tokens);

//==============================================================================
// builtins
//==============================================================================

int		ft_pwd(void);
int		ft_cd(char **path);
int		ft_echo(char **input);
int		ft_exit(t_token **tokens, char **input, char **env);
char	**copy_envp_in_tab(char **envp);
void	display_env(char **env);

//==============================================================================
// utils
//==============================================================================

void	free_tab(char **tab);

//==============================================================================
// Word expansion
//==============================================================================

char	*ft_extd_token(char *src, char *env_var, int start_var, int end_var);
char	*ft_find_var(char *var, char **envp);
int		ft_is_name(char c, t_state *state);
char	*ft_rm_quote(char *token);
int		ft_wexpanse(t_token **tokens, char **envp);

//==============================================================================
// Parsing
//==============================================================================

typedef struct s_pipe
{
	int				pipe_in;
	int				pipe_out;
}				t_pipe;
typedef struct s_exec
{
	char			**cmd;
	int				infile;
	int				outfile;
}			t_exec;

#endif