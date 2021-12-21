/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_parser_common_part.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalendi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 19:05:41 by lcalendi          #+#    #+#             */
/*   Updated: 2020/07/23 20:28:56 by lcalendi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	img_parse(char *line, t_main *data, void **image, t_texture *which)
{
	int loop;
	int t[3];
	int wi;
	int he;

	loop = 2;
	while (line[loop] == ' ')
		loop++;
	if (!(*image = mlx_xpm_file_to_image(data->mlx, &line[loop], &wi, &he)))
		return (-1);
	if (which)
	{
		which->width = wi;
		which->height = he;
		if (!new_malloc(which->texture = malloc((wi + 1) * 8), data))
			return (-1);
		which->texture[0] = (int*)mlx_get_data_addr(*image, t, t + 1, t + 2);
		loop = 0;
		while (++loop != which->width)
			which->texture[loop] = which->texture[0] + loop * (t[1] / 4);
		which->texture[loop] = NULL;
	}
	data->last_malloc->img = *image;
	return (0);
}
