/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:29:47 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/07 22:27:38 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int init_mlx_data(t_mlx_data *mlx_data)
{
    int i;

    i = -1;
    while (++i < 254)
        mlx_data->key_state[i] = 0;
    mlx_data->mlx = mlx_init();
    if (!mlx_data->mlx)
        return (printf("Error initializing MLX\n"), 0);
    mlx_data->win = mlx_new_window(mlx_data->mlx, WIN_WIDTH, WIN_HEIGHT, "Hello world!");
    if (!mlx_data->win)
        return (printf("Error creating window\n"), 0);

    mlx_data->background_img = mlx_new_image(mlx_data->mlx, WIN_WIDTH, WIN_HEIGHT);
    if (!mlx_data->background_img)
        return (printf("Error creating background image\n"), 0);
    mlx_data->addr = mlx_get_data_addr(mlx_data->background_img,
                                       &mlx_data->bits_per_pixel,
                                       &mlx_data->line_length,
                                       &mlx_data->endian);

    my_mlx_pixel_put(mlx_data, 5, 5, 0x00FF0000);
    return (1);
}

int set_entity_frames(t_mlx_data *mlx_data, t_ent *e, char **WALK_PATHS, char **IDLE_PATHS)
{
    int i;

    if (WALK_PATHS != NULL)
    {
        i = -1;
        while (++i < 2)
        {
            if (WALK_PATHS[i] != NULL)
            {
                e->walk_frames[i] = add_img(WALK_PATHS[i], &e->size.x, &e->size.y, mlx_data->mlx);
                if (e->walk_frames[i] != NULL)
                    e->walk_frames_xFLip[i] = flip_image_x(mlx_data->mlx, e->walk_frames[i], e->size.x, e->size.y);
            }
            if (IDLE_PATHS[i] != NULL)
            {
                e->idle_frames[i] = add_img(IDLE_PATHS[i], &e->size.x, &e->size.y, mlx_data->mlx);
                if (e->idle_frames[i] != NULL)
                    e->idle_frames_xFlip[i] = flip_image_x(mlx_data->mlx, e->idle_frames[i], e->size.x, e->size.y);
            }
        }
    }
    e->cur_frame = e->idle_frames[0];
    e->cur_frame_xFlip = e->idle_frames_xFlip[0];
    return (1);
}

int init_mobs(t_mlx_data *mlx_data, char *frames_path, int ammount)
{
    char **idle_frames;
    char **walk_frames;
    int i;
    
    idle_frames = get_frames(frames_path, "IDLE_", 2);
    walk_frames = get_frames(frames_path, "WALK_", 2);

    i = -1;
    while (++i < ammount)
    {
        t_ent *ent = &mlx_data->MOBS[i];
        ent->type = mob;
        ent->flip_X = 0;
        ent->walk_frame_amount = 2;
        ent->idle_frame_amount = 2;
        set_Vec3(&ent->pos, rand_range(0, WIN_WIDTH), rand_range(0, WIN_HEIGHT), 1);
        set_Vec3(&ent->movement, rand_range(-1, 2), rand_range(-1, 2), 0);
        set_entity_frames(mlx_data, &mlx_data->MOBS[i], idle_frames, walk_frames);
	}
    free(idle_frames);
    free(walk_frames);
    return (1);
}


int init_player(t_mlx_data *mlx_data, char *frames_path)
{
    char **idle_frames;
    char **walk_frames;

    t_ent *player = &mlx_data->player;
    player->flip_X = 0;
    set_Vec3(&player->pos, WIN_WIDTH / 2, WIN_HEIGHT / 2, 0);
    set_Vec3(&player->movement, 0, 0, 0);
    set_Vec2(&player->size, 50, 50);
    player->type = Player;
    idle_frames = get_frames(frames_path, "IDLE_", 2);
    walk_frames = get_frames(frames_path, "WALK_", 2);
    player->walk_frame_amount = 2;
    player->idle_frame_amount = 2;
    set_entity_frames(mlx_data, &mlx_data->player, idle_frames,  walk_frames);
    return (1);
}

int init_entities(t_mlx_data *mlx_data)
{
    (void)mlx_data;
    init_player(mlx_data, PLAYER_SPRITES_PATH);
    init_mobs(mlx_data, MOB_SPRITES_PATH, MOB_AMOUNT);
    
    return (1);
}