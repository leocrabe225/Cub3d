/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalendi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 19:54:50 by lcalendi          #+#    #+#             */
/*   Updated: 2020/07/29 17:40:53 by lcalendi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_func3(t_main *data)
{
	if (data->key_tab[361])
		data->you.angle -= M_PI / 80;
	if (data->key_tab[363])
		data->you.angle += M_PI / 80;
	if (data->key_tab[307])
		destroy_hook(data, 1);
}

void	key_func2(t_main *data, float fx_add, float fy_add, char content)
{
	if (data->key_tab[97])
	{
		content = data->map[(int)(data->you.fy - fx_add * data->you.speed)]
						[(int)(data->you.fx + fy_add * data->you.speed)];
		if (content && content != '1')
		{
			data->you.fx += fy_add * data->you.speed;
			data->you.fy -= fx_add * data->you.speed;
			data->you.x = (int)data->you.fx;
			data->you.y = (int)data->you.fy;
		}
	}
	if (data->key_tab[100])
	{
		content = data->map[(int)(data->you.fy + fx_add * data->you.speed)]
						[(int)(data->you.fx - fy_add * data->you.speed)];
		if (content && content != '1')
		{
			data->you.fx -= fy_add * data->you.speed;
			data->you.fy += fx_add * data->you.speed;
			data->you.x = (int)data->you.fx;
			data->you.y = (int)data->you.fy;
		}
	}
	key_func3(data);
}

void	key_func(t_main *data, float fx_add, float fy_add, char content)
{
	if (data->key_tab[119])
	{
		content = data->map[(int)(data->you.fy + fy_add * data->you.speed)]
						[(int)(data->you.fx + fx_add * data->you.speed)];
		if (content && content != '1')
		{
			data->you.fx += fx_add * data->you.speed;
			data->you.fy += fy_add * data->you.speed;
			data->you.x = (int)data->you.fx;
			data->you.y = (int)data->you.fy;
		}
	}
	if (data->key_tab[115])
	{
		content = data->map[(int)(data->you.fy - fy_add * data->you.speed)]
						[(int)(data->you.fx - fx_add * data->you.speed)];
		if (content && content != '1')
		{
			data->you.fx -= fx_add * data->you.speed;
			data->you.fy -= fy_add * data->you.speed;
			data->you.x = (int)data->you.fx;
			data->you.y = (int)data->you.fy;
		}
	}
	key_func2(data, fx_add, fy_add, content);
}

int		key_release(int keycode, t_main *data)
{
	data->key_tab[keycode % 1000] = 0;
	return (0);
}

int		key_press(int keycode, t_main *data)
{
	data->key_tab[keycode % 1000] = 1;
	return (0);
}
