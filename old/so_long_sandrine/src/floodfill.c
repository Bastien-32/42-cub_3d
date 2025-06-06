/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapupier <sapupier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:14:32 by sapupier          #+#    #+#             */
/*   Updated: 2025/03/26 11:28:25 by sapupier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_map	copy_map(t_map *original)
{
	t_map	copy;
	int		i;

	i = 0;
	copy.find_exit = 0;
	copy.rows = original->rows;
	copy.cols = original->cols;
	copy.collectibles = original->collectibles;
	copy.grid = malloc(copy.rows * sizeof(char *));
	if (!copy.grid)
		return ((t_map){0});
	while (i < copy.rows)
	{
		copy.grid[i] = ft_strdup(original->grid[i]);
		if (!copy.grid[i])
		{
			while (i > 0)
				free(copy.grid[--i]);
			free(copy.grid);
			return ((t_map){0});
		}
		i++;
	}
	return (copy);
}

void	free_map_(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->rows)
		free(map->grid[i++]);
	free(map->grid);
}

int	find_start(t_map *map, int *start_x, int *start_y)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			if (map->grid[y][x] == 'P')
			{
				*start_x = x;
				*start_y = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	flood_fill(t_map *map, int x, int y)
{
	if (map->grid[y][x] == 'E')
		map->find_exit = 1;
	if (x < 0 || y < 0 || x >= map->cols || y >= map->rows
		|| map->grid[y][x] == '1' || map->grid[y][x] == 'E')
		return ;
	if (map->grid[y][x] == 'C')
		map->collectibles--;
	map->grid[y][x] = '1';
	flood_fill(map, x - 1, y);
	flood_fill(map, x + 1, y);
	flood_fill(map, x, y - 1);
	flood_fill(map, x, y + 1);
}

int	verify_path(t_map *map)
{
	int		start_x;
	int		start_y;
	t_map	map_copy;

	start_x = 0;
	map_copy = copy_map(map);
	if (!map_copy.grid)
		return (0);
	if (!find_start(&map_copy, &start_x, &start_y))
	{
		free_map_(&map_copy);
		return (0);
	}
	flood_fill(&map_copy, start_x, start_y);
	free_map_(&map_copy);
	if (map_copy.collectibles == 0 && map_copy.find_exit == 1)
		return (1);
	return (0);
}
