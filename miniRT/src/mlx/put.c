#include "main.h"

void	put_pixel(int x, int y, int color)
{
	char	*dst;

	dst = data()->addr + (y * data()->line_length + x * (data()->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
	printf("Pixel at %d, %d is %d\n", x, y, color);
}
