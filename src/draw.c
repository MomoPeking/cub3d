/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdang <qdang@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 14:53:54 by qdang             #+#    #+#             */
/*   Updated: 2020/10/04 11:48:41 by qdang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
** The block include the upper and left edges but not the lower and right edges.
*/

static void	draw_2d_block(t_info *s, int x, int y, int color)
{
	int		i;
	int		j;

	i = -1;
	while (++i < SL)
	{
		j = -1;
		while (++j < SL)
			s->img_add[(i + y) * s->sl + x + j] = color;
	}
}

void		draw_2d_frame(t_info *s)
{
	int		i;
	int		j;

	i = -1;
	while (++i < s->ms.y)
	{
		j = -1;
		while (++j < s->ms.x)
		{
			if (s->map[i][j] == '1')
				draw_2d_block(s, j * SL, i * SL, BLACK);
			else if (s->map[i][j] == '2')
				draw_2d_block(s, j * SL, i * SL, RED);
		}
	}
}

void		draw_2d_sight(t_info *s)
{
	int		i;
	int		j;

	i = -1;
	while (++i < s->ms.y)
	{
		j = -1;
		while (++j < s->ms.x)
			if (s->map[i][j] != '1'
				&& s->map[i][j] != '2'
				&& s->map[i][j] != ' ')
				draw_2d_block(s, j * SL, i * SL, WHITE);
	}
	calculate(s, s->sight);
	draw_line(s, s->stand, s->its, BLUE);
	calculate(s, s->sight + M_PI / 180 * FOV);
	draw_line(s, s->stand, s->its, BLUE);
}

static int	draw_3d_wall(t_info *s, t_wall w, int i, int k)
{
	int		temp;

	temp = k;
	while (++k < w.down)
	{
		if (w.h <= s->res.y)
			s->tex.y = (k - temp) * 64 / w.h;
		else
			s->tex.y = (double)(k * 64 + (w.h - s->res.y) * 32) / w.h;
		if (s->wall == 'N')
			s->img_add[k * s->sl + i] = s->no_add[s->tex.y * 64 + s->tex.x];
		else if (s->wall == 'E')
			s->img_add[k * s->sl + i] = s->ea_add[s->tex.y * 64 + s->tex.x];
		else if (s->wall == 'W')
			s->img_add[k * s->sl + i] = s->we_add[s->tex.y * 64 + s->tex.x];
		else
			s->img_add[k * s->sl + i] = s->so_add[s->tex.y * 64 + s->tex.x];
	}
	return (k);
}

void		draw_3d_vline(t_info *s, int i)
{
	int		k;
	t_wall	w;

	w.up = s->res.y / 2 - s->wall_cf / s->length / 2;
	w.down = s->res.y / 2 + s->wall_cf / s->length / 2;
	w.h = w.down - w.up;
	w.up < 0 ? w.up = 0 : 0;
	w.down > s->res.y ? w.down = s->res.y : 0;
	k = -1;
	while (++k < w.up)
		s->img_add[k * s->sl + i] = s->color_c;
	k--;
	k = draw_3d_wall(s, w, i, k);
	k--;
	while (++k < s->res.y)
		s->img_add[k * s->sl + i] = s->color_f;
}

//	牆可以擋住小精靈，小精靈也可以擋住牆。
//	簡化模型，目前只按照中點判斷是否在視野之內，只考慮一個sprite的情況。
//	在calc方程中 確定是否能看到spirte？
