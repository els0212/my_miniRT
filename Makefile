SRC=ft_miniRT.c
OBJ=${SRC:.c=.o}
CC=gcc
CFLAGS=-Wall -Wextra -Werror
NAME=miniRT

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(SRC) main.c -o $@

.c.o : $(SRC)
	$(CC) $(CFLAGS) -Ilmx -c $< -o $@

all : $(NAME)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all re clean fclean
