# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aranger <aranger@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/12 12:15:59 by aranger           #+#    #+#              #
#    Updated: 2024/03/29 22:43:13 by aranger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-PATH FILES-#

SRC_DIR			= src
OBJ_DIR			= obj

#-LIBFT-#

LIBFT			= lib/libft
LIBFT_A			= lib/libft/libft.a

#-SRC-#

SRCS			= 	\
					parsing/lexer.c \
					parsing/parsing.c \
					parsing/split_lexer.c \
					parsing/utils_free.c \
					parsing/struct_command.c \
					parsing/find_command_path.c \
					parsing/utils.c \
					prompt_terminal/main.c \
					prompt_terminal/prompt.c \
					prompt_terminal/signals.c \
					prompt_terminal/signals_handlers.c \
					exec/exec.c \
					exec/execve.c \
					exec/here_docs.c \
					exec/here_docs_files.c \
					exec/pipes.c \
					builtins/exec_builtins.c \
					builtins/echo.c \
					builtins/env.c \
					builtins/pwd.c \
					builtins/exit.c \
					builtins/cd.c \
					builtins/export.c \
					builtins/export2.c \
					builtins/unset.c \
					utils/free_all.c \
					utils/errors.c \
					utils/print_functions.c \
					utils/print_export.c \
					utils/free_functions.c \
					utils/new_envp.c \
					utils/r_values.c \
					parsing/redirection_parse.c \
					parsing/parsing_command.c \
					parsing/lexer_checking.c \
					parsing/replace_variable.c \
					parsing/suppr_quotes.c \
					parsing/split_token.c \
					parsing/split_cmd.c \
					parsing/expand_var_for_here_doc.c \

SRC				= $(addprefix src/, $(SRCS))
OBJS			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
D_OBJS			= mkdir -p $(@D)

#-UTILS-#

CC 				= cc
CFLAGS 			= -Wall -Wextra -Werror -g
NAME 			= minishell
RM 				= rm -f
RMR				= rm -rf

#-RULES-#

all:			$(NAME)

$(LIBFT_A) :
				@make -C $(LIBFT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
				$(D_OBJS)
				$(CC) $(CFLAGS)  -c -o $@ $< 

$(NAME): 		$(OBJS)  $(LIBFT_A) 
				@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME) -lreadline

clean:
				@$(RMR) $(OBJ_DIR)
				@make -C $(LIBFT) clean

fclean: 		clean
				@$(RM) $(NAME)
				@make -C $(LIBFT) fclean

re:				fclean all

.PHONY : 		all clean fclean re