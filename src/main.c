/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:39:49 by aranger           #+#    #+#             */
/*   Updated: 2024/02/12 15:05:23 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
    argc++;
	argv++;
	printf("Début du programme.\n");

    // Nom du fichier à afficher
    char *filename = "mon_fichier.txt";
	char *fdf = "sdfsdfg";
	char *filename2 = "README.md";
    // Tableau d'arguments pour la commande "cat" avec le nom du fichier
    char *args[] = {"cat", filename, fdf, filename2, NULL};

    // Exécute la commande "cat" avec le chemin d'accès automatiquement recherché.
    //execvp("cat", args);

	execve("/usr/bin/cat", args, envp);

    // Si execvp échoue, le code ci-dessous sera exécuté.
    perror("execvp");
    return 1;
}