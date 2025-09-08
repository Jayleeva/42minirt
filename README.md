# Consignes
Creer un programme de ray tracing.
- chaque element peut etre separe de 1 ou plusieurs retour a la ligne
- chaque information de l'element peut etre separe de 1 ou plusieurs espaces
- la premier info doit etre le type, les suivantes dans l'ordre exige par le type
- pas d'obligation de nombre: plane (pl), sphere (sp), cylinder (cy) order is not important
- strictly one: ambiant lighting (A), camera (C), light (L). order is not important

Programme doit pouvoir resize les objets (diametre de la sphere, largeur et hauteur du cylindre) --> apparemment pas en live?

Programme doit pouvoir appliquer translation et rotation aux : objets sauf sphere, lumieres sauf lumiere ambiante, camera --> apparemment pas en live?

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
- ajouter message d'erreur si map vide?


