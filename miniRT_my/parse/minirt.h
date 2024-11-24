#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include "../mlx_mac/mlx.h"

typedef struct	s_img 
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_infos
{
    t_list *garbage;
}              t_infos;

typedef struct s_parse
{
    char    **map;
    t_infos infos;
}              t_parse;

typedef struct s_mini
{
    void    *mlx;
    void    *window;
    t_img   img;
}             t_mini;


typedef struct s_rt
{
    int         fd;
    t_parse     parse;
    t_mini      mini;
}              t_rt;


// Errors

void    print_err(char *message);
void    free_all(t_infos *infos, char *msg, unsigned int ex_s);

#endif