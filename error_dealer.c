/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_dealer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalendi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 14:39:30 by lcalendi          #+#    #+#             */
/*   Updated: 2020/08/03 14:43:11 by lcalendi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	last_resort(t_main *data)
{
	while (data->first_malloc)
	{
		data->last_malloc = data->first_malloc;
		free(data->last_malloc->ptr);
		if (data->last_malloc->img)
		{
			mlx_destroy_image(data->mlx, data->last_malloc->img);
		}
		data->first_malloc = data->first_malloc->next;
		free(data->last_malloc);
	}
	exit(EXIT_SUCCESS);
	return (0);
}

int	new_malloc(void *ptr, t_main *data)
{
	if (!ptr)
		return (0);
	if (!data->first_malloc)
	{
		data->first_malloc = malloc(sizeof(t_malloc));
		data->last_malloc = data->first_malloc;
	}
	else
	{
		data->last_malloc->next = malloc(sizeof(t_malloc));
		data->last_malloc = data->last_malloc->next;
	}
	data->last_malloc->img = 0;
	data->last_malloc->next = 0;
	data->last_malloc->ptr = ptr;
	return (1);
}

int	error_dealer(int reason)
{
	if (reason == FILE_NOT_OPEN)
		write(1, "Error\nWhile trying to open the file.\n", 37);
	if (reason == NOT_2_ARGS)
		write(1, "Error\nWrong number of arguments.\n", 33);
	if (reason == NOT_CUB)
		write(1, "Error\nThis is not a \".cub\" file.\n", 33);
	if (reason == INVALID_WIDTH)
		write(1, "Error\nThe width isn't a valid number.\n", 38);
	if (reason == INVALID_HEIGHT)
		write(1, "Error\nThe height isn't a valid number.\n", 39);
	if (reason == INVALID_CEIL_RGB)
		write(1, "Error\nThe ceil rgb is not well formated.\n", 41);
	if (reason == CEIL_GARBAGE)
		write(1, "Error\nThere is garbage after the ceil rgb.\n", 43);
	if (reason == INVALID_FLOOR_RGB)
		write(1, "Error\nThe floor rgb is not well formated.\n", 42);
	if (reason == FLOOR_GARBAGE)
		write(1, "Error\nThere is garbage after the floor rgb.\n", 44);
	if (reason == NOT_ENOUGH_LINES)
		write(1, "Error\nThere is not enough lines in the file.\n", 45);
	if (reason == SOMETHING)
		write(1, "Error\nA line is missing.\nOr a line header is ", 45);
	if (reason == SOMETHING)
		write(1, "missformated.\nOr an empty line is not empty enough.\n", 52);
	return (-1);
}

int	error_dealer2(int reason)
{
	if (reason == ERROR_OPEN_SOUTH)
		write(1, "Error\nThe South texture file doesn't open.\n", 44);
	if (reason == SOUTH_MISFORMATED)
		write(1, "Error\nThe South texture isn't a texture.\n", 42);
	if (reason == ERROR_OPEN_NORTH)
		write(1, "Error\nThe North texture file doesn't open.\n", 44);
	if (reason == NORTH_MISFORMATED)
		write(1, "Error\nThe North texture isn't a texture.\n", 42);
	if (reason == ERROR_OPEN_WEST)
		write(1, "Error\nThe West texture file doesn't open.\n", 43);
	if (reason == WEST_MISFORMATED)
		write(1, "Error\nThe West texture isn't a texture.\n", 41);
	if (reason == ERROR_OPEN_EAST)
		write(1, "Error\nThe East texture file doesn't open.\n", 43);
	if (reason == EAST_MISFORMATED)
		write(1, "Error\nThe East texture isn't a texture.\n", 41);
	if (reason == ERROR_OPEN_SPRITE)
		write(1, "Error\nThe Sprite texture file doesn't open.\n", 44);
	if (reason == SPRITE_MISFORMATED)
		write(1, "Error\nThe Sprite texture isn't a texture.\n", 43);
	return (-1);
}

int	error_dealer3(int reason)
{
	if (reason == MAP_HAS_HOLES)
		write(1, "Error\nThere is a hole in the map.\n", 34);
	if (reason == INVALID_ARG_2)
		write(1, "Error\nThe second argument is not valid.\n", 40);
	if (reason == TWO_PLAYERS_IN_MAP)
		write(1, "Error\nThere is 2 players in the map.\n", 37);
	if (reason == INVALID_MAP_CHAR)
		write(1, "Error\nThere is an invalid map character.\n", 41);
	if (reason == NO_PLAYER_IN_MAP)
		write(1, "Error\nThere is no player in the map.\n", 37);
	if (reason == SIMILAR_LINES)
		write(1, "Error\nThere is two lines for the same parameter\n", 48);
	if (reason == RESOLUTION_GARBAGE)
		write(1, "Error\nThere is garbage after the resolution.\n", 45);
	if (reason == EMPTY_LINE_IN_MAP)
		write(1, "Error\nThere is an empty line in the map.\n", 41);
	return (-1);
}
