/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:15:37 by fdreijer          #+#    #+#             */
/*   Updated: 2025/09/09 13:12:41 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft_mini.h"
# include "mini_structs.h"
# include <signal.h>
# define HEREDOC_PREFIX "/tmp/.heredoc_"

t_cmds	*cmd_last(t_cmds *head);
t_cmds	*cmd_new_node(void);
void	cmd_add_back(t_cmds **head, t_cmds *newnode);
t_cmds	*cmd_first(t_cmds *tail);
void	make_cmds(t_cmds *cmds, t_env *env, char *line);
void	find_paths(t_cmds *cmds, t_env *env);
void	execute_cmd(t_cmds *cmds, t_env *env);
int		error_parse_line(char *line, int i, int wordbefore, int openquote);

void	parent_sigint_handler(int sig);
void	heredoc_sigint_handler(int sig);
int		set_signals_default(void);
int		set_child_signals(void);
int		set_signals_ignore(void);
int		set_signals_heredoc(void);
int		heredoc_sig_hook(void);

void	fix_empty_cmds(t_cmds *cmds);
void	free_cmds_node(t_cmds *node);
void	free_cmds(t_cmds *node);

void	expand_line_char(char **line, char **expandedline);
void	expand_line_dollar(t_cmds *cmds, t_env *env, char **line, char **expandedline);
void	expand_line_double_q(t_cmds *cmds, t_env *env, char **line, char **expandedline);
void	expand_line_single_q(char **line, char **expandedline);
void	expand_line_space(t_cmds *cmds, char **line, char **expandedline);

void	handle_infile(t_cmds *cmds, t_env *env, char **line);
void	handle_outfile(t_cmds *cmds, t_env *env, char **line);
void	handle_pipe(t_cmds **cmds, t_info *info, char **line);

void	handle_heredoc(t_cmds *cmds, t_env *env, char **line);
int		isbuiltin(t_cmds *cmds);

int		exec_pipe_single(t_cmds *cmds, t_env *env, int fd_in, int fd_out);
char	**make_envp(t_cmds *cmds, t_env *env);
char	**make_args(t_cmds *cmds);
void	check_access(t_cmds *cmds);
void	exec_builtin(t_cmds *cmds);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h> //to use size_t

typedef struct s_list
{
	char			*line;
	int				fd;
	int				hasnl;
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;

//get next line
char	*free_all(t_list **head);
char	*get_next_line(int fd);
char	*return_line(t_list **head, int fd);
void	delnode(t_list *node, t_list **head);
int		fill_node(t_list *head, int fd, char *buffer);

//utils
void	*gnl_calloc(size_t nmemb, size_t size);
t_list	*get_fd_node(t_list *head, int fd);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
ssize_t	charpos(char *s, char c);
int		create_node(t_list **head, char *buffer, int fd);


#endif
