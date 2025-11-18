NAME	=	cube3D					

SRCS	=  	main.c\
			initialize.c\
			Raycasting.c\
		
OBJS	=	$(SRCS:.c=.o)					

CC	=	cc									

RM	=	rm -f								

CFLAGS	=	-Wall -Wextra -Werror -I$(LIBMLX_DIR)/include

LIBMLX_DIR = MLX42

LIBMLX = $(LIBMLX_DIR)/libmlx42.a

all	:	$(NAME)									

$(NAME): $(OBJS) $(LIBMLX)	
	$(CC) $(CFLAGS) -v -o $(NAME) $(OBJS) -L$(LIBMLX_DIR) -lmlx42 -lglfw -ldl -pthread -lm

$(LIBMLX):
	make -C $(LIBMLX_DIR)		

%.o: %.c									
	$(CC) $(CFLAGS) -c $< -o $@

clean	:										
	$(RM) $(OBJS)

fclean	: clean						
	$(RM) $(NAME)

re	:	fclean all							

.PHONY	:	all clean fclean re	