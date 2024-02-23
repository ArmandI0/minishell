/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:20:46 by aranger           #+#    #+#             */
/*   Updated: 2024/02/23 15:35:41 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include "../lib/libft/src/libft.h"
#define TRUE 1
#define FALSE 0

/* typedef */

typedef int t_bool;

/* TOKEN for lexer*/

typedef enum e_token
{
	CHARACTER,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	REDIRECTION_OPERATOR,
	PIPE,
	DOLLAR,
	IS_SPACE,
	END,
} t_token;

typedef struct s_lexer
{
	char *entry;
	t_token	*lexing;
}				t_lexer;

typedef enum e_builtin
{
	BT_NO,
	BT_ECHO,
	BT_CD,
	BT_PWD,
	BT_EXPORT,
	BT_UNSET,
	BT_ENV,
	BT_EXIT,
} t_builtin;

/* s_env_var liste pour stocker variables d'environnement */
/* exported : 0 = oui ; 1 = non */

typedef struct s_env_var
{
	char *name;
	char *value;
	t_bool exported;
	struct s_env_var *next;
} t_env_var;

/* s_shell_data contains global data for the actual minishell processus */
typedef struct s_shell_data
{
	int return_value;
	int ac;
	char **av;
	char **envp;
} t_sh_data;

/* s_command contains all options and arguments for exec */

typedef struct s_command
{
	char *name;
	char *path;
	char **args;
	int argc;
} t_cmd;

/* s_redir contains all redirections for one command in the right order */
/* in_out : 0 = in ; 1 = out - */
/* app_mod_: 0 = oui ; 1 = non */
/* bien initialiser chaque pointeur */

typedef struct s_redir
{
	char *file_path;
	t_bool in_out;
	t_bool app_mod;
	struct s_redir *next;
} t_redir;

/* s_cmd_data contains all data required for redirections and execution of one cmd */
/* builtin : 0 = oui ; 1 = non - */
/* bien initialiser chaque pointeur */

typedef struct s_list_cmd
{
	int id;
	char *limiter;
	char *hdoc;
	t_cmd cmd;
	t_builtin builtin;
	t_redir *redir;
	struct s_list_cmd *prev;
	struct s_list_cmd *next;
} t_list_cmd;

void		*lst_cmd_new(size_t size);
void		lst_cmd_add_back(t_list_cmd **lst, t_list_cmd *new);

/* PARSING FUNCTIONS */

t_lexer *lexing(char *line);
void	parsing(t_lexer	*entry);
char	**split_lexer(t_lexer *lx, t_token sep, char c);
void		quote_error(t_lexer *lx);
void	free_lexer(t_lexer *lx);

/* BUILTINS FUNCTIONS */

void bt_echo(t_cmd *echo_cmd);

/* EXEC FUNCTION */
int exec_cmds_loop(t_sh_data *sh_data, t_list_cmd *list_cmds);
void launch_hdocs(t_list_cmd *list_cmds);

/* FREE FUNCTIONS*/
void free_tabchar(char **tabchar);
void free_cmd(t_cmd *cmd);

/* PROMPT TERMINAL FUNCTIONS */
int		prompt_rl(void);

#endif
