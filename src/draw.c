/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jripoute <jripoute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 06:49:18 by jripoute          #+#    #+#             */
/*   Updated: 2015/05/03 21:47:36 by jripoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arkanoid.h"

static void		draw_one_brick(t_brick *brick)
{
	glBegin(GL_QUADS);
	if (brick->state == 9)
		glColor3ub(75, 75, 75);
	if (brick->state == 1)
		glColor3ub(209, 66, 51);
	if (brick->state == 2)
		glColor3ub(46, 142, 206);
	if (brick->state == 3)
		glColor3ub(155, 80, 186);
	if (brick->state == 4)
		glColor3ub(53, 75, 96);
	glVertex2d(brick->pos.x, brick->pos.y);
	glVertex2d(brick->pos.x, brick->pos.y - brick->height);
	glVertex2d(brick->pos.x + brick->width, brick->pos.y - brick->height);
	glVertex2d(brick->pos.x + brick->width, brick->pos.y);
	glEnd();
}

static void		draw_bricks(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j].state >= 1)
				draw_one_brick(&map->map[i][j]);
			j++;
		}
		i++;
	}
}

static void		draw_edges(void)
{
	glColor3ub(75, 75, 75);
	glBegin(GL_LINE_STRIP);
	glVertex2d(0.99, 0.99);
	glVertex2d(-0.99, 0.99);
	glVertex2d(-0.99, -0.99);
	glVertex2d(0.99, -0.99);
	glVertex2d(0.99, 0.99);
	glEnd();
}

void			draw_all(t_all *all)
{
	draw_ship(&all->ship);
	draw_circle(all->ball.pos.x, all->ball.pos.y, all->ball.radius, 20);
	draw_bricks(&all->map);
	draw_edges();
}
