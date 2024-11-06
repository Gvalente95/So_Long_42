NAME = so_long
CC = gcc
CFLAGS = -Wall -Werror -Wextra
INCLUDES = -Imlx -Ilibft
SOURCES = $(wildcard *.c)
OBJ = $(SOURCES:.c=.o)
MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit -lz
LIBFTPATH = libft/
LIBFT = $(LIBFTPATH)libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFTPATH)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(MLXFLAGS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C $(LIBFTPATH) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTPATH) fclean

re: fclean all

.PHONY: all clean fclean re
