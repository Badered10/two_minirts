NAME			:= minirt

CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror
# 1 FOR MAC
# MFLAGS			:= -Lmlx_mac -lmlx -framework OpenGL -framework AppKit #-lX11 -lXext
# 2 FOR LINUX  
MFLAGS = -lm -g3 -fsanitize=address -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz


PARSE			:=	parse/parser.c parse/errs.c parse/garbage.c
RAYTRCING		:=	Raytracing/raytracing.c
GNL				:=	gnl/get_next_line.c gnl/get_next_line_utils.c

SRCS 			:= $(GNL) $(PARSE) $(RAYTRCING)
				
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