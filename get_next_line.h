/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalendi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:47:59 by lcalendi          #+#    #+#             */
/*   Updated: 2020/02/01 16:52:10 by lcalendi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 4096
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_gnl
{
	char	*buffer;
	int		stop;
	int		new;
	int		retour;
	int		max;
}				t_gnl;

typedef struct	s_linked_lst
{
	char	*buf;
	int		max;
	void	*next;
}				t_linked_lst;

#endif
