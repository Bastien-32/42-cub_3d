NAME = cub3d

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MINILIBX_LINUX_DIR = ./minilibx-linux
MLX = $(MINILIBX_LINUX_DIR)/libmlx.a

SRC_DIR = srcs

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I . -I includes -DGL_SILENCE_DEPRECATION

SRC =	srcs/check/check_text_and_map.c \
		srcs/check/floodfill.c \
		srcs/display/display_3d.c \
		srcs/display/display_map.c \
		srcs/display/handle_win.c \
		srcs/display/raycasting.c \
		srcs/display/utils_display.c \
		srcs/free/free.c \
		srcs/init/init_display.c \
		srcs/init/init.c \
		srcs/init/utils_init.c \
		srcs/move/move_player.c \
		srcs/parsing/handle_map.c \
		srcs/parsing/handle_textures.c \
		srcs/parsing/handles_colors.c \
		srcs/parsing/parsing.c \
		srcs/main.c \
		srcs/utils.c

OBJ = ${SRC:srcs/%.c=srcs/obj/%.o}

# Détection système
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	MLX_DIR = minilibx_macos
	MLX = $(MLX_DIR)/libmlx.a
	MLX_FLAGS = -framework OpenGL -framework AppKit
else
	MLX_DIR = minilibx-linux
	MLX = $(MLX_DIR)/libmlx.a
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
endif

all: ${NAME}

$(NAME): $(OBJ) $(LIBFT)
	@make -s -C $(MLX_DIR)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	@make -s -C $(LIBFT_DIR)
	@make -s -C $(LIBFT_DIR) bonus

$(MLX):
	@make -s -C $(MLX_DIR)
	@echo ✅ "mlx compiled"

srcs/obj/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	@${CC} ${CFLAGS} -I $(LIBFT_DIR) -I $(MINILIBX_LINUX_DIR) -I . -c $< -o $@

clean:
	@make -s -C $(LIBFT_DIR) clean
	@make -s -C $(MLX_DIR) clean
	@rm -rf srcs/obj

fclean: clean
	@make -s -C $(LIBFT_DIR) fclean
	@rm -f ${NAME}

re: fclean all