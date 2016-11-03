/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jripoute <jripoute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 21:36:08 by jripoute          #+#    #+#             */
/*   Updated: 2015/05/03 21:18:59 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arkanoid.h"

void		ft_error(int er)
{
	if (er == CREATE_WINDOW)
		printf("glfwCreateWindow() fail\n");
	if (er == NO_MAP)
		printf("Map wasn't found\n");
	glfwTerminate();
	exit(EXIT_FAILURE);
}

void		ft_arraydel(char ***tab)
{
	int len;

	len = 0;
	while ((*tab)[len] != NULL)
	{
		free((*tab)[len]);
		len++;
	}
	free((*tab));
}

int			move_ball(t_ball *ball, t_ship *ship, t_map *map, int *score)
{
	int ret;

	ret = set_ball_pos(&ball->pos.y, ball->pos.y + ball->vspeed.y, -1, 1);
	if (ret == -1)
		ball->vspeed.y = -ball->vspeed.y;
	if (ret == -2)
		return (-1);
	else if (set_ball_pos(&ball->pos.x,
				ball->pos.x + ball->vspeed.x, -1, 1) <= -1)
		ball->vspeed.x = -ball->vspeed.x;
	else if (check_ship_collision(ball, ship) == TRUE && ball->rebound == 0)
		ball_rebound(ball, ship);
	else if (check_brick_collision(ball, map) == TRUE)
		*score += 1;
	else
		ball->rebound = 0;
	return (0);
}

int			removeball_n_setnewvec(t_ball *ball, t_brick *brick)
{
	if (brick->state != 9)
		brick->state -= 1;
	ball->vspeed.y = -ball->vspeed.y;
	return (1);
}

t_bool		check_brick_collision(t_ball *ball, t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (ball_is_in_brick(ball, &map->map[i][j]) == TRUE)
				return (removeball_n_setnewvec(ball, &map->map[i][j]));
			j++;
		}
		i++;
	}
	return (FALSE);
}
