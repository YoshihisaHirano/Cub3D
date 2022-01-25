SRC		=	main.c initialization.c\
			draw/draw_plane.c draw/raycast_dda.c\
			hooks/key_hooks.c hooks/movements.c hooks/rotation.c\
			parser/map_parser.c parser/gnl/get_next_line.c parser/gnl/get_next_line_utils.c\
			parser/parser_utils.c parser/parser_utils2.c validation/map_validation.c validation/validation_utils.c\
			utils/check_walls.c utils/draw_utils.c utils/common_utils.c utils/clear_utils.c\
			draw/draw_minimap.c utils/texture_utils.c utils/draw_minimap_utils.c
OBJ		=	$(SRC:.c=.o)
NAME	=	cub3D
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g
LIBDIR	=	./libft
LIB		=	$(LIBDIR)/libft.a
MLXDIR	=	./minilibx
MLX		=	$(MLXDIR)/libmlx.a
LFLAGS	=	-L $(LIBDIR) -lft -L $(MLXDIR) -lmlx -framework OpenGL -framework AppKit
HEADER	=	cub3D.h constants.h

.PHONY	:	all re clean fclean

all		:	$(NAME)

$(MLX)	:	
			make -s -C $(MLXDIR)

$(LIB)	:
			make -s -C $(LIBDIR)

$(NAME)	:	$(OBJ) Makefile
			$(CC) $(CFLAGS) $(LFLAGS) $(OBJ)  -o $(NAME)

%.o		:	%.c $(LIB) $(MLX) $(HEADER)
			$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

clean	:	
			rm -f *.o */*.o
			make clean -C $(LIBDIR)
			make clean -C $(MLXDIR)

fclean	:	clean
			rm -f $(NAME)
			make fclean -C $(LIBDIR)
			make clean -C $(MLXDIR)

x		:	all
			./cub3D map.cub

re		:	fclean all