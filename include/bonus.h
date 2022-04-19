/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 04:02:22 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/30 04:02:22 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# define FILE_NAME "temp/file"

void	multiple_cmd(int fd[2], int argc, char **argv, char **envp);
int		limiter(char *limiter);
//void	pipex_alone(char *arg, char**envp);
void	pipex_alone(int input_file, int output_file, char *arg, char**envp);

#endif
