/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:29:47 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/08 06:28:04 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	init_mlx_data(t_mlx_data *mlx_data)
{
	int	i;

	i = -1;
	while (++i < 512)
		mlx_data->key_state[i] = 0;
	mlx_data->mlx = mlx_init();
	if (!mlx_data->mlx)
		return (printf("Error initializing MLX\n"), 0);
	mlx_data->win = mlx_new_window(mlx_data->mlx, WIN_W, WIN_H, "g");
	if (!mlx_data->win)
		return (printf("Error creating window\n"), 0);
	mlx_data->background_color = mlx_new_image(mlx_data->mlx, WIN_W, WIN_H);
	if (!mlx_data->background_color)
		return (printf("Error creating background image\n"), 0);
	mlx_data->addr = mlx_get_data_addr(mlx_data->background_color, &mlx_data->bits_per_pixel, &mlx_data->line_length, &mlx_data->endian);

	for (int y = 0; y < 50; y++)
	{
		for (int x = 0; x < 50; x++)
		{
			my_mlx_pixel_put(mlx_data, x, y, 0x00FF0000);
		}
	}
	mlx_data->background_img = add_img(BACKGROUND_SPRITE_PATH, &mlx_data->size.x, &mlx_data->size.y, mlx_data->mlx);
	mlx_data->ground = add_img(GROUND_SPRITES_PATH, &mlx_data->size.x, &mlx_data->size.y, mlx_data->mlx);
	return (1);
}

int	init_mobs(t_mlx_data *mlx_data, char *frames_path, int ammount)
{
	t_ent	*ent;
	char	**idle_frames;
	char	**wlk_frm;
	int		i;

	idle_frames = get_frames_paths(frames_path, "IDLE_", 2);
	wlk_frm = get_frames_paths(frames_path, "WALK_", 2);
	i = -1;
	while (++i < ammount)
	{
		ent = &mlx_data->MOBS[i];
		ent->type = mob;
		ent->flip_X = 0;
		ent->walk_frame_amount = 2;
		ent->idle_frame_amount = 2;
		set_Vec3(&ent->pos, rand_range(0, WIN_W), 0, 1);
		set_Vec3(&ent->movement, rand_range(-1, 2), rand_range(-1, 2), 0);
		set_entity_frames(mlx_data, &mlx_data->MOBS[i], wlk_frm, idle_frames, 2);
	}
	free(idle_frames);
	free(wlk_frm);
	return (1);
}

int	init_player(t_mlx_data *mlx_data, char *frames_path)
{
	char	**idle_frames;
	char	**wlk_frm;
	t_ent	*player;

	player = &mlx_data->player;
	player->flip_X = 0;
	player->jet_sky_timer = 0;
	set_Vec3(&player->pos, WIN_W / 2, 0, 0);
	set_Vec3(&player->movement, 0, 0, 0);
	set_Vec2(&player->size, 50, 50);
	player->type = Player;
	idle_frames = get_frames_paths(frames_path, "IDLE_", 2);
	wlk_frm = get_frames_paths(frames_path, "WALK_", 2);
	player->walk_frame_amount = 2;
	player->idle_frame_amount = 2;
	set_entity_frames(mlx_data, &mlx_data->player, wlk_frm, idle_frames, 2);
	return (1);
}

int	init_env(t_mlx_data *mlx_data)
{
	char **frames;
	void	*imgs[4];
	t_ent *e;
	int i;
	int r;
	t_Vec2 size[4];

	frames = get_frames_paths(WALL_SPRITES_PATH, "WALL_", 4);
	i = -1;
	while (++i < 4)
		imgs[i] = add_img(frames[i], &size[i].x, &size[i].y, mlx_data->mlx);
	i = -1;
	while (++i < ENV_AMOUNT)
	{
		e = &mlx_data->ENVIRONMENT[i];
		r = rand_range(0, 3);
		set_Vec3(&e->pos, rand_range(0, WIN_W - size[r].x), rand_range(0, WIN_H - size[r].y), 0);
		set_Vec3(&e->movement,0,0,0);
		e->size = size[r];
		e->jet_sky_timer = 0;
		e->type = env;
		e->cur_frame = imgs[r];
	}
	free(frames);
	return (1);
}

int	init_entities(t_mlx_data *mlx_data)
{
	init_player(mlx_data, PLAYER_SPRITES_PATH);
	init_mobs(mlx_data, MOB_SPRITES_PATH, MOB_AMOUNT);
	init_env(mlx_data);
	return (1);
}
