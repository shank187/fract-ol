# Compiler
CC = cc

# Compiler Flags
CFLAGS = -Wall -Wextra -Werror -Ofast -I./ -I/home/aelbour/MLX42/include

# MLX42 & GLFW Paths
MLX42_DIR = /home/aelbour/MLX42
GLFW_DIR = /home/aelbour/glfw_install

# Libraries
LIBS = -L$(MLX42_DIR)/build -lmlx42 -L$(GLFW_DIR)/lib -lglfw -ldl -pthread -lX11 -lGL -lm

# Source & Object Files (all .c in current dir)
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

# Executable Name
NAME = fractol

# Default Rule
all: $(NAME)

# Compile Object Files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ && echo "Compiled: $(notdir $<)"

# Link Executable
$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME) && echo "Linked: $(NAME)"

# Clean Object Files
clean:
	rm -f $(OBJS)

# Full Clean (remove executable too)
fclean: clean
	rm -f $(NAME)

# Recompile Everything
re: fclean all

# Phony Targets
.PHONY: all clean fclean re
