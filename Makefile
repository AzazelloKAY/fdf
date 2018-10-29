# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akokoshk <akokoshk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/16 20:46:24 by akokoshk          #+#    #+#              #
#    Updated: 2018/01/16 21:26:42 by akokoshk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Wextra -Werror
MLXFLAG = -lmlx -framework OpenGL -framework AppKit
NAME = fdf
SOURCES = fdffunctions.c fdfmain.c fdfmakeres.c fdfperspective.c ft_brez.c \
fdfkeyhooks.c fdfmakeimg.c fdfparser.c fdfrotation.c
OBJECTS = $(SOURCES:.c=.o)
LIBFOLDER = libft

all: $(NAME)

%.o : %.c
	@$(CC) $(FLAGS) -o $@ -c $<

$(NAME): $(OBJECTS)
	@make -C $(LIBFOLDER)
	@$(CC) $(FLAGS) $(MLXFLAG) $(OBJECTS) -L $(LIBFOLDER) -lft -o $(NAME)
	@echo "FDF compiled"

clean:
	@rm -f $(OBJECTS)
	@make clean -C $(LIBFOLDER)
	@echo "fdf cleaned"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFOLDER)
	@echo "fdf fcleaned"

re:	fclean all
