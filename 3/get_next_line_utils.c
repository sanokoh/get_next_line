/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksano <ksano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 10:00:27 by ksano             #+#    #+#             */
/*   Updated: 2020/11/07 16:10:48 by ksano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char				*ft_strchr(const char *s, int c)
{
	int				i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char				*ft_strdup(char *s1)
{
	int				len;
	char			*dest;

	len = ft_strlen(s1);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s1, len + 1);
	return (dest);
}

char				*ft_strjoin(char const *s1, char const *s2)
{
	char			*res;
	unsigned int	len1;
	unsigned int	len2;

	if (!s1)
		return (NULL);
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	res = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, (char *)s1, len1 + 1);
	ft_strlcat(res, (char *)s2, len1 + len2 + 1);
	return (res);
}

int					ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t			i;

	if (!dst || !src)
		return (0);
	i = 0;
	if (dstsize > 0)
	{
		while (i < (dstsize - 1) && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	i = 0;
	while (src[i])
		i++;
	return (i);
}

size_t				ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t			i;
	size_t			j;
	size_t			d_len;
	size_t			s_len;

	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	i = 0;
	j = d_len;
	if (d_len < dstsize - 1 && dstsize > 0)
	{
		while (src[i] && d_len + i < dstsize - 1)
		{
			dst[j++] = src[i++];
		}
		dst[j] = '\0';
	}
	if (d_len >= dstsize)
		d_len = dstsize;
	return (d_len + s_len);
}
