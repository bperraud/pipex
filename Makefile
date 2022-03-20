# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/19 19:18:03 by bperraud          #+#    #+#              #
#    Updated: 2022/03/20 02:48:21 by bperraud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			    = main.c pipex.c parsing.c utils.c split.c

CC				= gcc
RM				= rm -f
#CFLAGS			= -Wall -Wextra -Werror 

SDIR			= src
HDIR			= include
ODIR			= objs

OBJ	  			= $(SRC:.c=.o)

NAME			= pipex

all:			$(NAME)

$(NAME): 		$(OBJ)
				$(CC) $(OBJ) -o $(NAME)

%.o:        	$(SDIR)/%.c
				$(CC) $(CFLAGS) -c $< -o $@
				
clean:
				$(RM) $(OBJ)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re 
