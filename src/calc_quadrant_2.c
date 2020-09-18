/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_quadrant_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdang <qdang@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 11:29:01 by qdang             #+#    #+#             */
/*   Updated: 2020/09/18 10:47:18 by qdang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	calc_quadrant_2_i(t_info *s, double angle)
{
	int		temp_x;
	int		temp_y;
	char	c;
	int		i;

	i = 0;
	c = ' ';
	temp_y = s->grid.y - (int)(0.5 + (0.5 + i) * tan(angle));
	temp_x = s->grid.x - (1 + i);
	if (temp_y >= 0 && temp_x >= 0)
		c = s->map[temp_y][temp_x];
	while (c == '0' || c == s->start)
	{
		i++;
		temp_y = s->grid.y - (int)(0.5 + (0.5 + i) * tan(angle));
		temp_x = s->grid.x - (1 + i);
		if (temp_y >= 0 && temp_x >= 0)
			c = s->map[temp_y][temp_x];
		else
			break ;
	}
	return (i);
}

static int	calc_quadrant_2_j(t_info *s, double angle)
{
	int		temp_x;
	int		temp_y;
	char	c;
	int		j;

	j = 0;
	c = ' ';
	temp_y = s->grid.y - (1 + j);
	temp_x = s->grid.x - (int)(0.5 + (0.5 + j) / tan(angle));
	if (temp_y >= 0 && temp_x >= 0)
		c = s->map[temp_y][temp_x];
	while (c == '0' || c == s->start)
	{
		j++;
		temp_y = s->grid.y - (1 + j);
		temp_x = s->grid.x - (int)(0.5 + (0.5 + j) / tan(angle));
		if (temp_y >= 0 && temp_x >= 0)
			c = s->map[temp_y][temp_x];
		else
			break ;
	}
	return (j);
}

static void	calc_quadrant_2_0(t_info *s)
{
	char	c;
	int		i;

	i = 0;
	c = s->map[s->grid.y][s->grid.x - 1];
	while (c == '0' || c == s->start)
	{
		i++;
		c = s->map[s->grid.y][s->grid.x - 1 - i];
	}
	s->length = (0.5 + i) * SL;
	s->its.x = s->stand.x - s->length;
	s->its.y = s->stand.y;
	s->wall = 'W';
}

static void	calc_quadrant_2_1(t_info *s, int i, double angle, double dev)
{
	s->its.x = s->stand.x - (int)((0.5 + i) * SL);
	s->its.y = s->stand.y - (int)((0.5 + i) * SL * tan(angle));
	s->length = (0.5 + i) * SL / cos(angle) * cos(dev);
	s->wall = 'W';
	if (tan(angle) > 1 - REDUND && tan(angle) < 1 + REDUND)
		check_stand(s, 0, -1) == 0 ? s->wall = 'N' : 0;
}

void		calc_quadrant_2(t_info *s, double angle, double dev)
{
	int		i;
	int		j;

	if (angle >= M_PI_2 * 3 - REDUND && angle <= M_PI_2 * 3 + REDUND)
		calc_quadrant_2_0(s);
	else
	{
		angle -= M_PI_2 * 3;
		i = calc_quadrant_2_i(s, angle);
		j = calc_quadrant_2_j(s, angle);
		if ((int)((0.5 + i) * SL) <= (int)((0.5 + j) * SL / tan(angle)))
			calc_quadrant_2_1(s, i, angle, dev);
		else
		{
			s->its.x = s->stand.x - (int)((0.5 + j) * SL / tan(angle));
			s->its.y = s->stand.y - (int)((0.5 + j) * SL);
			s->length = (0.5 + j) * SL / sin(angle) * cos(dev);
			s->wall = 'N';
			if (tan(angle) > 1 - REDUND && tan(angle) < 1 + REDUND)
				check_stand(s, -1, 0) == 0 ? s->wall = 'W' : 0;
		}
	}
}
