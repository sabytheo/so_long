# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/02 00:25:03 by tsaby             #+#    #+#              #
#    Updated: 2025/01/21 12:23:58 by tsaby            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS		:=	so_long.c				\
				init_map.c				\
				check_error.c				\
				print_map.c					\
				keycontrol.c					\
				check_path.c					\

SRCS_D		:=	sources/

OBJS_D		:=	objs/

OBJS		:=	$(SRCS:%.c=$(OBJS_D)%.o)

HEAD		:=	include/so_long.h	\

HEAD_D		:=	.

CFLAGS		:=	-Wall -Wextra -Werror -g3

NAME		:=	so_long

LIBFT		=	Libft/

LIBFT_A		=	$(addprefix $(LIBFT), libft_ex.a)

MLX			:=	libmlx.a

MLX_D		:=	mlx_linux/

MLX_F		:=	-L$(MLX_D) -L/usr/lib -lmlx -lXext -lX11 -lm -lz

MLX_H		:=	$(MLX_D)mlx.h

MLX_A		:=	$(addprefix $(MLX_D), $(MLX))



all			:	lib
				$(MAKE) $(NAME)

lib			:
				$(MAKE) -C $(MLX_D)

$(NAME)		:	$(OBJS_D) $(OBJS) $(MLX_A) $(LIBFT_A) $(HEAD)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_A) $(MLX_F) -Lft_ex $(LIBFT_A)

$(OBJS)		:	$(OBJS_D)%.o: $(SRCS_D)%.c $(HEAD) $(MLX_H)
				$(CC) $(CFLAGS) -Iinclude -I$(LIBFT)/includes -Imlx_linux -c $< -o $@

$(LIBFT_A):
				@$(MAKE) -s -C $(LIBFT)

$(OBJS_D)	:
				@mkdir -p $(OBJS_D)

clean		:
				$(RM) -r $(OBJS) $(OBJS_D) $(OBJS_B) $(OBJS_B_D)
				$(MAKE) clean -s -C $(LIBFT)
				$(MAKE) clean -C mlx_linux

fclean		:	clean
				$(RM) $(NAME) $(NAME_B)
				$(MAKE) fclean -s -C $(LIBFT)
				$(MAKE) clean -C mlx_linux

re			:	fclean all


.PHONY: all bonus clean fclean re lib
