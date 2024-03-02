# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nledent <nledent@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/12 12:15:59 by aranger           #+#    #+#              #
#    Updated: 2024/03/02 18:08:58 by nledent          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-LIBFT-#

LIBFT			= ../../lib/libft
LIBFT_A			= ../../lib/libft/libft.a

#-SRC-#

SRCS			= 	UT_exec.c \
					../../src/utils/errors.c \
					../../src/utils/free_functions.c \
					../../src/utils/new_envp.c \
					../../src/utils/del_tmp_hdoc.c \
					../../src/exec/exec.c \
					../../src/exec/here_docs.c \
					../../src/exec/exit_functions.c \
					../../src/exec/pipes.c \
					../../src/builtins/echo.c \
					../../src/builtins/pwd.c \
					../../src/builtins/env.c \
					../../src/builtins/cd.c \
					../../src/builtins/export.c \
					../../src/builtins/exec_builtins.c \

OBJS		= $(SRCS:.c=.o)

#-UTILS-#

CC 				= cc
CFLAGS 			= -Wall -Wextra -Werror -g
NAME 			= unit_test
RM 				= rm -f
RMR				= rm -rf

#-RULES-#

all:			$(NAME)

$(LIBFT_A) :
				@make -C $(LIBFT)

%.o: %.c
				$(CC) $(CFLAGS)  -c -o $@ $<

$(NAME): 		$(OBJS)  $(LIBFT_A) 
				@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME) -lreadline 
				
clean:
				@$(RM) $(OBJS)
				@make -C $(LIBFT) clean

fclean: 		clean
				@$(RM) $(NAME)
				@make -C $(LIBFT) fclean

re:				fclean all

.PHONY : 		all clean fclean re bonus