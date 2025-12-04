NAME=cube3D
CC=cc
CFLAGS=-Wall -Wextra -Werror -Wunreachable-code -Ofast -g -fsanitize=address -fsanitize-blacklist=blacklist.txt
LIBMLX=MLX42

HEADERS=-I ./include -I $(LIBMLX)/include -I ./libft

SRCS=	main.c\
		error_free_utils.c\
		flood_fill_player.c\
		flood_fill_utils.c\
		flood_fill.c\
		get_next_line.c\
		init_color_split.c\
		init_cub3d_utils.c\
		init_floor_sky.c\
		init_val_formats.c\
		initialize.c\
		key_hook.c\
		map_utils.c\
		movement.c\
		raycasting_text.c\
		raycasting_utils.c\
		raycasting.c\
		texture_utils.c\
		textures.c\
		#minimap.c minimap_utils.c

SRCSBONUS=	$(BONUS_DIR)/main_bonus.c\
$(BONUS_DIR)/error_free_utils_bonus.c\
$(BONUS_DIR)/flood_fill_player_bonus.c\
$(BONUS_DIR)/flood_fill_utils_bonus.c\
$(BONUS_DIR)/flood_fill_bonus.c\
$(BONUS_DIR)/init_color_split_bonus.c\
$(BONUS_DIR)/init_cub3d_utils_bonus.c\
$(BONUS_DIR)/init_floor_sky_bonus.c\
$(BONUS_DIR)/init_val_formats_bonus.c\
$(BONUS_DIR)/initialize_bonus.c\
$(BONUS_DIR)/key_hook_bonus.c\
$(BONUS_DIR)/map_utils_bonus.c\
$(BONUS_DIR)/movement_bonus.c\
$(BONUS_DIR)/raycasting_text_bonus.c\
$(BONUS_DIR)/raycasting_utils_bonus.c\
$(BONUS_DIR)/raycasting_bonus.c\
$(BONUS_DIR)/texture_utils_bonus.c\
$(BONUS_DIR)/textures_bonus.c\
$(BONUS_DIR)/minimap_bonus.c\
$(BONUS_DIR)/minimap_utils_bonus.c\
$(BONUS_DIR)/sword.c\
get_next_line.c

BONUS_DIR=cub3d_bonus

OBJS=$(SRCS:%.c=%.o)

OBJSBONUS=$(SRCSBONUS:%.c=%.o)

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
	@rm -f $(OBJS) $(OBJSBONUS)

bonus: libmlx libft $(OBJSBONUS)
	@$(CC) $(CFLAGS) $(OBJSBONUS) $(LIBS) -o $(NAME)

fclean: clean
	@$(MAKE) -C libft fclean
	@rm -f $(OBJSBONUS)
	@rm -f $(NAME)

re: fclean all

.PHONY: all libmlx libft clean fclean bonus re