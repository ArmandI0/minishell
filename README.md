### ERREURS :
- Ctrl -C dans le Heredoc ne fonctionne pas ->FIXED
- Probleme avec les codes retour des signaux -> FIXED
- Find_command_path cherche dans le vrai envp (du coup les commande fonctionne meme avec unset PATH) -> a changer dans PARSING
- entre = $? seul ne fonctionne pas (retourne une erreur) -> NORMAL, c est juste qu on affiche pas la mm erreur que bash
- si la commande commence par un | bash retourne une erreur -> a changer dans PARSING

### LEAK :
- De fd open sur exit -> FIXED

### Differences avec bash 
- lors de ctrl + \ dans un heredoc, ne quitte pas (ok) mais affiche "^\"
- lors de ctrl + d dans un heredoc si on a déjà tapé plusieurs caracteres, va quitter apres plusieurs ctrl+d (bash ne quitte pas si des caracteres sont déjà tapés)
- dans bash, export sans argument affiche les variables d'env precedees de declare -x (et affiche toutes les variables d'env meme celles qui n'ont pas de valeur contrairement à cmd env)
