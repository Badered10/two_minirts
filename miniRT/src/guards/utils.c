#include "../../includes/main.h"

int	ft_int_len(int n)
{
	int	len;

	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int split_len(char **split)
{
    int i;

    if (!split)
        return 0;
    i = 0;
    while (split[i])
        i++;
    return i;
}

double double_guard(char *arg, int line, double min, double max)
{
    double   left;
    double   right;
    char    **lighting_ratio;
    double   res;


    if (ft_strlen(arg) < 3 || !ft_strchr(arg, '.'))
    {
        res = (double)ft_atoi(arg);
        if (res < min || res > max)
            throw_error("Value out of range in line: ", line, arg);
        return res;
    }

    res = .0;
    lighting_ratio = ft_c_split(arg, ".");
    left = ft_atoi(lighting_ratio[0]);
    right = ft_atoi(lighting_ratio[1]);
    if ((left > max) || (left == max && right != 0))
        throw_error("Value out of range in line: ", line, arg);
    if (left < min)
        throw_error("Value out of range in line: ", line, arg);
    res += left;
    res += (double)((right) * pow(10, -(ft_int_len(right))));
    return res;
}
