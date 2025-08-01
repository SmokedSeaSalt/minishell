/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_mini.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:29:45 by fdreijer          #+#    #+#             */
/*   Updated: 2025/07/28 09:54:19 by fdreijer         ###   ########.fr       */
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
# include <errno.h>

#define FORBIDDENCHARS "\\;\n"

#define TRUNCATE 0
#define APPEND 1

#define FALSE 0
#define TRUE 1

typedef	struct s_env
{
	char	*v_name;
	char	*v_val;
	struct s_env	*next;
}	t_env;

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
char	*expand_env(t_env *head, char *str);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_realloc(void *oldptr, int oldsize, int newsize);
int		charinstr(char c, char *str);
t_env	*init_env(char **envp);
char	*return_env(t_env *head, char *str);


#endif
