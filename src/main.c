/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:38:08 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/22 16:57:20 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/get_next_line.h"

# define FILE_NAME "file3"
char **g_envp;

int main(int argc, char **argv, char **envp)
{
    int	f1;
    int	f2;
    int f3;
    int i;

    if (argc < 5)
        return (-1); 

    g_envp = envp;
    f1 = open(argv[1], O_RDONLY);
    f2 = open(argv[argc-1], O_CREAT | O_RDWR | O_TRUNC, 0644);
    f3 = open(FILE_NAME, O_CREAT | O_RDWR | O_TRUNC, 0644);

    if (f1 < 0 || f2 < 0)
        return (-1);
    i = 2; 
    pipex(f1, f2, argv, i);       // from file 1 to file 2
    while (i < argc - 1)
    {
        f3 = open(FILE_NAME, O_CREAT | O_RDWR | O_TRUNC, 0644);
        copy_file(f2, f3);
        f2 = open(argv[argc-1], O_CREAT | O_RDWR | O_TRUNC, 0644);
        pipex(f3, f2, argv, i) ;
        i += 2;
    }

    //pipe_alone(f3, f2, argv[6]);

    close(f1);
    close(f2);
    close(f3);
    
    // si le nombre d'argument est impair : 
    // pipex_alone(f3, f2) -> FIN 
    // ou pipex_alone(f2, f3) -> copie f3 dans f2 FIN  

    //unlink(FILE_NAME);
    
    /*
    while (i < argc - 1)
    {
        // seul condition si dernier file = file2 -> delete f3 ; si dernier file = file3 -> copie dans f2 puis delete f3
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
    */

    return (0);
}
