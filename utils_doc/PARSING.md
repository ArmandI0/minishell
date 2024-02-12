# Notes pour le parsing :
- Si le premiers arguments n'est pas une commande valide retourner une erreur

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

# Les differents elements :

### "<" et ">"
	
	< : redirige l'argument suivant sur la stdin
	> : redirige stdout dans l'argument suivant
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

### echo :

	echo >> envoi l'argument qui le precede dans stdout
	echo -n >> n'affiche pas la sortie de echo

##### Cas particuliers :
	echo sans arguments >> Doit renvoyer \n
____

## cd :	
	cd [path] >> change de dossier


##### Cas particuliers :
	cd sans arguments doit renvoyer retourner au home
##### Gestion d'erreur :
	si path non-valide >> cd: no such file or directory: [path]


