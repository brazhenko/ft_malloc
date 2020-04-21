# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/21 22:42:57 by a17641238         #+#    #+#              #
#    Updated: 2020/04/21 22:49:12 by a17641238        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft_malloc.so

all:
	@make --directory sources
	@ln -fs sources/libft_malloc.so ${NAME}

re: fclean all

fclean:
	@make --directory sources fclean
	@rm  $(NAME)

clean:
	@make --directory sources clean