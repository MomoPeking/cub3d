# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qdang <qdang@student.42.us.org>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/14 11:38:08 by qdang             #+#    #+#              #
#    Updated: 2020/07/21 23:01:06 by qdang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

FLAGS = -Wall -Wextra -Werror

SOURCE = main.c error.c check.c memory.c store_info.c store_texture.c store_map.c

HED = ./include/cub3d.h

LIB_PATH = ./libft
LIB_LINK = -I $(LIB_PATH) -L $(LIB_PATH) -lft

SRC_PATH = ./src
SRC = $(addprefix $(SRC_PATH)/,$(SOURCE))

OBJ = $(SOURCE:.c=.o)

$(NAME):
	@make re -C $(LIB_PATH)
	@gcc $(FLAGS) -c $(SRC) -I $(HED)
	@gcc $(LIB_LINK) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	@make clean -C $(LIB_PATH)
	@rm -f *.o

fclean: clean
	@make fclean -C $(LIB_PATH)
	@rm -f $(NAME)

re: fclean all