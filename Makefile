NAME=cub3d
#SRCS=flood_fil.c  main.c map_errors.c
SRCS=main.c get_next_line.c flood_fil.c
OBJS=$(SRCS:.c=.o)
CC=cc
CFLAGS=-Wall -Wextra -Werror -g3
LIBFT_DIR=libft
LIBFT=$(LIBFT_DIR)/libft.a

all:$(NAME)

$(NAME):$(OBJS)
	@make bonus -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

%.o:.%c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(OBJS)

fclean:clean
	@make fclean -C $(LIBFT_DIR)
	@rm -rf $(NAME)

re:fclean all

.PHONY: all clean fclean re