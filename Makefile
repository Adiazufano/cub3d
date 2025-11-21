NAME=cube3D
CC=cc
CFLAGS=-Wall -Wextra -Werror -Wunreachable-code -Ofast -g -fsanitize=address
LIBMLX=MLX42

HEADERS=-I ./include -I $(LIBMLX)/include -I ./libft

SRCS=main.c Raycasting.c raycasting_utils.c get_next_line.c initialize.c flood_fil.c textures.c key_hook.c
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