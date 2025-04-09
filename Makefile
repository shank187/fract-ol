NAME        := fractol
BONUS       := fractol_bonus

CC          := cc
MLX42_DIR   := /mnt/homes/aelbour/MLX42/MLX42
MLX42_INC   := $(MLX42_DIR)/include
CFLAGS      := -I$(MLX42_INC) -Imandatory -Ibonus

MAND_HEADERS := mandatory/fractol.h
BONUS_HEADERS := bonus/fractol_bonus.h

MAND_SRCS   := mandatory/fractol.c \
               mandatory/converting.c \
               mandatory/sstring.c \
               mandatory/events.c
MAND_OBJS   := $(MAND_SRCS:.c=.o)

BONUS_SRCS  := bonus/fractol_bonus.c \
               bonus/converting_bonus.c \
               bonus/sstring_bonus.c \
               bonus/events_bonus.c
BONUS_OBJS  := $(BONUS_SRCS:.c=.o)

MLX42_LIB   := $(MLX42_DIR)/build/libmlx42.a
GLFW_LIB    := $(MLX42_DIR)/build/_deps/glfw-build/src/libglfw3.a
LIBS        := -ldl -pthread -lm
LDFLAGS     := $(MLX42_LIB) $(GLFW_LIB) $(LIBS) \
               -framework Cocoa -framework OpenGL -framework IOKit

.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(MAND_OBJS)
	$(CC) $(CFLAGS) $(MAND_OBJS) $(LDFLAGS) -o $(NAME)

bonus: $(BONUS)

$(BONUS): $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LDFLAGS) -o $(BONUS)

%.o: %.c $(MAND_HEADERS) $(BONUS_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(MAND_OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS)

re: fclean all
