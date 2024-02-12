# Authorized External Functions in C
## readline
librairy needed : 
       #include <stdio.h>
       #include <readline/readline.h>
       #include <readline/history.h>
en gros c'est un GNL ouù tu peux envoyer le prompt à afficher à la fonction (genre "here_doc>"). nécessite la lib readline installée et d'ajouter -lreadline lors de la compil. possibilité de naviguer dans l'historique grace aux fleches. 

## rl_clear_history
librairy needed : readline
permet de supprimer l'historique des commandes entrées dans readline

## rl_on_new_line
librairy needed : readline
notifie a readline le passage a une nouvelle ligne
--- a quoi ça sert ??

## rl_replace_line
librairy needed : readline
permet de remplacer ce qui est saisi au clavier (par exemple pour l'auto complétion)

## rl_redisplay
librairy needed : readline
forcer l'affichage de l'éditeur de ligne après que le contenu de la ligne a été modifié d'une manière qui nécessite une mise à jour de l'affichage.

## add_history
librairy needed : readline
ajouter des entrées dans l'historique

## printf, malloc, free, write, access, open, read close, fork, wait, waitpid, pipe, dup, dup2, execve, perror
On connaît

## wait3, wait4
librairy needed : 
       #include <sys/types.h>
       #include <sys/time.h>
       #include <sys/resource.h>
       #include <sys/wait.h>
pid_t wait3(int *status, int options,struct rusage *rusage);

pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);   

similaires  à  waitpid, mais  retournent  également  des  informations  sur  l’utilisation  des ressources par le fils dans la structure pointée par "rusage".    

## signal
librairy needed : 
       #include <signal.h>
permet de lancer une fonction lorsque un signal spécifié est reçu exemple  : signal(SIGINT, function); -> lance function lorsque ctrl+c, SIGQUIT c'est pour ctrl+\ (produit un coredump pour le deboggage)

## sigaction
idem que signal mais alternative plus robuste. prend 3 parametres dont une struct sigaction

## sigemptyset
initialiser un ensemble de signaux vides. prend en param un pointeur sur variable sigset_t

## sigaddset
ajouter un signal spécifique à un ensemble de signaux. prend en param un pointeur sur variable sigset_t + un signal

## kill
librairy needed : 
       #include <signal.h>
       #include <sys/types.h>
envoyer un signal à un processus spécifié par son PID       

## exit
terminer l'exécution du programme en cours et pour retourner un code de sortie à l'environnement d'exécution.

## getcwd
librairy needed : 
       #include <stdio.h>
       #include <unistd.h>
       #include <limits.h>
obtenir le répertoire de travail actuel du processus.

## chdir
librairy needed : 
       #include <unistd.h>
permet de changer le répertoire de travail courant du processus

## stat
librairy needed : 
       #include <sys/stat.h>
obtenir des informations sur un fichier, telles que sa taille, ses autorisations, son type, etc dans une structure struct stat nomdefichier

## lstat
idem que stat mais ne suit pas liens symboliques

## fstat
idem que stat mais sur un fd ouvert

## unlink
librairy needed : 
       #include <unistd.h>
Cette fonction est utilisée pour supprimer (effacer) un fichier spécifié par son nom de chemin. détruit un nom dans le système de fichiers. Si ce nom était le dernier lien sur un fichier, et si aucun processus n'a ouvert ce fichier, ce dernier est effacé, et l'espace qu'il utilisait est rendu disponible. 

## opendir
## readdir
## closedir
## strerror
## isatty
## ttyname
## ttyslot
## ioctl
## getenv
## tcsetattr
## tcgetattr
## tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs