/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_mini.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:29:45 by fdreijer          #+#    #+#             */
/*   Updated: 2025/06/19 16:15:18 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MINI_H
# define LIBFT_MINI_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>

//built-in commands
int	ft_cd(char **input);
int	echo_mini(char **cmd);

//helper functions
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isquote(char c);
int		ft_isspace(char c);
int		ft_max(int a, int b);
int		ft_min(int a, int b);
char	**ft_split(char const *s, char c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strndup(char *str, int n);
int		is_valid_in_name(char c);
int		skip_to_quote(char **str);
char	*strjoin_char(char *s1, char *s2, char c);
char	*strjoin_path(char *s1, char *s2);
char	*strjoin_space(char *s1, char *s2);
char	*expand_env(char *str);


#endif
