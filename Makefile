# **************************************************************************** #
#                                  FRACTOL                                     #
# **************************************************************************** #
# Name of the executable
NAME    := fractol
# Compiler and Flags
CC      := cc
MLX42_DIR := /mnt/homes/aelbour/MLX42/MLX42
MLX42_INC := $(MLX42_DIR)/include
CFLAGS  :=  -I$(MLX42_INC) 
# Sources and Objects
SRCS    := fractol.c  converting.c  sstring.c events.c 
OBJS    := $(SRCS:.c=.o)
# MLX42 Library Path
MLX42_LIB := $(MLX42_DIR)/build/libmlx42.a
# GLFW Library Path (direct path)
GLFW_LIB := $(MLX42_DIR)/build/_deps/glfw-build/src/libglfw3.a
# Other dependencies
LIBS    := -ldl -pthread -lm
# macOS specific frameworks for MLX42
LDFLAGS := $(MLX42_LIB) $(GLFW_LIB) $(LIBS) -framework Cocoa -framework OpenGL -framework IOKit
# Default rule
all: $(NAME)
# Linking
$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
# Compilation rule
%.o: %.c fractol.h
	$(CC) $(CFLAGS) -c $< -o $@
# Cleaning object files
clean:
	rm -f $(OBJS)
# Cleaning everything
fclean: clean
	rm -f $(NAME)
# Rebuild everything
re: fclean all
.PHONY: all clean fclean re