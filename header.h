/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:32:42 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/06 18:05:56 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

#include <mlx.h>
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define TEST_LOGO "TEST_IMG.png"
#define WIN_WIDTH 1980
#define WIN_HEIGHT 1080


typedef struct	s_data {
	void	*mlx;
	void	*win;
	void	*background_img;
	void	*images;
	void	*tiles;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x_pos;
	int		y_pos;
}				t_data;

void	*add_img(char *relative_path, int width, int height, void *mlx_screen);

#endif