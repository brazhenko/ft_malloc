# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/21 22:42:57 by a17641238         #+#    #+#              #
#    Updated: 2020/04/22 14:47:58 by a17641238        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

############################## HOST ############################################

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif


NAME=libft_malloc.so
HOSTLIB = libft_malloc_$(HOSTTYPE).so

all:
	@make --directory sources
	@ln -fs sources/libft_malloc_$(HOSTTYPE).so  "${NAME}"
	@cp sources/libft_malloc_$(HOSTTYPE).so .

re: fclean all

fclean:
	@make --directory sources fclean
	@rm -f $(NAME) $(HOSTLIB)

clean:
	@make --directory sources clean