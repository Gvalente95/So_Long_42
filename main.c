/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:23:39 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/06 18:13:07 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	t_data	d;

	d.mlx = mlx_init();
	d.win = mlx_new_window(d.mlx, 1920, 1080, "Hello world!");

	d.background_img = mlx_new_image(d.mlx, 1920, 1080);
	d.addr = mlx_get_data_addr(d.background_img, &d.bits_per_pixel, &d.line_length,
								&d.endian);
	d.x_pos = 0;

	my_mlx_pixel_put(&d, 5, 5, 0x00FF0000);
	ft_printf("hello");
	
	//d.images = add_img(TEST_LOGO, 50, 50, img.mlx)
	//mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	//mlx_loop_hook(img.mlx, move_image, &img);
	//mlx_loop(img.mlx);
}

int	move_image(t_data *data)
{
	//mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);

	data->x_pos += 1;

	//mlx_put_image_to_window(data->mlx, data->mlx_win, data->new_img, data->x_pos, 50);

	if (data->x_pos > 1920)
		data->x_pos = 0;

	usleep(30000);
	return (0);
}