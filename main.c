//
// Created by Lommy Reznak on 7/2/20.
//

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

# define EXP_COUNT			600
# define EXP_SIZE			1000

int main()
{
    char		**array;
    size_t		 i;
    char		*addr;


    array = malloc(EXP_COUNT * sizeof(char *));
    i = 0;
    while (i < EXP_COUNT)
    {
        array[i] = malloc(EXP_SIZE);
        i++;
    }
    write(1, "realloc\n", 8);
    i = 0;
    while (i < EXP_COUNT)
    {
        array[i] = realloc(array[i], EXP_SIZE + 111);
        i++;
    }
    write(1, "free\n", 5);

    i = 0;
    while (i < EXP_COUNT)
    {
        //printf("%p\n",array[i]);
        free(array[i]);
        i++;
    }
    return (0);
}
//gcc  -g ./test0.c