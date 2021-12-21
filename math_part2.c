/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_part2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalendi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 20:00:57 by lcalendi          #+#    #+#             */
/*   Updated: 2020/07/23 20:32:07 by lcalendi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_column_while(t_main *data, t_vars *vars, int rgb)
{
	vars->loop = data->constant.h2 - vars->list->size;
	vars->see = data->constant.h2 + vars->list->size;
	vars->temp2 = vars->see - vars->loop + 1;
	vars->fx_add = (float)(vars->see - data->constant.i_height + 1)
	/ (float)vars->temp2;
	vars->loop = (vars->loop < 0) ? 0 : vars->loop;
	vars->see = (vars->see >= data->constant.i_height) ?
		data->constant.i_height - 1 : vars->see;
	vars->temp1 = 0;
	while (vars->loop < vars->see)
	{
		rgb = data->parse.prite.texture[(int)((((float)vars->temp1
	/ (float)vars->temp2) + ((vars->fx_add > 0) ? vars->fx_add : 0))
	* (float)data->parse.prite.height)]
	[(int)(vars->list->s_distance * (float)data->parse.prite.width)];
		if (rgb % (256 * 256 * 256))
			data->image[vars->loop][vars->leep] = rgb;
		vars->loop++;
		vars->temp1++;
	}
	vars->temp = vars->list->next;
	free(vars->list);
	vars->list = 0;
	vars->list = vars->temp;
}

void	fill_column_2(t_main *data, t_vars *vars, int places)
{
	while (vars->loop >= 0)
		if (vars->loop >= data->constant.h2 - vars->see)
		{
			data->image[vars->loop][vars->leep] = vars->which->texture
[(vars->which->height / 2 - 1) - (int)(((float)(data->constant.h2 - vars->loop)
	/ (float)(vars->see * 2 + 1)) * (vars->which->height))]
[(vars->which->width - 1) - places];
			vars->loop--;
		}
		else
			data->image[vars->loop--][vars->leep] = data->parse.ceiling;
	vars->loop = 0;
	data->image += data->constant.h2;
	while (vars->loop != data->constant.h2)
		if (vars->loop < vars->see)
		{
			data->image[vars->loop][vars->leep] = vars->which->texture
[(vars->which->height / 2) + (int)(((float)(vars->loop) / (float)(vars->see
	* 2 + 1)) * (vars->which->height))][(vars->which->width - 1) - places];
			vars->loop++;
		}
		else
			data->image[vars->loop++][vars->leep] = data->parse.flor;
	data->image -= data->constant.h2;
}

void	fill_column(t_main *data, t_vars *vars)
{
	int places;

	vars->see = data->constant.height /
(sqrtf(powf(data->you.fx - vars->fx, 2) + powf(data->you.fy - vars->fy, 2))
	* (cosf(vars->angel) > 0 ? cosf(vars->angel) : -cosf(vars->angel)));
	places = vars->which->goal ?
(*vars->which->pos - floorf(*vars->which->pos)) * vars->which->height :
(ceilf(*vars->which->pos) - *vars->which->pos)
		* vars->which->width;
	vars->loop = data->constant.h2 - 1;
	fill_column_2(data, vars, places);
	while (vars->list)
	{
		fill_column_while(data, vars, 0);
	}
	vars->angle += data->constant.add_fov;
	vars->angel += data->constant.add_fov;
	vars->leep++;
}
