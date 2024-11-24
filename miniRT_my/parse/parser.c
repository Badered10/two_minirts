/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 02:43:06 by baouragh          #+#    #+#             */
/*   Updated: 2024/11/24 15:02:32 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


// int strings_len(char **str)
// {
//     int i;

//     i = 0;
//     while (str[i])
//         i++;
//     return (i);
// }

// int parse_colors(char **args, t_parse *parse)
// {
//     if (strcmp(args[0], "F"))
//     parse->f++;
//     else if (strcmp(args[0], "C"))
//     parse->c++;
//     else
//         return (-1);
//     return (0);
// }

// int parse_dirs(char **args, t_parse *parse)
// {
//     if (strcmp(args[0], "NO"))
//     {
//         if (info->path_no)
//             error;
//          info->path_no = args[1];    
//         parse->no++;
//     }
//     else if (strcmp(args[0], "SO"))
//     parse->so++;
//     else if (strcmp(args[0], "WE"))
//     parse->we++;
//     else if (strcmp(args[0], "EA"))
//     parse->ea++;
//     else
//         return (-1);
//     return (0);
// }


// char **process_line(char *line, t_parse *parse)
// {
//     char **args;
//     int    len;

//     (void)parse;
//     args = ft_split(line, ' ');
//     if (!args)
//         return (NULL);
//     if (strings_len(args) > 2 || strings_len(args) == 0)
//         return (NULL);
//     len = ft_strlen(args[0]);
//     // if (len == 2 && parse_dirs(args, parse) == -1)
//     //     return (NULL);
//     // else if (len == 1 && parse_colors(args, parse) == -1)
//     //     return (NULL);
//     return (NULL);
// }

// t_list *parse_content(t_parse *parse)
// {
//     char    *line;
//     t_list  *res;

//     res = NULL;
//     line = get_next_line(parse->fd);
//     while (line)
//     {
//         line = get_next_line(parse->fd);
//         if (*line != '\n')
//             process_line(line, parse);
//     }
//     return (res);
// }

// int check_name(char *name, t_parse *parse)
// {
//     char *full;

//     full = name;
//     if (!name || !*name)
//         return (ft_putstr_fd("you enterd an empty file name\n", 2), -1);
//     name = ft_strrchr(name, '.');
//     if (!name)
//         return (ft_putstr_fd("File format .cub not found\n", 2), -1);
//     if (strcmp(name, ".cub"))
//         return (ft_putstr_fd("File format must end with .cub\n", 2), -1);
//     parse->fd = open(full, O_RDONLY);
//     if (parse->fd < 0)
//         return (ft_putstr_fd("File Not found or not readable\n", 2), -1);
//     return (0);
// }

// int parsing(int ac, char **av, t_parse *parse)
// {
//     if (ac != 2)
//         return (ft_putstr_fd("Not enough args!\n", 2), -1);
//     if (check_name(av[1], parse))
//         return (-1);
//     // parse_content(cub);
//     return (0);
// }

// void  main2()
// {
//     t_infos infos;

//     // ft_bzero(&parse, sizeof(t_parse));
//     // if (parsing(ac, av, &parse))
//     //     return (1);
//     char **str;
//     int i = 0;

//     infos.garbage = NULL;
//     str = (char **) malloc(sizeof(char *) * 5);
//     ft_lstadd_back(&infos.garbage, ft_lstnew(str));
//     while (i < 4)
//     {
//         str[i] = (char *) malloc(sizeof(char) * 5);
//         i++;
//     }
//     i = 0;
//     while (i < 4)
//     {
//         ft_lstadd_back(&infos.garbage, ft_lstnew(str[i]));
//         i++;
//     }
//     free_all(&infos, "free all", 1);
// }

// int main()
// {
//     main2();
//     system("leaks cub3d");
// }
