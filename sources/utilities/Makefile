LIBNAME		= libutils.a
FLAGS		= -Wall  -pedantic
CC			= clang
CFLAGS		= -c -Wall -Wextra -Werror -I .
LDFLAGS=


SOURCES =itoa.c \
         mem_to_hex.c \
         memcpy.c \

HEADERS =utilities.h

OBJECTS=$(SOURCES:.c=.o)

(LIBNAME): $(OBJECTS) $(HEADERS)
	@ar rc $(LIBNAME)  $(OBJECTS)
	@echo $(LIBNAME) "compiled!"

.c.o:
	@$(CC) $(CFLAGS) $< -o $@

clear: all clean

clean:
	@rm -rf $(OBJECTS)
	@echo $(LIBNAME) "object files removed"

fclean: clean
	@rm  -f ${LIBNAME}
	@echo ${LIBNAME} removed

re: fclean all