# **Utilisation du lplex**

1. Modifier le fichier "lp-generatir.py" en fonction des objectifs et des contraintes du problème
2. Exécuter le fichier "lp-generatir.py" sur Python 2
3. Un nouveau fichier "problem.lp" apparait dans le dossier
4. Lancer cplex 
5. Charger le problème avec la commande "read" (nom du fichier)
6. Résoudre le problème avec "optimize"
7. Exporter les solutions avec "write" (format "sol")
8. Vous obtenez un fichier sol de type xml contenant les solutions

# **Exemple par défaut**

## Problem

### **Explication**

Problème :
- 5 tâches
- Durée des tâches : 1, 2, 3, 2 et 3
- Date limite : 2, 3, 4, 4 et 5
- Indisponibilités des 3 machines :
    - Machine 1 : entre 4 et 5
    - Machine 2 : entre 3 et 5
    - Machine 3 : entre 5 et 6

### **Solution**

Solution donnée par Cplex :
- sur machine 1 : tâches 1 et 2
- sur machine 2 : tâche 3
- sur machine 3 : tâche 4 et 5
