/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_render.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:42:36 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/08 03:44:25 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	render_player(t_mlx_data *mlx_data)
{
	t_ent	*player;

	player = &mlx_data->player;
	if (player->flip_X)
		mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, \
		player->cur_frame_xFlip, player->pos.x, player->pos.y);
	else
		mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, \
		player->cur_frame, player->pos.x, player->pos.y);
}

void	render_mobs(t_mlx_data *mlx_data)
{
	t_ent	*mob;
	int		i;

	sort_entities_by_z_pos(mlx_data->MOBS, MOB_AMOUNT);
	i = -1;
	while (++i < MOB_AMOUNT)
	{
		mob = &mlx_data->MOBS[i];
		if (mob->flip_X)
			mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, \
			mob->cur_frame_xFlip, mob->pos.x, mob->pos.y);
		else
			mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, \
			mob->cur_frame, mob->pos.x, mob->pos.y);
	}
}

void render_env(t_mlx_data *mlx_data)
{
	t_ent *e;
	int i;

	i = -1;
	while (++i < ENV_AMOUNT)
	{
		e = &mlx_data->ENVIRONMENT[i];
		mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, \
			e->cur_frame, e->pos.x, e->pos.y);
	}
}

void	render_images(t_mlx_data *mlx_data)
{
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, \
	mlx_data->background_img, 0, 0);
	render_env(mlx_data);
	render_mobs(mlx_data);
	render_player(mlx_data);
}
