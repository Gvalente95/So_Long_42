/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_images.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:31:53 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/08 03:50:17 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void    my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void swap_entities(t_ent *a, t_ent *b)
{
    t_ent temp = *a;
    *a = *b;
    *b = temp;
}

void sort_entities_by_z_pos(t_ent *entities, int count)
{
	int i;
	int	j;

	
	i = -1;
	j = -1;
	while (++i < count - 1)
	{
		while (++j < count - i -1)
		{
			if (entities[j].pos.z > entities[j + 1].pos.z)
                swap_entities(&entities[j], &entities[j + 1]);
		}
	}
}

void *add_img(char *relative_path, int *width, int *height, void *mlx)
{
    void *img;

    if (!relative_path) {
        ft_printf("Tried to add image with null path\n");
        return NULL;
    }
    if (!mlx) {
        ft_printf("Error: mlx instance is NULL\n");
        return NULL;
    }
    img = mlx_png_file_to_image(mlx, relative_path, width, height);
    if (!img) {
        printf("ERROR: Failed to load image at path: %s\n", relative_path);
        return NULL;
    }
    //printf("Image loaded successfully from path: %s, Width: %d, Height: %d\n", relative_path, *width, *height);
    return img;
}

int	set_entity_frames(t_mlx_data *d, t_ent *e, char **WLK_P, char **IDLE_P, int amount)
{
	int	i;

	if (WLK_P != NULL)
	{
		i = -1;
		while (++i < amount)
		{
			if (WLK_P[i] != NULL)
			{
				e->wlk_frm[i] = add_img(WLK_P[i], &e->size.x, &e->size.y, d->mlx);
				if (e->wlk_frm[i] != NULL)
					e->wlk_frm_x[i] = flip_image_x(d->mlx, e->wlk_frm[i], e->size.x, e->size.y);
			}
			if (IDLE_P[i] != NULL)
			{
				e->idl_frm[i] = add_img(IDLE_P[i], &e->size.x, &e->size.y, d->mlx);
				if (e->idl_frm[i] != NULL)
					e->idl_frm_x[i] = flip_image_x(d->mlx, e->idl_frm[i], e->size.x, e->size.y);
			}
		}
	}
	e->cur_frame = e->idl_frm[0];
	e->cur_frame_xFlip = e->idl_frm_x[0];
	e->cur_frame_index = 0;
	e->jump_timer = 0;
	e->action = IDLE;
	return (1);
}