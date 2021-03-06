# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/19 19:18:03 by bperraud          #+#    #+#              #
#    Updated: 2022/04/07 01:45:36 by bperraud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			    = main.c pipex.c files.c utils.c utils2.c split.c split_arg.c process.c
SRCB			= pipex.c files.c utils.c utils2.c split.c split_arg.c process.c
BONUS			= bonus.c pipex_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror 

SDIR			= src
HDIR			= include
ODIR			= objs

OBJ	  			= $(SRC:.c=.o)
OBJB 			= $(SRCB:c=o)
BONUS_OBJ		= $(BONUS:.c=.o)

NAME			= pipex

all:			tmp $(NAME)

$(NAME): 		$(OBJ)
				$(CC) $(OBJ) -o $(NAME)

%.o:        	$(SDIR)/%.c
				$(CC) $(CFLAGS) -c $< -o $@

tmp:
				mkdir -p temp

clean:			
				$(RM) $(OBJ) $(BONUS_OBJ) $(OBJB)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

bonus:			$(OBJB) $(BONUS_OBJ)
				$(CC) $(OBJB) -o $(NAME) $(BONUS_OBJ)

.PHONY:			all clean fclean re 
