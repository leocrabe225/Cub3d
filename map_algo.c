/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalendi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 20:03:46 by lcalendi          #+#    #+#             */
/*   Updated: 2020/07/30 14:43:56 by lcalendi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_spot(t_main *data, int x, int y)
{
	if (y != -1 && x != -1 && data->map[y]
	&& data->map[y][x] && x <= data->map_size[y])
	{
		if (data->map[y][x] == '0' || data->map[y][x] == '2')
		{
			data->map[y][x] += 30;
			return (0);
		}
		else
			return (1);
	}
	else
		return (error_dealer3(MAP_HAS_HOLES));
}

int	algo_core(t_main *data, int x, int y, int check)
{
	check = check_spot(data, x + 1, y);
	if (!check)
		if (algo_core(data, x + 1, y, 0) == -1)
			return (-1);
	if (check == -1)
		return (-1);
	check = check_spot(data, x - 1, y);
	if (!check)
		if (algo_core(data, x - 1, y, 0) == -1)
			return (-1);
	if (check == -1)
		return (-1);
	check = check_spot(data, x, y + 1);
	if (!check)
		if (algo_core(data, x, y + 1, 0) == -1)
			return (-1);
	if (check == -1)
		return (-1);
	check = check_spot(data, x, y - 1);
	if (!check)
		if (algo_core(data, x, y - 1, 0) == -1)
			return (-1);
	if (check == -1)
		return (-1);
	return (0);
}

int	map_algo(t_main *data)
{
	int loop;
	int leep;

	if (algo_core(data, data->you.x, data->you.y, 0) == -1)
		return (-1);
	loop = 0;
	while (data->map[loop])
	{
		leep = 0;
		while (data->map[loop][leep])
		{
			if (data->map[loop][leep] == '0' + 30 ||
				data->map[loop][leep] == '2' + 30)
				data->map[loop][leep] -= 30;
			leep++;
		}
		loop++;
	}
	return (0);
}
