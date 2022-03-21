/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:38:08 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/21 01:18:47 by bperraud         ###   ########.fr       */
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

    if (argc < 5)
        return (-1); 
	
    g_envp = envp;
    f1 = open(argv[1], O_RDONLY);
    //f2 = open(argv[1], O_RDWR);
    f2 = open(argv[argc-1], O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (f1 < 0 || f2 < 0)
        return (-1);
    
    i = 2; // cmd 2 + 3
    //int f3 = open("file3", o_creat | o_rdwr);
    while (i < argc - 1)
    {
        printf("i : %i\n", i);
        pipex(f1, f2, argv, i);
        close(f1);      // logique 
        close(f2);


        f2 = open(argv[argc-1], O_RDWR);   // pas logique
        f1 = open("file3", O_CREAT | O_RDWR | O_TRUNC, 0644);  // nom de fichier qui n'existe pas déjà
        copy_file(f2, f1);  // copie f2 dans f1


        //close(f1);
        //close(f2);
        //f1 = open("file3", O_RDWR);
        //f2 = open(argv[argc-1], O_CREAT | O_RDWR | O_TRUNC, 0644); 

        i += 2;
    }
    
    //pipex(f1, 1);
    //pipex(1, f2);
    //copy_file(f2, f3);

    close(f1);
    close(f2);
    
    return (0);
}
