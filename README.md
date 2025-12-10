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
- calculer les intersections pour chaque forme : OK (L)
- calculer la distance avec la camera pour determiner l'ordre de proximite : OK (L)
- gerer la lumiere : OK (L)
- ajouter les ombres : OK (L)
- attribuer une couleur a chaque pixel : OK (C et L)
- mettre a la norme

# D'ICI PROCHAINE REU
- C: mettre a la norme
- C & L: corriger forme du cylindre en fonction de l'inclinaison
- C & L: corriger le segfault quand plus de x cylindres

# A FAIRE
- ajouter message d'erreur si map vide?
- preparer des maps interessantes pour les evals


# Concepts

- la fenetre n'est pas le viewport, le viewport est l'ecran de la camera, la fenetre affiche le viewport en fonction du fov (plus ou moins compresse / etire). La width = la largeur de la fenetre en pixels. La v_width est la largeur du viewport en unites. Ainsi, les deux largeurs ne sont pas forcement en 1:1, un pixel ne vaut pas forcement une unite. Pour savoir combien d'unites sont necessaires pour remplir un pixel, je dois calculer la v_width et la diviser par la width.
- Pour calculer la v_wdith, j'ai besoin du fov transforme en radian (au lieu de degres) et divise par deux, sur lequel j'effectue une tangeante avant de multiplier le resultat par deux (trigonometrie). Pour obtenir la v_height, je divise la w_width par l'aspect ratio.
- Si je veux un aspect ratio de 16:9, je determine une width et une height (taille de la fenetre donc) qui respectent ce ratio: width / height doit pouvoir etre reduit a 16/9. Je peux aussi choisir une width et une height au hasard et calculer l'aspect ratio avec width / height. Bien de le faire et de gerer les cas bizarres (if aspect ratio < 1) si jamais evaluateurs modifient width et/ou height?
- C'est bien de garder la moitie de la v_width et la moitie de la h_width car le point 0.0 du viewport est au centre, meme si le point 0.0 du canva est en haut a gauche.
- Pour simplifier les calculs, on peut decider que la distance du point de la cam au viewport est de 1 unite.
- Tres important de "normaliser" les chiffres au moment des calculs des points/vecteurs x,y,z .
- "Envoyer des rayons sur chaque pixel": parcourir tous les pixels; pour chacun, appeler les fonctions qui calculent si chaque forme est sur le chemin du vecteur actuel ou non et si oui a quelle distance du point d'origine (pour determiner qui est devant).

# Le ray tracing explique pour celleux qui n'aiment pas les maths
On va pas se mentir, si les maths c'est pas votre truc, le ray tracing ca sera pas votre truc (j'en ai fait la difficile experience). Cela dit, je vais tout de meme essayer de presenter la chose d'une maniere plus accessible, de non matheuse a non matheux.

## Les bases, en gros
### La fenetre sur un monde imaginaire
La base de la technologie du ray tracing consiste a imaginer des chose: on imagine un monde en 3D dans lequel seront presentes ou non des formes (pour minirt: des spheres, des cylindres, et des plans), et ou une camera filmera ce qu'il s'y passe. La camera est donc elle aussi presente *dans* le monde en 3D. La fenetre de minirt nous transmet ce que filme cette camera. Autrement dit, le contenu de la fenetre correspond a celui du viewport de la camera (ce qu'on voit a travers elle). 

ATTENTION: la fenetre N'EST PAS le viewport, la distinction est importante. Voyez cela comme deux ecrans separes: l'un est dans le monde imaginaire en 3D, rattache a la camera (= le viewport); l'autre est sur votre tres reel ecran a vous (= la fenetre). Chacun a ses propres dimensions et unites. Les unites qui composent votre fenetre sont des pixels. Celles qui composent le viewport, des unites differentes (appelez-les comme vous le voulez). Cela permet de mettre plusieurs unites dans un pixel, et donc d'etirer plus ou moins l'image rendue sur votre fenetre. Ce ratio "x unites dans 1 pixel" depend de votre FOV.

### Le FOV: breve presentation
"Mon quoi?" me dites-vous perplexe. Ouvrez donc Minecraft, modifiez le FOV dans les parametres, et observez le resultat (si vous n'avez pas le jeu, vous trouverez sans doute une video youtube qui vous fera la demonstration). Un regard attentif notera que l'image semble plus ou moins etiree en fonction de la valeur du FOV. Comme dit plus haut, c'est ce qui va determiner combien d'unites propre au viewport valent 1 pixel de la fenetre. Moins il faut d'unites pour 1 pixel, plus l'image sera etiree, et a l'inverse, plus il en faut, plus elle sera compressee.

Dans minirt, le FOV nous est donne par la map: c'est une des proprietes de la camera. Avec l'aspect ratio (la largeur de la fenetre divisee par la hauteur de la fenetre), il influence les dimensions du viewport, et donc le centre de ce dernier, qui nous servira plus tard. Nous en explorerons les details plus loin.

### Le canevas: une mosaique de pixels
Pour que la fenetre puisse nous transmettre le contenu du viewport, notre programme doit calculer la couleur a donner a chaque pixel de cette fenetre et le transposer sur un "canevas": une image unique que pourra afficher la minilibx en une seule fois. Si vous decidez de faire un programme qui prend en compte les modifications de la map en temps reel (ne le faites pas), vous recreerez un canevas a chaque modification.

### Uuuuuuun rayon d'soleil (et d'ombre)
Pour executer ce calcul, on s'imagine "envoyer des rayons" en direction de chaque pixel depuis la position de la camera. Pour simplifier les calculs, on dit que le viewport de la camera est a 1 unite de distance de la position de la camera. Cette derniere phrase n'a pas de sens pour vous? C'est normal. Pour la comprendre, il nous faudra, helas, se pencher sur la notion de vecteur.

Mais nous verrons cela plus tard, restons meta. Nous envoyons donc des rayons en direction de chaque pixel. Notre programme doit maintenant verifier si, sur son chemin vers l'infini, le rayon traite rencontre une ou plusieurs formes. Si c'est le cas, il faut savoir lesquelles, laquelle est la plus proche, et surtout quelle est sa couleur, afin de pouvoir calculer la couleur du pixel concerne.

Nous ne sommes pourtant pas au bout de nos peines: une fois la couleur de la forme la plus proche identifiee, il nous faut encore la moduler en fonction de la lumiere ambiante et de la lumiere directe, qui se compose en "diffuse" et "specular". Et bien sur, prendre en compte si le point de contact avec la forme est en realite dans l'ombre (par ex: la lumiere vient du cote droit, laissant donc le cote gauche de la forme dans l'ombre, ou une autre forme est placee entre celle qu'on a touchee et la lumiere, projetant alors son ombre sur le point d'impact). Pour faire cette verification, on renvoie des rayons, cette fois depuis le point d'impact en direction de la lumiere: si on rencontre une nouvelle forme sur le chemin, le pixel sera dans l'ombre, sinon, il sera illumine. Tada!

### A chaque forme sa formule
Pour savoir quelle forme est touchee ou non par nos rayons, nous aurons besoin de formules mathematiques propres a chaque forme: en effet, une sphere n'a pas la meme aire qu'un cylindre, et encore moins qu'un plan (qui n'a qu'une surface et non une aire). Ah, d'ailleurs, petit point sur le plan: la meilleure facon non mathematique de decrire cette forme a mon sens est "une surface plate qui s'etend a l'infini dans toutes les directions depuis son origine, genre un sol sans fin, ou un plafond sans fin, ou un mur sans fin, en fonction de son inclinaison." Personnellement, j'aurais gagne du temps si j'avais eu acces a cette petite precision. 

Ce qui peut etre perturbant, c'est qu'on ne cherche pas la position des formes, qui nous sont donnees par la map, mais plutot les points d'impact (ou d'intersection): la ou les rayons rencontrent des formes. Il nous faut donc trouver "t", la longueur du deplacement depuis l'origine du rayon jusqu'au point d'impact s'il y en a, pour ensuite verifier si ce "t" est valable ou non (y a-t-il intersection avec la forme verifiee?). Et ce calcul de "t" change en fonction de la forme en question.


BON. On a vu les bases en gros, il est l'heure de passer aux choses concretes.

## Le FOV: les calculs
Comme j'en ai une pauvre comprehension, je me contenterai de vous transmettre les operations a suivre, sans pouvoir en expliquer le pourquoi (desolee).

Commencons par transformer les degres recu par la map (ex.: 70) en "radian": multiplions la valeur du FOV par Pi, puis divisons le resultat par 180 (tout doit etre en float).

Divisons maintenant ce resultat par deux, puis effectuons une tangeante sur ce produit, avant de multiplier le resultat par 2.

Voici un exemple de comment coder ce calcul:
```
transformed_fov = (float)fov * (float)M_PI / 180.0f;
transformed_fov = 2.0f * tanf(transformed_fov * 0.5f);
```
Super, la transformation de notre FOV est faite! Plus qu'a l'utiliser concretement.

Pour que le viewport soit affecte par notre FOV, on en calcule les dimensions a partir de celui-ci, ainsi que des dimensions de la fenetre. Plus precisement, on calcule le centre du viewport, en passant par la moitie de sa largeur et la moitie de sa hauteur; on obtient ces moities en utilisant le FOV et l'aspect ratio (la largeur de la fenetre divisee par la hauteur de la fenetre).

Voici un exemple de comment coder ce calcul:
```
aspect_ratio = (float)window_width / (float)window_height;
viewport_half_h = transformed_fov * 0.5f;
viewport_half_w = viewport_half_h * aspect_ratio;
```

Precision: le sujet ne fixe pas de dimensions a la fenetre, nous sommes donc libres de les choisir, en nous protegeant habilement du cas ou l'aspect ratio serait inferieur a 1.

## Vecteur
Je redoutais ce moment. Expliquer les vecteurs. Bon.

Commencons par cette info rigolote (non): le terme "vecteur" evoque des choses differentes (mais pas vraiment) en fonction de la discipline qui l'utilise. Par exemple, en informatique, c'est une simple combinaison de nombre (ex: 5,2,10). Alors qu'en mathematiques, c'est une distance entre un point et un autre, et qu'en physique, c'est carrement un deplacement.
Je le precise parce que ne pas le savoir peut vous embrouiller lors de vos recherches.

Globalement, pour minirt, nous allons utiliser des vecteurs pour signaler des coordonnees (x,y,z) dans notre espace en 3D. Cela va nous servir a la fois pour representer des positions et des directions, autrement dit: d'ou part le rayon, et dans quel sens il part.

Un des calculs que vous allez souvent utiliser consiste donc a vous deplacer d'un point d'origine pendant "t" (longueur du deplacement) dans une direction donnee par la position d'un objectif (le pixel traite, la lumiere ou le point d'impact). Pour effectuer ce calcul, on prend le point d'origine, et on lui ajoute les coordonnees de l'objectif multipliees par la longueur du deplacement. "Mais" me diriez-vous, "mon point est compose de 3 chiffres! Comment je peux lui additionner quoi que ce soit?" Pas de panique, c'est tres simple: vous additionnez le premier chiffre de vos premieres coordonnees avec le premier chiffre de vos secondes coordonnees, le deuxieme chiffre avec le deuxieme, et ainsi de suite. Autrement dit, le x avec le x, le y avec le y, et le z avec le z. C'est la meme pour toutes les operations.

Concretement, en pseudo code (les parentheses sont superflues mais donnent, a mon sens, plus de lisibilite):
````
origin.x + (objective.x * t);
origin.y + (objective.y * t);
origin.z + (objective.z * t);
````

## Les couleurs: du format RGB au format HEX (et vice-versa)
Vous y avez peut-etre deja pense, mais finalement, le format RGB des couleurs, c'est un peu des vecteurs non? Eh bien, informatiquement parlant, oui, car c'est bien une combinaison de chiffres (par ex.: 255,0,80). C'est pertinent car on peut utiliser la meme logique pour les operations: si vous voulez additionner deux couleurs, vous additionnez le r avec le r, le g avec le g, ... Ca vous rappelle quelque chose?

Seulement, bien que la map vous fournisse les couleur au format RGB, la minilibx ne travaille qu'avec le format HEX. Il va donc vous falloir des fonctions qui permettent de passer d'un format a l'autre.

## La normale, la norme, normaliser
Vous savez ce qui est marrant (non)? C'est qu'on pourrait croire que ces trois mots ont des choses en commun, voire que c'est la meme chose. Apres tout, ils se ressemblent tellement! He bien non. Nous avons bien affaire a trois choses differente.

La normale est un vecteur perpendiculaire a un point d'impact par exemple. Elle va etre largement utilisee dans les formules des formes, c'est donc important d'en comprendre le concept.

La norme est la longueur de l'interpretation physique d'un vecteur ("deplacement"). C'est notre "t" dont on aura besoin pour calculer les intersections comme vu plus haut. Pour chaque forme, on verifie si le "t" est contenu dans des bornes predefinies (appelons-les ``tmin`` et ``tmax``); s'il ne l'est pas, il n'y a pas d'intersection, sinon, oui. ``tmin`` correspond a EPSILON, et ``tmax`` a 1e30f.

Normaliser signifie effectuer un calcul sur une variable qui la rend egale a 1. Cette operation est utilisee pour s'assurer qu'on compare et transforme des valeurs en se basant sur la meme echelle / limiter les imprecisions dues aux floats?

## Calcul des intersections
Pour rappel, le ray tracing fonctionne en "envoyant des rayons" dans la direction de chaque pixel. Concretement, cela signifie que votre programme doit avoir une boucle iterant sur chaque pixel, et pour chacun, lancer les fonctions qui verifient si, sur le chemin du rayon allant de la camera a l'infini dans la direction du pixel, on croise soit une sphere, soit un cylindre, soit un plan. 

Comme la map vous dit deja s'il y a des formes, lesquelles et combien de chaque, vous savez combien de fois par pixel appeler chaque fonction. Si vous avez 3 spheres, vous ferez les calculs "y a-t-il une sphere sur le chemin de ce rayon" 3 fois. En realite, la question est plutot "la sphere numero 1/2/3 est-elle sur le chemin de ce rayon?" 

### Sphere
J'aimerais dire que le calcul permettant de savoir si le chemin du rayon croise une sphere est simple. Ce n'est pas vraiment le cas, mais c'est bien de commencer par lui.

Tout d'abord, nous avons besoin de mettre la direction du rayon au carre, ce qui resulte en un "dot product" (un vecteur fois un vecteur). Je vous conseille de creer une fonction "dot_product()", car c'est une operation tres commune dans le ray tracing.

Par exemple, on peut la coder ainsi:
```
float	dot_product(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
```
Pour la sphere, les deux vecteurs (a et b) seront donc le meme, a savoir la direction du rayon, soit la position du pixel.
```
float a = dot_product(ray.direction, ray.direction);
```
Ensuite, on calcule la distance entre l'origine du rayon et le centre de la sphere (donne par les coordonnees de la sphere), en soustrayant la premiere a la deuxieme. A nouveau, je vous conseille de faire une fonction qui calcule un vecteur moins un vecteur.
```
t_vector vector_minus_vector(t_vector a, t_vector b)
{
    t_vector    res;

    res.x = a.x - b.x;
    res.y = a.y - b.y;
    res.z = a.z - b.z;
    return (res);
}

t_vector oc = vector_minus_vector(sphere.coord, ray.origin);
```
Preparez une nouvelle variable (appelons-la ``c``). Sa valeur sera un dot product de la distance ``oc`` que nous venons de calculer, moins le rayon de la sphere au carre.

Voici un exemple de comment le coder:
```
float   c = dot_product(oc, oc) - (sphere.diameter * 0.5f) * (sphere.diameter * 0.5f);
```
Preparez encore une variable (appelons-la ``half_b``, car elle correspond a b/2 dans la fonction quadratique qui est au centre du calcul des spheres): sa valeur correspond au dot product de ``oc`` et de la direction du rayon.

Voici un exemple de comment le coder:
```
float   half_b = dot_product(oc, ray.direction);
```
Nous avons encore besoin d'une variable, qui nous servira de discrimant. Appelons-la ``discr``. Sa valeur est obtenue en mettant ``half_b`` au carre, puis en lui soustrayant ``a`` fois ``c``.
```
float   discr = half_b * half_b - a * c;
```
Ici, nous devons verifier si cette valeur est inferieure a zero: si tel est le cas, il n'y a pas d'intersection avec cette sphere; votre fonction doit donc retourner une valeur correspondant a "cette sphere n'est pas sur le chemin de ce rayon". Sinon, on continue.

Ajoutons encore une variable (courage, c'est bientot fini). Appelons-la ``squareroot``. Sa valeur est obtenue grace a la fonction ``sqrtf()`` de la librairie <maths.h>, en lui passant le discriminant calcule plus haut.
```
float   squareroot = sqrtf(discr);
```
Nous arrivons enfin (ENFIN!!) a notre derniere variable, le fameux `t`!

Nous allons devoir tester deux valeurs de ``t``, la premiere obtenue en utilisant ``squareroot`` en positif, et la deuxieme en l'utilisant en negatif. Si la premiere valeur est en-dehors des bornes (``tmin`` et ``tmax`` dont nous avons parle plus haut), on teste la deuxieme: si la deuxieme est aussi en-dehors des bornes, alors il n'y a pas d'intersection. Sinon, la fonction renvoie l'equivalent de "cette sphere est bien sur le chemin de ce rayon".

Les valeurs en question sont obtenues en passant ``half_b`` en negatif, puis en lui soustrayant (pour la premiere) ou lui additionnant (pour la deuxieme) ``squareroot``, et enfin en divisant le resultat par ``a``.

Voici un exemple de comment le coder:
```
	float   t = (-half_b - squareroot) / a;

	if (t < tmin || t > tmax)
	{
		t = (-half_b + squareroot) / a;
		if (t < tmin || t > tmax)
			return ("pas d'intersection");
	}
    return ("intersection");
```
Votre programme doit donc recevoir comme information: 
- s'il y a une intersection avec la sphere
- ou exactement cette intersection a lieu
- quelle est la sphere rencontree exactement et quelle est sa couleur

Envoyez toutes ces informations a une fonction qui calculera quel eclairage s'applique au point d'intersection.

Dans un premier temps, vous pouvez simplement appliquer au pixel la couleur de la forme, sans vous preoccuper de la lumiere. Si tout est correct, vous devrez voir apparaitre des cercles colores la ou vous avez place vos spheres! Vous les voyez? Bravo!


