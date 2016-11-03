/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jripoute <jripoute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 21:34:49 by jripoute          #+#    #+#             */
/*   Updated: 2015/05/03 21:49:40 by jripoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arkanoid.h"

static void		get_map_dimensions(char *file, int *height, int *width)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	line = NULL;
	*height = 0;
	*width = 1;
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_error(NO_MAP);
	while (get_next_line(fd, &line) > 0)
	{
		if (*height == 0)
		{
			while (line[i])
			{
				i++;
				*width += 1;
			}
		}
		ft_strdel(&line);
		*height += 1;
	}
	close(fd);
}

void			init_map_parser2(t_map *map, char *line, int j, double y)
{
	char	**buf;
	double	x;
	int		i;

	i = 0;
	x = -0.90;
	buf = ft_strsplit(line, ' ');
	while (buf[i])
	{
		map->map[j][i].state = ft_atoi(buf[i]);
		map->map[j][i].pos.x = x;
		map->map[j][i].pos.y = y;
		map->map[j][i].height = BRICK_H;
		map->map[j][i].width = BRICK_W;
		x += BRICK_OFFSET_X;
		free(buf[i]);
		i++;
	}
	free(buf);
}

void			init_map_parser(t_map *map, char *filename)
{
	int		i;
	int		fd;
	char	*line;
	double	y;

	i = 0;
	y = 1.1;
	get_map_dimensions(filename, &map->height, &map->width);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_error(NO_MAP);
	map->map = (t_brick **)ft_memalloc(sizeof(t_brick *) * map->height + 1);
	while (get_next_line(fd, &line) > 0)
	{
		map->map[i] = (t_brick *)ft_memalloc(sizeof(t_brick) * map->width);
		init_map_parser2(map, line, i, y);
		free(line);
		y -= BRICK_OFFSET_Y;
		i++;
	}
	map->map[i] = NULL;
	close(fd);
}
