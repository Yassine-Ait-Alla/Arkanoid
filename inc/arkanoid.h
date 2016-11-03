/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arkanoid.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jripoute <jripoute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 03:18:43 by jripoute          #+#    #+#             */
/*   Updated: 2015/05/03 21:44:55 by jripoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARKANOID_H
# define ARKANOID_H

# include <GLUT/glut.h>
# define GLFW_INCLUDE_GLU
# include <GLFW/glfw3.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"

# define TRUE 1
# define FALSE 0

# define SHIP_SPEED 0.04
# define SHIP_W 0.15
# define SHIP_H 0.015
# define SHIP_OFFSET -0.85

# define BRICK_W 0.15
# define BRICK_H 0.04
# define BRICK_OFFSET_X 0.165
# define BRICK_OFFSET_Y 0.085

# define BALL_SIZE 0.02
# define BALL_SPEED 0.02

# define COEFF_D 0.05
# define COEFF_SPEED 0.2
# define M_PI       3.14159265358979323846

typedef int		t_bool;

typedef struct	s_win
{
	GLFWwindow	*ptr;
	int			width;
	int			height;
}				t_win;

typedef struct	s_dpos
{
	double		x;
	double		y;
}				t_dpos;

typedef struct	s_pos
{
	int			x;
	int			y;
}				t_pos;

typedef struct	s_ship
{
	t_dpos		pos;
	t_dpos		vdir;
	double		height;
	double		width;
}				t_ship;

typedef struct	s_ball
{
	t_dpos		pos;
	t_dpos		vspeed;
	double		radius;
	double		radius_pow_2;
	int			rebound;
}				t_ball;

typedef struct	s_brick
{
	int			state;
	t_dpos		pos;
	double		height;
	double		width;
}				t_brick;

typedef struct	s_map
{
	t_brick		**map;
	int			height;
	int			width;
}				t_map;

typedef struct	s_all
{
	t_win		win;
	t_ship		ship;
	t_ball		ball;
	t_map		map;
	char		*level;
	int			score;
	int			life;
}				t_all;

typedef enum	e_error
{
	CREATE_WINDOW,
	NO_MAP,
}				t_error;

void			init_all(t_all *all);
void			draw_all(t_all *all);
void			draw_circle(double x, double y, double rayon, int aliasing);
int				set_ball_pos(double *pos, double ret, double min, double max);
void			draw_ship(t_ship *ship);
void			init_scene(t_all *all);
void			init_map_parser(t_map *map, char *filename);
void			load_new_map(t_all *all);
int				move_ball(t_ball *ball, t_ship *ship, t_map *map, int *score);
void			key_hook(t_all *all);
t_bool			collision_xy_circle(double x, double y, t_ball *b);
t_bool			check_ship_collision(t_ball *ball, t_ship *ship);
void			ball_rebound(t_ball *ball, t_ship *ship);
t_bool			check_brick_collision(t_ball *ball, t_map *map);
t_bool			ball_is_in_brick(t_ball *ball, t_brick *brick);
void			init_map_parser2(t_map *map, char *line, int j, double y);

/*
** maths.c
*/
double			sinus(double angle);
double			cosinus(double angle);

/*
** Misc.c
*/
void			ft_error(int er);
void			ft_arraydel(char ***tab);

#endif
