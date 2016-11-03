/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jripoute <jripoute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 06:41:08 by jripoute          #+#    #+#             */
/*   Updated: 2015/05/03 21:51:58 by jripoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arkanoid.h"

static void			key_callback(GLFWwindow *window, int key, \
	int scancode, int action, int mod)
{
	(void)scancode;
	(void)mod;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

static GLFWwindow	*init_window(void)
{
	GLFWwindow *win;

	if (glfwInit() == GL_FALSE)
		exit(EXIT_FAILURE);
	if ((win = glfwCreateWindow(560, 480, "Arkanoid", NULL, NULL)) == NULL)
		ft_error(CREATE_WINDOW);
	glfwMakeContextCurrent(win);
	glfwSwapInterval(1);
	glfwSetKeyCallback(win, key_callback);
	return (win);
}

static void			init_hitbox_ship(t_ship *ship)
{
	ship->pos.x = -SHIP_W;
	ship->pos.y = SHIP_OFFSET + SHIP_H;
	ship->vdir.x = 0;
	ship->vdir.y = 0;
	ship->height = SHIP_H * 2;
	ship->width = SHIP_W * 2;
}

static void			init_hitbox_ball(t_ball *ball)
{
	ball->pos.x = 0;
	ball->pos.y = (SHIP_OFFSET) + ((BALL_SIZE) * 2);
	ball->vspeed.x = 0;
	ball->vspeed.y = 0;
	ball->radius = (BALL_SIZE);
	ball->radius_pow_2 = (BALL_SIZE) * (BALL_SIZE);
	ball->rebound = 0;
}

void				init_all(t_all *all)
{
	all->life = 3;
	all->score = 0;
	all->level = ft_strdup("./levels/level_00.txt");
	init_hitbox_ship(&all->ship);
	init_hitbox_ball(&all->ball);
	init_map_parser(&all->map, all->level);
	all->win.ptr = init_window();
}
