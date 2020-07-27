/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdang <qdang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:41:18 by qdang             #+#    #+#             */
/*   Updated: 2020/07/27 15:32:25 by qdang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include "./marco.h"
# include "./structure.h"
# include <fcntl.h>
# include <stdio.h> // 記得刪除

int		count_split(char **str);
int		check_unsigned_int(char *str);
int		check_color(char **color);
int		check_map(char *line, t_info *s);
int		check_map_2(char *line);
int		check_map_3(t_info *s);

void	init_info(t_info *s);
void	free_split(char **str);
void	free_info(t_info *s);

void	ft_error(int err);

int		read_and_store(char	*file, t_info *s);
int		store_resolution(t_info *s, char **split);
int		store_texture_no(t_info *s, char **split);
int		store_texture_so(t_info *s, char **split);
int		store_texture_we(t_info *s, char **split);
int		store_texture_ea(t_info *s, char **split);
int		store_texture_s(t_info *s, char **split);
int		store_color_floor(t_info *s, char **split);
int		store_color_ceiling(t_info *s, char **split);
int		store_start(t_info *s, int i, int j);

int 	press_key(int key, t_info *s);
int		close_scene(t_info *s);

void    draw_2dmap(t_info *s);

#endif