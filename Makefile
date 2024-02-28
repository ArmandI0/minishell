# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aranger <aranger@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/12 12:15:59 by aranger           #+#    #+#              #
#    Updated: 2024/02/28 10:01:23 by aranger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-PATH FILES-#

SRC_DIR			= src
SRC_BONUS_DIR	= src_bonus
OBJ_DIR			= obj
OBJ_BONUS_DIR	= obj_bonus

#-LIBFT-#

LIBFT			= lib/libft
LIBFT_A			= lib/libft/libft.a

#-SRC-#

SRCS			= 	\
					parsing/lexer.c \
					parsing/parsing.c \
					parsing/split_lexer.c \
					parsing/manage_list_cmd.c \
					parsing/manage_error.c \
					parsing/utils_free.c \
					parsing/struct_command.c \
					parsing/find_command_path.c \
					parsing/utils.c \
					prompt_terminal/main.c \
					prompt_terminal/prompt.c \
					prompt_terminal/signals.c \
					exec/exec.c \
					exec/exit_functions.c \
					exec/here_docs.c \
					exec/pipes.c \
					builtins/exec_builtins.c \
					builtins/echo.c \
					builtins/env.c \
					builtins/pwd.c \
					utils/del_tmp_hdoc.c \
					utils/errors.c \
					utils/free_functions.c \
					utils/new_envp.c \

SRC				= $(addprefix src/, $(SRCS))
OBJS			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
D_OBJS			= mkdir -p $(@D)

#-BONUS-#

SRCS_BONUS		=	\

SRC_BONUS		= $(addprefix src_bonus/, $(SRCS_BONUS))
OBJS_BONUS		= $(SRC_BONUS:$(SRC_BONUS_DIR)/%.c=$(OBJ_BONUS_DIR)/%.o)
D_OBJS_BONUS	= mkdir -p $(@D)

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

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c
				$(D_OBJS_BONUS)
				$(CC) $(CFLAGS)  -c -o $@ $<

$(NAME): 		$(OBJS)  $(LIBFT_A) 
				@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME) -lreadline
				
clean:
				@$(RMR) $(OBJ_DIR)
				@$(RMR) $(OBJ_BONUS_DIR)
				@make -C $(LIBFT) clean

fclean: 		clean
				@$(RM) $(NAME)
				@$(RM) $(NAME_BONUS)
				@make -C $(LIBFT) fclean

re:				fclean all

bonus :			$(OBJS_BONUS) $(LIBFT_A)
				@$(RM) $(NAME)
				@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT_A) -o $(NAME)

.PHONY : 		all clean fclean re bonus