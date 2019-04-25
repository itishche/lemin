/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itishche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 10:51:30 by itishche          #+#    #+#             */
/*   Updated: 2019/04/24 10:51:33 by itishche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct	s_coord
{
	char		*room;
	int			x;
	int			y;
	int			st_or_end;
}				t_coord;

typedef struct	s_lem
{
	int			n;//number of ants
	int			rooms;//number of rooms
	char		**map;
	t_coord		*coord;
}				t_lem;


#endif
