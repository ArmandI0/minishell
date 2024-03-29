/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:45:23 by nledent           #+#    #+#             */
/*   Updated: 2024/03/29 22:51:35 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_strtrim_space(char const *s1)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	if (!s1)
		return (NULL);
	while (ft_isspace(s1[i]) != 0)
		i++;
	j = ft_strlen(s1);
	while (ft_isspace(s1[j]) != 0 && j != 0)
		j--;
	if (j == 0 && s1)
	{
		str = malloc(sizeof(char));
		if (str == NULL)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	str = malloc(sizeof(char) * (j - i + 2));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, &s1[i], j - i + 2);
	return (str);
}

static char	*trim_zero(char *arg)
{
	char	*trim_arg;
	int		i;
	int		j;

	i = 0;
	j = 0;
	trim_arg = ft_calloc(sizeof(char), ft_strlen(arg) + 1);
	if (trim_arg == NULL)
		return (NULL);
	if (arg[i] == '-')
	{
		trim_arg[j] = '-';
		j++;
		i++;
	}
	while (arg[i] != '\0' && ((arg[i] == '0' && arg[i + 1] != '\0')
			|| arg[i] == '+'))
		i++;
	while (arg[i] != '\0')
	{
		trim_arg[j] = arg[i];
		i++;
		j++;
	}
	return (trim_arg);
}

static int	check_arg(char *arg)
{
	int		nb;
	int		size;
	char	*tmp;
	char	*trim_arg;

	tmp = ft_strtrim_space(arg);
	trim_arg = trim_zero(tmp);
	free(tmp);
	nb = ft_atoi(arg);
	tmp = ft_itoa(nb);
	size = ft_strlen(arg);
	if (ft_strncmp(trim_arg, tmp, size) == 0)
		return (1);
	else
		return (0);
}

int	bt_exit(t_sh_data *sh, t_cmd *cmd)
{
	int		r_value;
	t_bool	a;

	r_value = 1;
	a = FALSE;
	if (cmd->argc > 2 && check_arg(cmd->args[1]))
		print_error(ER_TOO_MANY_ARGS, cmd, NULL);
	else if (cmd->argc == 1)
		r_value = 0;
	else if (check_arg(cmd->args[1]) && cmd->argc == 2)
	{
		r_value = ft_atoi(cmd->args[1]);
		a = TRUE;
	}
	else
		r_value = 2;
	ft_printf_fd(1, "exit\n");
	if (r_value == 1 && a == FALSE)
		return (r_value);
	if (r_value == 2 && a == FALSE)
		print_error(ER_EXIT, cmd, NULL);
	free_sh_data(sh);
	exit (r_value);
}
