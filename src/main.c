/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jripoute <jripoute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 22:40:28 by jripoute          #+#    #+#             */
/*   Updated: 2015/05/03 21:47:08 by jripoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arkanoid.h"

void		init_frame(t_all *all)
{
	float ratio;

	glfwGetFramebufferSize(all->win.ptr, &all->win.width, &all->win.height);
	ratio = all->win.width / (float)all->win.height;
	glViewport(0, 0, all->win.width, all->win.height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1, 1, 1, -1);
	glMatrixMode(GL_MODELVIEW);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

t_bool		did_u_win(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j].state >= 1 && map->map[i][j].state != 9)
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

void		graphic_render_string(float x, float y, void *font, const char *s)
{
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glRasterPos2f(x, y);
	while (*s)
	{
		glutBitmapCharacter(font, *s);
		s++;
	}
}

void		display_score(t_all *all)
{
	char *str;
	char *nb;

	nb = ft_itoa(all->score);
	str = ft_strjoin("Score : ", nb);
	glColor3d(1.0, 1.0, 1.0);
	graphic_render_string(-0.95, -0.95, GLUT_BITMAP_9_BY_15, str);
	free(nb);
	free(str);
	nb = ft_itoa(all->life);
	str = ft_strjoin("Life : ", nb);
	graphic_render_string(0.55, -0.95, GLUT_BITMAP_9_BY_15, str);
	free(nb);
	free(str);
}

int			main(void)
{
	t_all	all;

	init_all(&all);
	while (!glfwWindowShouldClose(all.win.ptr))
	{
		init_frame(&all);
		draw_all(&all);
		display_score(&all);
		glfwSwapBuffers(all.win.ptr);
		if (move_ball(&all.ball, &all.ship, &all.map, &all.score) == -1)
		{
			all.life--;
			init_scene(&all);
		}
		key_hook(&all);
		if (did_u_win(&all.map) == TRUE)
		{
			load_new_map(&all);
			all.life++;
		}
	}
	glfwDestroyWindow(all.win.ptr);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
