/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:20:46 by aranger           #+#    #+#             */
/*   Updated: 2024/03/09 20:10:47 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <signal.h>
# include "../lib/libft/src/libft.h"
# define TRUE 1
# define FALSE 0

typedef int t_bool;

/* typedef */

typedef	enum mn_errors
{
	ER_EXECVE,
	ER_CMD_N_FOUND,
	ER_NO_ARG,
	ER_PARS_QUOTE,
	ER_PARS_REDIR,
	ER_CD_DIR_FILE_N_FOUND,
	ER_HDOC_EOF,
	ER_TOO_MANY_ARGS,
	ER_EXPORT,
	ER_UNSET,
}			t_errors;

typedef	enum e_redir_def
{
	HEREDOC,
	INPUT_REDIR,
	OUTPUT_REDIR,
	APPEND,
}			t_redir_def;

typedef	enum token
{
	T_NULL,
	CHARACTER,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	REDIRECTION_OPERATOR,
	PIPE,
	DOLLAR,
	SPACES,
	SPLIT,
}			t_token;

typedef	enum builtin
{
	BT_NO,
	BT_ECHO,
	BT_CD,
	BT_PWD,
	BT_EXPORT,
	BT_UNSET,
	BT_ENV,
	BT_EXIT,
}			t_builtin;

/* STRUCTURE POUR LE LEXER */

typedef struct s_lexer
{
	char *entry;
	t_token	*lexing;
}				t_lexer;

/* s_env_var liste pour stocker variables d'environnement */
/* exported : 0 = oui ; 1 = non */
typedef struct s_env_var
{
	char				*name;
	char				*value;
	int					exported;
	struct s_env_var	*next;
}			t_env_var;


/* s_command contains all options and arguments for exec */
typedef struct s_command
{
	char	*name;
	char	*path;
	char	**args;
	int		argc;
}			t_cmd;

/* s_redir contains all redirections for one command in the right order */
/* in_out : 0 = in ; 1 = out - */
/* app_mod_: 0 = oui ; 1 = non */
/* bien initialiser chaque pointeur */
typedef struct s_redir
{
	char			*file_path;
	t_redir_def		type;
	char			*lim_hdoc;
	struct s_redir	*prev;
	struct s_redir	*next;
}			t_redir;

/* s_cmd_data contains all data required for redirections and execution of one cmd */
/* builtin : 0 = oui ; 1 = non - */
/* bien initialiser chaque pointeur */
typedef struct s_bloc_cmd
{
	int					id;
	t_cmd				*cmd;
	t_builtin			builtin;
	t_redir				*redir;
	struct s_bloc_cmd	*prev;
	struct s_bloc_cmd	*next;
}			t_bloc_cmd;

/* s_shell_data contains global data for the actual minishell processus */
typedef struct s_shell_data
{
	int			return_value;
	int 		ac;
	char		**av;
	char		**envp;
	t_bloc_cmd	*bloc;
	char		*dir_tmp_files;
	t_env_var	*env_var1;
	int			n_env_var;
}			t_sh_data;

/* PARSING FUNCTIONS */

char	*find_command_path(char **envp, char *command);
t_lexer	*lexing(char *line);
void add_token(t_lexer *lx);

t_cmd	*init_command_struct(char *arg, t_token *t_arg, char **envp);
void	free_lexer(t_lexer *lx);
t_bool	check_path_acces(char *path);
void	quote_error(t_lexer *lx);
char	**split_lexer(t_lexer *lx, t_token sep, char c);
char	*strdup_size(const char *src, size_t size);
t_bool	parsing(char *line, t_sh_data *data);
void	free_node(t_list *node);
void	redirection_parsing(t_list **args, t_sh_data *data);
void	command_parsing(t_list **args, t_sh_data *data);
void	replace_var(t_list **args, t_sh_data *data);
t_bool	lexer_checking(t_lexer *lx);
char	*replace_variable(t_sh_data *data, t_lexer *lx);
void	suppr_quotes(t_list **args);
char	**split_token(t_lexer *lx, t_token sep);



/* FONCTION POUR TEST LE PARSING*/

void	print_all_bloc(t_sh_data *a);
void	printList(t_list* node);
void	print_lexer(t_lexer *lx);

/* BUILTINS FUNCTIONS */

void	bt_echo(t_cmd *echo_cmd);
void	bt_env(t_sh_data *sh_data);
int		bt_pwd(void);
char	*ft_getcwd(void);
int	    bt_cd(t_sh_data *sh, t_cmd *cd);
int		exec_bt(t_sh_data *sh_data, t_bloc_cmd *cmd_bloc);
int		bt_export(t_sh_data *sh, t_cmd *cmd);
int		check_var_name(char *name);
int		bt_unset(t_sh_data *sh, t_cmd *unset);
int		bt_exit(t_sh_data *sh, t_cmd *cmd);

/* EXEC FUNCTION */

int		exec_cmds_loop(t_sh_data *sh_data);
void	launch_hdocs(t_sh_data *sh,t_bloc_cmd *cmds);
void	close_pipes(int pipe_x[2]);
void	pipes_redir(t_sh_data *sh, int out[2], int in[2], t_bloc_cmd *bloc);
int		redirections(t_bloc_cmd *bloc_data);
int		one_bloc_bt(t_sh_data *sh_data, t_bloc_cmd *cmd_bloc);

/* FREE FUNCTIONS */

void	free_tabchar(char **tabchar);
void	free_cmd(t_cmd *cmd);
void	free_redir(t_redir *redir);
void 	free_env_var(t_env_var *var1);
void	free_list_cmd(t_bloc_cmd *cmd_data);
void	free_sh_data(t_sh_data *sh);
void	free_one_env_var(t_env_var *var);

/* PROMPT TERMINAL FUNCTIONS */

int		prompt_rl(t_sh_data *sh_data);

/* SIGNALS FUNCTIONS */

void	init_signals(void);
void	re_init_def_signals(void);
void    ign_sigint(void);

/* UTILS FONCTIONS */
void	print_error(t_errors error, t_cmd *cmd, char *str);
void	del_tmp_hdocs(t_sh_data *sh);
int		add_env_var(t_sh_data *sh, char *name, char *value);
void	envp_to_list(t_sh_data *sh_data);
char	**list_to_envp(t_sh_data *sh_data);
void	print_env(t_sh_data *sh_data);
void	print_tabchar(char **tabchar);
int   	upd_env_var(t_sh_data *sh, char *name_var, char *new_value);

#endif
