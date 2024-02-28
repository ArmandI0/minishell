/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:57:46 by aranger           #+#    #+#             */
/*   Updated: 2024/02/28 18:36:09 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*FOR TESTING*/
// cat file2 file3
// cat < file2 file3
// cat file3 < file2
// file2 cat < file3

void printList(t_list* node);

void afficher_redirs(t_bloc_cmd *cmd_bloc)
{
	ft_putstr_fd("blabla", 1);
    while (cmd_bloc != NULL) {
        t_redir *redir = cmd_bloc->redir;
        while (redir != NULL) {
			ft_putstr_fd("redir file_path :", 1);
			ft_putstr_fd(redir->file_path, 1);
			ft_putstr_fd("\n", 1);
			ft_putstr_fd("redir limiter:", 1);
			ft_putstr_fd(redir->lim_hdoc, 1);
			ft_putstr_fd("\n", 1);
            redir = redir->next;
        }
        cmd_bloc = cmd_bloc->next;
    }
}
 
void	add_new_redir(t_redir *lst, t_redir_def type, char *path, char *lim)
{
	t_redir	*tmp;

	tmp = ft_calloc(1, sizeof(t_redir));
	if (tmp == NULL)
		return ;
	tmp->type = type;
	tmp->file_path = path;
	tmp->lim_hdoc = lim;
	if (lst == NULL)
		lst = tmp;
	else
	{
		while (lst->next != NULL)
			lst = lst->next;
		lst->next = tmp;
	}
}

t_bloc_cmd	*add_new_bloc(t_bloc_cmd *lst)
{
	t_bloc_cmd	*tmp;

	tmp = ft_calloc(1, sizeof(t_bloc_cmd));
	if (lst == NULL)
		lst = tmp;
	else
	{
		while (lst->next != NULL)
			lst = lst->next;
		lst->next = tmp;
	}
	return (tmp);
}

void	redirection_parsing(t_list **args, t_sh_data *data)
{
	t_list		*tmp;
	t_bloc_cmd	*tmpbc;

	tmp = *args;
	tmpbc = add_new_bloc(data->cmd_bloc1);
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "|", 2) == 0)
			add_new_bloc(data->cmd_bloc1);
		if (tmp->next != NULL)
		{
			if (ft_strncmp(tmp->content, "<<", 3) == 0)
				add_new_redir(tmpbc->redir, HEREDOC, NULL, tmp->next->content);
			else if (ft_strncmp(tmp->content, ">>", 3) == 0)
				add_new_redir(tmpbc->redir, APPEND, tmp->next->content, NULL);
			else if (ft_strncmp(tmp->content, "<", 2) == 0)
				add_new_redir(tmpbc->redir, INPUT_REDIR, tmp->next->content, NULL);
			else if (ft_strncmp(tmp->content, ">", 2) == 0)
				add_new_redir(tmpbc->redir, OUTPUT_REDIR, tmp->next->content, NULL);
		}
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

/*#################test : <<here_doc infile cat < file1 <file2 | cat >> here | grep -a "file 1   " */

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
	
	split_cmd(lx, a);
	redirection_parsing(a, data);
	ft_lstclear(a);
	//ft_putstr_fd("jsdjkjkfdg", 1);
	afficher_redirs(data->cmd_bloc1);
	free(a);
	free_lexer(lx);
}

// void	parsing(char *line, t_sh_data *data) ////TEST
// {
// 	t_lexer		*lx;
// 	//t_bloc_cmd **lc;
// 	t_list		**a = NULL;
// 	int		i;
// 	(void)data;
// 	i = 0;
// 	lx = lexing(line);
// 	if (lx == NULL) 	
// 		return ;
// 	a = ft_calloc(1, sizeof(t_list *));	
// 	if (a == NULL)
// 		return ;
// 	ft_printf("ENTRY : -%s- \n", lx->entry);
// 	ft_printf("LEXER : -");

// 	while (lx->entry[i])
// 	{
// 		ft_printf("%d", lx->lexing[i]);
// 		i++;
// 	}
// 	ft_printf("-\n");
// 	ft_printf("NOMBRE D'ARGUMENTS : %d\n", count_argument(lx));

// 	split_cmd(lx, a);
// //	ft_printf("%p\n", *a);
// 	printf("BLABLABLA\n");
// 	printList(*a);
// 	ft_lstclear(a);
// 	free(a);
// 	free_lexer(lx);

// 	// lc = malloc(sizeof(t_bloc_cmd *));
// 	// *lc = set_new_node(lx->entry, lx->lexing, envp);
// 	// ft_printf("%s\n", (*lc)->cmd->name);
// 	// ft_printf("%s\n", (*lc)->cmd->path);
// }


/*  ##MAIN TEST : PARSING ## */

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
