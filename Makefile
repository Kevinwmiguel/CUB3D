VALGRIND = valgrind --leak-check=full --show-leak-kinds=definite \
--track-origins=yes --suppressions=mlx.supp

NAME = game
CC = cc

SRC = srcs/main.c srcs/player.c srcs/map.c srcs/draws.c srcs/movments.c srcs/raycasting.c srcs/minimap.c\
      get_next_line/get_next_line.c get_next_line/get_next_line_utils.c srcs/parse_colors.c srcs/validators.c\
	  srcs/player_val.c srcs/cleaners.c srcs/get_floor.c srcs/get_ceiling.c srcs/transform.c srcs/draws2.c

OBJ = $(SRC:.c=.o)

MLX_DIR = includes/minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

LFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
CFLAGS = -Wall -Wextra -Werror -g

all: $(LIBFT_LIB) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBFT_LIB) $(LFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

vg: all
	$(VALGRIND) ./$(NAME) assets/map_kevin.cub

