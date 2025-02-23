NAME			:= minirt

CC				:= cc #-fsanitize=address -g3
CFLAGS			:= 
# 1 FOR MAC
# MFLAGS			:= -Lmlx_mac -lmlx -framework OpenGL -framework AppKit #-lX11 -lXext
# 2 FOR LINUX  
MFLAGS = -lm   -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

VEC3			:= vec3/vec3.c
PARSE			:=	parse/parser.c parse/errs.c parse/garbage.c

SRC_DIR = /home/baouragh/Desktop/two_minirts/miniRT/src
ACTIONS	=	$(SRC_DIR)/actions/colors.c

GC	=	$(SRC_DIR)/gc/gc.c

MAP	=	$(SRC_DIR)/map/reader.c \
		$(SRC_DIR)/map/getter.c \
		$(SRC_DIR)/map/writer.c \
		$(SRC_DIR)/map/renderer.c \
		$(SRC_DIR)/map/ft_c_split.c \

GUARDS = $(SRC_DIR)/guards/light.c	\
		$(SRC_DIR)/guards/camera.c	\
		$(SRC_DIR)/guards/sphere.c	\
		$(SRC_DIR)/guards/plane.c	\
		$(SRC_DIR)/guards/cylinder.c	\
		$(SRC_DIR)/guards/utils.c	\
		$(SRC_DIR)/guards/point.c	\
		$(SRC_DIR)/guards/colors.c	\
		$(SRC_DIR)/guards/filter.c	\

ERROR	=	$(SRC_DIR)/error/error.c

# RAYTRCING		:=	raytracing/raytracing.c
# COLOR			:=	color/color.c
# RAY				:=	ray/ray.c
GEO				:=    geo/get_next_line.c geo/get_next_line_utils.c geo/merge.c #geo/copy.c
# GNL				:=	gnl/get_next_line.c gnl/get_next_line_utils.c

SRCS 			:= $(GNL) $(PARSE) $(GEO) $(VEC3) $(ACTIONS) $(GC) $(GUARDS) $(MAP) $(ERROR)
				
LIBFT_PATH		:=	libft/
LIBFT			:=	libft/libft.a

OBJS			:=	$(SRCS:.c=.o)

all:	$(NAME)
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MFLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)
	make -C $(LIBFT_PATH) bonus

clean:
	@make clean -C $(LIBFT_PATH)
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@rm -f $(NAME) $(BONUS)

re: fclean all

bonus:	re

.PHONY: clean