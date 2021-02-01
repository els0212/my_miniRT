SRC=ft_libft.c get_next_line.c get_next_line_utils.c ft_split.c ft_struct.c ft_utils.c ft_list_utils.c ft_parse_rt_1.c ft_parse_rt_2.c ft_math_utils.c ft_vec_operations.c ft_ray_utils.c ft_rotations.c ft_shader.c ft_save.c ft_error.c ft_color_utils.c main.c
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
