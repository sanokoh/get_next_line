/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksano <ksano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 11:15:04 by ksano             #+#    #+#             */
/*   Updated: 2020/11/28 16:24:10 by ksano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	int			ret;
	char		*tmp;

	ret = SUCCESS;
	if (*new_line)
	{
		*line = ft_substr(*save, 0, *new_line - *save);
		tmp = *save;
		if (!(*save = ft_strdup((*new_line + 1))))
			ret = ERROR;
		safe_free(&tmp);
	}
	else
	{
		*line = ft_strdup(*save);
		safe_free(save);
		ret = ALL_DONE;
	}
	if (!(*line) || ret == ERROR)
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
	static char	*save;
	char		*buf;
	char		*new_line;
	int			rc;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ERROR);
	buf = (char *)malloc((sizeof(char)) * (BUFFER_SIZE + 1));
	if (!buf || !line || read(fd, buf, 0) < 0)
	{
		safe_free(&save);
		safe_free(&buf);
		return (ERROR);
	}
	new_line = NULL;
	rc = get_save(fd, &save, &buf, &new_line);
		if (rc == -1)
			return (ERROR);
	safe_free(&buf);
	if (!(save))
		return (ERROR);
	// if (!new_line && rc == 0)
	// 	new_line = ft_strchr(save, '\n');
	return (get_line(&save, &new_line, line));
}
