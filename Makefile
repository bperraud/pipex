# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/19 19:18:03 by bperraud          #+#    #+#              #
#    Updated: 2022/04/19 23:13:40 by bperraud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			    = bonus.c files.c utils.c utils2.c split.c split_arg.c pipex.c get_next_line_bonus.c get_next_line_utils_bonus.c

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -Iinclude

SDIR			= src
HDIR			= include

OBJ	  			= $(SRC:.c=.o)

NAME			= pipex

all:			tmp $(NAME)

$(NAME): 		$(OBJ)
				$(CC) $(OBJ) -o $(NAME)

%.o:        	$(SDIR)/%.c
				$(CC) $(CFLAGS) -c $< -o $@

tmp:
				mkdir -p temp

clean:
				$(RM) $(OBJ)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
