LIBNAME		= libutils.a
FLAGS		= -Wall -Wextra -Weror -pedantic
CC			= clang
CFLAGS		= -c -Wall -Wextra -Werror -I .
LDFLAGS=


SOURCES =itoa.c \
         mem_to_hex.c \
         memcpy.c \
         nums.c \

HEADERS =utilities.h

OBJECTS=$(SOURCES:.c=.o)

(LIBNAME): $(OBJECTS) $(HEADERS)
	@ar rc $(LIBNAME)  $(OBJECTS)
	@echo $(LIBNAME) "compiled!"

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS)  $< -o $@

clear: all clean

clean:
	@rm -rf $(OBJECTS)
	@echo $(LIBNAME) "object files removed"

fclean: clean
	@rm  -f ${LIBNAME}
	@echo ${LIBNAME} removed

re: fclean all