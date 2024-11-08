/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_collisions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 05:47:08 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/08 07:00:50 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


int *is_ent_colliding(t_mlx_data *mlx_data, t_ent *e)
{
    t_ent *env;
    int *col_dir;
    int i;

    col_dir = (int *)calloc(5, sizeof(int));
    if (!col_dir)
        return NULL;
    i = -1;
    while (++i < ENV_AMOUNT)
    {
        env = &mlx_data->ENVIRONMENT[i];
        if (env == e)
            continue;
        t_dir collision_side = is_colliding(e, env);
        if (collision_side != none)
            col_dir[collision_side] = 1;
    }

    if (!col_dir[up] && !col_dir[down] && !col_dir[left] && !col_dir[right])
    {
        free(col_dir);
        return NULL;
    }

    return col_dir;
}

t_dir is_colliding(t_ent *entity1, t_ent *entity2)
{
    if (entity1->pos.x < entity2->pos.x + entity2->size.x &&
        entity1->pos.x + entity1->size.x > entity2->pos.x &&
        entity1->pos.y < entity2->pos.y + entity2->size.y &&
        entity1->pos.y + entity1->size.y > entity2->pos.y)
    {
        int delta_left = (entity1->pos.x + entity1->size.x) - entity2->pos.x;
        int delta_right = (entity2->pos.x + entity2->size.x) - entity1->pos.x;
        int delta_top = (entity1->pos.y + entity1->size.y) - entity2->pos.y;
        int delta_bottom = (entity2->pos.y + entity2->size.y) - entity1->pos.y;

        if (delta_top < delta_bottom && delta_top < delta_left && delta_top < delta_right)
            return down;
        else if (delta_bottom < delta_top && delta_bottom < delta_left && delta_bottom < delta_right)
            return up;
        else if (delta_left < delta_right - 10 && delta_left < delta_top && delta_left < delta_bottom - 10)
            return left;
        else if (delta_right < delta_top - 10 && delta_right < delta_bottom - 10)
            return right;
    }
    return none;
}