NAME = game
CC = cc

SRC = srcs/main.c srcs/player.c srcs/map.c \
      get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

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

