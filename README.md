# 42minirt
Projet 5eme cercle cursus 42

- chaque element peut etre separe de 1 ou plusieurs retour a la ligne
- chaque information de l'element peut etre separe de 1 ou plusieurs espaces
- la premier info doit etre le type, les suivantes dans l'ordre exige par le type
- pas d'obligation de nombre: plane (pl), sphere (sp), cylinder (cy) order is not important
- strictly one: ambiant lighting (A), camera (C), light (L). order is not important

Programme doit pouvoir resize les objets (diametre de la sphere, largeur et hauteur du cylindre)

Programme doit pouvoir appliquer translation et rotation aux : objets, lumieres, camera sauf sphere et lumiere ambiante? --> doit gerer des mouvements camera???


# A FAIRE

- adapter memoire si lignes vides entre lignes pleine: actuellement, risque de double free, corruption, core dump.
- adapter memoire si plusieurs el qui sont censes etre uniques: actuellement, risque de leak.
- ajouter message d'erreur si map vide?