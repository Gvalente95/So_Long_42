/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:23:39 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/07 23:02:22 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	update_and_render(t_mlx_data *mlx_data)
{
	mlx_data->time++;
	update(mlx_data);
	render_images(mlx_data);
	return (0);
}

int	main(void)
{
	t_mlx_data	mlx_data;

	mlx_data.time = 0;
	srand(time(0));
	if (!init_mlx_data(&mlx_data))
		return (1);
	if (!init_entities(&mlx_data))
		return (1);
	mlx_hook(mlx_data.win, KEY_PRESS, 0, handle_key_press, &mlx_data);
	mlx_hook(mlx_data.win, KEY_RELEASE, 0, handle_key_release, &mlx_data);
	mlx_loop_hook(mlx_data.mlx, (int (*)())update_and_render, &mlx_data);
	mlx_loop(mlx_data.mlx);
	return (0);
}
