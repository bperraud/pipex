/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:38:08 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/20 23:28:59 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/get_next_line.h"

char **g_envp;

int main(int argc, char **argv, char **envp)
{
    int	f1;
    int	f2;
    int i;

	g_envp = envp;

    if (argc < 5)
        return (-1);
    
    f1 = open(argv[1], O_RDONLY);
    f2 = open(argv[argc-1], O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (f1 < 0 || f2 < 0)
        return (-1);
    i = 1;
    

    //while (i++ < argc-3)
    //{
    //    //printf("i : %i", i);
    //    pipex(f1, f2, argv, i);
    //    close(f1);      // sur ? 
    //    //f1 = f2;        // pas fermé ? 
    //    f1 = open("file3", O_CREAT | O_RDWR);       // nom de fichier qui n'existe pas déjà
    //    copy_file(f2, f1);  // copie f2 dans f1
    //}

    //pipex(f1, 1);
    //pipex(1, f2);
   
    close(f1);
    close(f2);
    
    return (0);
}
