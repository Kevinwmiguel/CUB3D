VALGRIND = valgrind --leak-check=full --show-leak-kinds=definite \
--track-origins=yes --suppressions=mlx.supp

NAME = cub3D
CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SRC =	srcs/main.c srcs/player.c srcs/map.c srcs/draws.c \
		srcs/movments.c srcs/raycasting.c srcs/minimap.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \
		srcs/parse_colors.c srcs/validators.c \
		srcs/player_val.c srcs/cleaners.c \
		srcs/get_floor.c srcs/get_ceiling.c \
		srcs/transform.c srcs/draws2.c \
		srcs/draws3.c srcs/painting.c \
		srcs/init.c srcs/validators2.c \
		srcs/utils.c srcs/init2.c \
		srcs/dda.c srcs/dda2.c \
		srcs/map_validation.c srcs/parser.c \
		srcs/draws1.c srcs/validators3.c

OBJ = $(SRC:.c=.o)

MLX_DIR = includes/minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

INCLUDES = -I$(MLX_DIR) -I$(LIBFT_DIR)

LFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

all: $(MLX_LIB) $(LIBFT_LIB) $(NAME)

$(MLX_LIB):
	@echo "Compiling mlx..."
	-@make -C $(MLX_DIR) > /dev/null 2>&1
	@echo "MLX is ready!"

$(LIBFT_LIB):
	@echo "Compiling libft..."
	@make -C $(LIBFT_DIR) > /dev/null
	@echo "Libft is ready!"

$(NAME): $(OBJ)
	@echo "Compiling game..."
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) $(LFLAGS) -o $(NAME)
	@echo "Game is ready!"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "Cleaning objects..."
	@rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean > /dev/null
	@make -C $(MLX_DIR) clean > /dev/null
	@echo "Objects cleaned!"

fclean: clean
	@echo "Cleaning project..."
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean > /dev/null
	@echo "Project cleaned!"

re: fclean all

vg: all
	$(VALGRIND) ./$(NAME) assets/map_kevin.cub

.PHONY: all clean fclean re vg