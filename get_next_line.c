/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuyamatakahito <okuyamatakahito@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 23:44:14 by okuyamataka       #+#    #+#             */
/*   Updated: 2023/02/21 23:15:37 by okuyamataka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*backup_after_linebreak(char *backup)
{
	char	*str;
	size_t	start;
	size_t	end;
	size_t	size;
	size_t	i;

	if (!backup)
		return (NULL);
	start = 0;
	while (backup[start] != '\n' && backup[start] != '\0')
		start++;
	end = start;
	while (backup[end] != '\0')
		end++;
	size = end - start;
	str = (char *)malloc(size * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (size--)
		str[i++] = backup[++start];
	free(backup);
	return (str);
}

static char	*make_line(char *backup)
{
	char	*str;
	int		trim_len;
	int		i;

	trim_len = 0;
	while (backup[trim_len] != '\n' && backup[trim_len] != '\0')
		trim_len++;
	if (backup[trim_len] == '\n')
		trim_len++;
	str = (char *)malloc((trim_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < trim_len){
		str[i] = backup[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*buf;
	char		*line;
	ssize_t		read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = NULL;
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	read_bytes = 1;
	while (!(ft_strchr(backup, '\n')))
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buf);
			return (NULL);	
		}
		buf[read_bytes] = '\0';
		backup = ft_strjoin_with_free(backup, buf); //結合前のbackupってfree必要じゃない？
		if (!read_bytes)
		{
			if (ft_strlen(backup))
				break ;
			else
			{
				free(buf);
				free(backup);
				backup = NULL;
				return (NULL);
			}
		}
	}
	free(buf);
	line = make_line(backup);
	backup = backup_after_linebreak(backup);
	return (line);
}

// #include <stdio.h>
// #include <fcntl.h>

// int main()
// {
// 	char	*str;
// 	int i;
// 	int fd;

// 	// fd = open("test.txt", O_RDONLY);
// 	// fd = open("nl.txt", O_RDONLY);
// 	// fd = open("41_no_nl", O_RDONLY);
// 	// fd = open("41_with_nl", O_RDONLY);
// 	// fd = open("42_no_nl", O_RDONLY);
// 	// fd = open("empty", O_RDONLY);
// 	// fd = open("big_line_no_nl", O_RDONLY);
// 	fd = open("multiple_nlx5", O_RDONLY);
// 	i = 5;
// 	while(i--)
// 	{
// 		str = get_next_line(fd);
// 		printf("buf=%s", str);
// 		free(str);
// 	}
// 	// printf("buf=%s", get_next_line(fd2));
// 	// printf("buf=%s", get_next_line(fd3));
// 	// printf("buf=%s", get_next_line(fd4));
//     return 0;
// }

// // __attribute__((destructor))
// // static void destructor() {
// //     system("leaks -q a.out");
// // }

// char	*ft_strjoin_with_free(char *s1, char const *s2)
// {
// 	char	*str;
// 	size_t	s1_len;
// 	size_t	s2_len;
// 	size_t	i;

// 	s1_len = 0;
// 	s2_len = 0;
// 	if (!s1 && !s2)
// 		return (NULL);
// 	if (s1)
// 		s1_len = ft_strlen(s1);
// 	if (s2)
// 		s2_len = ft_strlen(s2);
// 	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (s1_len--)
// 	{
// 		str[i] = s1[i];
// 		i++;
// 	}
// 	while (s2_len--)
// 	{
// 		str[i] = *s2++;
// 		i++;
// 	}
// 	str[i] = '\0';
// 	free(s1);
// 	return (str);
// }

// char	*ft_strchr(const char *s, int c)
// {
// 	const char	*str;

// 	if (!s)
// 		return (NULL);
// 	str = (char *)s;
// 	while (*str != '\0')
// 	{
// 		if (*str == (char)c)
// 			return ((char *)str);
// 		str++;
// 	}
// 	if (c == '\0')
// 		return ((char *)str);
// 	return (NULL);
// }

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i] != '\0')
// 		i++;
// 	return (i);
// }
