/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksano <ksano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 11:15:04 by ksano             #+#    #+#             */
/*   Updated: 2020/11/27 23:23:47 by ksano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void			safe_free(char **p)
{
	if (p)
	{
		free(*p);
		*p = NULL;
	}
	return ;
}

static int		get_line(char **save, char **new_line, char **line)
{
	char		*tmp;
	int			ret;

	ret = SUCCESS;
	if (*new_line)
	{
		*line = ft_substr(*save, 0, *new_line - *save);
		tmp = *save;
		if (!(*save = ft_strdup(*save + (*new_line - *save) + 1)))
			return (ERROR);
		safe_free(&tmp);
	}
	else
	{
		*line = ft_strdup(*save);
		safe_free(save);
		ret = ALL_DONE;
	}
	if (!(*line || ret == ALL_DONE))
	{
		safe_free(line);
		safe_free(save);
		ret = ERROR;
	}
	return (ret);
}

static int		get_save(int fd, char **save, char **buf, char **new_line)
{
	char		*tmp;
	int			rc;

	while ((rc = read(fd, *buf, BUFFER_SIZE)) >= 0)
	{
		(*buf)[rc] = '\0';
		if (*save == NULL)
			*save = ft_strdup(*buf);
		else
		{
			tmp = *save;
			*save = ft_strjoin(*save, *buf);
			safe_free(&tmp);
		}
		if ((*new_line = ft_strchr(*save, '\n')) || !*save || !rc)
			break ;
	}
	return (rc);
}

int				get_next_line(int fd, char **line)
{
	static char	*save[FD_LIMIT];
	char		*buf;
	char		*new_line;
	int			rc;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd < FD_LIMIT)
		return (ERROR);
	buf = (char *)malloc((sizeof(char)) * (BUFFER_SIZE + 1));
	if (!buf || !line || read(fd, buf, 0) < 0)
	{
		safe_free(&save[fd]);
		safe_free(&buf);
		return (ERROR);
	}
	new_line = NULL;
	rc = get_save(fd, &save[fd], &buf, &new_line);
	safe_free(&buf);
	if (!save[fd])
		return (ERROR);
	if (!new_line && rc == 0)
		new_line = ft_strchr(save[fd], '\n');
	return (get_line(&save[fd], &new_line, line));
}
