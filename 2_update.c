/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_update.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:08:31 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/08 07:02:23 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	handle_col(t_ent *e, int *col_dir)
{
	int displ_am;

	displ_am = 10;
	if (col_dir[left])
		e->pos.x -= displ_am;
	if (col_dir[right])
		e->pos.x += displ_am;
	if (col_dir[up])
		e->pos.y -= displ_am;
	if (col_dir[up] || col_dir[down])
		e->movement.y = 0;
	if (col_dir[left] || col_dir[right])
		e->movement.x = 0;
}
char dirs[4][20] = {"up", "down", "left", "right"};
void	handle_movement(t_mlx_data *mlx_data, t_ent *e, int base_speed_x, int base_speed_y)
{
	int	adjusted_speed;
	int *col_dir;

	col_dir = is_ent_colliding(mlx_data, e);
	if (col_dir != NULL) 
	{
		handle_col(e, col_dir);
		if (e->type == Player && mlx_data->time % 50 == 0)
		{
			for (int i = 0; i < 4; i++)
				if (col_dir[i])
					ft_printf("COL %s: %i\n", dirs[i], col_dir[i]);
			ft_printf("\n");
		}
	}
	if (e->movement.x != 0)
	{
		adjusted_speed = base_speed_x * (abs(e->movement.x) / (float)MV_DUR);
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
		adjusted_speed = base_speed_y * (abs(e->movement.y) / (float)MV_DUR);
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

int	update_entity(t_ent *e, t_Vec3 frm_mv, int speed_x, int speed_y, t_mlx_data *mlx)
{
	if (mlx->key_state[UP_KEY])
		frm_mv.y = -1;
	if (e->pos.y < GROUND_LEVEL)
		e->action = FALL;
	if (e->jump_timer > 0)
	{
		e->jump_timer--;
		if (e->jump_timer <= 0)
		{
			e->jump_timer = 0;
			e->action = IDLE;
		}
	}
	if (e->pos.y > GROUND_LEVEL + 1)
	{
		if (e->action == FALL)
			e->action = IDLE;
		e->movement.y = 0;
		e->pos.y = GROUND_LEVEL;
	}
	if (e->action == FALL)
	{
		e->movement.y+=10;
		handle_movement(mlx, e, speed_x, speed_y); 		
	}
	else
	{
		if (frm_mv.x != 0)
		{
			e->movement.x = frm_mv.x * MV_DUR;
			if (frm_mv.x > 0)
				e->flip_X = 0;
			else
				e->flip_X = 1;
		}
		if (frm_mv.y != 0)
			e->movement.y = frm_mv.y * MV_DUR;
	}
	if ((frm_mv.x == 0 && frm_mv.y == 0))
	{
		e->cur_frame = e->idl_frm[e->cur_frame_index];
		e->cur_frame_xFlip = e->idl_frm_x[e->cur_frame_index];
		e->action = IDLE;
	}
	else
	{
		e->cur_frame = e->wlk_frm[e->cur_frame_index];
		e->cur_frame_xFlip = e->wlk_frm_x[e->cur_frame_index];
		e->action = WALK;
	}
	if (mlx->time % ANIM_REFRESH == 0)
	{
		e->cur_frame_index++;
		if (e->cur_frame_index > e->idle_frame_amount - 1)
			e->cur_frame_index = 0;
	}
	handle_movement(mlx, e, speed_x, speed_y);
	return (1);
}

char *action_names[5] = {"WALK", "FALL", "IDLE", "JUMP"};

int update_mobs(t_mlx_data *mlx_data)
{
	t_Vec3	new_movement;
	int			i;

	i = -1;
	while (++i < MOB_AMOUNT)
	{
		set_Vec3(&new_movement, 0,0,0);
		if (rand() % 500 == 0)
			new_movement = rand_Vec3(-MV_DUR / 2, MV_DUR / 2);
		update_entity(&mlx_data->MOBS[i], new_movement, MOBS_SPEED, MOBS_SPEED, mlx_data);
	}
	return (1);
}

int	update_player(t_mlx_data *mlx_data)
{
	int			move_speed[2];
	t_Vec3	new_mv;

	//printf("PLAYER: %s JMP_TIMER: %d\n", action_names[mlx_data->player.action], mlx_data->player.jump_timer);
	set_Vec3(&new_mv, 0,0,0);
	if (mlx_data->key_state[LEFT_KEY] || mlx_data->key_state[A_KEY])
		new_mv.x = -1;
	else if (mlx_data->key_state[RIGHT_KEY] || mlx_data->key_state[D_KEY])
		new_mv.x = 1;
	else if (mlx_data->key_state[DOWN_KEY] || mlx_data->key_state[S_KEY])
		new_mv.y = 1;
	if (mlx_data->key_state[SPACE_KEY] && mlx_data->player.jump_timer == 0 && mlx_data->player.action != FALL)
	{
		mlx_data->player.jump_timer = 60;
		new_mv.y = -4;
	}
	if (mlx_data->key_state[SHIFT_KEY])
		move_speed[0] = PLAYER_SPEED * 3;
	else
		move_speed[0] = PLAYER_SPEED;
	move_speed[1] = PLAYER_SPEED;
	return (update_entity(&mlx_data->player, new_mv, move_speed[0], move_speed[1], mlx_data));
}

int	update(t_mlx_data *mlx_data)
{
	update_player(mlx_data);
	update_mobs(mlx_data);
	return (1);
}
