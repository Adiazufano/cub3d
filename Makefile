NAME=cube3D
CC=cc
CFLAGS=-Wall -Wextra -Werror -Wunreachable-code -Ofast -g
LIBMLX=MLX42

HEADERS=-I ./include -I $(LIBMLX)/include -I ./libft

SRCS=	main.c\
		error_free_utils.c\
		flood_fil.c\
		get_next_line.c\
		init_color_split.c\
		init_cub3d_utils.c\
		init_floor_sky.c\
		init_val_formats.c\
		initialize.c\
		key_hook.c\
		map_utils.c\
		movement.c\
		minimap.c\
		minimap_utils.c\
		raycasting_utils.c\
		Raycasting.c\
		texture_utils.c\
		textures.c\

OBJS=$(SRCS:%.c=%.o)

LIBS=libft/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

all: libmlx libft $(NAME)

libmlx:
	@cmake -S $(LIBMLX) -B $(LIBMLX)/build -DCMAKE_BUILD_TYPE=Release
	@cmake --build $(LIBMLX)/build -j4

libft:
	@$(MAKE) -C libft

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	@$(MAKE) -C libft clean
	@rm -f $(OBJS)

fclean: clean
	@$(MAKE) -C libft fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all libmlx libft clean fclean re