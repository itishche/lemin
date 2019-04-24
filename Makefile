# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: itishche <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/24 10:32:21 by itishche          #+#    #+#              #
#    Updated: 2019/04/24 10:32:23 by itishche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= 	lem-in
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -I ./includes
SRC		=	./main.c

OBJ = $(SRC:.c=.o)
FT_DIR	= ./libft/
FT_LNK	= -L $(FT_DIR) -lft
all: $(NAME)

$(NAME): $(OBJ) includes/filler.h
	make -C $(FT_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(FT_LNK) -o $(NAME)

clean:
	make -C $(FT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(FT_DIR) fclean
	rm -f $(NAME)

re: fclean all
