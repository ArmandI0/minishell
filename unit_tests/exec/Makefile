# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nledent <nledent@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/12 12:15:59 by aranger           #+#    #+#              #
#    Updated: 2024/02/23 15:05:46 by nledent          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-LIBFT-#

LIBFT			= ../../lib/libft
LIBFT_A			= ../../lib/libft/libft.a

#-SRC-#

SRCS			= 	UT_exec.c \
					errors.c \
					exec.c \
					exit_functions.c \
					free_functions.c \
					here_docs.c \
					pipes.c \

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