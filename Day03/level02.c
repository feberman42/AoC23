/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feberman <feberman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 08:26:06 by feberman          #+#    #+#             */
/*   Updated: 2023/12/03 11:14:25 by feberman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "../libft.h"

int		get_file_size(char *path);
char	**get_lines(char *path);
int		sum_ratios(char **lines);
int		rev_atoi(char *str, int i);
void	free_split(char **split);

int	main(int argc, char **argv)
{
	char **lines;

	if (argc != 2)
		return (1);
	lines = get_lines(argv[1]);
	if (!lines)
		return (5);
	
	ft_printf("%d\n", sum_ratios(lines));
	free_split(lines);
	return (0);
}

int	sum_ratios(char **lines)
{
	int	nc;
	int	ratio;
	int	sum = 0;
	int	x = 0;
	int y = 0;

	while (lines[y])
	{
		x = -1;
		while (++x < ft_strlen(lines[y]))
		{
			if (lines[y][x] != '*')
				continue ;
			nc = 0;
			ratio = 1;
			if (x > 0)
			{
				if (ft_isdigit(lines[y][x - 1]))
				{
					nc++;
					ratio *= rev_atoi(lines[y], x - 1);
				}
			}
			if (ft_isdigit(lines[y][x + 1]))
			{
				nc++;
				ratio *= ft_atoi(lines[y] + x + 1);
			}
			if (y > 0)
			{
				if (ft_isdigit(lines[y - 1][x]))
				{
					nc++;
					ratio *= rev_atoi(lines[y - 1], x);
				}
				else
				{
					if (x > 0)
					{
						if (ft_isdigit(lines[y - 1][x - 1]))
						{
							nc++;
							ratio *= rev_atoi(lines[y - 1], x - 1);
						}
					}
					if (x < ft_strlen(lines[y]) - 1)
					{
						if (ft_isdigit(lines[y - 1][x + 1]))
						{
							nc++;
							ratio *= ft_atoi(lines[y - 1] + x + 1);
						}
					}
				}
			}
			if (lines[y + 1])
			{
				if (ft_isdigit(lines[y + 1][x]))
				{
					nc++;
					ratio *= rev_atoi(lines[y + 1], x);
				}
				else
				{
					if (x > 0)
					{
						if (ft_isdigit(lines[y + 1][x - 1]))
						{
							nc++;
							ratio *= rev_atoi(lines[y + 1], x - 1);
						}
					}
					if (x < ft_strlen(lines[y]) - 1)
					{
						if (ft_isdigit(lines[y + 1][x + 1]))
						{
							nc++;
							ratio *= ft_atoi(lines[y + 1] + x + 1);
						}
					}
				}
			}
			if (nc == 2)
				sum += ratio;
			}
		y++;
	}
	return (sum);
}

int	rev_atoi(char *str, int i)
{
	int	t;

	t = i;
	while (ft_isdigit(str[t]))
	{
		if (t > 0)
			t--;
		else
			return (ft_atoi(str + t));
	}
	return (ft_atoi(str + t + 1));
}

char	**get_lines(char *path)
{
	int		file_size;
	char	*file_raw;
	char	**lines;
	int		fd;

	file_size = get_file_size(path);
	if (file_size <= 0)
		exit(2);
	file_raw = malloc(file_size);
	if (!file_raw)
		exit(3);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(file_raw);
		exit(4);
	}
	read(fd, file_raw, file_size);
	close(fd);
	lines = ft_split(file_raw, '\n');
	free(file_raw);
	return (lines);
}

int	get_file_size(char *path)
{
	int		fd;
	int		file_size;
	char	buf[1];


	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	file_size = 0;
	while (read(fd, buf, 1) > 0)
		file_size++;
	close(fd);
	return (file_size);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split[i]);
	free(split);
}
