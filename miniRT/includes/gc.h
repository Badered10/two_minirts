#ifndef GC_H
#define GC_H

# include "libs.h"

typedef struct gc_s
{
    void    *ptr;
    void    *next;
}   gc_t;

void *new_(size_t size);
void delete_(void *gc);
void clean_();

#endif