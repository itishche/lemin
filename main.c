/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itishche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 10:31:47 by itishche          #+#    #+#             */
/*   Updated: 2019/04/24 10:31:50 by itishche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/lemin.h"


int		map_init(t_lem *lem)
{
	char	*line;
	int		k;

	k = 0;
	while (get_next_line(0, &line) > 0)
	{
		lem->map[k++] = ft_strdup(line);
		free(line);
	}
	lem->map[k] = NULL;
	if (k == 0)
		return (write(1, "usage: ./lem-in < ant_farm_map2\n", 32));
	else
		return (222);
}

int		valid_symb(t_lem *lem)
{
	int	i;
	int start;

	i = 0;
	start = 0;
	while (lem->map[i] != NULL)
	{
		if (lem->map[i + 1] == NULL)
		 	break ;
		if (lem->map[i][0] == 'L')
			return (-1);
		while (lem->map[i][0] == '#' && ft_strcmp(lem->map[i], "##start") != 0
			&& ft_strcmp(lem->map[i], "##end") != 0 && lem->map[i] != NULL)
			i++;
		if (ft_strcmp(lem->map[i], "##start") == 0)
		{
			if (start == 0)
				start = 1;
			else
			{
				// printf("lem->map[i]= %s\n", lem->map[i]);
				printf("1--------------------problem with start or/and\n");
				return (-1);
			}

			if (i == 0)
				return (-1);
			lem->n = ft_atoi(lem->map[i - 1]);
			
			printf("number of ants = %d\n", lem->n);
			if (lem->n > 2147483647 || lem->n <= 0)
			{
				printf("wrong number of ants\n");
				return (-1);
			}
		}
		if (ft_strcmp(lem->map[i], "##end") == 0)
		{
			if (start == 1)
			start = 2;
			else
			{
				printf("lem->map[i]= %s\n", lem->map[i]);
				printf("22--------------------prblem with start or/and\n");
				return (-1);
			}
		}

		i++;
	}
	if (start != 2)
	{
		printf("prblem with start or/and and\n");
		return (-1);
	}
	return (1);
}

int		validator(t_lem *lem)
{

	if (map_init(lem) != 222)
	{
		printf("validator NOT OK-1 (directory or smth else)\n");

		return (-1);
	}
	if (valid_symb(lem) == -1)
	{
		printf("validator NOT OK-2\n");
		return (-1);
	}
	return (1);
}

int		main(int argc, char **argv)
{
	t_lem			lem;

	if (argc != 1)
		return(write(1, "usage: ./lem-in < ant_farm_map1\n", 32));
	*argv = NULL;
	ft_bzero(&lem, sizeof(lem));
	if (validator(&lem) == -1)
		return (write(1, "usage: ./lem-in < ant_farm_map3\n", 32));
	else
		return (write(1, "validator is OK\n", 16));
	return (0);
}