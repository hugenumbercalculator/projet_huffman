# projet_huffman
dépôt pour le projet de compression de fichiers

UTILISATION DU PROGRAMME :
- Veuillez entrer le texte à compresser dans le fichier "input.txt".
- Exécutez le programme.
- Constater la modification dans les fichiers .txt

FONCTIONNEMENT :
- Les fonctions read_txt() et write_binary() effectuent la translations de chaque caractère en suite binaire dans le fichier "binary.txt".
- La fonction occurrences() crée une liste chainée contenant l'intégralité des caractères et leurs occurrences dans le fichier .txt
- La fonction create_arbre_huffman() utilise des files pour la création de l'arbre
- La fonction write_dictionay() prend en argument l'arbre afin de génerer un fichier texte contenant tous les caractères ainsi que leur nouvelle suite binaire.