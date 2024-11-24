#include "main.h"

gc_t **local_gc()
{
    static gc_t *gc = NULL;
    return (&gc);
}

void *new_(size_t size)
{
    gc_t *gc;
    gc_t *iter;

    gc = malloc(sizeof(gc_t));
    if (!gc)
        throw_error("malloc failed", -1, NULL);
    gc->ptr = malloc(size);
    if (!gc->ptr)
    {
        free(gc);
        throw_error("malloc failed", -1, NULL);
    }
    ft_bzero(gc->ptr, size);
    gc->next = NULL;
    iter = *local_gc();
    if (!iter)
        *local_gc() = gc;
    else
    {
        while (iter->next)
            iter = iter->next;
        iter->next = gc;
    }
    return (gc->ptr);
}

void delete_(void *ptr)
{
    gc_t *iter;
    gc_t *prev;

    iter = *local_gc();
    prev = NULL;
    while (iter)
    {
        if (iter->ptr == ptr)
        {
            if (prev)
                prev->next = iter->next;
            else
                *local_gc() = iter->next;
            free(iter->ptr);
            free(iter);
            break;
        }
        prev = iter;
        iter = iter->next;
    }
}

void clean_()
{
    gc_t *iter;
    gc_t *next;

    iter = *local_gc();
    while (iter)
    {
        next = iter->next;
        free(iter->ptr);
        free(iter);
        iter = next;
    }
    *local_gc() = NULL;
}
