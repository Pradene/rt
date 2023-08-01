FILES	= parsing/check_file_extension.c \
		parsing/create_objs.c \
		parsing/gnl.c \
		parsing/objects.c \
		parsing/parsing.c \
		parsing/string_array.c \
		parsing/strtof.c \
		parsing/strtov3.c \
		main.c

SRCS	= $(addprefix srcs/, $(FILES))

OBJS	= $(SRCS:.c=.o)

CC		= cc

CFLAGS	= -std=c99 -Wall -Wextra -Werror -g

NAME	= minirt

.SILENT:

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

all: | lft	$(NAME)

lft:
	make -C libft

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) -L./libft -lft

clean:
	rm -rf $(OBJS)
	make -C libft clean

fclean:	clean
	rm -rf $(NAME)
	make -C libft fclean

re:	fclean all

.PHONY: re fclean clean all