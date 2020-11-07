/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksano <ksano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 11:15:04 by ksano             #+#    #+#             */
/*   Updated: 2020/11/07 16:36:40 by ksano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void			safe_free(char **ptr)
{
	int			i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i++]);
		*ptr = NULL;
	}
}

size_t			ft_strlen(const char *s)
{
	size_t		i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

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
	// char		*tmp;

	check_save(save, line);
	nl = NULL;
	while (!nl && (rc = read(fd, buf, BUFFER_SIZE)))
	{
		buf[rc] = '\0';
		if ((nl = ft_strchr(buf, '\n')))
		{
			*nl = '\0';
			nl++;
			if (!(save = ft_strdup(nl)))
				return (ERROR);
		}
		// tmp = *line;
		if (!(*line = ft_strjoin(*line, buf)))
			return (ERROR);
		// free(tmp);
	}
	return (rc || ft_strlen(save) || ft_strlen(*line) ? SUCCESS : 0);
}


int				main(void)
{
	char		*line;
	int			fd;

	fd = open("normal.txt", O_RDONLY);

	while (get_next_line(fd, &line))
		printf("%s\n", line);
	return (0);
}
