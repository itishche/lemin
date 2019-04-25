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
	t_list	*lst;
	// t_list	*head;
	int		k;


	k = 0;
	lst = ft_lstnew(NULL, 0); 
	// head = lst;
	while (get_next_line(0, &line) > 0)
	{//ft_lstadd - добавляет все время в начало списка
		ft_lstadd(&lst, ft_lstnew(line, ft_strlen(line) + 1));
		k++;
		free(line);
	}
	if (k == 0)
		return (write(1, "usage: ./lem-in < ant_farm_map2\n", 32));
	lem->map = (char**)malloc(sizeof(char*) * (k + 1));
	lem->map[k--] = NULL;
	while (lst->next)
	{
		lem->map[k--] = ft_strdup(lst->content);
		lst = lst->next;
	}
	k = 0;
	while (lem->map[k] != NULL)
	{	
		printf("%s\n", lem->map[k]); 
		k++;
	}
	// lst = head;
	printf("нужно почистить лист!\n");
	// while (lst->next)
	// {
	// 	k++;
	// 	free(lst->content);
	// 	head = lst->next;
	// 	free(lst);
	// 	lst = head;
	// 	printf("k = %d\n", k);
	// }
	// printf("k = %d\n", k);
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
				printf("1--------------------problem with start or/and\n");
				return (-1);
			}
			if (i == 0)
				return (-1);
			lem->n = ft_atoi(lem->map[i - 1]);
			printf("number of ants = %d\n", lem->n);
			if (lem->n > 2147483647 || lem->n <= 0)
			{
				printf("WRONG NUMBER of ants\n");
				return (-1);
			}
		}
		if (ft_strcmp(lem->map[i], "##end") == 0)
		{
			if (start == 1)
			start = 2;
			else
			{
				// printf("lem->map[i]= %s\n", lem->map[i]);
				printf("22--------------------problem with start or/and\n");
				return (-1);
			}
		}

		i++;
	}
	if (start != 2)
	{
		printf("problem with start or/and and------------------------\n");
		return (-1);
	}
	return (1);
}

int		size_2d_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

void	free_free(char **arr)
{
	int		i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
}

int		chek_coord(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
		{
			printf("letter or - in coord\n");
			return (-1);
		}
		i++;
	}
	return (1);
}

int		write_rooms(t_lem *lem)
{
	int		i;
	int		k;
	char	**s;
	int		st_or_end;//0 - обычная комната, 1 = старт, 2 = конец

	lem->coord = (t_coord*)ft_memalloc(sizeof(t_coord) * (lem->rooms));
	i = 0;
	k = 0;
	st_or_end = 0;
	while (k < lem->rooms)
	{
		if (ft_strcmp(lem->map[i], "##start") == 0)
			st_or_end = 1;
		if (ft_strcmp(lem->map[i], "##end") == 0)
			st_or_end = 2;
		s = ft_strsplit(lem->map[i], ' ');
		if (size_2d_arr(s) == 3)
		{
			lem->coord[k].room = ft_strdup(s[0]);
			if (chek_coord(s[1]) == -1 || chek_coord(s[2]) == -1)
				return (-1);//проверка на отрицательные коорд и буквы
			lem->coord[k].x = ft_atoi(s[1]);
			lem->coord[k].y = ft_atoi(s[2]);
			lem->coord[k].st_or_end = st_or_end;
			st_or_end = 0;
			k++;
		}
		free_free(s);
		i++;
	}
	k = 0;
	while (k < lem->rooms)//печать всех комнат
	{
		if (lem->coord[k].st_or_end == 0)
			printf("room: ");
		if (lem->coord[k].st_or_end == 1)
			printf("start room: ");
		if (lem->coord[k].st_or_end == 2)
			printf("end room: ");
		printf("%s, %d, %d\n", lem->coord[k].room, lem->coord[k].x, lem->coord[k].y);
		k++;
	}
	return (1);
}

int		valid_coord(t_lem *lem)
{
	int		i;
	char	**s;
	//поcчитать кол-во комнат!!
	i = 0;
	while (lem->map[i] != NULL)
	{
		s = ft_strsplit(lem->map[i], ' ');
		if (size_2d_arr(s) > 3 || size_2d_arr(s) == 0)
		{
			printf("ERR: 3 coordinates OR empty line\n");
			return (-1);
		}
		if (size_2d_arr(s) == 3)
			lem->rooms++;
		free_free(s);
		i++;
	}
	printf("lem->rooms = %d\n", lem->rooms);
	if (write_rooms(lem) == -1)
		return (-1);

	return (1);
}

int		validator(t_lem *lem)
{

	if (map_init(lem) != 222)
	{
		printf("validator NOT OK-1\n");
		return (-1);
	}
	if (valid_symb(lem) == -1)
	{
		printf("validator NOT OK-2\n");
		return (-1);
	}
	if (valid_coord(lem) == -1)
	{
		printf("validator NOT OK-3  (3 coord, duplicate or letter in coord)\n");
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