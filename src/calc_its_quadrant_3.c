/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_its_quadrant_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdang <qdang@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 10:43:10 by qdang             #+#    #+#             */
/*   Updated: 2020/08/18 22:51:51 by qdang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	calc_its_quadrant_3_i(t_info *s, double radian)
{
	int		temp_x;
	int		temp_y;
	char	c;
	int		i;

	i = 0;
	c = ' ';
	temp_y = s->grid.y + 1 + i;
	temp_x = s->grid.x - (int)(0.5 + (0.5 + i) * tan(radian));
	if (temp_y <= s->ms.x - 1 && temp_x >= 0)
		c = s->map[temp_y][temp_x];
	while (c == '0' || c == s->start)
	{
		i++;
		temp_y = s->grid.y + 1 + i;
		temp_x = s->grid.x - (int)(0.5 + (0.5 + i) * tan(radian));
		if (temp_y <= s->ms.x - 1 && temp_x >= 0)
			c = s->map[temp_y][temp_x];
		else
			break ;
	}
	return (i);
}

static int	calc_its_quadrant_3_j(t_info *s, double radian)
{
	int		temp_x;
	int		temp_y;
	char	c;
	int		j;

	j = 0;
	c = ' ';
	temp_y = s->grid.y + (int)(0.5 + (0.5 + j) / tan(radian));
	temp_x = s->grid.x - 1 - j;
	if (temp_y <= s->ms.x - 1 && temp_x >= 0)
		c = s->map[temp_y][temp_x];
	while (c == '0' || c == s->start)
	{
		j++;
		temp_y = s->grid.y + (int)(0.5 + (0.5 + j) / tan(radian));
		temp_x = s->grid.x - 1 - j;
		if (temp_y <= s->ms.x - 1 && temp_x >= 0)
			c = s->map[temp_y][temp_x];
		else
			break ;
	}
	return (j);
}

static void	calc_its_quadrant_3_0(t_info *s)
{
	char	c;
	int		i;

	i = 0;
	c = s->map[s->grid.y + 1][s->grid.x];
	while (c == '0' || c == s->start)
	{
		i++;
		c = s->map[s->grid.y + 1 + i][s->grid.x];
	}
	s->its.x = s->stand.x;
	s->its.y = s->stand.y + (int)((0.5 + i) * UL);
}

void		calc_its_quadrant_3(t_info *s, double radian)
{
	int		i;
	int		j;

	if (radian >= M_PI - REDUND && radian <= M_PI + REDUND)
		calc_its_quadrant_3_0(s);
	else
	{
		radian -= M_PI;
		i = calc_its_quadrant_3_i(s, radian);
		j = calc_its_quadrant_3_j(s, radian);
		if ((int)((0.5 + i) * UL) <= (int)((0.5 + j) * UL / tan(radian)))
		{
			s->its.x = s->stand.x - (int)((0.5 + i) * UL * tan(radian));
			s->its.y = s->stand.y + (int)((0.5 + i) * UL);
		}
		else
		{
			s->its.x = s->stand.x - (int)((0.5 + j) * UL);
			s->its.y = s->stand.y + (int)((0.5 + j) * UL / tan(radian));
		}
	}
}
