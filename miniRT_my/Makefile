NAME			:= minirt

CC				:= cc
CFLAGS			:= #-Wall -Wextra -Werror
# 1 FOR MAC
# MFLAGS			:= -Lmlx_mac -lmlx -framework OpenGL -framework AppKit #-lX11 -lXext
# 2 FOR LINUX  
MFLAGS = -lm -g3 -fsanitize=address -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz


VEC3			:= vec3/vec3.c
PARSE			:=	parse/parser.c parse/errs.c parse/garbage.c
# RAYTRCING		:=	raytracing/raytracing.c
# COLOR			:=	color/color.c
# RAY				:=	ray/ray.c
GEO				:=  geo/geo.c
GNL				:=	gnl/get_next_line.c gnl/get_next_line_utils.c

SRCS 			:= $(GNL) $(PARSE) $(GEO) $(VEC3)
				
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