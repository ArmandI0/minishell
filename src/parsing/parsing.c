/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:57:46 by aranger           #+#    #+#             */
/*   Updated: 2024/02/28 14:46:03 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*FOR TESTING*/
// cat file2 file3
// cat < file2 file3
// cat file3 < file2
// file2 cat < file3

void printList(t_list* node);

void	redirection_parsing(t_list **args, t_sh_data *data)
{
	t_list	*tmp;

	(void)data;
	tmp = *args;
	while (tmp != NULL && tmp->content[0] != '|')
	{
		if (ft_strncmp(tmp->content, "<<", 3) == 0)
			ft_printf("<<");
		else if (ft_strncmp(tmp->content, ">>", 3) == 0)
			ft_printf(">>");
		else if (ft_strncmp(tmp->content, "<", 2) == 0)
			ft_printf("<");
		else if (ft_strncmp(tmp->content, ">", 2) == 0)
			ft_printf(">");
		tmp = tmp->next;
	}
}

int	count_argument(t_lexer *lx)
{
	int	i;
	int a;
	int	count;

	i = 0;
	a = 0;
	count = 0;
	while (lx->entry[i])
	{
		if (lx->lexing[i] != 0 && lx->lexing[i] != SPACES)
		{
			count++;
			a = 0;
		}
		if (lx->lexing[i] == 0 && a == 0)
		{
			count++;
			a = 1;
		}
		i++;
	}
	return (count);
}
void	split_cmd(t_lexer *lx, t_list **args)
{
	size_t		i;
	size_t		j;
	size_t		size;
	t_token	tmp;
	t_list	*new_arg;

	i = 0;
	while (i < ft_strlen(lx->entry))
	{
		size = 0;
		j = i;
		tmp = lx->lexing[i];
		if (lx->lexing[i] != SPACES)
		{
			while (lx->lexing[j] == tmp)
			{
				size++;
				j++;
			}
			new_arg = ft_lstnew(strdup_size(&lx->entry[i], size));
			ft_lstadd_back(args, new_arg);
		}
		else
			i++;
		i += size;
	}
}

t_bloc_cmd	*set_new_node(char *line, t_token *tline, char **envp)
{
	int			i;
	t_bloc_cmd	*n_node;
	t_bool		operator;

	i = 0;
	operator = FALSE;
	n_node = ft_calloc(1, sizeof(t_bloc_cmd));
	while (line[i] != '\0' && tline[i] != PIPE)
	{
		if (operator == FALSE && n_node->cmd == NULL && tline[i] == CHARACTER)
			n_node->cmd = init_command_struct(&line[i], &tline[i], envp);
		i++;
	}	
	return (n_node);
}

/*################################## test : <<here_doc infile cat < file1 <file2 | cat >> here | grep -a "file 1   "*/

void	parsing(char *line, t_sh_data *data)
{
	t_lexer		*lx;
	//t_bloc_cmd **lc;
	t_list		**a = NULL;
	int		i;
	(void)data;
	i = 0;
	lx = lexing(line);
	if (lx == NULL) 	
		return ;
	a = ft_calloc(1, sizeof(t_list *));	
	if (a == NULL)
		return ;
	ft_printf("ENTRY : -%s- \n", lx->entry);
	ft_printf("LEXER : -");

	while (lx->entry[i])
	{
		ft_printf("%d", lx->lexing[i]);
		i++;
	}
	ft_printf("-\n");
	ft_printf("NOMBRE D'ARGUMENTS : %d\n", count_argument(lx));

	split_cmd(lx, a);
//	ft_printf("%p\n", *a);
	printf("BLABLABLA\n");
	printList(*a);
	ft_lstclear(a);
	free_lexer(lx);

	// lc = malloc(sizeof(t_bloc_cmd *));
	// *lc = set_new_node(lx->entry, lx->lexing, envp);
	// ft_printf("%s\n", (*lc)->cmd->name);
	// ft_printf("%s\n", (*lc)->cmd->path);
}


/*  ################### MAIN TEST : PARSING ###################  */

void printList(t_list* node) 
{
    while (node != NULL) 
	{
	//	ft_printf("%p\n", node->prev);
        ft_printf("-%s-", node->content);
	//	ft_printf("%p\n", node->next);
	//	ft_printf("\n");
        node = node->next;
    }
    printf("\n");
}

// int main(int argc, char **argv, char **envp)
// {
// 	char	*all_arg;
// 	int		i;
	
// 	i = 1;
// 	if (argc < 2)
// 		return (0);					
// 	all_arg = ft_calloc(1, sizeof(char));
// 	while (argv[i])
// 	{
// 		all_arg = ft_strjoin(all_arg, argv[i], TRUE);
// 		if (argv[i + 1] != NULL)
// 			all_arg = ft_strjoin(all_arg, " ", TRUE);
// 		i++;
// 	}
// 	parsing(all_arg, envp);	
// }
