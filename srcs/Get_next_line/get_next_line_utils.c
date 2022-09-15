/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 10:32:44 by mriant            #+#    #+#             */
/*   Updated: 2022/09/15 15:59:26 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

char	*ft_strjoin_free(char *s, char const *s2)
{
	char	*result;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	result = ft_calloc(sizeof(char), (ft_strlen(s) + ft_strlen(s2) + 1));
	if (!result)
	{
		free (s);
		return (NULL);
	}
	while (s && s[i])
	{
		result[i] = s[i];
		i ++;
	}
	while (s2 && s2[j])
	{
		result[i] = s2[j];
		i ++;
		j ++;
	}
	free(s);
	return (result);
}

long int	ft_readline(int fd, char **buf, char **line)
{	
	long int	ret;

	if (!(*buf))
		return (-1);
	ret = 1;
	while (ret > 0 && !ft_strchr(line[0], '\n'))
	{
		ret = read (fd, buf[0], BUFFER_SIZE);
		if (ret >= 0)
		{
			buf[0][ret] = '\0';
			line[0] = ft_strjoin_free(line[0], buf[0]);
		}
	}
	return (ret);
}

void	ft_setline(char **line, char **tail)
{
	char	*endline;

	endline = ft_strchr(line[0], '\n');
	free(*tail);
	if (endline && *(endline + 1) != '\0')
	{
		*tail = ft_strdup(endline + 1);
		endline[1] = '\0';
	}
	else
		*tail = NULL;
}

int	ft_check_fd(int fd, char *tail[256])
{
	int	i;

	if (fd == -1)
	{
		i = 0;
		while (i < 256)
		{
			free(tail[i]);
			i++;
		}
	}
	if (fd < 0 || fd >= 255 || BUFFER_SIZE <= 0)
		return (1);
	return (0);
}

void	ft_clean_gnl(char *buf, char *tail, char *line)
{
	free(buf);
	free(tail);
	free(line);
}
