/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksano <ksano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 11:15:04 by ksano             #+#    #+#             */
/*   Updated: 2020/11/21 15:02:08 by ksano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t			ft_strlen(const char *s)
{
	size_t		i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void			safe_free(char **ptr)
{
	if (ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return ;
}

char			*check_save(char *save, char **line)
{
	char		*nl;

	nl = NULL;
	if (save)
	{
		if ((nl = ft_strchr(save, '\n')))
		{
			// if (nl[0] != '\n')
				*nl = '\0';
			if (!(*line = ft_strdup(save)))
				return (NULL);
			nl++;
			ft_strlcpy(save, nl, ft_strlen(nl) + 1);
		}
		else
		{
			if (!(*line = ft_strdup(save)))
				return (NULL);
			while (*save)
				*save++ = '\0';
		}
	}
	else
		*line = ft_strdup("");
	return (nl);
}

int			get_line(int fd, char **line, char **save)
{
	char		buf[BUFFER_SIZE + 1];
	int			rc;
	char		*nl;
	char		*tmp;

	nl = NULL;
	nl = check_save(*save, line);
	while (!nl && (rc = read(fd, buf, BUFFER_SIZE)))
	{
		buf[rc] = '\0';
		if ((nl = ft_strchr(buf, '\n')) != NULL)
		{
			*nl = '\0';
			nl++;
			tmp = *save;
			if (!(*save = ft_strdup(nl)))
				return (ERROR);
			safe_free(&tmp);
		}
		tmp = *line;
		if (!(*line = ft_strjoin(*line, buf)))
			return (ERROR);
		safe_free(&tmp);
	}
	return((ft_strlen(*save) || ft_strlen(*line) ? CONTINUED : ALL_DONE));
}

int				get_next_line(int fd, char **line)
{
	static char	*save;
	int			ret;
	char		*e;

	e = NULL;
	if (fd < 0 || !line || BUFFER_SIZE <= 0 || read(fd, e, 0) < 0)
		return (ERROR);
	ret = get_line(fd, line, &save);
	if (ret == ERROR)
		return (ERROR);
	if (save)
		if (save[0] == '\0')
			safe_free(&save);
	if (ret == ALL_DONE)
		safe_free(&save);
	return (ret);
}
