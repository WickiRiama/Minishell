/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:02:57 by mriant            #+#    #+#             */
/*   Updated: 2022/07/14 14:25:56 by mriant           ###   ########.fr       */
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
int		ft_token_types(t_dlist *tokens);
t_dlist	*ft_tokenisation(char *input);
int		ft_dlist_types(t_dlist *tokens);
t_dlist	*ft_trim_empty_token(t_dlist *tokens);

//==============================================================================
// builtins
//==============================================================================

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
	struct s_env	*prev;
}			t_env;

int		ft_pwd(void);
int		ft_cd(char **path, t_env **env);
int		ft_echo(char **input);
int		ft_exit(char **cmd, t_dlist **blocks, t_dlist **pipes, t_env **env);
char	*get_env_var(char **envp, t_env **env);
void	display_env(t_env *env);

//==============================================================================
// utils_list_env
//==============================================================================

t_env	*ft_lstnew_env(char *env_var);
t_env	*ft_lstlast_env(t_env *lst);
void	ft_lstadd_back_env(t_env **alst, t_env *new);
void	ft_lstclear_env(t_env **lst, void (*del)(void *));
void	ft_lstdelone_env(t_env *lst, void (*del)(void *));

//==============================================================================
// utils
//==============================================================================

void	free_tab(char **tab);

//==============================================================================
// Word expansion
//==============================================================================

char	*ft_extd_token(char *src, char *env_var, int start_var, int end_var);
char	*ft_find_var(char *var, t_env *envp);
int		ft_is_name(char c, t_state *state);
char	*ft_rm_quote(char *token);
int		ft_wexpanse(t_dlist **tokens, t_env **envp);

//==============================================================================
// Parsing
//==============================================================================

typedef struct s_pipe
{
	int				pipe_to_read_from;
	int				pipe_to_write_to;
	struct s_pipe	*prev;
	struct s_pipe	*next;
}				t_pipe;
typedef struct s_exec
{
	char			**cmd;
	int				infile;
	int				outfile;
	struct s_exec	*prev;
	struct s_exec	*next;
}			t_exec;
int		ft_add_block(t_dlist *tokens, t_dlist **blocks);
int		ft_add_pipe(t_dlist **pipes);
t_dlist	*ft_cmd_orga(t_dlist *tokens, t_dlist **pipes);
int		ft_copy_tab(char **dest, char **src);
void	ft_del_blocks(void *content);
void	ft_del_pipes(void *content);
void	ft_open_redir(t_dlist *tokens, t_exec *blocks);
t_dlist	*ft_parsing(t_dlist **pipes, t_env **env);
char	**ft_update_cmd(char **cmd, char *new);

//==============================================================================
// Executor
//==============================================================================

int		ft_executor(t_dlist	*blocks, t_dlist *pipes, t_env *env, char **envp);
int		ft_run_builtin(char **cmd, t_env *env, t_dlist **blocks,
			t_dlist **pipes);

#endif
