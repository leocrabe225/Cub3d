/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_part3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalendi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 20:03:13 by lcalendi          #+#    #+#             */
/*   Updated: 2020/07/23 20:10:21 by lcalendi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	x_math(t_main *data, t_vars *vars)
{
	if (vars->fx_add > 0)
	{
		vars->which = &data->parse.nord;
		vars->temp1 = (floorf(vars->fx + 1) - vars->fx) / vars->fx_add;
		vars->ax = 1;
	}
	else if (vars->fx_add < 0)
	{
		vars->which = &data->parse.sud;
		vars->temp1 = (vars->fx - ceilf(vars->fx - 1)) / (-vars->fx_add);
		vars->ax = -1;
	}
	else
	{
		vars->which = &data->parse.nord;
		vars->temp1 = 10;
		vars->ax = 0;
	}
}

void	y_math(t_main *data, t_vars *vars)
{
	if (vars->fy_add > 0)
	{
		vars->which2 = &data->parse.est;
		vars->temp2 = (floorf(vars->fy + 1) - vars->fy) / vars->fy_add;
		vars->ay = 1;
	}
	else if (vars->fy_add < 0)
	{
		vars->which2 = &data->parse.ouest;
		vars->temp2 = (vars->fy - ceilf(vars->fy - 1)) / (-vars->fy_add);
		vars->ay = -1;
	}
	else
	{
		vars->which = &data->parse.est;
		vars->temp2 = 10;
		vars->ay = 0;
	}
}

void	end_math(t_vars *vars)
{
	if (vars->temp1 == vars->temp2)
	{
		vars->x += vars->ax;
		vars->y += vars->ay;
		return ;
	}
	else if (vars->temp1 > vars->temp2)
	{
		vars->temp1 = vars->temp2;
		vars->which = vars->which2;
		vars->fx += vars->fx_add * vars->temp1;
		vars->fy += vars->fy_add * vars->temp1;
		vars->y += vars->ay;
		if (vars->fx == floorf(vars->fx)
				&& vars->fx != vars->fx - vars->fx_add * vars->temp1)
			vars->x += vars->ax;
		return ;
	}
	vars->fx += vars->fx_add * vars->temp1;
	vars->fy += vars->fy_add * vars->temp1;
	vars->x += vars->ax;
	if (vars->fy == floorf(vars->fy)
			&& vars->fy != vars->fy - vars->fy_add * vars->temp1)
		vars->y += vars->ay;
}
