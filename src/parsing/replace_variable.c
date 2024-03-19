/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:45:02 by aranger           #+#    #+#             */
/*   Updated: 2024/03/12 12:27:05 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*find_and_change_var(t_lexer *lx,
				t_sh_data *data, char *newline, int i);
static char	*find_var(t_sh_data *data, char *var);
static char	*return_value(t_sh_data *data, char *var);
static int	var_size(char *var);

t_lexer	*replace_variable(t_sh_data *data, t_lexer *lx)
{
	int		i;
	char	*newline;

	i = 0;
	newline = NULL;
	while (lx->entry[i])
	{
		if (lx->lexing[i] == DOLLAR)
		{
			newline = find_and_change_var(lx, data, newline, i);
			lx = replace_lexer(newline, lx);
			newline = NULL;
		}
		i++;
	}
	return (lx);
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
				break ;
			}
			tmp = tmp->next;
		}
	}
	if (value == NULL)
		value = ft_strdup("");
	return (value);
}

static int	var_size(char *var)
{
	int	size;

	size = 0;
	if (var[0] == '?')
		return (1);
	while (var[size] && check_var_char(var[size]) == TRUE)
		size++;
	return (size);
}

static char	*find_and_change_var(t_lexer *lx,
				t_sh_data *data, char *newline, int i)
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
