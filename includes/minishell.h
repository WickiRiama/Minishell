/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-huec <sle-huec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:02:57 by mriant            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/07/07 12:11:58 by sle-huec         ###   ########.fr       */
=======
/*   Updated: 2022/07/07 09:56:45 by mriant           ###   ########.fr       */
>>>>>>> Add a structure to hold all informations about one command and a structure to hold informations about pipes
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef unsigned int	t_ui;
extern int				g_exitcode;

//==============================================================================
// Lists
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
	char			*token;
	struct s_token	*prev;
	struct s_token	*next;
}			t_token;
void	ft_lstadd_back_msh(t_token **alst, t_token *new);
void	ft_lstclear_msh(t_token **lst, void (*del)(void *));
void	ft_lstdelone_msh(t_token *lst, void (*del)(void *));
t_token	*ft_lstlast_msh(t_token *lst);
t_token	*ft_lstnew_msh(t_types type, char *token);

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
int		ft_token_types(t_token *tokens);
t_token	*ft_trim_empty_token(t_token *tokens);

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
	struct s_pipe	*prev;
	struct s_pipe	*next;	
}				t_pipe;
typedef struct s_exec
{
	char 			**cmd;
	int				infile;
	int				outfile;
	struct s_exec	*prev;
	struct s_exec	*next;
}			t_exec;

#endif