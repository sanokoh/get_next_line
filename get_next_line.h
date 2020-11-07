/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksano <ksano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 17:18:40 by ksano             #+#    #+#             */
/*   Updated: 2020/11/07 16:37:38 by ksano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

# define FD_LIMIT 256
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# define ERROR -1
# define SUCCESS 1

char		*ft_strdup(char *s1);
size_t		ft_strlen(const char *s);
int			ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_strjoin(char const *s1, char const *s2);
int			get_next_line(int fd, char **line);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strchr(const char *s, int c);

#endif
