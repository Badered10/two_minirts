INCLUDES=-I includes
NAME=miniRT
# all source files are inside the src directory
SRC_DIR=src
DEBUG=1

# 1 FOR LINUX #   
MLX = mlx_linux/libmlx_Linux.a
# MLX = mlx_mac/libmlx.a

ACTIONS	=	$(SRC_DIR)/actions/colors.c

GC	=	$(SRC_DIR)/gc/gc.c

MAP	=	$(SRC_DIR)/map/reader.c \
		$(SRC_DIR)/map/getter.c \
		$(SRC_DIR)/map/writer.c \
		$(SRC_DIR)/map/renderer.c \

GUARDS = $(SRC_DIR)/guards/light.c	\
		$(SRC_DIR)/guards/camera.c	\
		$(SRC_DIR)/guards/sphere.c	\
		$(SRC_DIR)/guards/plane.c	\
		$(SRC_DIR)/guards/cylinder.c	\
		$(SRC_DIR)/guards/utils.c	\
		$(SRC_DIR)/guards/point.c	\
		$(SRC_DIR)/guards/colors.c	\
		$(SRC_DIR)/guards/filter.c	\

MLX_SRC =	$(SRC_DIR)/mlx/init.c \
			$(SRC_DIR)/mlx/put.c \
			$(SRC_DIR)/mlx/events.c \


ERROR	=	$(SRC_DIR)/error/error.c

MAIN	=	$(SRC_DIR)/main.c

CFLAGS = -Wall -Wextra -Werror -I/usr/include  -O3
# 2 FOR LINUX # 
LDFLAGS = -lm -g3 -fsanitize=address -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
# LDFLAGS = -lm -g3 -fsanitize=address -Lmlx_mac  -Imlx_mac -Lmlx  -framework OpenGL -framework AppKit

SRC = $(ACTIONS) $(GC) $(GUARDS) $(MAP) $(ERROR) $(MAIN) $(MLX_SRC)
OBJ = $(SRC:.c=.o)

LIBFT=libft/libft.a
GNL=get_next_line/get_next_line.o

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(GNL) $(MLX)
	@echo "Compiling miniRT..."
	gcc $(OBJ) $(GNL) $(LIBFT) $(MLX) -o $(NAME) $(LDFLAGS)
	@echo "miniRT compiled successfully!"

%.o: %.c
	gcc -c $< -D DEBUG=$(DEBUG) -o $@ $(INCLUDES) $(CFLAGS)

$(LIBFT):
	@echo "Compiling libft..."
	@make -C libft

$(GNL):
	@echo "Compiling get_next_line..."
	@gcc -c get_next_line/get_next_line.c -o get_next_line/get_next_line.o

$(MLX):
	@echo "Compiling mlx..."
	# @make -C mlx_mac
	# 3 FOR LINUX # 
	@make -C mlx_linux

clean:
	@echo "Cleaning object files..."
	@rm -f $(OBJ) $(GNL)
	@make -C libft fclean
	@echo "Object files cleaned successfully!"

fclean: clean
	@echo "Cleaning miniRT..."
	@rm -f $(NAME)
	@echo "miniRT cleaned successfully!"

re: fclean all