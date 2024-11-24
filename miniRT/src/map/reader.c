#include "main.h"

bool    is_valid_extension(char *filename)
{
    char *ext;

    ext = ft_strrchr(filename, '.');
    if (!ext)
        return (false);
    if (ft_strncmp(ext, ".rt", ft_strlen(ext)) != 0)
        return (false);
    return (true);
}

/**
 * this function will guard items
 */
void    *guard(char **split, int line)
{
    if (ft_strncmp(split[0], "A", ft_strlen(split[0])) == 0)
        return ambient_lighting_guard(split, line);
    else if (ft_strncmp(split[0], "C", ft_strlen(split[0])) == 0)
    {
        if ((scene())->camera)
            throw_error("Multiple cameras: ", line, NULL);
        scene()->camera = camera_guard(split, line);
        return scene()->camera;
    }
    else if (ft_strncmp(split[0], "L", ft_strlen(split[0])) == 0)
        return light_guard(split, line);
    else if (ft_strncmp(split[0], "sp", ft_strlen(split[0])) == 0)
        return sphere_guard(split, line);
    else if (ft_strncmp(split[0], "pl", ft_strlen(split[0])) == 0)
        return plane_guard(split, line);
    else if (ft_strncmp(split[0], "cy", ft_strlen(split[0])) == 0)
        return cylander_guard(split, line);
    return (NULL);
}

/**
 * this function will process the line
 */
void    process_line(char *line, int line_count)
{
    char        **split;
    void        *item;

    line = ft_strtrim(line, "\n");

    if (ft_strlen(line) == 0)
        return (throw_error("Empty line: ", line_count, NULL));

    split = ft_split(line, " \t");
    if (!split)
        throw_error("Invalid line: ", line_count, NULL);

    item = guard(split, line_count);
    if (item)
        return ;
    throw_error("Invalid arguments at line: ", line_count, line); 
}

/**
 * this function will read line by line
 */
void read_map_data(char *filename)
{
    int     fd;
    char    *line;
    int     line_count;

    if (!is_valid_extension(filename))
        throw_error("Invalid file extension", -1, filename);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        throw_error("Can't open file", -1, filename);
    line_count = 1;
    line = get_next_line(fd);
    if (!line)
        throw_error("Empty file", -1, filename);
    while (line)
    {
        process_line(line, line_count);
        delete_(line);
        line = get_next_line(fd);
        line_count++;
    }
}
