# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mforstho <mforstho@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/10/12 16:16:58 by mforstho      #+#    #+#                  #
#    Updated: 2022/08/03 17:19:07 by mforstho      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# gcc main.c -I include -L MLX42 -l mlx42 -l glfw3 -framework Cocoa -framework OpenGL -framework IOKit

NAME := so_long
CC := gcc
CFLAGS ?= -Wextra -Wall -Werror

SOURCES :=									\
	src/map/draw_map.c						\
	src/map/check_map.c						\
	src/get_next_line/get_next_line.c		\
	src/get_next_line/get_next_line_utils.c

HEADERS := so_long.h libft/libft.h src/get_next_line/get_next_line.h
OBJDIR := obj
OBJECTS := $(addprefix $(OBJDIR)/, $(SOURCES:c=o))

LIBFLAGS := -L libft -l ft -L MLX42 -l mlx42 -l glfw3 -framework Cocoa -framework OpenGL -framework IOKit

LIBFT := libft/libft.a
MLX := MLX42/libmlx42.a

INCLUDES := $(addprefix -I, $(sort $(dir $(HEADERS))))
CFLAGS += $(INCLUDES)

all : $(NAME)

$(NAME) : $(OBJECTS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(LIBFLAGS) $(OBJECTS) -o $(NAME)

$(OBJDIR)/%.o : %.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) :
	$(MAKE) -C $(dir $(LIBFT))

$(MLX) :
	$(MAKE) -C $(dir $(MLX))

clean :
	rm -rf $(OBJDIR)
	$(MAKE) -C $(dir $(LIBFT)) clean
	$(MAKE) -C $(dir $(MLX)) clean

fclean : clean
	rm -f $(NAME)
	$(MAKE) -C $(dir $(LIBFT)) fclean
	$(MAKE) -C $(dir $(MLX)) fclean

re : fclean all

.PHONY : all clean fclean re
