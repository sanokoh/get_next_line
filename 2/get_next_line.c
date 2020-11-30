/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksano <ksano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 11:15:04 by ksano             #+#    #+#             */
/*   Updated: 2020/11/21 15:32:55 by ksano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void		freelist(t_gnl *head)
{
	t_gnl	*tmp;

	while (head != NULL)
	{
		tmp = head->next;
		free(head->save);
		free(head);
		head = tmp;
	}
}

t_gnl			*add_list(int fd)
{
	t_gnl		*new;
	int			i;

	if (!(new = (t_gnl *)malloc(sizeof(t_gnl))))
		return (NULL);
	new->fd = fd;
	if(!(new->save = (char *)malloc((sizeof(char) * BUFFER_SIZE) + 1)))
		return (NULL);
	i = 0;
	while (i < BUFFER_SIZE)
		new->save[i++] = '\0';
	new->save[BUFFER_SIZE] = '\0';
	new->next = NULL;
	return (new);
}

char			*check_save(char **save, char **line)
{
	char		*nl;

	nl = NULL;
	if (*save)
	{
		if ((nl = ft_strchr(*save, '\n')))
		{
			*nl = '\0';
			if (!(*line = ft_strdup(*save)))
				return (NULL);
			nl++;
			ft_strlcpy(*save, nl, ft_strlen(nl) + 1);
		}
		else
		{
			if (!(*line = ft_strdup(*save)))
				return (NULL);
			while (*save)
				*save++ = '\0';
		}
	}
	else
	{
		*line = ft_strdup("");
	}
	return (nl);
}

int				get_line(int fd, char **line, char **save)
{
	char		buf[BUFFER_SIZE + 1];
	int			rc;
	char		*nl;
	char		*tmp;

	nl = NULL;
	nl = check_save(save, line);
	while (!nl && (rc = read(fd, buf, BUFFER_SIZE)))
	{
		buf[rc] = '\0';
		if ((nl = ft_strchr(buf, '\n')))
		{
			*nl = '\0';
			nl++;
			// if (!(*save = ft_strdup(nl)))
			// 	return (ERROR);
			ft_strlcpy(*save, nl, BUFFER_SIZE + 1);
		}
		tmp = *line;
		if (!(*line = ft_strjoin(tmp, buf)))
			return (ERROR);
		free(tmp);
	}
	return ((ft_strlen(*save) || ft_strlen(*line)) ? SUCCESS : ALL_DONE);
}

int				get_next_line(int fd, char **line)
{
	static t_gnl	*head;
	t_gnl			*tmp;
	int				ret;

	if (fd < 0 || line == 0 || BUFFER_SIZE <= 0)
		return (ERROR);
	if (head == NULL)
		if (!(head = add_list(fd)))
			return (ERROR);
	tmp = head;
	while (tmp->fd != fd)
	{
		if (tmp->next == NULL)
			tmp->next = add_list(fd);
		tmp = tmp->next;
	}
	ret = get_line(fd, line, &tmp->save);
	if (ret == 0)
		freelist(head);
	return (ret);
}

