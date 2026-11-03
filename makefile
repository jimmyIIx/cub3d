# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nippolit <nippolit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/29 12:15:39 by nippolit          #+#    #+#              #
#    Updated: 2025/06/29 12:15:39 by nippolit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	    = 	cub3d

NAME_H		=	cub3d.h

INCLUDE	    =	-I./includes -I./libraries/libft -I./MLX42/include/MLX42

CC	 	    = 	clang
CFLAGS	    =  -Wall -Wextra -Werror -g -O3 #-fsanitize=undefined,address
CCF		    =	${CC} ${CFLAGS}

LIBMLX	= 	./MLX42
LIBFT	=	./libraries/libft
LIBS	=	$(LIBFT)/libft.a  $(LIBMLX)/build/libmlx42.a
SRCS 	=	source/main.c\
			source/game/init_game.c\
			source/init_struct/init_texture.c\
			source/init_struct/t_config.c\
			source/init_struct/t_data.c\
			source/init_struct/t_li.c\
			source/init_struct/t_map.c\
			source/init_struct/t_pl.c\
			source/init_struct/t_player.c\
			source/init_struct/t_ray.c\
			source/movement/menu.c\
			source/movement/player_move.c\
			source/movement/player_pos.c\
			source/movement/player_rotate.c\
			source/parsing/parsing.c\
			source/parsing/parse_arg/parse_args.c\
			source/parsing/parse_config/parse_config.c\
			source/parsing/parse_config/stock_pix.c\
			source/parsing/parse_config/stock_rgb.c\
			source/parsing/parse_map/parse_map.c\
			source/parsing/parse_map/stock_map.c\
			source/parsing/parse_map/check_map.c\
			source/raycasting/raycast.c\
			source/raycasting/render.c\
			source/raycasting/texture.c\
			source/utils/ft_strcpy.c\
			source/utils/ft_tablen.c\

OBJS    =	${SRCS:.c=.o}

all 	: ${NAME}

${NAME} : ${OBJS}
		@make -C ${LIBFT} --no-print-directory
		@cmake -B $(LIBMLX)/build -S $(LIBMLX)
		@cmake --build $(LIBMLX)/build -j$(nproc)
		@${CCF} ${OBJS} -o ${NAME} ${LIBS} -ldl -lglfw -pthread -lm
		@printf "$(MSG_BCOLOR_SUCCESS)compiled !$(TERM_CONTROL_RESET)\n"

%.o : %.c
		@${CCF} ${INCLUDE} -c $< -o $@
		@printf "$(MSG_BCOLOR_WARNING)compilation: $< !$(TERM_CONTROL_RESET)\n"

clean  :
		@rm -rf ${OBJS}
		@make -C ${LIBFT} clean --no-print-directory
		@rm -rf $(LIBMLX)/build
		@printf "$(MSG_BCOLOR_FAILURE)clean: $(NAME) ! $(TERM_CONTROL_RESET)\n"

fclean : clean
		@rm -rf ${NAME}
		@make -C ${LIBFT} fclean --no-print-directory

re     : fclean all

.PHONY : all, clean, fclean, re








# >>>>>>>>>> MESSAGES COLORS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

 MSG_BCOLOR_FAILURE		:=	\001\e[1;31m\002 # Rouge gras
 MSG_BCOLOR_LOGGING		:=	\001\e[1;37m\002 # Blanc gras
 MSG_BCOLOR_SUCCESS		:=	\001\e[1;32m\002 # Vert  gras
 MSG_BCOLOR_WARNING		:=	\001\e[1;33m\002 # Jaune gras


# >>>>>>>>>> TERMINAL <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

 TERM_CONTROL_CLEAR		:=	\001\e[1;1H\e[2J\002
 TERM_CONTROL_RESET		:=	\001\e[0m\002

# >>>>>>>>>> Autre <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

# ${NAME} : ${OBJS}S

# ${CCF} -o ${NAME} ${OBJS}
#            ou
# ar -rsc ${NAME} ${OBJS} $(MLX_FLAGS)

# >>>>>>>>>> FIN <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
