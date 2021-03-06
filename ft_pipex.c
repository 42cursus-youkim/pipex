/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkim <youkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 19:34:22 by youkim            #+#    #+#             */
/*   Updated: 2021/08/11 19:34:22 by youkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"
#include <stdio.h>

void	ft_pipein(t_info *info, int pipefd[2])
{
	close(pipefd[PIPE_READ]);
	if (dup2(pipefd[PIPE_WRITE], STDOUT_FILENO) == ERROR)
		ft_error("while connecting pipe write END with STDOUT_FILENO");
	if (dup2(info->infd, STDIN_FILENO) == ERROR)
		ft_error("while  connecting infile fd with STDIN_FILENO");
	ft_exec(info, 0);
	close(info->infd);
	close(pipefd[PIPE_WRITE]);
}

void	ft_pipeout(t_info *info, int pipefd[2])
{
	close(pipefd[PIPE_WRITE]);
	dup2(info->outfd, STDOUT_FILENO);
	dup2(pipefd[PIPE_READ], STDIN_FILENO);
	ft_exec(info, 1);
	close(info->outfd);
	close(pipefd[PIPE_READ]);
	wait(CHILD);
}

void	ft_pipex(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	t_info	info;

	if (argc != 5)
		ft_error("to use: ./pipex inflie cmd1 cmd2 outfile");
	info.envp = envp;
	info.infd = open(argv[1], O_RDONLY);
	if (info.infd == ERROR)
		ft_error("while opening input file");
	info.outfd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (info.outfd == ERROR)
		ft_error("while opening output file");
	if (pipe(pipefd) == ERROR)
		ft_error("while creating pipe");
	info.pid = fork();
	if (info.pid == ERROR)
		ft_error("while forking process");
	info.argslst[0] = ft_qsplit(argv[2], ' ');
	info.argslst[1] = ft_qsplit(argv[3], ' ');
	if (info.pid == CHILD)
		ft_pipein(&info, pipefd);
	else
		ft_pipeout(&info, pipefd);
}
