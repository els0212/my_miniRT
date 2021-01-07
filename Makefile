SRC=ft_miniRT.c main.c
#OBJ=${SRC:.c=.o}
CC=gcc
CFLAGS=-Wall -Wextra #-Werror
NAME=miniRT

#.c.o : $(SRC)
#	$(CC) $(CFLAGS) -Lmlx_opengl -lmlx -c $< -o $@

$(NAME) : $(SRC)
	$(CC) $(CFLAGS) -Lmlx -lmlx -framework OpenGL -framework AppKit $(SRC) -o $@

all : $(NAME)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all re clean fclean
