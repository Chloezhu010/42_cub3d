# executable name
NAME = cub3D

# dir
SRC_DIR = ./src
PARSER_DIR = $(SRC_DIR)/parsing
LIBFT_DIR = $(SRC_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a
# MLX_DIR = ./minilibx-linux
# MLX = $(MLX_DIR)/libmlx.a

# compiler & flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
# MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm -lz

# main src files
SRC = $(PARSER_DIR)/map_validation.c \
		$(PARSER_DIR)/map_validation_utils.c \
		$(PARSER_DIR)/map_check.c
OBJ = $(SRC:.c=.o)

# include dir
INC = -I./incl -I$(SRC_DIR)/libft #-I$(MLX_DIR)


# fules
all: $(LIBFT) $(NAME)

# build libft first
$(LIBFT):
	make -C $(LIBFT_DIR)

# # make mlx
# $(MLX):
# 	make -C $(MLX_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L$(LIBFT_DIR) -lft $(MLX_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re