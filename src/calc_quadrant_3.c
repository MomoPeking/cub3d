/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_quadrant_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdang <qdang@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 10:43:10 by qdang             #+#    #+#             */
/*   Updated: 2020/10/12 13:12:38 by qdang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	calc_quadrant_3_i(t_info *s, double angle)
{
	int		temp_x;
	int		temp_y;
	char	c;
	int		i;

	i = 0;
	c = ' ';
	temp_y = s->grid.y + 1 + i;
	temp_x = s->grid.x - (int)(0.5 + (0.5 + i) * tan(angle));
	if (temp_y <= s->ms.x - 1 && temp_x >= 0)
		c = s->map[temp_y][temp_x];
	while (c != '1')
	{
		i++;
		temp_y = s->grid.y + 1 + i;
		temp_x = s->grid.x - (int)(0.5 + (0.5 + i) * tan(angle));
		if (temp_y <= s->ms.y - 1 && temp_x >= 0)
			c = s->map[temp_y][temp_x];
		else
			break ;
	}
	return (i);
}

static int	calc_quadrant_3_j(t_info *s, double angle)
{
	int		temp_x;
	int		temp_y;
	char	c;
	int		j;

	j = 0;
	c = ' ';
	temp_y = s->grid.y + (int)(0.5 + (0.5 + j) / tan(angle));
	temp_x = s->grid.x - 1 - j;
	if (temp_y <= s->ms.y - 1 && temp_x >= 0)
		c = s->map[temp_y][temp_x];
	while (c != '1')
	{
		j++;
		temp_y = s->grid.y + (int)(0.5 + (0.5 + j) / tan(angle));
		temp_x = s->grid.x - 1 - j;
		if (temp_y <= s->ms.y - 1 && temp_x >= 0)
			c = s->map[temp_y][temp_x];
		else
			break ;
	}
	return (j);
}

static void	calc_quadrant_3_0(t_info *s)
{
	char	c;
	int		i;

	i = 0;
	c = s->map[s->grid.y + 1][s->grid.x];
	while (c != '1')
	{
		i++;
		c = s->map[s->grid.y + 1 + i][s->grid.x];
	}
	s->length = (0.5 + i) * SL;
	s->its.x = s->stand.x;
	s->its.y = s->stand.y + s->length;
	s->tex.x = 32;
	s->wall = 'S';
}

static void	calc_quadrant_3_1(t_info *s, int i, double angle, double dev)
{
	s->its.x = s->stand.x - (int)((0.5 + i) * SL * tan(angle));
	s->its.y = s->stand.y + (int)((0.5 + i) * SL);
	s->length = (0.5 + i) * SL / cos(angle);
	s->tex.x = s->length * sin(angle) * 64 / SL + 32;
	while (s->tex.x >= 64)
		s->tex.x -= 64;
	s->length *= cos(dev);
	s->wall = 'S';
	if (tan(angle) > 1 - REDUND && tan(angle) < 1 + REDUND)
		check_stand(s, -1, 0) == 0 ? s->wall = 'W' : 0;
}

void		calc_quadrant_3(t_info *s, double angle, double dev)
{
	t_point		p;

	if (angle >= M_PI - REDUND && angle <= M_PI + REDUND)
		calc_quadrant_3_0(s);
	else
	{
		angle -= M_PI;
		p.x = calc_quadrant_3_i(s, angle);
		p.y = calc_quadrant_3_j(s, angle);
		if ((int)((0.5 + p.x) * SL) <= (int)((0.5 + p.y) * SL / tan(angle)))
			calc_quadrant_3_1(s, p.x, angle, dev);
		else
		{
			s->its.x = s->stand.x - (int)((0.5 + p.y) * SL);
			s->its.y = s->stand.y + (int)((0.5 + p.y) * SL / tan(angle));
			s->length = (0.5 + p.y) * SL / sin(angle);
			s->tex.x = -1 * s->length * cos(angle) * 64 / SL - 32;
			while (s->tex.x < 0)
				s->tex.x += 64;
			s->length *= cos(dev);
			s->wall = 'W';
			if (tan(angle) > 1 - REDUND && tan(angle) < 1 + REDUND)
				check_stand(s, 0, 1) == 0 ? s->wall = 'S' : 0;
		}
	}
}
