# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/19 19:18:03 by bperraud          #+#    #+#              #
#    Updated: 2022/03/24 00:59:02 by bperraud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			    = main.c pipex.c files.c utils.c utils2.c process.c split.c get_next_line.c get_next_line_utils.c

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror 

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
