#include "header.h"

void set_img_color(int width, int height, void *frame, int new_color, float intensity)
{
    int     x;
    int     y;
    int     *addr;
    int     bpp;
    int     line_length;
    int     endian;

    addr = (int *)mlx_get_data_addr(frame, &bpp, &line_length, &endian);
    y = -1;
    while (++y < height)
    {
        x = -1;
        while (++x < width)
        {
            int pixel_index = (y * line_length / 4) + x;
            int pixel_color = addr[pixel_index];

            if (pixel_color)
            {
                int original_alpha = (pixel_color & 0xFF000000);
                int original_red = (pixel_color & 0x00FF0000) >> 16;
                int original_green = (pixel_color & 0x0000FF00) >> 8;
                int original_blue = (pixel_color & 0x000000FF);
                int new_red = (new_color & 0x00FF0000) >> 16;
                int new_green = (new_color & 0x0000FF00) >> 8;
                int new_blue = (new_color & 0x000000FF);
                int blended_red = (int)((original_red * (1 - intensity)) + (new_red * intensity));
                int blended_green = (int)((original_green * (1 - intensity)) + (new_green * intensity));
                int blended_blue = (int)((original_blue * (1 - intensity)) + (new_blue * intensity));
                addr[pixel_index] = original_alpha | (blended_red << 16) | (blended_green << 8) | blended_blue;
            }
        }
    }
}


void adjust_image_brightness(int width, int height, void *frame, float brightness_factor)
{
    int     x;
    int     y;
    int     *addr;
    int     bpp;
    int     line_length;
    int     endian;

    addr = (int *)mlx_get_data_addr(frame, &bpp, &line_length, &endian);
    y = -1;
    while (++y < height)
    {
        x = -1;
        while (++x < width)
        {
            int pixel_index = (y * line_length / 4) + x;
            int pixel_color = addr[pixel_index];

            //if (get_t(pixel_color) != 0)
            {
                unsigned char alpha = get_t(pixel_color);
                unsigned char red = get_r(pixel_color);
                unsigned char green = get_g(pixel_color);
                unsigned char blue = get_b(pixel_color);

                red = (unsigned char)(red * brightness_factor);
                green = (unsigned char)(green * brightness_factor);
                blue = (unsigned char)(blue * brightness_factor);
                addr[pixel_index] = create_trgb(alpha, red, green, blue);
            }
        }
    }
}

int	create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

unsigned char	get_t(int trgb)
{
	return (((unsigned char *)&trgb)[3]);
}

unsigned char	get_r(int trgb)
{
	return (((unsigned char *)&trgb)[2]);
}

unsigned char	get_g(int trgb)
{
	return (((unsigned char *)&trgb)[1]);
}

unsigned char	get_b(int trgb)
{
	return (((unsigned char *)&trgb)[0]);
}
