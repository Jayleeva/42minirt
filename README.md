# Consignes
Creer un programme de ray tracing.
- chaque element peut etre separe de 1 ou plusieurs retour a la ligne
- chaque information de l'element peut etre separe de 1 ou plusieurs espaces
- la premier info doit etre le type, les suivantes dans l'ordre exige par le type
- pas d'obligation de nombre: plane (pl), sphere (sp), cylinder (cy) order is not important
- strictly one: ambiant lighting (A), camera (C), light (L). order is not important

Pas besoin de faire des transformations en live (bonus).


# Etapes
- parser : OK (C)
- gerer la fenetre : OK (C)
- trouver comment envoyer des rayons sur chaque pixel : OK (L)
- calculer les intersections pour chaque forme : O/K (L)
- calculer la distance avec la camera pour determiner l'ordre de proximite : O/K (L)
- attribuer une couleur a chaque pixel en fonction : O/K (C)
- gerer la lumiere

# D'ICI PROCHAINE REU
- C: trouver calcul pour plane
- L: trouver calcul pour cylindre

# A FAIRE
- ajouter message d'erreur si map vide?


