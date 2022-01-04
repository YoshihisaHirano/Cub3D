SRC		=	new_draft.c draw_utils.c
#main.c draw_utils.c hooks/keys.c draft_funcs.c utils/math_utils.c
OBJ		=	$(SRC:.c=.o)
NAME	=	cub3D
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g
LIBDIR	=	./libft
LIB		=	$(LIBDIR)/libft.a
MLXDIR	=	./minilibx
MLX		=	$(MLXDIR)/libmlx.a
LFLAGS	=	-L $(LIBDIR) -lft -L $(MLXDIR) -lmlx -framework OpenGL -framework AppKit
HEADER	=	cub3D.h

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

re		:	fclean all