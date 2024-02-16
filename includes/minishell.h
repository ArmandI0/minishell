/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:20:46 by aranger           #+#    #+#             */
/*   Updated: 2024/02/16 19:06:49 by nledent          ###   ########.fr       */
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
# include "../lib/libft/src/libft.h"

/* typedef */

typedef	enum token
{
	CHARACTER,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	REDIRECTION_OPERATOR,
	PIPE,
	DOLLAR,
	SPACES,
}			t_token;

/* s_shell_data contains global data for the actual minishell processus */
typedef struct s_shell_data
{
	int		return_value;
	int 	ac;
	char	**av;
	char	**envp
}			t_sh_data;

/* s_command contains all options and arguments for exec */
typedef struct s_command
{
	char	*name;
	char	*path;
	char	**args;
}			t_cmd;

/* s_redir contains all redirections for one command in the right order */
typedef struct s_redir
{
	char			*file_path;
	int				in_out;
	struct s_redir	*next;
}			t_redir;

/* s_cmd_data contains all data required for redirections and execution of one cmd */
typedef struct s_list_cmd
{
	struct s_list_cmd	*previous;
	t_cmd				cmd;
	int					builtin;
	int					append_mode;
	int					here_doc;
	char				*limiter;
	t_redir				*redir;
	struct s_list_cmd	*next;
}			t_list_cmd;

/* PARSING FUNCTIONS */

void	list_of_command(int argc, char **argv);

/* BUILTINS FUNCTIONS */
void	ft_echo(char *string);

/* EXEC FUNCTION */


/* PROMPT TERMINAL FUNCTIONS */
int	prompt_rl(argc, argv, envp);

#endif
