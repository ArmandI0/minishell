/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:45:02 by aranger           #+#    #+#             */
/*   Updated: 2024/03/10 14:13:45 by aranger          ###   ########.fr       */
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
		value = ft_strdup("");
	return (value);
}

//char	*set_newline(t_sh_data *data, char *start, char *end)

int		var_size(char *var)
{
	int size;

	size = 0;
	if (var[0] == '?')
		return (1);
	while (var[size] && check_var_char(var[size]) == TRUE)
		size++;
	return (size);
}

t_lexer	*set_lexer_entry(t_lexer *lx , char *newline)
{
	int	size;

	if (newline[0] != '\0')
	{
		free(lx->entry);
		free(lx->lexing);
		lx->entry = newline;
		size = ft_strlen(lx->entry);
		lx->lexing = malloc(sizeof(t_token) * (size + 1));
		if (lx->lexing == NULL)
		{
			free(newline);
			return (NULL);
		}
		add_token(lx);
		return (lx);
	}
	else
	{
		free(newline);
		return (lx);
	}

}

t_lexer	*replace_lexer(char *new_entry, t_lexer *lx)
{
	int	size;

	size = ft_strlen(new_entry);
	if (lx != NULL)
	{
		free(lx->lexing);
		free(lx->entry);
		lx->lexing = malloc(sizeof(t_token) * (size + 1));
		if (lx->lexing == NULL)
			return (NULL);
		lx->entry = new_entry;
		add_token(lx);
		return (lx);
	}
	return (NULL);
}

char	*find_and_change_var(t_lexer *lx, t_sh_data *data, char *newline, int i)
{
	int		size;
	char	*var;

	if (newline == NULL)
	{
		newline = strdup_size(lx->entry, i);
		if (newline == NULL)
			return (NULL);
	}
	size = var_size(&lx->entry[i + 1]);
	var = strdup_size(&lx->entry[i + 1], size);
	if (var == NULL)
		return (NULL);
	newline = ft_fstrjoin(newline, find_var(data, var));
	if (newline == NULL)
	{
		free(var);
		return (NULL);
	}
	newline = ft_strjoin(newline, &lx->entry[i + size + 1], TRUE);
	free (var);
	return (newline);
}

t_lexer	*replace_variable(t_sh_data *data, t_lexer *lx)
{
	int		i;
	//int		size;
	char	*start;
	//char	*var;
	char	*newline;

	i = 0;
	start = lx->entry;
	newline = NULL;
	while (lx->entry[i])
	{
		if (lx->lexing[i] == DOLLAR)
		{
			newline = find_and_change_var(lx, data, newline, i);
			lx = replace_lexer(newline, lx);
			newline = NULL;
			//i = 0;
			// if (newline[0] == '\0')
			// 	newline = strdup_size(start, i);
			// size = var_size(&lx->entry[i + 1]);
			// var = strdup_size(&lx->entry[i + 1], size);
			// start = &lx->entry[i + size + 1];
			// newline = ft_strjoin(newline, find_var(data, var), TRUE);
			// newline = ft_strjoin(newline, start, TRUE);
		}
		i++;
	}
//	lx = set_lexer_entry(lx, newline);
	return (lx);
}
