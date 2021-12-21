/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_to_bmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalendi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 20:24:24 by lcalendi          #+#    #+#             */
/*   Updated: 2020/07/29 17:58:21 by lcalendi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned char g_header[55] = {66, 77, 182, 224, 98, 0, 0, 0, 0, 0, 54, 0, 0, 0,
	40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	19, 11, 0, 0, 19, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void	write_in_h(int loop, int number)
{
	while (number)
	{
		g_header[loop] = number % 256;
		number /= 256;
		loop++;
	}
}

void	bmp_header_creator(t_main *data, int fd)
{
	write_in_h(18, data->constant.i_width);
	write_in_h(22, data->constant.i_height);
	write_in_h(2, data->constant.i_width * data->constant.i_height * 4 + 54);
	write(fd, g_header, 54);
}

void	save_to_bmp(t_main *data)
{
	int fd;
	int loop;

	fd = open("./save.bmp", O_CREAT, 0777);
	close(fd);
	fd = open("./save.bmp", O_WRONLY);
	bmp_header_creator(data, fd);
	loop = data->constant.i_height - 1;
	while (loop != -1)
	{
		write(fd, (char*)data->image[loop], data->constant.i_width * 4);
		loop--;
	}
	close(fd);
}
