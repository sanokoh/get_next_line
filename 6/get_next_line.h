/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksano <ksano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 17:18:40 by ksano             #+#    #+#             */
/*   Updated: 2020/11/21 21:50:12 by ksano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

typedef struct		s_gnl
{
	int				fd;
	char			*save;
	struct s_gnl	*next;
}					t_gnl;

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>

# define FD_LIMIT 256
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif
# define ERROR -1
# define ALL_DONE 0
# define SUCCESS 1

char		*ft_strdup(char *s1);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlen(const char *s);
int			get_next_line(int fd, char **line);

#endif
