/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:20:46 by aranger           #+#    #+#             */
/*   Updated: 2024/02/12 17:25:55 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define TRUE 1
# define FALSE 0
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include "../lib/libft/src/libft.h"

/* TYPEDEF */

typedef int	t_bool;


/* s_command contains all options and arguments for exec */
typedef struct s_command
{
	char	*name;
	char	*path;
	char	**args;
}			t_cmd;

/* PARSING FUNCTIONS */




/* EXEC FUNCTION */



#endif