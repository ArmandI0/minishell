# Lexer

- Prendre tous les elements et split selon ' ' dans un ** et continuer jusqu'a operateur ou \0;


# Notes pour le parsing :
- Prendre la commande jusqu'a un '\0' ou un operateur

Synthaxe d'entree

	cmd [options1] [options2] [arguments1] [arguments2];

	exemple d'execution : 
	
	cat -t -e [arguments1] [arguments2]
	exec sur arg1
	exec sur arg2

	cat -t -e [arguments1] [bad arguments] [arguments2]
	exec arg1
	return error
	exec arg2

# Les differents operateurs :

- '>'
- '<'
- '>>'
- '|'
- ""
- ''
- $

### Opérateurs de redirection : 

	> : Redirige la sortie standard vers un fichier, écrasant le contenu existant.
	>> : Redirige la sortie standard vers un fichier, en ajoutant à la fin du fichier.
	< : Redirige l'entrée standard depuis un fichier.
#
### " " et ' ':
	echo salut\nds :
	salutnds

	echo 'salut\nds'
	salut
	ds

	echo "salut\nds" : 
	salut
	ds


# Les fonctions :

### pwd [with no options]:
	affiche dans la sortie standard le chemin complet du repertoire actuel.
	nb: la racine de l'ordinateur s'écrit "/" (il n'est donc pas possible de remonter plus haut)

##### Caractéristiques de la fonction
	- une variable environnement "PWD" contenant le chemin vers le répertoire actuel et qui sera mis à jour à chaque utilisation de "cd" ou déplacement vers un autre dossier
	- une scde variable environnement "OLDPWD"  contenant le dernier répertoire visité -- a voir si néc
	- utilisation de la fonction en C getcwd qui récupere le chemin du repertoire de travail courant

### exit [with no options]:
	terminer l'exécution d'un script Bash ou d'un shell interactif. 

##### Caractéristiques de la fonction
	- peut prendre une argument ex : exit [n]
	- si plus d'un argument donné : affiche exit: too many arguments
	- si reçoit un argument, sort avec ce nombre comme code d'erreur. sinon avec 0
	- Si une valeur en dehors de 0-255 est spécifiée, elle sera automatiquement réduite à un entier de 8 bits. (unsigned char)

### export [with no options]:
	utilisée pour rendre une variable accessible à tous les processus enfants d'un shell. Elle est principalement utilisée pour définir des variables d'environnement.
	exemple: si on déclare une variable env avec export VARIABLE=123 et qu'on créér un processus bash enfant, la variable sera accessible alors qu'avec une déclaration simple sans export, elle ne sera accessible que dans le parent (non transmise à l'environnement des processus fils);

##### Caractéristiques de la fonction
	- nécessite acces à la variable envp
	- nécessite d'ajouter une entrée à envp
	- peut prendre en parametre une variable prealablement déclarée ex : export MAVARIABLE 
	ou bien exporter et déclarer sur la meme ligne 
	ex : export MAVARIABLE2=123
	- sans arguments : affichera la liste des variables d'environnement actuellement définies dans le shell avec le préfixe declare -x DANS L ORDRE ALPHABETIQUE
	ex : export
			declare -x VARIABLE1="value1"
			declare -x VARIABLE2="value2"


##### Cas particuliers : 

### echo :

	echo >> envoi l'argument qui le precede dans stdout
	echo -n >> n'affiche pas la sortie de echo

##### Cas particuliers :
	echo sans arguments >> Doit renvoyer \n
____

### cd :	
	cd [path] >> change de dossier


##### Cas particuliers :
	cd sans arguments doit renvoyer retourner au home
##### Gestion d'erreur :
	si path non-valide >> cd: no such file or directory: [path]


