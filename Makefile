NAME = game
CC = cc
OBJ = $(SRC:.c=.o)

LFLAGS = -L./includes/minilibx-linux-lmlx -lXext -lX11 -lm -g
INCLUDES = includes/minilibx-linux/libmlx.a
SRC = srcs/main.c srcs/player.c srcs/map.c

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(SRC) -o $(NAME) $(INCLUDES) $(LFLAGS)

fclean:
	rm -rf $(OBJ)
	rm -rf $(NAME)