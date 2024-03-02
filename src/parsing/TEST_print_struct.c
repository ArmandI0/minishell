/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TEST_print_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armandanger <armandanger@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:57:46 by aranger           #+#    #+#             */
/*   Updated: 2024/03/02 14:25:00 by armandanger      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

const char* redir_def_to_string(t_redir_def redir)
{
    switch (redir) {
        case HEREDOC:
            return "HEREDOC";
        case INPUT_REDIR:
            return "INPUT_REDIR";
        case OUTPUT_REDIR:
            return "OUTPUT_REDIR";
        case APPEND:
            return "APPEND";
        default:
            return "UNKNOWN";
    }
}

void print_all_bloc(t_sh_data *a)
{
	int i = 0;
	t_bloc_cmd	*bloc;
	t_redir		*tmp;
	
	bloc = a->bloc;
	ft_printf_fd(1, "%p", bloc);
	while (bloc != NULL)
	{
		ft_printf_fd(1, "\n--------------------------------------------------------------\n");
		ft_printf_fd(1, "ID = %d // ADR %p : redir %p \n", i, bloc, bloc->redir);
		tmp = bloc->redir;
		while (tmp != NULL)
		{
			ft_printf_fd(1, "ADR=%p NEXT=%p TYPE=%s PATH=%s\n",tmp, tmp->next, redir_def_to_string(tmp->type), tmp->file_path);
			tmp = tmp->next;
		}	
		bloc = bloc->next;
		i++;
	}
	
}

void printList(t_list* node) 
{
    while (node != NULL) 
	{

        ft_printf_fd(1, "-%s-", node->content);
        node = node->next;
    }
    printf("\n");
}




