/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalendi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 20:13:16 by lcalendi          #+#    #+#             */
/*   Updated: 2020/07/23 20:29:31 by lcalendi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	south_parse(char *line, t_main *data)
{
	int ret;

	if (data->parse.south)
		return (error_dealer3(SIMILAR_LINES));
	ret = img_parse(line, data, &data->parse.south, &data->parse.sud);
	data->parse.sud.goal = 1;
	if (ret == -1)
		return (error_dealer2(ERROR_OPEN_SOUTH));
	else if (ret == -2)
		return (error_dealer2(SOUTH_MISFORMATED));
	return (1);
}

int	north_parse(char *line, t_main *data)
{
	int ret;

	if (data->parse.north)
		return (error_dealer3(SIMILAR_LINES));
	ret = img_parse(line, data, &data->parse.north, &data->parse.nord);
	data->parse.nord.goal = 0;
	if (ret == -1)
		return (error_dealer2(ERROR_OPEN_NORTH));
	else if (ret == -2)
		return (error_dealer2(NORTH_MISFORMATED));
	return (1);
}

int	west_parse(char *line, t_main *data)
{
	int ret;

	if (data->parse.west)
		return (error_dealer3(SIMILAR_LINES));
	ret = img_parse(line, data, &data->parse.west, &data->parse.ouest);
	data->parse.ouest.goal = 0;
	if (ret == -1)
		return (error_dealer2(ERROR_OPEN_WEST));
	else if (ret == -2)
		return (error_dealer2(WEST_MISFORMATED));
	return (1);
}

int	east_parse(char *line, t_main *data)
{
	int ret;

	if (data->parse.east)
		return (error_dealer3(SIMILAR_LINES));
	ret = img_parse(line, data, &data->parse.east, &data->parse.est);
	data->parse.est.goal = 1;
	if (ret == -1)
		return (error_dealer2(ERROR_OPEN_EAST));
	else if (ret == -2)
		return (error_dealer2(EAST_MISFORMATED));
	return (1);
}

int	sprite_parse(char *line, t_main *data)
{
	int ret;

	if (data->parse.sprite)
		return (error_dealer3(SIMILAR_LINES));
	ret = img_parse(line, data, &data->parse.sprite, &data->parse.prite);
	if (ret == -1)
		return (error_dealer2(ERROR_OPEN_SPRITE));
	else if (ret == -2)
		return (error_dealer2(SPRITE_MISFORMATED));
	return (1);
}
