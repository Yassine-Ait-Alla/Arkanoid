/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <yaitalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/03 20:34:32 by yaitalla          #+#    #+#             */
/*   Updated: 2015/05/03 21:19:46 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arkanoid.h"

void			draw_ship(t_ship *ship)
{
	glBegin(GL_QUADS);
	glColor3ub(78, 78, 78);
	glVertex2d(ship->pos.x, ship->pos.y);
	glVertex2d(ship->pos.x, ship->pos.y - ship->height);
	glVertex2d(ship->pos.x + ship->width, ship->pos.y - ship->height);
	glVertex2d(ship->pos.x + ship->width, ship->pos.y);
	glEnd();
}

void			draw_circle(double x, double y, double rayon, int aliasing)
{
	int		i;
	float	angle;

	i = 0;
	glBegin(GL_POLYGON);
	glColor3ub(190, 190, 190);
	while (i < aliasing)
	{
		angle = i * 2 * M_PI / aliasing;
		glVertex2f(x + (cosinus(angle) * rayon), y + (sinus(angle) * rayon));
		i++;
	}
	glEnd();
}

t_bool			collision_xy_circle(double x, double y, t_ball *b)
{
	double d2;

	d2 = (x - b->pos.x) * (x - b->pos.x) + (y - b->pos.y) * (y - b->pos.y);
	if (d2 > b->radius_pow_2)
		return (FALSE);
	return (TRUE);
}

t_bool			check_ship_collision(t_ball *ball, t_ship *ship)
{
	double y;
	double x;

	glColor3ub(255, 255, 255);
	x = ship->pos.x;
	while (x < ship->pos.x + ship->width)
	{
		if (collision_xy_circle(x, ship->pos.y, ball) == TRUE)
			return (TRUE);
		if (collision_xy_circle(x, ship->pos.y - ship->height, ball) == TRUE)
			return (TRUE);
		x += 0.01;
	}
	y = ship->pos.y;
	while (y > ship->pos.y - ship->height)
	{
		if (collision_xy_circle(ship->pos.x, y, ball) == TRUE)
			return (TRUE);
		if (collision_xy_circle(ship->pos.x + ship->width, y, ball) == TRUE)
			return (TRUE);
		y -= 0.01;
	}
	return (FALSE);
}

t_bool			ball_is_in_brick(t_ball *ball, t_brick *brick)
{
	double x;

	if (brick->state == 0)
		return (FALSE);
	x = brick->pos.x;
	while (x < brick->pos.x + brick->width)
	{
		if (collision_xy_circle(x, brick->pos.y, ball) == TRUE)
			return (TRUE);
		if (collision_xy_circle(x, brick->pos.y - brick->height, ball) == TRUE)
			return (TRUE);
		x += 0.01;
	}
	return (FALSE);
}
