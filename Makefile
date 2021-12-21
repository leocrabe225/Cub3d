SRCS = get_next_line.c parser.c number_parser.c image_parser.c image_parser_common_part.c math_part1.c math_part2.c math_part3.c error_dealer.c save_to_bmp.c map_parser.c map_algo.c add_sprite.c initialize.c key_hook.c

OBJS = ${SRCS:.c=.o}

NAME = Cub3D

FLAGS = -Werror -Wall -Wextra

CC = gcc

RM = rm -rf

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o} 

${NAME}: ${OBJS} mlx
	${CC} -o ${NAME} ${OBJS} -L./mlx -lmlx_Linux -lm -lbsd -lX11 -lXext

all: ${NAME}

play:	all
	./${NAME} map.cub

save:	all
	./${NAME} map.cub --save

mlx:
	cd mlx && make 

pc:		play clean

clean:
	${RM} ${OBJS}
	cd mlx && make clean

fclean:	clean
	${RM} ${NAME} ./mlx/libmlx.a

re: fclean all

.PHONY: mlx play all save pc clean fclean re .c.o
