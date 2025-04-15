# executable name
NAME = cub3D

# dir
SRC_DIR = ./src
LIBFT_DIR = $(SRC_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

# compiler & flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm -lz

# main src files
SRC = map.c map_validate.c map_floodfill.c init.c render.c movement.c movement_key.c main_solong.c cleanup.c
OBJ = $(SRC:.c=.o)

# include dir
INC = -I./incl -I$(SRC_DIR)/libft -I$(MLX_DIR)


# fules
all: $(NAME)

# build libft first
$(LIBFT):
	make -C $(LIBFT_DIR)

# make mlx
$(MLX):
	make -C $(MLX_DIR)

$(NAME): $(MLX) $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L$(LIBFT_DIR) -lft $(MLX_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_DIR) fclean

re: fclean all

.PHONY: all clean fclean re