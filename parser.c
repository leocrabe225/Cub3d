/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalendi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 14:29:58 by lcalendi          #+#    #+#             */
/*   Updated: 2020/07/29 17:58:32 by lcalendi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strcmp(char *str1, char *str2)
{
	int loop;

	loop = 0;
	while (str1[loop] == str2[loop] && str1[loop])
		loop++;
	return (str1[loop] == str2[loop]);
}

int	ft_atoi(char *str, int *loop, int max)
{
	int nb;

	nb = 0;
	if (str[*loop] < '0' || str[*loop] > '9')
		return (-1);
	while (str[*loop] >= '0' && str[*loop] <= '9')
	{
		if (((long long int)nb) * 10 + str[*loop] - '0' > 2147483647)
		{
			while (str[*loop] >= '0' && str[*loop] <= '9')
				*loop += 1;
			return (max);
		}
		nb = nb * 10 + str[*loop] - '0';
		*loop += 1;
	}
	return ((nb > max) ? max : nb);
}

int	classify(char *line, t_main *data)
{
	if (!*line)
		return (0);
	if (*line == 'R')
		return (parse_resolution(line, data));
	else if (*line == 'C')
		return (parse_ceiling(line, data, 0));
	else if (*line == 'F')
		return (parse_floor(line, data, 0));
	else if (*line == 'N' && line[1] == 'O')
		return (north_parse(line, data));
	else if (*line == 'S' && line[1] == 'O')
		return (south_parse(line, data));
	else if (*line == 'W' && line[1] == 'E')
		return (west_parse(line, data));
	else if (*line == 'E' && line[1] == 'A')
		return (east_parse(line, data));
	else if (*line == 'S' && line[1] == ' ')
		return (sprite_parse(line, data));
	else
		return (error_dealer(SOMETHING));
}

int	parser_2(char **argv, t_main *data, int fd)
{
	int		loop;
	int		change;
	char	*line;
	char	*cub;

	cub = ".cub";
	loop = 4;
	while (*argv[1])
		argv[1] += 1;
	while (loop >= 0)
		if (*argv[1] != cub[loop--])
			return (error_dealer(NOT_CUB));
		else
			argv[1] -= 1;
	loop = 0;
	change = 0;
	while ((loop += change) < 8)
	{
		if (get_next_line(fd, &line) == 0)
			return (cht(&error_dealer, line, NOT_ENOUGH_LINES, -1));
		else if ((change = classify(line, data)) == -1)
			return (cht(0, line, 0, -1));
		free(line);
	}
	return (0);
}

int	parser(int argc, char **argv, t_main *data)
{
	int		fd;
	char	*line;

	parse_init(data);
	data->save_now = 0;
	if (argc == 3)
		if (!(data->save_now = ft_strcmp("--save", argv[2])))
			return (error_dealer3(INVALID_ARG_2));
	if (argc == 2 || argc == 3)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			return (error_dealer(FILE_NOT_OPEN));
		if (parser_2(argv, data, fd) == -1)
			return (-1);
		while (get_next_line(fd, &line) && !*line)
			free(line);
		if (map_parser(line, fd, data) == -1)
			return (-1);
	}
	else
		return (error_dealer(NOT_2_ARGS));
	close(fd);
	return (0);
}
