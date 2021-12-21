/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalendi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 14:52:47 by lcalendi          #+#    #+#             */
/*   Updated: 2020/08/03 16:15:32 by lcalendi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map_list	*map_part_creator(char *line)
{
	t_map_list	*map_part;
	int			loop;

	map_part = malloc(sizeof(t_map_list));
	map_part->line = line;
	map_part->next = 0;
	loop = 0;
	while (map_part->line[loop])
		loop++;
	map_part->size = loop;
	return (map_part);
}

int			map_creator(t_main *data, t_map_list *map_part, int map_size, int i)
{
	t_map_list	*temp;
	int			leep;

	if (!new_malloc(data->map = malloc(8 * (map_size + 1)), data) ||
	!new_malloc(data->sprite_map = malloc(8 * (map_size + 1)), data) ||
	!new_malloc(data->map_size = malloc(4 * (map_size + 1)), data))
		return (0);
	while (map_part && !(leep = 0))
	{
		data->map[i] = map_part->line;
		data->map_size[i] = map_part->size;
		if (!new_malloc(data->map[i], data))
			return (0);
		while (data->map[i][leep])
			leep++;
		if (!new_malloc(data->sprite_map[i++] = malloc(4 * (leep)), data))
			return (0);
		temp = map_part;
		map_part = map_part->next;
		free(temp);
	}
	data->map[map_size] = 0;
	data->sprite_map[map_size] = 0;
	return (1);
}

int			check_content(t_main *data, char *c, int loop, int leep)
{
	if (*c == ' ')
		*c = '1';
	else if (*c == 'N' || *c == 'S' || *c == 'W' || *c == 'E')
	{
		if (data->map_parse.player_found)
			return (error_dealer3(TWO_PLAYERS_IN_MAP));
		data->you.x = leep;
		data->you.y = loop;
		data->you.fx = leep + 0.500001;
		data->you.fy = loop + 0.500001;
		if (*c == 'N')
			data->you.angle = 0;
		else if (*c == 'S')
			data->you.angle = M_PI;
		else if (*c == 'E')
			data->you.angle = M_PI / 2;
		else if (*c == 'W')
			data->you.angle = 3 * (M_PI / 2);
		*c = '0';
		data->map_parse.player_found = 1;
	}
	else if (*c != '0' && *c != '1' && *c != '2')
		return (error_dealer3(INVALID_MAP_CHAR));
	return (0);
}

int			map_checker(t_main *data, char **map)
{
	int loop;
	int leep;

	loop = 0;
	while (map[loop])
	{
		if (!*map[loop])
			return (error_dealer3(EMPTY_LINE_IN_MAP));
		leep = 0;
		while (map[loop][leep])
		{
			if (check_content(data, &map[loop][leep], loop, leep) == -1)
				return (-1);
			leep++;
		}
		loop++;
	}
	if (!data->map_parse.player_found)
		return (error_dealer3(NO_PLAYER_IN_MAP));
	if (map_algo(data) == -1)
		return (-1);
	return (0);
}

int			map_parser(char *line, int fd, t_main *data)
{
	t_map_list	*map_start;
	t_map_list	*map_part;
	int			loop;

	data->map_parse.player_found = 0;
	map_start = malloc(sizeof(t_map_list));
	map_start->line = line;
	map_part = map_start;
	loop = 0;
	while (map_start->line[loop])
		loop++;
	map_start->size = loop;
	loop = 1;
	while (get_next_line(fd, &line))
	{
		loop++;
		map_part->next = map_part_creator(line);
		map_part = map_part->next;
	}
	free(line);
	if (!map_creator(data, map_start, loop, 0))
		return (-1);
	if (map_checker(data, data->map) == -1)
		return (-1);
	return (0);
}
