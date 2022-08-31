# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mforstho <mforstho@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/10/12 16:16:58 by mforstho      #+#    #+#                  #
#    Updated: 2022/08/31 18:40:13 by mforstho      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# gcc main.c -I include -L MLX42 -l mlx42 -l glfw3 -framework Cocoa -framework OpenGL -framework IOKit

NAME := so_long
CC := gcc
CFLAGS ?= -Wextra -Wall -Werror
CFLAGS += -g -fsanitize=address

SOURCES :=									\
	src/entities/collectible_pickup.c		\
	src/entities/initialize_entity_data.c	\
	src/entities/player_movement.c			\
	src/map/check_map/check_map_edge.c		\
	src/map/check_map/check_map_entities.c	\
	src/map/check_map/check_map_path.c		\
	src/map/check_map/check_map_rect.c		\
	src/map/check_map/check_map.c			\
	src/map/convert_map.c					\
	src/map/draw_entities.c					\
	src/map/draw_map.c						\
	src/map/free_map_array.c				\
	src/map/save_map.c						\
	src/get_next_line/get_next_line.c		\
	src/get_next_line/get_next_line_utils.c	\
	so_long.c

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
