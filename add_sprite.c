/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalendi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 19:57:13 by lcalendi          #+#    #+#             */
/*   Updated: 2020/08/03 14:41:19 by lcalendi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	reset_sprite_map(t_main *data)
{
	int loop;
	int leep;

	loop = 0;
	while (data->sprite_map[loop])
	{
		leep = 0;
		while (data->sprite_map[loop][leep])
			data->sprite_map[loop][leep++] = 1;
		loop++;
	}
}

void	add_sprite_2(t_sprite_list *link, t_main *data, t_vars *vars)
{
	float s_x;
	float s_y;

	s_x = (float)vars->x + 0.5;
	s_y = (float)vars->y + 0.5;
	link->s_distance = sqrtf((s_x - link->x_cross) * (s_x - link->x_cross)
			+ (s_y - link->y_cross) * (s_y - link->y_cross));
	if (link->s_distance >= 0.5 || ((link->x_cross - data->you.fx > 0) !=
	(vars->fx_add > 0) && (link->y_cross - data->you.fy > 0)
	!= (vars->fy_add > 0)))
	{
		vars->list = link->next;
		free(link);
		link = 0;
	}
	else if (data->sprite_map[vars->y][vars->x] > link->s_distance)
	{
		data->sprite_map[vars->y][vars->x] = link->s_distance;
		link->s_distance = 0.5 - link->s_distance;
	}
	else
	{
		data->sprite_map[vars->y][vars->x] = link->s_distance;
		link->s_distance += 0.5;
	}
}

void	add_sprite(t_sprite_list *list, t_main *data, t_vars *vars)
{
	t_sprite_list	*link;
	float			x_diff;
	float			y_diff;
	float			s_x;
	float			s_y;

	link = malloc(sizeof(t_sprite_list));
	link->next = list;
	vars->list = link;
	s_x = (float)vars->x + 0.5;
	s_y = (float)vars->y + 0.5;
	x_diff = data->you.fx - s_x;
	y_diff = data->you.fy - s_y;
	link->distance = sqrtf(x_diff * x_diff + y_diff * y_diff);
	link->size = data->constant.height / (float)link->distance;
	link->p_line_factor = vars->fy_add / vars->fx_add;
	link->p_line_term = data->you.fy - (data->you.fx * link->p_line_factor);
	link->s_line_factor = (s_x - data->you.fx) / (-(s_y - data->you.fy));
	link->s_line_term = s_y - (s_x * link->s_line_factor);
	link->x_cross = (link->p_line_term - link->s_line_term)
		/ (link->s_line_factor - link->p_line_factor);
	link->y_cross = link->x_cross * link->p_line_factor + link->p_line_term;
	add_sprite_2(link, data, vars);
}
