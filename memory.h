/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 23:24:15 by a17641238         #+#    #+#             */
/*   Updated: 2020/04/19 23:24:15 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_MEMORY_H
# define FT_MALLOC_MEMORY_H

# include <stddef.h>

void		*malloc(size_t size);
void		*realloc(void *ptr, size_t size);
void		free(void *ptr);
void		show_alloc_mem();
void 		show_mem_hex();

#endif

//getrlimit(2)
