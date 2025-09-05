# 42minirt
Projet 5eme cercle cursus 42

- chaque element peut etre separe de 1 ou plusieurs retour a la ligne
- chaque information de l'element peut etre separe de 1 ou plusieurs espaces
- la premier info doit etre le type, les suivantes dans l'ordre exige par le type
- pas d'obligation de nombre: plane (pl), sphere (sp), cylinder (cy) order is not important
- strictly one: ambiant lighting (A), camera (C), light (L). order is not important

Programme doit pouvoir resize les objets (diametre de la sphere, largeur et hauteur du cylindre)

Programme doit pouvoir appliquer translation et rotation aux : objets, lumieres, camera sauf sphere et lumiere ambiante? --> doit gerer des mouvements camera???

# Etapes
- parser : quasi OK (C)
- gerer la fenetre : OK, sauf display des pixels (C)
- trouver comment envoyer des rayons sur chaque pixel
- calculer les intersections pour chaque forme
- calculer la distance avec la camera pour determiner l'ordre de proximite
- attribuer une couleur a chaque pixel en fonction
- gerer la lumiere

# D'ICI PROCHAINE REU
- C et L: se renseigner sur comment envoyer des rayons sur chaque pixel

# A FAIRE
- corriger erreurs de contexte liees a atof
- corriger conditional jump pour data->map
- corriger still reachable si return(0) apres un get_next_line (count_elem OK? et is_map_valid KO)
- ajouter message d'erreur si map vide?


