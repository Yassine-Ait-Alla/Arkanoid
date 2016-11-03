/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_n_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jripoute <jripoute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 07:06:41 by jripoute          #+#    #+#             */
/*   Updated: 2015/05/03 21:16:32 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arkanoid.h"

int			set_ball_pos(double *pos, double ret, double min, double max)
{
	if (ret < max && ret > min)
	{
		*pos = ret;
		return (1);
	}
	if (ret < min)
		return (-2);
	return (-1);
}

static void	set_valid_ship_pos(t_ship *ship, double ret, t_ball *ball)
{
	if (ret > -1 && ret < 1 - ship->width)
	{
		ship->pos.x = ret;
		if (ball->vspeed.x == 0 && ball->vspeed.y == 0)
			ball->pos.x = ret + (ship->width / 2);
	}
}

void		ball_rebound(t_ball *ball, t_ship *ship)
{
	double mid_ship;
	double dx;

	mid_ship = ship->pos.x + (ship->width / 2);
	dx = mid_ship + ship->width / 2. - ball->pos.x;
	ball->vspeed.y *= -1;
	ball->vspeed.x = -dx * COEFF_D + SHIP_SPEED * COEFF_SPEED;
	while (check_ship_collision(ball, ship) == TRUE)
	{
		ball->pos.y += 0.01;
	}
}

static void	mouse_tracking(t_all *all)
{
	double		xpos;
	double		ypos;

	glfwGetCursorPos(all->win.ptr, &xpos, &ypos);
	if (ypos && ypos < all->win.height)
	{
		if (xpos > 0 && xpos < all->win.width
				&& xpos < (all->win.width - (all->win.width / 100) * 16))
		{
			all->ship.pos.x = (xpos / (all->win.width / 2) - 1);
		}
	}
}

void		key_hook(t_all *all)
{
	glfwPollEvents();
	mouse_tracking(all);
	if (glfwGetKey(all->win.ptr, GLFW_KEY_LEFT) == GLFW_PRESS)
		set_valid_ship_pos(&all->ship,
				all->ship.pos.x - SHIP_SPEED, &all->ball);
	if (glfwGetKey(all->win.ptr, GLFW_KEY_RIGHT) == GLFW_PRESS)
		set_valid_ship_pos(&all->ship,
				all->ship.pos.x + SHIP_SPEED, &all->ball);
	if (glfwGetKey(all->win.ptr, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		all->ball.vspeed.x = BALL_SPEED;
		all->ball.vspeed.y = BALL_SPEED;
	}
}
