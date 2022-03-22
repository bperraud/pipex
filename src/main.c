/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:38:08 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/23 00:11:12 by bperraud         ###   ########.fr       */
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

    if (argc < 5)
        return (-1); 

    g_envp = envp;
    f1 = open(argv[1], O_RDONLY);
    f2 = open(argv[argc-1], O_CREAT | O_RDWR | O_TRUNC, 0644);

    if (f1 < 0 || f2 < 0)
        return (-1);
    i = 2; 
    pipex(f1, f2, argv, i);       // from file 1 to file 2
    while (i < argc - 3)
    {
        i += 2;
        f3 = open(FILE_NAME, O_CREAT | O_RDWR | O_TRUNC, 0644);
        copy_file(f2, f3);
        f2 = open(argv[argc-1], O_CREAT | O_RDWR | O_TRUNC, 0644);
        pipex(f3, f2, argv, i) ;
    }

    //pipe_alone(f3, f2, argv[6]);

    close(f1);
    close(f2);
    close(f3);
    
    // si le nombre d'argument est impair : 
    // pipex_alone(f3, f2) -> FIN 
    // ou pipex_alone(f2, f3) -> copie f3 dans f2 FIN  

    //unlink(FILE_NAME);
    
    

    return (0);
}
