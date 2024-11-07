/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:32:42 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/07 22:26:53 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

#include <mlx.h>
#include "libft/libft.h"
#include "Keys.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

#define PLAYER_SPRITES_PATH "PNG/ENTITIES/PLAYER/"
#define MOB_SPRITES_PATH "PNG/ENTITIES/MOBS/"

#define PLAYER_IDLE_0 "PNG/ENTITIES/PLAYER/IDLE_0.png"
#define PLAYER_IDLE_1 "PNG/ENTITIES/PLAYER/IDLE_1"
#define PLAYER_WALK_0 "PNG/ENTITIES/PLAYER/WALK_0"
#define PLAYER_WALK_1 "PNG/ENTITIES/PLAYER/WALK_1"

#define GROUND_0 "PNG/TILES/GROUND_0"
#define WALL_0 "PNG/TILES/WALL_0"

#define WIN_WIDTH 	1980
#define WIN_HEIGHT 	1080

#define	MOB_AMOUNT 	10
#define	COIN_AMOUNT 10
#define ENV_AMOUNT 10

#define MV_DUR 20
#define MV_AM 2

#define PLAYER_SPEED 3
#define MOBS_SPEED 2

typedef enum e_dir {up, left, down, right} t_dir;
typedef enum e_entity_types {Player, mob, coin} t_ent_type;

typedef struct s_Vector2
{
	int x;
	int y;
} t_Vector2;

typedef struct s_Vector3
{
	int x;
	int y;
	int z;
} t_Vector3;

typedef struct s_entity
{
	void		*cur_frame;
	void		*cur_frame_xFlip;

	void		*walk_frames[3];
	void		*idle_frames[3];
	void		*walk_frames_xFLip[3];
	void		*idle_frames_xFlip[3];

	int			walk_frame_amount;
	int			idle_frame_amount;
	int			hp;
	int			flip_X;
	t_ent_type 	type;
	t_dir 		dir;
	t_Vector3			pos;
	t_Vector2			size;
	t_Vector3			movement;
}	t_ent;

typedef struct	s_mlx_data 
{
	t_ent       **ENTITIES;
	t_ent		ENVIRONMENT[ENV_AMOUNT];
	t_ent		COINS[COIN_AMOUNT];
	t_ent		MOBS[MOB_AMOUNT];
	t_ent		player;
	int 		key_state[512];
	int			last_key_pressed;
	void		*mlx;
	void		*win;
	void		*background_img;
	void		*images;
	void		*tiles;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_mlx_data;


// INIT
int 	init_mlx_data(t_mlx_data *mlx_data);
int 	init_entities(t_mlx_data *mlx_data);
// UPDATE
int 	update(t_mlx_data *mlx_data);

// RENDER
void 	render_images(t_mlx_data *mlx_data);

// IMAGE
void 	*add_img(char *relative_path, int *width, int *height, void *mlx);
void    my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color);

// INPUT
int 	handle_key_release(int keycode, t_mlx_data *mlx_data);
int 	handle_key_press(int keycode, t_mlx_data *mlx_data);

// TOOLS
void 		sort_entities_by_z_pos(t_ent *entities, int count);
char 		**get_frames(char *path, char *suffix, int amount);
int 		set_Vec2(t_Vector2 *Vec2, int x, int y);
int 		set_Vec3(t_Vector3 *Vec3, int x, int y, int z);
char 		print_Vec3(t_Vector3 Vec3);
int 		rand_range(int min, int max);
t_Vector3 	rand_Vec3(int min, int max);
void 		*flip_image_x(void *mlx, void *img, int width, int height);

#endif