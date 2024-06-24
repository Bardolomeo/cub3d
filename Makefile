# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsapio <gsapio@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/29 16:36:33 by gsapio            #+#    #+#              #
#    Updated: 2024/06/24 20:41:52 by gsapio           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_MANDATORY	=	main.c \
					parsing/parsing.c parsing/bit_colors.c parsing/parse_elements.c \
					utils/clean_game_closure.c utils/parsing_utils.c parsing/parse_map.c utils/drawing.c utils/raycasting_utils.c \
					game/movement.c game/keys_and_mouse.c \
					graphics/ray_casting.c graphics/dda.c graphics/ray_vertical.c graphics/ray_horizontal.c \
					graphics/color_manipulation.c 

LFLAGS = -lft -L./Libft -lmlx -Lminilibx-linux -lX11 -lXext -lm -no-pie

IFLAGS = -I./Libft -I./minilibx_linux

PATH_LIBS =

MLX = "https://github.com/42Paris/minilibx-linux.git"

MLX_DIR = minilibx-linux

LIBFT_PATH = Libft

MLX_PATH = minilibx-linux

HEADER = ./

OBJS_MANDATORY	= $(SRCS_MANDATORY:.c=.o)

# BONUS			=

CC				= gcc -g

RM				= rm -f

CFLAGS			= -Wall -Wextra -Werror

NAME			= cub3D

# BONUS_NAME		=

all:			$(NAME)

call_mlx:
				echo "$(GREEN)Cloning 'mlx' via HTTP into './mlx'...$(DEF_COLOR)"; \
				git clone https://github.com/42Paris/minilibx-linux minilibx-linux;


$(NAME):		$(MLX_DIR) $(SRCS_MANDATORY)
				make -C $(LIBFT_PATH) --no-print-directory
				make bonus -C $(LIBFT_PATH) --no-print-directory
				make -C $(MLX_PATH) --no-print-directory
				$(CC) $(CFLAGS) $(SRCS_MANDATORY) $(LFLAGS) $(IFLAGS) -o $(NAME)

$(MLX_DIR):
				@git clone $(MLX)
				@cd $(MLX_DIR) && ./configure


$(BONUS_NAME):	$(SRCS_BONUS)
				make -C $(LIBFT_PATH) --no-print-directory
				make -C $(MLX_PATH) --no-print-directory
				$(CC) $(CFLAGS) $(SRCS_BONUS) -o $(BONUS_NAME) Bonus/so_long_bonus.c $(PATH_LIBS) $(LFLAGS)

bonus:			$(BONUS_NAME)

clean:
				$(RM)

fclean:			clean
				$(RM) $(NAME)
				$(RM) -r ./mlx
				$(RM) $(NAME)_bonus
				$(RM) $(LIBFT_PATH)/*.o
				$(RM) $(LIBFT_PATH)/*.a
				$(RM) $(MLX_PATH)/*.o
				$(RM) $(MLX_PATH)/*.a

re:				fclean $(NAME)

.PHONY:			all clean fclean re bonus
