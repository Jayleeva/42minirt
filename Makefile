NAME = minirt
LIBFT = libft
LIBFT_DIR := ./libft
LIBFT_LIB := $(LIBFT_DIR)/$(LIBFT)
MLX_DIR = ./minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a

SRC_DIR = ./src
OBJ_DIR = ./obj
DIR = ./obj ./obj/parsing

SRC = 	main.c \
		handle_window.c \
		parsing/is_playable.c \
		parsing/config_upper.c \
		parsing/config_lower.c \
		parsing/config_common.c \
		parsing/parsing_utils.c \
		rgb_to_hex.c \
		ray_tracing.c \
		
		
SRCS = $(addprefix $(SRC_DIR)/, $(SRC))

OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ))

CC = cc
CFLAGS = -Wall -Wextra -Werror -I ./inc -I ./libft/inc -g 

MATH_FLAGS = -lm
MLX_FLAGS = -lXext -lX11
INCLUDES = -I/usr/include -Imlx

MKDIR = mkdir -p
RM = rm -rf

all: $(MLX_LIB) $(NAME)

$(DIR):
	$(MKDIR) $(DIR)

$(NAME): $(OBJS) | $(DIR) $(LIBFT_LIB)
	@${CC} ${CFLAGS} ${OBJS} $(LIBFT_LIB) $(MLX_LIB) -o $(NAME) $(MLX_FLAGS) $(MATH_FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(DIR)
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)

$(LIBFT_LIB):
	@${MAKE} -C libft

$(MLX_LIB):
	@${MAKE} -C $(MLX_DIR)

clean:
	@${MAKE} -C libft fclean
	@${MAKE} -C $(MLX_DIR) clean
	@$(RM) $(OBJ_DIR)
fclean: clean
	@$(RM) $(NAME)
re: fclean all

.PHONY : all clean fclean re