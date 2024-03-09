/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:45:02 by aranger           #+#    #+#             */
/*   Updated: 2024/03/09 21:09:38 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	check_var_char(char c)
{
	if (c == '_')
		return (TRUE);
	else if (c >= 'A' && c <= 'Z') 
		return (TRUE);
	else if (c >= 'a' && c <= 'z')
		return (TRUE);
	else if (c >= '0' && c <= '9')
		return (TRUE);
	return (FALSE);
}

static char	*return_value(t_sh_data *data, char *var)
{
	char	*newvar;
	char	*tmp;

	if (var[0] == '\0')
		return (ft_itoa(data->return_value));
	else
	{
		tmp = ft_strdup(var);
		newvar = ft_strjoin(ft_itoa(data->return_value), tmp, FALSE);
		return (newvar);
	}		
}

static char	*find_var(t_sh_data *data, char *var)
{
	t_env_var	*tmp;
	char		*value;

	value = NULL;
	tmp = data->env_var1;
	if (var != NULL && var[0] != '\0' && var[0] == '?')
		value = return_value(data, &var[1]);
	else
	{	
		while (tmp != NULL)
		{	
			if (ft_strncmp(tmp->name, var, ft_strlen(var) + 1) == 0)
			{
				value = ft_strdup(tmp->value);
				break;
			}
			tmp = tmp->next;
		}
	}
	if (value == NULL)
		value = ft_strdup(" ");
	return (value);
}

char	*replace_variable(t_sh_data *data, t_lexer *lx)
{
	int		i;
	int		j;
	char	*start;
	char	*var;
	char	*newline;

	i = 0;
	j = 0;
	start = lx->entry;
	newline = ft_calloc(1 , sizeof(char));
	while (lx->entry[i])
	{
		if (lx->lexing[i] == DOLLAR)
		{
			if (newline[0] == '\0')
				newline = strdup_size(start, i);
			//test == NULL
			j = 0;
			start = &lx->entry[i + 1];
			i++;
			while (check_var_char(lx->entry[i]) == TRUE)
			{
				i++;
				j++;
			}
			var = strdup_size(start, j);
			start = &lx->entry[i];
			newline = ft_strjoin(newline, find_var(data, var), TRUE);
			newline = ft_strjoin(newline, start, TRUE);
			// free(lx->entry);
			// lx->entry = newline;
		}
		i++;
	}
	if (newline[0] != '\0')
	{
		free(lx->entry);
		free(lx->lexing);
		lx->entry = newline;
		i = ft_strlen(lx->entry);
		lx->lexing = malloc(sizeof(t_token) * (i + 1));
		add_token(lx);
	}
	else
		free(newline);
	
	return (lx->entry);
}