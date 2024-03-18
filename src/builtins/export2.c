/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:45:23 by nledent           #+#    #+#             */
/*   Updated: 2024/03/18 20:29:06 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_var_name(char *name)
{
	int	i;

	i = 0;
	if (name == NULL)
		return (1);
	else if ((name[0] <= '9' && name[0] >= '0') || name[0] == '=')
		return (1);
	while (name[i] != 0)
	{
		if (name[i] == '_')
			i++;
		else if (name[i] >= 'A' && name[i] <= 'Z')
			i++;
		else if (name[i] >= 'a' && name[i] <= 'z')
			i++;
		else if (name[i] >= '0' && name[i] <= '9')
			i++;
		else if (name[i] == '=')
			return (0);
		else
			return (1);
	}
	return (0);
}
