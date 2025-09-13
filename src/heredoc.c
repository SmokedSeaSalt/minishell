#include "minishell.h"

void	here_expand_line_double_q(t_env *env, char **line, char **expandedline)
{
	(*line)++;
	while (**line && **line != '\"')
	{
		expand_line_char(line, expandedline);
		if (*expandedline == NULL)
			return ;
	}
	(*line)++;
}


char	*parse_word_heredoc(t_env *env, char **line)
{
	char	*word;

	//TODO DONT EXPAND ENV IF IN HEREDOC
	word = NULL;
	while (**line && !ft_isspace(**line) \
&& **line != '<' && **line != '>' && **line != '|')
	{
		if (**line == '\'')
			expand_line_single_q(line, &word);
		else if (**line == '\"')
			here_expand_line_double_q(env, line, &word);
		else
			expand_line_char(line, &word);
	}
	return (word);
}

int	itoa_heredoc(char *num, int count)
{
	if (count > 9999)
		return (0);
	num[0] = (count / 1000) + '0';
	num[1] = ((count / 100) % 10) + '0';
	num[2] = ((count / 10) % 10) + '0';
	num[3] = (count % 10) + '0';
	num[4] = 0;
	return (1);
}

char	*heredoc_filename(int count)
{
	int		i;
	int		j;
	char	num[5];
	char	*name;

	i = 0;
	if (!itoa_heredoc(num, count))
		return (NULL);
	name = ft_calloc(30, sizeof(char));
	if (!name)
		return (NULL);
	while (HEREDOC_PREFIX[i])
	{
		name[i] = HEREDOC_PREFIX[i];
		i++;
	}
	j = 0;
	while (j < 5)
	{
		name[i + j] = num[j];
		j++;
	}
	return (name);
}

int		heredoc_make_file(t_cmds *cmds, char **line, char **delim, int *fd, int *count)
{
	char	*name;

	*delim = parse_word_heredoc(cmds->info->head, line);
	name = heredoc_filename(*count);
	if (!name)
		return (1);
	if (cmds->infile)
	{
		if (!ft_strncmp(cmds->infile, "/tmp/.heredoc", 13))
			unlink(cmds->infile);
		free(cmds->infile);
	}
	cmds->infile = name;
	*fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	(*count)++;
	return (0);
}

void	heredoc_read(t_cmds *cmds, int fd, char *delim)
{
	extern int	g_signal_received;
	char		*heredoc_line;

	while (1)
	{
		heredoc_line = readline("mini heredoc> ");
		if (g_signal_received)
		{
			g_signal_received = 0;
			break ;
		}
		if (!heredoc_line)
			write(2, "Warning: heredoc delimited by end-of-file\n", 42);
		if (!heredoc_line || !ft_strncmp(heredoc_line, delim, \
ft_strlen(delim)) && !heredoc_line[ft_strlen(delim)])
			break ;
		write(fd, heredoc_line, ft_strlen(heredoc_line));
		write(fd, "\n", 1);
		free(heredoc_line);
	}
	free(heredoc_line);

}

void	handle_heredoc(t_cmds *cmds, t_env *env, char **line)
{
	static int	count = 0;
	char		*delim;
	int			fd;
	extern int	g_signal_received;

	// TODO HANDLE !NAME
	while (ft_isspace(**line))
		(*line)++;
	if (heredoc_make_file(cmds, line, &delim, &fd, &count))
		return ;
	set_signals_heredoc();
	rl_event_hook = heredoc_sig_hook;
	// function 2
	heredoc_read(cmds, fd, delim);
	// end function 2
	set_signals_default();
	rl_event_hook = NULL;
	//function 3 maybe
	free(delim);
	close(fd);
	if (cmds->permission_denied)
	{
		unlink(cmds->infile);
		free(cmds->infile);
		cmds->infile = NULL;
	}
	// end function 3
}