/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksano <ksano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 11:15:04 by ksano             #+#    #+#             */
/*   Updated: 2020/11/21 12:57:25 by ksano            ###   ########.fr       */
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

// void			readline(fd, **line, *buf, *save)
// {
// 	while (!nl && (rc = read(fd, buf, BUFFER_SIZE)))
// 	{
// 		buf[rc] = '\0';
// 		if ((nl = ft_strchr(buf, '\n')))
// 		{
// 			*nl = '\0';
// 			nl++;
// 			tmp = save;
// 			if (!(save = ft_strdup(nl)))
// 				return (ERROR);
// 			safe_free(&save);
// 		}
// 		tmp = *line;
// 		if (!(*line = ft_strjoin(*line, buf)))
// 			return (ERROR);
// 		safe_free(&tmp);
// 	}
// }

char			*check_save(char *save, char **line)
{
	char		*nl;

	nl = NULL;
	if (save)
	{
		if ((nl = ft_strchr(save, '\n')))
		{
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

int				get_next_line(int fd, char **line)
{
	static char	*save;
	char		buf[BUFFER_SIZE + 1];
	int			rc;
	char		*nl;
	char		*tmp;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (ERROR);
	nl = check_save(save, line);
	while (!nl && (rc = read(fd, buf, BUFFER_SIZE)))
	{
		buf[rc] = '\0';
		if ((nl = ft_strchr(buf, '\n')))
		{
			*nl = '\0';
			nl++;
			tmp = save;
			if (!(save = ft_strdup(nl)))
				return (ERROR);
			safe_free(&tmp);
		}
		tmp = *line;
		if (!(*line = ft_strjoin(*line, buf)))
			return (ERROR);
		safe_free(&tmp);
	}
	if (*save)
		if (save[0] == '\0')
			safe_free(&save);
	return ((rc || ft_strlen(save) || ft_strlen(*line)) ? SUCCESS : ALL_DONE);
}
