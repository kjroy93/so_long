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

# Source files listed manually
SRC = src/parse/read_maps.c src/parse/p_utils.c src/utils/utils.c src/so_long.c	\
		src/parse/filename.c													\

# Object files
OBJ = $(SRC:.c=.o)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I$(INCLUDE_DIR) -I$(LIBFT_INCLUDE)

# Static libft library
LIBFT = $(LIBFT_DIR)/libft.a

###########################################
#                RULES                    #
###########################################

all: $(LIBFT) $(NAME)

# Compile libft if not compiled or outdated
$(LIBFT):
	@echo "⚙️ 📘 Compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null 2>&1

# Compile so_long
$(NAME): $(OBJ_FILES)
	@echo "🎮 [42] Compiling so_long..."
	@$(CC) $(CFLAGS) $^ $(LIBFT) -o $@

# Compile each .c to .o inside obj directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

###########################################
#               CLEANING                  #
###########################################

clean:
	@echo "🧹 Swoosh swoosh... Removing object files..."
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean > /dev/null 2>&1

fclean: clean
	@echo "🧹🧹 Swoosh swoosh... Removing everything..."
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null 2>&1

re: fclean all

.PHONY: all clean fclean re
