# executable name
NAME = cub3D

# dir
SRC_DIR = ./src
PARSER_DIR = $(SRC_DIR)/parsing
CLEANUP_DIR = $(SRC_DIR)/cleanup
PLAYER_DIR = $(SRC_DIR)/player_movement
TEXTURE_DIR = $(SRC_DIR)/texture
3D_DIR = $(SRC_DIR)/3D
DEBUG_DIR = $(SRC_DIR)/debug
LIBFT_DIR = $(SRC_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

# compiler & flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm -lz

# main src files
SRC = $(PARSER_DIR)/input_validation.c \
		$(PARSER_DIR)/input_validation_utils_1.c \
		$(PARSER_DIR)/input_validation_utils_2.c \
		$(PARSER_DIR)/map_check.c \
		$(PARSER_DIR)/map_check_utils_1.c \
		$(PARSER_DIR)/map_check_utils_2.c \
		$(PARSER_DIR)/parsing.c \
		$(PARSER_DIR)/parse_rgb.c \
		$(PARSER_DIR)/parse_element_line.c \
		$(SRC_DIR)/init_game.c \
		$(SRC_DIR)/main.c \
		$(SRC_DIR)/main_utils.c \
		$(PLAYER_DIR)/player_key.c \
		$(CLEANUP_DIR)/cleanup.c \
		$(DEBUG_DIR)/debug_utils.c \
		$(TEXTURE_DIR)/texture.c \
		$(TEXTURE_DIR)/init_img.c \
		$(3D_DIR)/3d.c \
		

OBJ = $(SRC:.c=.o)

# include dir
INC = -I./incl -I$(SRC_DIR)/libft -I$(MLX_DIR)


# files
all: $(LIBFT) $(MLX) $(NAME)

# build libft first
$(LIBFT):
	make -C $(LIBFT_DIR)

# make mlx
$(MLX):
	make -C $(MLX_DIR)

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