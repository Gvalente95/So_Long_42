/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:24:00 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/06 17:40:47 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


void	*add_img(char *relative_path, int width, int height, void *mlx)
{
	void	*img;
	img = mlx_png_file_to_image(mlx, relative_path, &width, &height);
	if (!img)
	{
		printf("ERROR");
		return (NULL);
	}
	return (img);
}