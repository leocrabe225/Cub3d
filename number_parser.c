/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalendi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:22:44 by lcalendi          #+#    #+#             */
/*   Updated: 2020/07/23 17:38:37 by lcalendi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		cht(int (*f)(int), void *adr, int arg, int ret)
{
	if (f)
		f(arg);
	if (adr)
		free(adr);
	return (ret);
}

void	parse_init(t_main *data)
{
	data->parse.north = 0;
	data->parse.south = 0;
	data->parse.west = 0;
	data->parse.east = 0;
	data->parse.sprite = 0;
	data->parse.flor = -1;
	data->parse.ceiling = -1;
	data->constant.i_width = -1;
	data->constant.i_height = -1;
}

int		parse_resolution(char *line, t_main *data)
{
	int loop;

	if (data->constant.i_width != -1)
		return (error_dealer3(SIMILAR_LINES));
	loop = 1;
	while (line[loop] == ' ')
		loop++;
	if ((data->constant.i_width =
		ft_atoi(line, &loop, data->constant.max_width)) <= 0)
		return (error_dealer(INVALID_WIDTH));
	data->constant.width = data->constant.i_width;
	while (line[loop] == ' ')
		loop++;
	if ((data->constant.i_height =
		ft_atoi(line, &loop, data->constant.max_height)) <= 0)
		return (error_dealer(INVALID_HEIGHT));
	data->constant.height = data->constant.i_height;
	if (line[loop])
		return (error_dealer3(RESOLUTION_GARBAGE));
	return (1);
}

int		parse_ceiling(char *line, t_main *data, int rgb)
{
	int loop;
	int temp;

	if (data->parse.ceiling != -1)
		return (error_dealer3(SIMILAR_LINES));
	loop = 1;
	while (line[loop] == ' ')
		line++;
	if ((rgb = ft_atoi(line, &loop, 255)) < 0)
		return (error_dealer(INVALID_CEIL_RGB));
	if (line[loop++] != ',')
		return (error_dealer(INVALID_CEIL_RGB));
	if ((temp = ft_atoi(line, &loop, 255)) < 0)
		return (error_dealer(INVALID_CEIL_RGB));
	rgb = rgb * 256 + temp;
	if (line[loop++] != ',')
		return (error_dealer(INVALID_CEIL_RGB));
	if ((temp = ft_atoi(line, &loop, 255)) < 0)
		return (error_dealer(INVALID_CEIL_RGB));
	rgb = rgb * 256 + temp;
	if (line[loop])
		return (error_dealer(CEIL_GARBAGE));
	data->parse.ceiling = rgb;
	return (1);
}

int		parse_floor(char *line, t_main *data, int rgb)
{
	int loop;
	int temp;

	if (data->parse.flor != -1)
		return (error_dealer3(SIMILAR_LINES));
	loop = 1;
	while (line[loop] == ' ')
		line++;
	if ((rgb = ft_atoi(line, &loop, 255)) < 0)
		return (error_dealer(INVALID_FLOOR_RGB));
	if (line[loop++] != ',')
		return (error_dealer(INVALID_FLOOR_RGB));
	if ((temp = ft_atoi(line, &loop, 255)) < 0)
		return (error_dealer(INVALID_FLOOR_RGB));
	rgb = rgb * 256 + temp;
	if (line[loop++] != ',')
		return (error_dealer(INVALID_FLOOR_RGB));
	if ((temp = ft_atoi(line, &loop, 255)) < 0)
		return (error_dealer(INVALID_FLOOR_RGB));
	rgb = rgb * 256 + temp;
	if (line[loop])
		return (error_dealer(FLOOR_GARBAGE));
	data->parse.flor = rgb;
	return (1);
}
