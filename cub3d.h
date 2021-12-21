/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalendi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 16:49:05 by lcalendi          #+#    #+#             */
/*   Updated: 2020/07/30 18:30:36 by lcalendi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define FILE_NOT_OPEN		1
# define NOT_2_ARGS			2
# define NOT_CUB			3
# define INVALID_WIDTH		4
# define INVALID_HEIGHT		5
# define INVALID_CEIL_RGB	6
# define CEIL_GARBAGE		7
# define INVALID_FLOOR_RGB	8
# define FLOOR_GARBAGE		9
# define NOT_ENOUGH_LINES	10
# define SOMETHING			11

# define ERROR_OPEN_SOUTH	1
# define SOUTH_MISFORMATED	2
# define ERROR_OPEN_NORTH	3
# define NORTH_MISFORMATED	4
# define ERROR_OPEN_WEST	5
# define WEST_MISFORMATED	6
# define ERROR_OPEN_EAST	7
# define EAST_MISFORMATED	8
# define ERROR_OPEN_SPRITE	9
# define SPRITE_MISFORMATED	10

# define MAP_HAS_HOLES		1
# define INVALID_ARG_2		2
# define TWO_PLAYERS_IN_MAP	3
# define INVALID_MAP_CHAR	4
# define NO_PLAYER_IN_MAP	5
# define SIMILAR_LINES		6
# define RESOLUTION_GARBAGE	7
# define EMPTY_LINE_IN_MAP	8

# define FOV				40

typedef	struct	s_malloc
{
	void	*ptr;
	void	*img;
	void	*next;
}				t_malloc;

typedef struct	s_map_parse
{
	int		player_found;
}				t_map_parse;

typedef struct	s_sprite_list
{
	float	distance;
	float	p_line_factor;
	float	p_line_term;
	float	s_line_factor;
	float	s_line_term;
	float	x_cross;
	float	y_cross;
	float	s_distance;
	int		size;
	void	*next;
}				t_sprite_list;

typedef struct	s_map_list
{
	int		size;
	char	*line;
	void	*next;
}				t_map_list;

typedef struct	s_texture
{
	float	*pos;
	int		**texture;
	int		goal;
	int		width;
	int		height;
}				t_texture;

typedef struct	s_pars
{
	int			ceiling;
	int			flor;
	void		*north;
	void		*south;
	void		*west;
	void		*east;
	void		*sprite;
	t_texture	sud;
	t_texture	nord;
	t_texture	ouest;
	t_texture	est;
	t_texture	prite;
}				t_pars;

typedef struct	s_vars
{
	int				x;
	int				y;
	int				ax;
	int				ay;
	float			fx;
	float			fy;
	float			fx_add;
	float			fy_add;
	int				loop;
	int				leep;
	int				see;
	float			temp1;
	float			temp2;
	float			angle;
	float			angel;
	t_texture		*which;
	t_texture		*which2;
	t_sprite_list	*list;
	t_sprite_list	*temp;
}				t_vars;

typedef struct	s_player
{
	int		x;
	int		y;
	float	fx;
	float	fy;
	float	angle;
	float	fov;
	float	speed;
}				t_player;

typedef struct	s_colors
{
	int red;
	int blue;
	int green;
	int lgreen;
	int lred;
	int black;
	int grey;
	int white;
}				t_colors;

typedef struct	s_const
{
	int		h2;
	int		i_height;
	int		i_width;
	int		max_width;
	int		max_height;
	float	add_fov;
	float	height;
	float	width;
}				t_const;

typedef	struct	s_main
{
	void		*mlx;
	void		*window;
	void		*img;
	void		*img2;
	t_malloc	*first_malloc;
	t_malloc	*last_malloc;
	char		**map;
	int			*map_size;
	float		**sprite_map;
	int			**image;
	int			**image2;
	char		key_tab[1000];
	t_colors	colors;
	t_const		constant;
	t_player	you;
	t_pars		parse;
	t_map_parse	map_parse;
	int			save_now;
}				t_main;

int				get_next_line(int fd, char **line);
int				error_dealer(int reason);
int				error_dealer2(int reason);
int				error_dealer3(int reason);
int				parser(int argc, char **argv, t_main *data);
int				ft_atoi(char *str, int *loop, int max);
int				parse_resolution(char *line, t_main *data);
int				parse_ceiling(char *line, t_main *data, int rgb);
int				parse_floor(char *line, t_main *data, int rgb);
int				south_parse(char *line, t_main *data);
int				north_parse(char *line, t_main *data);
int				west_parse(char *line, t_main *data);
int				east_parse(char *line, t_main *data);
int				sprite_parse(char *line, t_main *data);
void			save_to_bmp(t_main *data);
int				map_parser(char *line, int fd, t_main *data);
int				map_algo(t_main *data);
int				new_malloc(void *ptr, t_main *data);
int				last_resort(t_main *data);
int				img_parse(char *line, t_main *data, void **img, t_texture *one);
void			fill_column(t_main *data, t_vars *vars);
void			x_math(t_main *data, t_vars *vars);
void			y_math(t_main *data, t_vars *vars);
void			end_math(t_vars *vars);
void			add_sprite(t_sprite_list *list, t_main *data, t_vars *vars);
int				initialize(t_main *data);
int				initialize_keys(t_main *data);
int				key_press(int keycode, t_main *data);
int				key_release(int keycode, t_main *data);
void			key_func(t_main *data, float fx_add, float fy_add, char cont);
int				destroy_hook(t_main *data, int on);
void			reset_sprite_map(t_main *data);
void			initialize_hooks(t_main *data);
int				loop_hook(t_main *data);
void			parse_init(t_main *data);
int				cht(int (*f)(int), void *adr, int arg, int ret);

#endif
