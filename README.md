COMMANDE POUR GIT : 

Gestion des branche 🌲:
- pour add une branche : `git branch "nom"`
- pour voir dans quelle branche : `git status` ou `git branch`
- pour changer de branche : `git checkout "nom de la branche"`

Pour push ➡️:
- `git add .`
- `git commit -m "msg"`
- `git push origin "nom de la branche"`

TESTS :

- `set -e`
- `exemple : set -e ["$(./minishell 'echo hello')" = hello]`
- `set -e indique au shell de quitter immédiatement si une commande échoue.`
- `Si une commande dans le script retourne une valeur de sortie non nulle (indiquant une erreur), le script s'arrête direct au lieu de continuer à exécuter les commandes suivantes.`

- `set -ex`
- pour aller plus loin, on peut utiliser -x pour afficher `chaque commande exécutée dans le terminal` avec ses arguments avant son exécution
- exemple : `set -ex`

- if [ "$(./minishell 'echo hello')" = "hello" ]; then
    echo "Succes : le minishell renvoi bien 'hello'"
else
    echo "Echec : pas d'envoi de 'hello'"
fi

- check : env

set -ex
if [ "$(./minishell 'env' | grep 'PATH')" != "" ]; then
    echo "Success: PATH variable is found in env output"
else
    echo "Failure: PATH variable is not found in env output"
fi

- check pwd

set -ex
mkdir -p /tmp/minishell_test
cd /tmp/minishell_test
if [ "$(./minishell 'pwd')" = "/tmp/minishell_test" ]; then
    echo "Success: pwd output matches changed directory"
else
    echo "Failure: pwd output does not match changed directory"
fi
cd - # Go back to previous directory
rm -r /tmp/minishell_test


- check export

set -ex
export TEST_VARIABLE="test_value"
if [ "$(./minishell 'env' | grep 'TEST_VARIABLE=test_value')" != "" ]; then
    echo "Success: Custom variable TEST_VARIABLE is found in env output"
else
    echo "Failure: Custom variable TEST_VARIABLE is not found in env output"
fi



VALGRIND :

- Dans le sujet, on nous dit que `La fonction readline() peut cause des fuites de memoire. Vous n'avez pas a les gerer'
- Je sais pas si c'est autorise, mais j'ai trouve une combine pour virer l'affichage des leaks de readline()

- `1. Creer un fichier valgrind.supp` : 
	A l'interieur on va expliquer a Valgrind qu'on veut pas gerer readline :
	{
   		readline_memory_leak
   		Memcheck:Leak
   		fun:readline
   		fun:_rl_init_terminal_io
   		fun:rl_initialize
   		fun:xmalloc
	} // copie / colle ca dans le fichier valgrind.supp 

- `2. Gerer valgrind par le Makefile` :
	Je sais pas pourquoi on a pas fait ca avant, mais on peut build direct avec les
	flag de Valgrind. Refere toi a mon Makefile et utilise 'make valgrind' pour build ton code
	et gerer des leak plus facilement
	
	Grace a `--suppressions=$(VALGRIND_SUPP)`, on affiche plus les leaks de readline et c'est plus lisible
	pour gerer ses leaks, super pratique 
	(J'attend de voir si yen a un qui vient me mp discord pour me dire 'tu peux pas faire ca')
	J'ajouterais des flags au fur et a mesure pour avoir un truc bien propre

.GITIGNORE :

- super pratique pour eviter de push les fichiers qui nous interessent pas
- il suffit de creer un fichier `.gitignore` et de creer une liste
- les `wildcards` fonctionnent 
- exemples de truc a mettre dans ton .gitignore :
*.out
*.swp
*.o
*.a
*.json

