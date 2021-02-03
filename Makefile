SRC=$(addprefix src/,ft_libft.c get_next_line.c get_next_line_utils.c ft_split.c ft_struct.c ft_utils.c ft_list_utils.c ft_parse_rt_1.c ft_parse_rt_2.c ft_math_utils.c ft_vec_operations.c ft_ray_utils.c ft_rotations.c ft_shader.c ft_save.c ft_error.c ft_color_utils.c ft_parse_utils_1.c ft_parse_utils_2.c ft_ray_hit_1.c ft_ray_hit_2.c ft_free_utils.c ft_mlx_utils.c ft_render.c main.c)
OBJ=${SRC:.c=.o}
INCLUDE=include
CC=gcc
CFLAGS=-Wall -Wextra #-Werror
NAME=miniRT

all : $(NAME)

.c.o : $(SRC) $(INCLUDE)
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -framework OpenGL -framework AppKit -Lmlx -lmlx -o $@ $(OBJ)


clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all re clean fclean
