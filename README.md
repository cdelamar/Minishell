COMMANDE POUR GIT : 

Gestion des branche 🌲:
- pour add une branche : `git branch "nom"`
- pour voir dans quelle branche : `git status` ou `git branch`
- pour changer de branche : `git checkout "nom de la branche"`

Pour push ➡️:
- `git add .`
- `git commit -m "msg"`
- `git push origin "nom de la branche"`

Tests :
- `set -e`
- `exemple : set -e ["$(./minishell 'echo hello`)" = hello]'
- `set -e indique au shell de quitter immédiatement si une commande échoue.'
- 'Si une commande dans le script retourne une valeur de sortie non nulle (indiquant une erreur), le script s'arrête direct au lieu de continuer à exécuter les commandes suivantes.`

- 'set -ex'
- 'pour aller plus loin, on peut utiliser -x pour afficher chaque commande exécutée dans le terminal avec ses arguments avant son exécution
- 'exemple : set -ex'
# Teste la sortie de ton programme minishell
if [ "$(./minishell 'echo hello')" = "hello" ]; then
    echo "Succes : le minishell renvoi bien 'hello'"
else
    echo "Echec : pas d'envoir de 'hello'"
fi
