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

# Concepts
- la fenetre n'est pas le viewport, le viewport est l'ecran de la camera, la fenetre affiche le viewport en fonction du fov (plus ou moins compresse / etire). La width = la largeur de la fenetre en pixels. La v_width est la largeur du viewport en unites. Ainsi, les deux largeurs ne sont pas forcement en 1:1, un pixel ne vaut pas forcement une unite. Pour savoir combien d'unites sont necessaires pour remplir un pixel, je dois calculer la v_width et la diviser par la width.
- Pour calculer la v_wdith, j'ai besoin du fov transforme en radian (au lieu de degres) et divise par deux, sur lequel j'effectue une tangeante avant de multiplier le resultat par deux (trigonometrie). Pour obtenir la v_height, je divise la w_width par l'aspect ratio.
- Si je veux un aspect ratio de 16:9, je determine une width et une height (taille de la fenetre donc) qui respectent ce ratio: width / height doit pouvoir etre reduit a 16/9. Je peux aussi choisir une width et une height au hasard et calculer l'aspect ratio avec width / height. Bien de le faire et de gerer les cas bizarres (if aspect ratio < 1) si jamais evaluateurs modifient width et/ou height?
- C'est bien de garder la moitie de la v_width et la moitie de la h_width car le point 0.0 du viewport est au centre, meme si le point 0.0 du canva est en haut a gauche.
- Pour simplifier les calculs, on peut decider que la distance du point de la cam au viewport est de 1 unite.
- Tres important de "normaliser" les chiffres au moment des calculs des points/vecteurs x,y,z .
- "Envoyer des rayons sur chaque pixel": parcourir tous les pixels; pour chacun, appeler les fonctions qui calculent si chaque forme est sur le chemin du vecteur actuel ou non et si oui a quelle distance du point d'origine (pour determiner qui est devant).

