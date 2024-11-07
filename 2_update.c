/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_update.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:08:31 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/07 22:32:25 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void handle_movement(t_ent *e, int base_speed)
{
    int adjusted_speed;

    if (e->movement.x != 0)
    {
        adjusted_speed = base_speed * (abs(e->movement.x) / (float)MV_DUR);
        if (e->movement.x > 0)
        {
            e->movement.x--;
            e->pos.x += adjusted_speed;
        }
        else if (e->movement.x < 0)
        {
            e->movement.x++;
            e->pos.x -= adjusted_speed;
        }
    }
    if (e->movement.y != 0)
    {
        adjusted_speed = base_speed * (abs(e->movement.y) / (float)MV_DUR);

        if (e->movement.y > 0)
        {
            e->movement.y--;
            e->pos.y += adjusted_speed;
        }
        else if (e->movement.y < 0)
        {
            e->movement.y++;
            e->pos.y -= adjusted_speed;
        }
    }
}

int update_entity(t_ent *e, t_Vector3 frame_movement, int speed)
{
	if (frame_movement.x != 0)
	{
		e->movement.x = frame_movement.x * MV_DUR;
		if (frame_movement.x > 0)
			e->flip_X = 0;
		else
			e->flip_X = 1;
	}
	if (frame_movement.y != 0)
		e->movement.y = frame_movement.y * MV_DUR;
	if (frame_movement.z != 0)
		e->movement.z = frame_movement.z * MV_DUR;

	handle_movement(e, speed);
	return (1);
}

int update_mobs(t_mlx_data *mlx_data)
{
	t_Vector3 new_movement;
    int i;

    i = -1;
    while (++i < MOB_AMOUNT)
    {
		set_Vec3(&new_movement, 0,0,0);
		if (rand() % 500 == 0)
			new_movement = rand_Vec3(-MV_DUR / 2, MV_DUR / 2);
        update_entity(&mlx_data->MOBS[i], new_movement, MOBS_SPEED);
    }
	return (1);
}

int update_player(t_mlx_data *mlx_data)
{
	int move_speed;
	t_Vector3 new_movement;

	new_movement.x = 0;
	new_movement.y = 0;
	new_movement.z = 0;
	if (mlx_data->key_state[LEFT_KEY] || mlx_data->key_state[A_KEY])
		new_movement.x = -1;
	else if (mlx_data->key_state[RIGHT_KEY] || mlx_data->key_state[D_KEY])
		new_movement.x = 1;
	if (mlx_data->key_state[UP_KEY] || mlx_data->key_state[W_KEY])
		new_movement.y = -1;
	else if (mlx_data->key_state[DOWN_KEY] || mlx_data->key_state[S_KEY])
		new_movement.y = 1;
	if (mlx_data->key_state[SHIFT_KEY])
		move_speed = PLAYER_SPEED * 3;
	else
		move_speed = PLAYER_SPEED;
	return (update_entity(&mlx_data->player, new_movement, move_speed));
}

int update(t_mlx_data *mlx_data)
{
	(void)
	mlx_data;
	update_player(mlx_data);
	update_mobs(mlx_data);
	return (1);
}