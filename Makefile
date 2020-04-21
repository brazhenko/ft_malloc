# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/21 19:23:01 by a17641238         #+#    #+#              #
#    Updated: 2020/04/21 19:42:26 by a17641238        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= malloc
FLAGS		= -Wall -Wextra -Werror -pedantic -g
CC			= clang
BUILD_DIR   = build
LIBMALLOC_DIR = sources


################################################################################
PUSH_SWAP_CFLAGS=-c -Wall -Wextra -Werror -I $(PUSH_SWAP_LIB_DIR) -I $(UTILITIES_LIB_DIR) -I $(PUSH_SWAP_DIR)
LIBMALLOC_SOURCES=	$(LIBMALLOC_DIR)/free.c \
					 $(LIBMALLOC_DIR)/get_free_block_from_cluster.c \
					 $(LIBMALLOC_DIR)/main_wrappers.c \
					 $(LIBMALLOC_DIR)/malloc.c \
					 $(LIBMALLOC_DIR)/mem_dump.c \
					 $(LIBMALLOC_DIR)/mutex_manager.c \
					 $(LIBMALLOC_DIR)/new_cluster.c \
					 $(LIBMALLOC_DIR)/realloc.c \
					 $(LIBMALLOC_DIR)/service_funcs.c \
					 $(LIBMALLOC_DIR)/show_mem_hex.c

LIBMALLOC_DFILES=$(LIBMALLOC_SOURCES:.c=.d)
LIBMALLOC_OBJECTS=$(LIBMALLOC_SOURCES:.d=.c)
LIBMALLOC_IFILES=$(LIBMALLOC_SOURCES:.c=.i)


all: $(NAME)


#libutils:
#	@make --directory $(UTILITIES_LIB_DIR)

$(NAME): $(LIBMALLOC_IFILES)


$(LIBMALLOC_DIR)/%.o : $(LIBMALLOC_DIR)/%.i
	#@$(CC) $(PUSH_SWAP_CFLAGS)  $< -o $@


$(LIBMALLOC_DIR)/%.i : $(LIBMALLOC_DIR)/%.c
	#@$(CC) -M $< -o $@
	cpp $< > $@



clear: all clean

clean:
	rm  -f $(LIBMALLOC_DFILES)
	@echo "CLEAN"


fclean: clean
	@echo "FCLEAN"

re: fclean all