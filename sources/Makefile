# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/21 22:21:37 by a17641238         #+#    #+#              #
#    Updated: 2020/04/22 00:47:28 by a17641238        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

############################## HOST ############################################

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

############################## VAR #############################################

NAME = libft_malloc.so

HOSTLIB = libft_malloc_$(HOSTTYPE).so

SRC =	malloc.c \
		realloc.c \
        free.c \
        get_free_block_from_cluster.c \
        main_wrappers.c \
        mem_dump.c \
        mutex_manager.c \
        new_cluster.c \
        service_funcs.c \
        show_mem_hex.c \

OBJDIR = objs

CFLAGS = -Wall -g -c

LDFLAGS = -shared

DEP = utilities/utilities.h malloc.h ../memory.h

CC = clang

MALLOC_OBJ = $(SRC:.c=.o)

LIB = -Lutilities -lutils -lpthread

INCL = -I utilities -I .. -I .


############################## RULES ###########################################

all: ${NAME}
	@echo ${G}Success"   "[${NAME}]${X}

${NAME}: UTLIB $(HOSTLIB)
	@echo ${C}Linking"   "[${HOSTLIB}]...${X}
	@ln -fs ${HOSTLIB} ${NAME}

UTLIB:
	@make --directory utilities


$(HOSTLIB): UTLIB $(MALLOC_OBJ)
	@$(CC) -shared -o $(HOSTLIB) $(MALLOC_OBJ) $(LIB)
	@echo $(HOSTLIB) compiled!


%.o : %.c
	@$(CC) $(CFLAGS)  $< -o $@

fclean: clean
	@rm -f $(NAME) $(HOSTLIB)
	@echo $(NAME) cleaned!
	@make --directory utilities fclean

clean:
	@rm -f $(MALLOC_OBJ)
	@echo Objects cleaned!
	@make --directory utilities clean

re: fclean all

.PHONY: all clean fclean re test test