/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itishche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 13:58:59 by itishche          #+#    #+#             */
/*   Updated: 2018/11/16 13:59:05 by itishche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static t_list	*checklist(const int fd, t_list **list)
{
	t_list *pro;

	if (!(*list))
	{
		*list = ft_lstnew("", fd);
		return (*list);
	}
	pro = *list;
	while (pro)
	{
		if (pro->content_size == (size_t)fd)
			return (pro);
		pro = pro->next;
	}
	pro = ft_lstnew("", fd);
	ft_lstadd(list, pro);
	return (*list);
}

static	int		nextlines(t_list **alst, char ***line)
{
	char			*str;
	int				i;

	i = 0;
	str = (*alst)->content;
	if (ft_strlen(str) == 0)
		return (0);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	**line = ft_strsub(str, 0, i);
	if (str[i] == '\n')
		str = ft_strdup(ft_strchr(str, '\n') + 1);
	else
		str = ft_strdup(ft_strchr(str, '\0'));
	free((*alst)->content);
	(*alst)->content = ft_strdup(str);
	free(str);
	return (1);
}

static	void	input(t_list **alst, const int fd)
{
	char			*buff;
	char			*temp;
	int				d;

	buff = (char *)malloc(sizeof(char) * BUFF_SIZE + 1);
	while ((d = read(fd, buff, BUFF_SIZE)))
	{
		buff[d] = '\0';
		temp = (*alst)->content;
		(*alst)->content = ft_strjoin((*alst)->content, buff);
		free(temp);
		if (ft_strchr((*alst)->content, '\n'))
			break ;
	}
	free(buff);
}

int				get_next_line(const int fd, char **line)
{
	static	t_list	*alst;
	t_list			*x;
	int				d;

	if (BUFF_SIZE < 1 || fd < 0 || read(fd, NULL, 0) < 0)
		return (-1);
	x = checklist(fd, &alst);
	input(&x, fd);
	d = nextlines(&x, &line);
	if (d == 0)
		return (0);
	else if (d < 0)
		return (-1);
	return (1);
}
// static void	new_lines(char **al, char **line, int r, int fd)
// {
// 	size_t	i;
// 	char	*t;

// 	i = 0;
// 	while (al[fd][i] != '\n' && al[fd][i])
// 		i++;
// 	if (al[fd][i] == '\n')
// 	{
// 		*line = ft_strsub(al[fd], 0, i);
// 		t = ft_strdup(&al[fd][i + 1]);
// 		free(al[fd]);
// 		al[fd] = t;
// 		if (al[fd][0] == '\0')
// 			ft_strdel(&al[fd]);
// 	}
// 	else if (al[fd][i] == '\0')
// 	{
// 		if (r == BUFF_SIZE)
// 			get_next_line(fd, line);
// 		*line = ft_strdup(al[fd]);
// 		ft_strdel(&al[fd]);
// 	}
// }

// int			get_next_line(const int fd, char **line)
// {
// 	static char	*a[4096];
// 	char		buff[BUFF_SIZE + 1];
// 	char		*t;
// 	int			d;

// 	if (fd < 0 || read(fd, 0, 0) < 0 || BUFF_SIZE <= 0 || !line)
// 		return (-1);
// 	if (a[fd] == NULL)
// 		a[fd] = ft_strnew(1);
// 	while (ft_strchr(a[fd], '\n') == NULL &&
// 		(d = read(fd, buff, BUFF_SIZE)) > 0)
// 	{
// 		buff[d] = '\0';
// 		t = ft_strjoin(a[fd], buff);
// 		free(a[fd]);
// 		a[fd] = t;
// 		if (ft_strchr(buff, '\n'))
// 			break ;
// 	}
// 	if (d == 0 && (a[fd] == NULL || a[fd][0] == '\0'))
// 		return (0);
// 	new_lines(a, line, d, fd);
// 	return (1);
// }
