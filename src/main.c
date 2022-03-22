/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:38:08 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/22 03:26:11 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/get_next_line.h"

char **g_envp;

int main(int argc, char **argv, char **envp)
{
    int	f1;
    int	f2;
    int f3;
    int i;

    //if (argc < 5)
        //return (-1); 

    g_envp = envp;
    
    f1 = open(argv[1], O_RDONLY);
    f2 = open(argv[argc-1], O_CREAT | O_RDWR | O_TRUNC, 0644);
    f3 = open("file3", O_CREAT | O_RDWR | O_TRUNC, 0644);

    if (f1 < 0 || f2 < 0)
        return (-1);
    i = 2; 

    pipex(f1, f2, argv, i);       // from file 1 to file 2
    pipex(f2, f3, argv, i+2);       // from file 2 to file 2
    close(f2);
    close(f3);
    /*
    close(f2);
    f2 = open(argv[argc-1], O_CREAT | O_RDWR | O_TRUNC, 0644);
    */

	pipe_alone(f3, f2, "wc -m");

    close(f1);
    close(f2);
    close(f3);

    //dup2(STDIN_FILENO, f1);
    //dup2(STDOUT_FILENO, f2);

     // échange continu entre f2 et f3

    //pipex(f1, 1, argv, i, argc);       // from file 1 to file 2
    //pipex(1, f2, argv, i+2, argc);       // from file 2 to file 2

    /*
    dup2(f1, STDIN_FILENO);         // STDIN devient f1 
    pipex2(argv[i], 0);
    dup2(f2, STDOUT_FILENO);

    i + 1;

    char **paths = parsing(g_envp);				// all path
	char ** cmd_arg = ft_split(argv[i], ' ');			// cmd 1 args { "ls", "-la", NULL }	
    exec(paths, cmd_arg);
    */
    
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
