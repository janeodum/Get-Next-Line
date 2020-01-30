/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaodum <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:02:26 by jaodum            #+#    #+#             */
/*   Updated: 2020/01/14 13:12:00 by jaodum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_append_line(char **saved, char **line)
{
	int		len;
	char	*temp;

	len = 0;
	while ((*saved)[len] != '\n' && (*saved)[len] != '\0')
		len++;
	if ((*saved)[len] == '\n')
	{
		*line = ft_strsub(*saved, 0, len);
		temp = ft_strdup(&((*saved)[len + 1]));
		free(*saved);
		*saved = temp;
		if ((*saved)[0] == '\0')
			ft_strdel(saved);
	}
	else
	{
		*line = ft_strdup(*saved);
		ft_strdel(saved);
	}
	return (1);
}

static int	ft_output(char **saved, char **line, int ret_value, int fd)
{
	if (ret_value < 0)
	{
		return (-1);
	}
	else if (ret_value == 0 && saved[fd] == NULL)
	{
		return (0);
	}
	else
	{
		return (ft_append_line(&saved[fd], line));
	}
}

int			get_next_line(const int fd, char **line)
{
	char		buff[BUFF_SIZE + 1];
	char		*temp;
	static char	*saved[MAXFD];
	int			ret_value;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((ret_value = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret_value] = '\0';
		if (saved[fd] == NULL)
		{
			saved[fd] = ft_strdup(buff);
		}
		else
		{
			temp = ft_strjoin(saved[fd], buff);
			free(saved[fd]);
			saved[fd] = temp;
		}
		if (ft_strchr(saved[fd], '\n'))
			break ;
	}
	return (ft_output(saved, line, ret_value, fd));
}
