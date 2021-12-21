/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalendi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 19:52:04 by lcalendi          #+#    #+#             */
/*   Updated: 2020/07/23 20:06:32 by lcalendi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		color(unsigned char r, unsigned char g, unsigned char b)
{
	return (256 * 256 * r + 256 * g + b);
}

void	initialize_colors(t_colors *colors)
{
	colors->lred = color(80, 0, 0);
	colors->lgreen = color(0, 80, 0);
	colors->blue = color(0, 0, 255);
	colors->red = color(255, 0, 0);
	colors->green = color(0, 255, 0);
	colors->black = color(0, 0, 0);
	colors->grey = color(128, 128, 128);
	colors->white = color(255, 255, 255);
}

int		initialize_keys(t_main *data)
{
	int loop;

	loop = 0;
	while (loop != 1024)
	{
		data->key_tab[loop] = 0;
		loop++;
	}
	return (0);
}

int		initialize(t_main *data)
{
	data->window = 0;
	initialize_colors(&data->colors);
	initialize_keys(data);
	data->you.fov = ((float)FOV / (float)360) * 2 * M_PI;
	data->you.speed = 0.1;
	data->constant.add_fov = data->you.fov / data->constant.i_width;
	data->constant.height = data->constant.i_height;
	if (!(new_malloc(data->image = malloc(8 * data->constant.i_height), data)))
		return (-1);
	if (!(new_malloc(data->image2 = malloc(8 * data->constant.i_height), data)))
		return (-1);
	return (0);
}

void	initialize_hooks(t_main *data)
{
	data->window = mlx_new_window(data->mlx, data->constant.i_width
			, data->constant.i_height, "cub3d");
	mlx_hook(data->window, 2, 1L << 0, *key_press, data);
	mlx_hook(data->window, 3, 1L << 1, *key_release, data);
	mlx_hook(data->window, 12, 0, *initialize_keys, data);
	mlx_hook(data->window, 17, 1L << 17, *destroy_hook, data);
}
