#include "main.h"

void    throw_error(char *msg, int line, char *add)
{
    size_t  size;

    ft_putstr_fd(RED"Error\n"RESET, STDERR_FILENO);
    size = ft_strlen(msg) + ft_strlen(ft_itoa(line));
    ft_putstr_fd("+", STDERR_FILENO);
    while (size--)
        ft_putstr_fd("-", STDERR_FILENO);
    ft_putstr_fd("+\n", STDERR_FILENO);
    if (add)
    {
        ft_putstr_fd("|", STDERR_FILENO);
        ft_putstr_fd(add, STDERR_FILENO);
        size = ft_strlen(add);
        while ((size++) < (ft_strlen(msg) + ft_strlen(ft_itoa(line))))
            ft_putstr_fd(" ", STDERR_FILENO);
        ft_putstr_fd("|\n", STDERR_FILENO);
    }
    ft_putstr_fd("|", STDERR_FILENO);
    ft_putstr_fd(msg, STDERR_FILENO);
    if (line != -1)
        ft_putnbr_fd(line, STDERR_FILENO);
    ft_putstr_fd("|\n", STDERR_FILENO);
    size = ft_strlen(msg) + ft_strlen(ft_itoa(line));
    ft_putstr_fd("+", STDERR_FILENO);
    while (size--)
        ft_putstr_fd("-", STDERR_FILENO);
    ft_putstr_fd("+\n", STDERR_FILENO);
    clean_();
    exit(1);
}
