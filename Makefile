# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/29 16:36:33 by gsapio            #+#    #+#              #
#    Updated: 2024/05/13 17:45:19 by gsapio           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_MANDATORY	=	main.c \
					parsing/parsing.c

LFLAGS = -lft -L./Libft -lmlx -Lminilibx-linux -lX11 -lXext -no-pie

IFLAGS = -I./Libft -I./minilibx_linux

PATH_LIBS =

LIBFT_PATH = Libft

MLX_PATH = minilibx-linux

HEADER = ./

OBJS_MANDATORY	= $(SRCS_MANDATORY:.c=.o)

# BONUS			=

OBJS_BONUS		= $(BONUS:.c=.o)

CC				= gcc -g

RM				= rm -f

CFLAGS			= -Wall -Wextra -Werror

NAME			= cub3D

# BONUS_NAME		=

all:			$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I $(HEADER) -c $< -o $@

$(NAME):		$(OBJS_MANDATORY)
				make -C $(LIBFT_PATH) --no-print-directory
				make bonus -C $(LIBFT_PATH) --no-print-directory
				make -C $(MLX_PATH) --no-print-directory
				$(CC) $(CFLAGS) $(OBJS_MANDATORY) $(LFLAGS) $(IFLAGS) -o $(NAME)

Bonus/%.o: Bonus/%.c
	$(CC) $(CFLAGS) -I /Bonus -c $< -o $@

$(BONUS_NAME):	$(OBJS_BONUS)
				make -C $(LIBFT_PATH) --no-print-directory
				make -C $(MLX_PATH) --no-print-directory
				$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(BONUS_NAME) Bonus/so_long_bonus.c $(PATH_LIBS) $(LFLAGS)

bonus:			$(BONUS_NAME)

clean:
				$(RM) $(OBJS_MANDATORY) $(OBJS_BONUS)

fclean:			clean
				$(RM) $(NAME)
				$(RM) -r ./mlx
				$(RM) $(NAME)_bonus
				$(RM) $(LIBFT_PATH)/*.o
				$(RM) $(LIBFT_PATH)/*.a
				$(RM) $(MLX_PATH)/*.o
				$(RM) $(MLX_PATH)/*.a

re:				fclean call_mlx $(NAME)

.PHONY:			all clean fclean re bonus
