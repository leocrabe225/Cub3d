/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_part1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalendi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 22:51:23 by lcalendi          #+#    #+#             */
/*   Updated: 2020/08/03 14:43:35 by lcalendi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		destroy_hook(t_main *data, int on)
{
	if (on == 1)
		mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_image(data->mlx, data->img2);
	last_resort(data);
	return (0);
}

void	fill_image(t_main *data, t_vars *vars)
{
	while (vars->leep != data->constant.i_width)
	{
		vars->x = data->you.x;
		vars->y = data->you.y;
		vars->fx = data->you.fx;
		vars->fy = data->you.fy;
		vars->fx_add = cosf(vars->angle);
		vars->fy_add = sinf(vars->angle);
		if (vars->fy_add < 0 && floorf(vars->fy) == vars->fy)
			vars->y--;
		if (vars->fx_add < 0 && floorf(vars->fx) == vars->fx)
			vars->x--;
		while (data->map[vars->y][vars->x] &&
				data->map[vars->y][vars->x] != '1')
		{
			if (data->map[vars->y][vars->x] == '2')
				add_sprite(vars->list, data, vars);
			x_math(data, vars);
			y_math(data, vars);
			end_math(vars);
		}
		fill_column(data, vars);
	}
}

void	rotate_buffer(t_main *data)
{
	void	*temp;

	temp = data->img;
	data->img = data->img2;
	data->img2 = temp;
	temp = data->image;
	data->image = data->image2;
	data->image2 = temp;
}

int		loop_hook(t_main *data)
{
	t_vars	vars;

	reset_sprite_map(data);
	vars.list = 0;
	vars.leep = 0;
	vars.angle = data->you.angle - (data->you.fov / 2);
	vars.angel = -(data->you.fov / 2);
	key_func(data, cosf(data->you.angle), sinf(data->you.angle), 0);
	data->parse.sud.pos = &vars.fy;
	data->parse.nord.pos = &vars.fy;
	data->parse.ouest.pos = &vars.fx;
	data->parse.est.pos = &vars.fx;
	vars.which = &data->parse.nord;
	fill_image(data, &vars);
	if (data->save_now)
	{
		data->save_now = 0;
		save_to_bmp(data);
		destroy_hook(data, 0);
	}
	else if (data->window == 0)
		initialize_hooks(data);
	mlx_put_image_to_window(data->mlx, data->window, data->img, 0, 0);
	rotate_buffer(data);
	return (0);
}

int		main(int argc, char **argv)
{
	t_main	data;
	int		tos[3];
	int		loop;

	loop = 0;
	data.mlx = mlx_init();
	data.first_malloc = 0;
	mlx_get_screen_size(data.mlx, &data.constant.max_width,
					&data.constant.max_height);
	if (parser(argc, argv, &data) == -1 || initialize(&data) == -1)
		last_resort(&data);
	data.img =
	mlx_new_image(data.mlx, data.constant.i_width, data.constant.i_height);
	data.img2 =
	mlx_new_image(data.mlx, data.constant.i_width, data.constant.i_height);
	data.image[0] = (int *)mlx_get_data_addr(data.img, tos, tos + 1, tos + 2);
	data.image2[0] = (int *)mlx_get_data_addr(data.img2, tos, tos + 1, tos + 2);
	data.constant.h2 = data.constant.i_height / 2;
	while (++loop != data.constant.i_height)
	{
		data.image[loop] = &data.image[loop - 1][tos[1] / 4];
		data.image2[loop] = &data.image2[loop - 1][tos[1] / 4];
	}
	mlx_loop_hook(data.mlx, *loop_hook, &data);
	mlx_loop(data.mlx);
}
