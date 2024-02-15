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
librairy needed : 
       #include <dirent.h>
ouvrir un répertoire spécifié par son chemin d'accès et pour obtenir un pointeur vers sa structure de répertoire
## readdir
librairy needed : 
       #include <dirent.h>
lire les entrées d'un répertoire ouvert avec opendir(). Elle retourne un pointeur vers une "struct dirent" qui représente la prochaine entrée dans le répertoire. Cette structure contient des informations telles que le nom de l'entrée et son type (fichier régulier, répertoire, etc.).  A chaque appel de la fonction readdir(), le pointeur de position dans le répertoire avance vers le fichier ou le dossier suivant. Renvoie NULL si a terminé.
struct dirent :
- d_ino : numero d'inode
- d_name : nom
- d_type : type (DT_REG, DT_DIR ou DT_LINK par ex)
## closedir
librairy needed : 
       #include <dirent.h>
fermer le repertoire ouvert avec opendir
## strerror
prend en parametre errno et retourne une chaine de caracetere détaillant l'erreur (mais ne l'affiche pas).
## isatty
librairy needed : 
       #include <unistd.h>
utilisée pour vérifier si un descripteur de fichier donné correspond à un terminal interactif (TTY) ou non. Elle prend en paramètre un descripteur de fichier (généralement le résultat d'une fonction comme open() ou fileno()) et renvoie une valeur différente de zéro si le descripteur de fichier correspond à un terminal, ou zéro sinon.
## ttyname
librairy needed : 
       #include <unistd.h>
utilisée pour obtenir le nom du terminal associé à un descripteur de fichier de type terminal (TTY). Elle prend en paramètre un descripteur de fichier de type terminal et retourne un pointeur vers une chaîne de caractères contenant le nom du terminal associé à ce descripteur, ou NULL en cas d'erreur.
## ttyslot
librairy needed : 
       #include <unistd.h>
utilisée pour obtenir le numéro de l'entrée dans la table des terminaux (TTY) pour le terminal associé à l'utilisateur actuel dans le fichier /etc/ttys       
## ioctl
librairy needed : 
       #include <ioctl.h>
 fonction système qui est utilisée pour effectuer diverses opérations de contrôle sur des périphériques, des fichiers ou des sockets.        
## getenv
La fonction getenv() prend en paramètre le nom de la variable d'environnement que vous souhaitez récupérer et renvoie un pointeur vers la chaîne de caractères correspondant à la valeur de cette variable
## tcsetattr
utilisée pour définir les attributs du terminal. Elle permet de modifier les paramètres de contrôle d'un terminal, tels que la vitesse de transmission (baud rate), les bits de données, les bits de stop, le contrôle de flux, etc.
## tcgetattr
La fonction tcgetattr() en C est utilisée pour obtenir les attributs du terminal (c'est-à-dire les paramètres de contrôle du terminal) et les stocker dans une structure de données spécifique, généralement struct termios.
## tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
librairy needed : 
       #include <ncurses.h>
       CC avec -lncurses
    tgetent() : Cette fonction est utilisée pour initialiser une base de données terminfo et récupérer les informations de configuration pour un terminal spécifique. Elle prend en argument un pointeur vers une structure de type termcap, un nom de terminal et renvoie 1 si la configuration a été trouvée, sinon 0.

    tgetflag() : Cette fonction est utilisée pour extraire des informations de configuration du terminal qui sont des drapeaux (booléens). Elle prend en argument une chaîne de caractères qui représente le nom du drapeau et renvoie 1 si le drapeau est défini, sinon 0.

    tgetnum() : Cette fonction est utilisée pour extraire des informations de configuration du terminal qui sont des nombres. Elle prend en argument une chaîne de caractères qui représente le nom du nombre et renvoie la valeur numérique associée.

    tgetstr() : Cette fonction est utilisée pour extraire des informations de configuration du terminal qui sont des chaînes de caractères. Elle prend en argument une chaîne de caractères qui représente le nom de la chaîne et renvoie un pointeur vers la chaîne associée.

    tgoto() : Cette fonction est utilisée pour générer une séquence de contrôle pour déplacer le curseur du terminal à une position spécifiée. Elle prend en argument une séquence de contrôle de déplacement de curseur (souvent récupérée à l'aide de tgetstr()), une colonne et une ligne, et renvoie la séquence de contrôle résultante.

    tputs() : Cette fonction est utilisée pour envoyer une séquence de contrôle au terminal. Elle prend en argument une séquence de contrôle de terminal (généralement récupérée à l'aide de tgetstr()) et envoie cette séquence au terminal.