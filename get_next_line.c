/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalendi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:47:33 by lcalendi          #+#    #+#             */
/*   Updated: 2019/11/22 18:39:01 by lcalendi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void			ditto(t_gnl *var_4d, t_linked_lst *line, int n, int mode)
{
	if (mode == 1)
	{
		var_4d->retour = (line->max == n) ? 0 : 1;
		var_4d->retour = (line->max == -1) ? -1 : var_4d->retour;
		line->next = 0;
		var_4d->new = n + 1;
	}
	else
	{
		if (var_4d->retour <= 0)
		{
			free(var_4d->buffer);
			var_4d->buffer = 0;
			var_4d->stop = BUFFER_SIZE;
			var_4d->max = BUFFER_SIZE;
		}
	}
}

static char			*super_join(int loop, t_linked_lst *chain, t_gnl *v, int i)
{
	t_linked_lst	*begin;
	char			*line;
	int				s;

	s = 0;
	begin = chain;
	while (chain->max != loop && chain->buf[loop] != '\n' && ++s)
		if (++loop == BUFFER_SIZE && !(loop = 0))
			chain = chain->next;
	if ((!(line = malloc(s + 1)))
			&& !(v->retour = -1))
		return (0);
	loop = 0;
	while (begin->max != i && begin->buf[i] != '\n')
	{
		line[loop++] = begin->buf[i++];
		if (i == BUFFER_SIZE && !(i = 0))
			begin = begin->next;
	}
	line[loop] = 0;
	return (line);
}

static void			*get_current_line(int fd, t_gnl *var_4d, int n)
{
	t_linked_lst	*line;
	t_linked_lst	*begin;

	if (!(begin = malloc(sizeof(t_linked_lst))))
		return (0);
	begin->buf = var_4d->buffer;
	line = begin;
	line->max = var_4d->max;
	while (1)
	{
		while (n != line->max && line->buf[n] != '\n' && line->max != -1)
			n++;
		if (n != BUFFER_SIZE)
			break ;
		if ((!(line->next = malloc(sizeof(t_linked_lst))))
				&& (var_4d->retour = -1) == -1)
			return (begin);
		line = line->next;
		line->buf = malloc(BUFFER_SIZE);
		line->max = read(fd, line->buf, BUFFER_SIZE);
		var_4d->max = line->max;
		n = 0;
	}
	ditto(var_4d, line, n, 1);
	return (begin);
}

int					get_next_line(int fd, char **line)
{
	static t_gnl	var_4d = {0, BUFFER_SIZE, 0, BUFFER_SIZE, BUFFER_SIZE};
	t_linked_lst	*current;
	t_linked_lst	*temp;

	if (BUFFER_SIZE < 1 || !line)
		return (-1);
	current = get_current_line(fd, &var_4d, var_4d.stop);
	if (!current)
		return (-1);
	if (var_4d.retour >= 0)
		line[0] = (var_4d.stop == BUFFER_SIZE) ? super_join(0, current->next
, &var_4d, 0) : super_join(var_4d.stop, current, &var_4d, var_4d.stop);
	var_4d.stop = var_4d.new;
	while (current && current->next)
	{
		free(current->buf);
		temp = current;
		current = current->next;
		free(temp);
	}
	var_4d.buffer = current->buf;
	free(current);
	ditto(&var_4d, 0, 0, 2);
	return (var_4d.retour);
}
