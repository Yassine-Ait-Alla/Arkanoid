/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_n_loose.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jripoute <jripoute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/03 05:33:40 by jripoute          #+#    #+#             */
/*   Updated: 2015/05/03 21:52:29 by jripoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arkanoid.h"

void		init_scene(t_all *all)
{
	all->ball.vspeed.x = 0;
	all->ball.vspeed.y = 0;
	all->ball.pos.x = 0;
	all->ball.pos.y = (SHIP_OFFSET) + ((BALL_SIZE) * 2);
	all->ship.pos.x = -(SHIP_W);
	all->ship.pos.y = (SHIP_OFFSET) + (SHIP_H);
}

void		load_new_map(t_all *all)
{
	int		fd;
	int		i;
	double	y;
	char	*line;

	i = 0;
	y = 1.1;
	line = NULL;
	init_scene(all);
	all->level[16] += 1;
	if ((fd = open(all->level, O_RDONLY)) == -1)
		ft_error(NO_MAP);
	while (get_next_line(fd, &line) > 0)
	{
		init_map_parser2(&all->map, line, i, y);
		y -= (BRICK_OFFSET_Y);
		i++;
	}
	all->map.map[i] = NULL;
	close(fd);
}
