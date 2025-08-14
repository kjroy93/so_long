###########################################
#             VARIABLES                   #
###########################################

NAME = so_long

# Directories
SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = libft
INCLUDE_DIR = include
LIBFT_INCLUDE = $(LIBFT_DIR)/include

# MLX42 variables
MLX42_DIR := ./MLX42
MLX42_INCLUDE := $(MLX42_DIR)/include
MLX42_LIB := $(MLX42_DIR)/build/libmlx42.a
MLX42_LIBS := -lglfw -ldl -lm -pthread -lGL
LDLIBS := $(MLX42_LIB) $(MLX42_LIBS)

# Source files listed manually
SRC = 	src/parse/read_maps.c src/parse/p_utils.c src/utils/utils.c src/so_long.c				\
		src/parse/filename.c src/parse/playable_map.c src/keys/keys.c src/draw_textures/draw.c	\

# Object files (put into obj folder)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I$(INCLUDE_DIR) -I$(LIBFT_INCLUDE) -I$(MLX42_INCLUDE)

# Static libft library
LIBFT = $(LIBFT_DIR)/libft.a

###########################################
#                RULES                    #
###########################################

all: mlx42 $(LIBFT) $(NAME)

# Compile MLX42 library with CMake
mlx42: $(MLX42_LIB)
$(MLX42_LIB):
	@echo "📦 Compiling MLX42..."
	@cmake -B $(MLX42_DIR)/build $(MLX42_DIR) > /dev/null
	@make -C $(MLX42_DIR)/build -j4 > /dev/null

# Compile libft if not compiled or outdated
$(LIBFT):
	@echo "⚙️ 📘 Compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null 2>&1

# Compile so_long executable
$(NAME): $(OBJ_FILES)
	@echo "🎮 Compiling so_long..."
	@$(CC) $(CFLAGS) $^ $(LIBFT) $(LDLIBS) -o $@

# Compile each .c to .o inside obj directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

###########################################
#               CLEANING                  #
###########################################

clean:
	@echo "Swosh 🧹 Swosh Removing object files..."
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean > /dev/null 2>&1
	@rm -rf $(MLX42_DIR)/build

fclean: clean
	@echo "Swosh 🧹🧹 Swosh Removing executable and libraries..."
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null 2>&1

re: fclean all

.PHONY: all mlx42 clean fclean re
