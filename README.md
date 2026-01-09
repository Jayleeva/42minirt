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
- gerer la fenêtre : OK (C)
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

# A FAIRE
- ajouter message d'erreur si map vide?
- preparer des maps interessantes pour les evals


# Concepts

- la fenêtre n'est pas le viewport, le viewport est l'ecran de la camera, la fenêtre affiche le viewport en fonction du fov (plus ou moins compresse / etire). La width = la largeur de la fenêtre en pixels. La v_width est la largeur du viewport en unites. Ainsi, les deux largeurs ne sont pas forcement en 1:1, un pixel ne vaut pas forcement une unite. Pour savoir combien d'unites sont necessaires pour remplir un pixel, je dois calculer la v_width et la diviser par la width.
- Pour calculer la v_wdith, j'ai besoin du fov transforme en radian (au lieu de degres) et divise par deux, sur lequel j'effectue une tangeante avant de multiplier le resultat par deux (trigonometrie). Pour obtenir la v_height, je divise la w_width par l'aspect ratio.
- Si je veux un aspect ratio de 16:9, je determine une width et une height (taille de la fenêtre donc) qui respectent ce ratio: width / height doit pouvoir etre reduit a 16/9. Je peux aussi choisir une width et une height au hasard et calculer l'aspect ratio avec width / height. Bien de le faire et de gerer les cas bizarres (if aspect ratio < 1) si jamais evaluateurs modifient width et/ou height?
- C'est bien de garder la moitie de la v_width et la moitie de la h_width car le point 0.0 du viewport est au centre, meme si le point 0.0 du canva est en haut a gauche.
- Pour simplifier les calculs, on peut decider que la distance du point de la cam au viewport est de 1 unite.
- Tres important de "normaliser" les chiffres au moment des calculs des points/vecteurs x,y,z .
- "Envoyer des rayons sur chaque pixel": parcourir tous les pixels; pour chacun, appeler les fonctions qui calculent si chaque forme est sur le chemin du vecteur actuel ou non et si oui a quelle distance du point d'origine (pour determiner qui est devant).

# Le ray tracing expliqué pour celleux qui n'aiment pas les maths
On va pas se mentir, si les maths c'est pas votre truc, le ray tracing ça sera pas votre truc (j'en ai fait la difficile expérience). Cela dit, je vais tout de même essayer de présenter la chose d'une manière plus accessible, de non matheuse a non matheux.

## Les bases, en gros
### La fenêtre sur un monde imaginaire
La base de la technologie du ray tracing consiste à imaginer des chose: on imagine un monde en 3D dans lequel seront présentes ou non des formes (pour minirt: des sphères, des cylindres, et des plans), et où une caméra filmera ce qu'il s'y passe. La caméra est donc elle aussi présente *dans* le monde en 3D et peut y être placée n'importe où. La fenêtre de minirt nous transmet ce que filme cette caméra. Autrement dit, le contenu de la fenêtre correspond à celui du viewport de la caméra (ce qu'on voit à travers elle). 

ATTENTION: la fenêtre N'EST PAS le viewport, la distinction est importante. Voyez cela comme deux écrans séparés: l'un est dans le monde imaginaire en 3D, rattaché à la caméra (= le viewport); l'autre est sur votre très réel écran à vous (= la fenêtre). Chacun a ses propres dimensions et unités. Les unités qui composent votre fenêtre sont des pixels. Celles qui composent le viewport, des unités différentes (appelez-les comme vous le voulez). Cela permet de mettre plusieurs unités dans un pixel, et donc d'étirer plus ou moins l'image rendue sur votre fenêtre. Ce ratio "x unités dans 1 pixel" dépend de votre FOV.

### Le FOV: brève présentation
"Mon quoi?" me dites-vous perplexe. Ouvrez donc Minecraft, modifiez le FOV dans les paramètres, et observez le résultat (si vous n'avez pas le jeu, vous trouverez sans doute une video youtube qui vous en fera la démonstration). Un regard attentif notera que l'image semble plus ou moins étirée en fonction de la valeur du FOV. Comme dit plus haut, c'est ce qui va déterminer combien d'unités propre au viewport valent 1 pixel de la fenêtre. Moins il faut d'unités pour 1 pixel, plus l'image sera étirée, et à l'inverse, plus il en faut, plus elle sera compressée. La valeur 70 est assez standard, pour une image ni trop étirée ni trop compressée.

Dans minirt, le FOV nous est donné par la map: c'est une des propriétés de la camera. Avec l'aspect ratio (la largeur de la fenêtre divisée par la hauteur de la fenêtre), il influence les dimensions du viewport, et donc le centre de ce dernier, qui nous servira plus tard. Nous en explorerons les details plus loin. Retenez pour l'instant que vous ne pouvez pas ignorer le FOV, et que vous *devrez* faire des maths avec (me regardez pas comme ça, c'est vous qui avez choisi de faire minirt hein).

### Le canevas: une mosaïque de pixels
Pour que la fenêtre puisse nous transmettre le contenu du viewport, notre programme doit calculer la couleur à donner à chaque pixel de cette fenêtre, stocker ces informations dans un "canevas" (double array [x][y] de pixels), et s'en servir pour créer une image unique, que pourra afficher la minilibx en une seule fois. Si vous décidez de faire un programme qui prend en compte les modifications de la map en temps réel (ne le faites pas), vous recréerez un canevas à chaque modification. 

### Uuuuuuun rayon d'soleil (et d'ombre)
Pour exécuter ce calcul de la couleur, on s'imagine "envoyer des rayons" en direction de chaque pixel depuis la position de la caméra. Pour simplifier les calculs, on dit que le viewport de la caméra est à 1 unité de distance de la position de la caméra. Cette dernière phrase n'a pas de sens pour vous? C'est normal. Pour la comprendre, il nous faudra, helas, se pencher sur les notions de vecteur et de normalisation.

Mais nous verrons cela plus tard, restons meta. Nous envoyons donc des rayons en direction de chaque pixel. Notre programme doit maintenant vérifier si, sur son chemin vers l'infini, le rayon traité rencontre une ou plusieurs formes. Si c'est le cas, il faut savoir lesquelles, laquelle est la plus proche, et surtout quelle est sa couleur, afin de pouvoir calculer la couleur du pixel concerné.

Nous ne sommes pourtant pas au bout de nos peines: une fois la couleur de la forme la plus proche identifiée, il nous faut encore la moduler en fonction de la lumière ambiante et de la lumière directe, qui se compose en "diffuse" et "specular". Et bien sûr, prendre en compte si le point de contact avec la forme est en réalité dans l'ombre (par ex: la lumière vient du côté droit, laissant donc le côté gauche de la forme dans l'ombre, ou une autre forme est placée entre celle qu'on a touchée et la lumière, projetant alors son ombre sur le point d'impact). Pour faire cette vérification, on renvoie des rayons, cette fois depuis le point d'impact en direction de la lumière: si on rencontre une nouvelle forme sur le chemin, le pixel sera dans l'ombre, sinon, il sera illuminé plus ou moins fort en fonction de la distance avec la source de lumière. Tada! (en gros)

### A chaque forme sa formule
Pour savoir quelle forme est touchée ou non par nos rayons, nous aurons besoin de formules mathématiques propres à chaque forme: en effet, une sphère n'a pas la même aire qu'un cylindre, et encore moins qu'un plan (qui n'a qu'une surface et non une aire). Ah, d'ailleurs, petit point sur le plan: la meilleure façon non mathématique de décrire cette forme à mon sens est "une surface plate qui s'etend à l'infini dans toutes les directions depuis son origine, genre un sol sans fin, ou un plafond sans fin, ou un mur sans fin, en fonction de son inclinaison." Personnellement, j'aurais gagné du temps si j'avais eu accès à cette petite précision. 

Ce qui peut être perturbant, c'est qu'on ne cherche pas la position des formes, qui nous sont données par la map, mais plutôt les points d'impact (ou d'intersection): là où les rayons rencontrent des formes. Il nous faut donc trouver "t", la longueur du déplacement depuis l'origine du rayon jusqu'au point d'impact s'il y en a, pour ensuite vérifier si ce "t" est valable ou non. Et ce calcul de "t" change en fonction de la forme en question.

**BON. On a vu les bases en gros, il est l'heure de passer aux choses concretes.**

## Créer et afficher une image
La minilibx est parfois un peu obscure. Voici de quoi vous aurez besoin pour afficher une image de la taille de la fenêtre, créée pixel par pixel.

D'une part, il vous faut allouer de la mémoire pour une image, dont vous devrez définir l'endian, la size et le bpp (bit per pixel). Ensuite, il vous faudra utiliser la fonction ``mlx_new_image()`` pour attribuer un pointeur à votre image. Puis, vous utiliserez la fonction ``mlx_get_data_addr()`` pour obtenir l'adresse de l'image, ce qui vous permettra d'assigner les pixels avec le paragraphe ci-dessous, avant de finalement utiliser la fonction ``mlx_put_image_to_window()`` qui affichera (ENFIN) votre image.

D'autre part, il vous faut allouer de la mémoire pour votre canevas, qui consistera en une double array ([x][y]) de pixels, dans laquelle vous stockerez notamment la couleur de chacun. Pour cela, vous créerez une fonction ``put_pixel()`` appelée pour chaque pixel, qui leur attribuera leurs couleurs en utilisant le pointeur obtenu plus haut. 

Voici un exemple de comment la coder:
```
void	put_pixel(t_image *img, int canvas_x, int canvas_y, int color) // on reçoit le pointeur sur l'image, les coordonnees x et y du pixel du canevas, et la couleur
{
	char	*pixel;	// on déclare un nouveau pointeur sur pixel

	if (canvas_x >= 0 && canvas_x < window_width && canvas_y >= 0 && canvas_y < w_height)	 // on vérifie que les coordonnées reçues soient bien comprises dans les dimensions de la fenêtre
	{
		pixel = img->addr + (canvas_y * img->size + canvas_x * (img->bpp / 8)); // on assigne au pointeur du pixel l'adresse de l'image à laquelle on ajoute les coordonnées modulées par la size pour le y et par le bpp pour le x
		*(unsigned int *)pixel = color; // on assigne la couleur à la valeur du pixel cast en unsigned int.
	}
} 
```
Bien sûr, il ne faudra pas oublier de détruire les élements ci-dessous à la fermeture du programme:
- l'image avec ``mlx_destroy_image()``
- la fenêtre avec ``mlx_destroy_window()``
- le pointeur sur la minilibx avec ``mlx_destroy_display()``
Et comme toujours, pensez à libérer la mémoire allouée.


## Le FOV: les calculs
Comme j'en ai une pauvre compréhension, je me contenterai de vous transmettre les opérations à suivre, sans pouvoir en expliquer le pourquoi (désolée).

Commençons par transformer les degrés reçus par la map (ex.: 70) en "radian": multiplions la valeur du FOV par Pi, puis divisons le resultat par 180 (tout doit être en float).

Divisons maintenant ce résultat par deux, puis effectuons une tangeante sur ce produit, avant d'en multiplier le resultat par 2.

Voici un exemple de comment coder ce calcul:
```
transformed_fov = (float)fov * (float)M_PI / 180.0f;
transformed_fov = 2.0f * tanf(transformed_fov * 0.5f);
```
Super, la transformation de notre FOV est faite! Plus qu'à l'utiliser concrètement.

Pour que le viewport soit affecté par notre FOV, on en calcule les dimensions à partir de celui-ci, ainsi que des dimensions de la fenêtre. Plus précisement, on calcule le centre du viewport, en passant par la moitié de sa largeur et la moitié de sa hauteur; on obtient ces moitiés en utilisant le FOV et l'aspect ratio (la largeur de la fenêtre divisée par la hauteur de la fenêtre).

Voici un exemple de comment coder ce calcul:
```
aspect_ratio = (float)window_width / (float)window_height;
viewport_half_h = transformed_fov * 0.5f;
viewport_half_w = viewport_half_h * aspect_ratio;
```

Précision: le sujet ne fixe pas de dimensions à la fenêtre, nous sommes donc libres de les choisir, en nous protégeant habilement du cas où l'aspect ratio serait inférieur à 1.

## Vecteur
Je redoutais ce moment. Expliquer les vecteurs. Bon.

Commençons par cette info rigolote (non): le terme "vecteur" évoque des choses différentes (mais pas vraiment) en fonction de la discipline qui l'utilise. Par exemple, en informatique, c'est une simple combinaison de nombres (ex: 5,2,10). Alors qu'en mathématiques, c'est une distance entre un point et un autre, et qu'en physique, c'est carrément un déplacement. Je le précise parce que ne pas le savoir peut vous embrouiller lors de vos recherches.

Globalement, pour minirt, nous allons utiliser des vecteurs pour signaler des coordonnées (x,y,z) dans notre espace en 3D. Cela va nous servir à la fois pour représenter des positions et des directions, autrement dit: d'où part le rayon, et dans quel sens il part.

Un des calculs que vous allez souvent utiliser consiste donc à vous "déplacer" d'un point d'origine pendant "t" (longueur du déplacement) dans une direction donnée par la position d'un objectif (le pixel traité, la lumière ou le point d'impact). Pour effectuer ce calcul, on prend le point d'origine, et on lui ajoute les coordonnées de l'objectif multipliées par la longueur du déplacement. "Mais" me diriez-vous, "mes points sont composés de 3 chiffres! Comment je peux leur additionner ou multiplier quoi que ce soit?" Pas de panique, c'est très simple: vous opérez le premier chiffre de vos premières coordonnées avec le premier chiffre de vos secondes coordonnées, le deuxième chiffre avec le deuxième, et ainsi de suite. Autrement dit, le x avec le x, le y avec le y, et le z avec le z. C'est la même pour toutes les opérations (+-*/).

Concrètement, en pseudo code (les parenthèses sont superflues mais donnent, à mon sens, plus de lisibilité):
````
origin.x + (objective.x * t);
origin.y + (objective.y * t);
origin.z + (objective.z * t);
````


## Les couleurs: du format RGB au format HEX (et vice-versa)
Vous y avez peut-être déjà pensé, mais finalement, le format RGB des couleurs, c'est un peu des vecteurs non? Eh bien, informatiquement parlant, oui, car c'est bien une combinaison de chiffres (par ex.: 255,0,80). C'est pertinent car on peut utiliser la même logique pour les opérations: si vous voulez multiplier deux couleurs, vous multipliez le r avec le r, le g avec le g, ... Ca vous rappelle quelque chose?

Mais pourquoi auriez-vous besoin de multiplier des couleurs? Pour les moduler pardi! Vous pensez qu'une sphère rouge reste à 255,0,0 quand elle baigne dans une lumière ambiante violette à 255,0,255 * un ratio de 0.2 et a une de ses faces exposée à une lumière directe? Ha! Pour mélanger des couleurs, ce que vous devrez faire, vous aurez besoin d'une fonction qui les multiplie.

Seulement, bien que la map vous fournisse les couleurs au format RGB, la minilibx ne travaille qu'avec le format HEX. Il va donc vous falloir des fonctions qui permettent de passer d'un format à l'autre.

Une fois que vous savez quelle couleur doit avoir un pixel, vous le transformez donc en format HEX, et vous stockez cette information dans votre canevas. Lorsque tous vos pixels auront leur couleur assignée, vous pourrez créer une image comme explicité plus haut.

## La normale, la norme, normaliser
Vous savez ce qui est marrant (non)? C'est qu'on pourrait croire que ces trois mots ont des choses en commun, voire que c'est la même chose. Après tout, ils se ressemblent tellement! Hé bien non. Nous avons bien affaire à trois choses différentes.

La normale est un vecteur perpendiculaire à un point d'impact par exemple. Elle va être largement utilisée dans les formules des formes, c'est donc important d'en comprendre le concept.

La norme est la longueur de l'interpretation physique d'un vecteur ("déplacement"). C'est notre "t" dont on aura besoin pour calculer les intersections comme vu plus haut. Pour chaque forme, on vérifie si le "t" est contenu dans des bornes prédéfinies (appelons-les ``tmin`` et ``tmax``); s'il ne l'est pas, il n'y a pas d'intersection, sinon, oui. ``tmin`` correspond à EPSILON, et ``tmax`` à 1e30f.

Normaliser signifie effectuer un calcul sur une variable qui la rend égale à 1. Cette opération est utilisée pour s'assurer qu'on compare et transforme des valeurs en se basant sur la même échelle / limiter les imprécisions dues aux floats?

## Calcul des intersections
Pour rappel, le ray tracing fonctionne en "envoyant des rayons" dans la direction de chaque pixel. Concrètement, cela signifie que votre programme doit avoir une boucle itérant sur chaque pixel, et pour chacun, lancer les fonctions qui vérifient si, sur le chemin du rayon allant de la camera à l'infini dans la direction du pixel, on croise soit une sphère, soit un cylindre, soit un plan. 

Comme la map vous dit déjà s'il y a des formes, lesquelles et combien de chaque, vous savez combien de fois par pixel appeler chaque fonction. Si vous avez 3 sphères, vous ferez les calculs "y a-t-il une sphère sur le chemin de ce rayon" 3 fois. En réalité, la question est plutôt "la sphère numero 1/2/3 est-elle sur le chemin de ce rayon?" 

### Sphère
J'aimerais dire que le calcul permettant de savoir si le chemin du rayon croise une sphère est simple. Ce n'est pas vraiment le cas, mais c'est bien de commencer par lui.

Tout d'abord, nous avons besoin de mettre la direction du rayon au carré, ce qui résulte en un "dot product" (un vecteur fois un vecteur). Je vous conseille de créer une fonction ``dot_product()``, car c'est une opération très commune dans le ray tracing.

Par exemple, on peut la coder ainsi:
```
float	dot_product(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
```
Ici, on calcule la valeur d'une première variable (appelons-la ``a``) avec un dot product d'un meme vecteur, à savoir la direction du rayon.
```
float a = dot_product(ray->direction, ray->direction);
```
Ensuite, on calcule la distance entre l'origine du rayon et le centre de la sphère (donné par les coordonnées de la sphère), en soustrayant la première à la deuxième. A nouveau, je vous conseille de créer une fonction qui calcule un vecteur moins un vecteur.

```
t_vector vector_minus_vector(t_vector a, t_vector b)
{
    t_vector    res;

    res.x = a.x - b.x;
    res.y = a.y - b.y;
    res.z = a.z - b.z;
    return (res);
}

t_vector X = vector_minus_vector(sphere->coord, ray->origin);
```
Préparez une nouvelle variable (appelons-la ``c``). Sa valeur sera un dot product de la distance ``X`` que nous venons de calculer, moins le rayon de la sphère au carré.

Voici un exemple de comment le coder:
```
float   c = dot_product(X, X) - (sphere->diameter * 0.5f) * (sphere->diameter * 0.5f);
```
Préparez encore une variable (appelons-la ``half_b``, car elle correspond à b/2 dans la fonction quadratique qui est au centre du calcul des sphères): sa valeur correspond au dot product de ``X`` et de la direction du rayon.

Voici un exemple de comment le coder:
```
float   half_b = dot_product(X, ray->direction);
```
Nous avons encore besoin d'une variable, qui nous servira de discrimant. Appelons-la ``discr``. Sa valeur est obtenue en mettant ``half_b`` au carré, puis en lui soustrayant ``a`` fois ``c``:
```
float   discr = half_b * half_b - a * c;
```
Ici, nous devons vérifier si cette valeur est inférieure à zéro: si tel est le cas, il n'y a pas d'intersection avec cette sphère; votre fonction doit donc retourner une valeur correspondant à "cette sphère n'est pas sur le chemin de ce rayon". Sinon, on continue.

Ajoutons encore une variable (courage, c'est bientôt fini). Appelons-la ``squareroot``. Sa valeur est obtenue grâce à la fonction ``sqrtf()`` de la librairie <maths.h>, en lui passant le discriminant calculé plus haut.
```
float   squareroot = sqrtf(discr);
```
Nous arrivons enfin (ENFIN!!) à notre dernière variable, le fameux `t`!

Nous allons devoir tester deux valeurs de ``t``, la première obtenue en utilisant ``squareroot`` en positif, et la deuxième en l'utilisant en négatif. Si la première valeur est en-dehors des bornes (``tmin`` et ``tmax`` dont nous avons parlé plus haut), on teste la deuxième: si la deuxième est aussi en-dehors des bornes, alors il n'y a pas d'intersection. Sinon, la fonction renvoie l'equivalent de "cette sphère est bien sur le chemin de ce rayon".

Les valeurs en question sont obtenues en passant ``half_b`` en négatif, puis en lui soustrayant (pour la première) ou lui additionnant (pour la deuxième) ``squareroot``, et enfin en divisant le résultat par ``a``.

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

Votre programme doit recevoir comme information: 
- s'il y a une intersection avec la sphère
- où exactement cette intersection a lieu et quelle est sa normale
- quelle est la sphère rencontrée exactement et quelle est sa couleur

Il vous reste donc quelques calculs à faire.
Préparez une variable qui stockera les coordonnées du point d'impact, appelons-la ``hit_vector``. Pour en calculer la valeur, vous aurez besoin de deux fonctions qui vous serviront également ailleurs, une première qui additionne deux vecteurs, et une deuxième qui multiplie un vecteur par un "scalaire" (une sorte d'échelle quoi, ou ici, un simple float finalement).

En effet, nous avons trouvé le "t", par lequel multiplier la direction du rayon, avant d'en additionner le résultat à l'origine du rayon. 

Voici comment on peut le coder:
```
t_vector	scale(t_vector v, float scalar)
{
	t_vector	res;

	res.x = v.x * scalar;
	res.y = v.y * scalar;
	res.z = v.z * scalar;
	return (res);
}

t_vector	vector_plus_vector(t_vector a, t_vector b)
{
	t_vector	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_vector	hit_vector = vector_plus_vector(ray->origin, scale(ray->direction, t));
```
Nous avons le point d'impact! Reste, c'est très important pour la suite, à calculer la normale de ce point.

Préparez une variable (appelons-la ``n``). Sa valeur sera le résultat de la normalisation de la longueur entre les coordonnées de la sphère et le point d'impact. A nouveau, je vous conseille de créer une fonction ``normalize()``, elle-même faisant appel à d'autres fonctions qui vont beaucoup vous servir.

Voici un exemple de comment les coder:
```
float	get_norm(t_vector v)
{
	return (sqrtf(dot_product(v, v)));
}

t_vector	normalize(t_vector v)
{
	float		norm;
	t_vector	res;

	norm = get_norm(v);
	if (norm > 0.0f)
		res = scale(v, 1.0f / norm);
	else
		res = v;
	return (res);
}

t_vector	n = normalize(vector_minus_vector(sphere->coord, hit_vector));
```
C'est bon, on sait s'il y a intersection, où exactement, la longueur du déplacement jusqu'au point d'impact, la normale de ce dernier, quelle forme a été touchée et donc, quelle est sa couleur.

Envoyez toutes ces informations à une fonction qui calculera quel éclairage s'applique au point d'intersection et en modulera donc la couleur.

Dans un premier temps, vous pouvez simplement appliquer au pixel la couleur de la forme, sans vous préoccuper de la lumière. Si tout est correct, vous devrez voir apparaitre des cercles colorés là ou vous avez placé vos sphères! Vous les voyez? Bravo!

### Plan
Contrairement à la sphère, le plan a une inclinaison, ce qui nécessite de calculer son "dénominateur?".

Préparez une variable qui stockera la normale du plan (appelons-la ``n``). Sa valeur sera le résultat de la normalisation de l'inclinaison du plan. On réutilise donc notre fonction ``normalize()`` créée plus haut:
```
t_vector	n = normalize(plane->incline);
```

A présent, préparez une variable pour y stocker le "denom". Celui-ci est obtenu par le dot product de la direction du rayon et de la normale. Si cette variable passée à la fonction ``fabsf()`` est plus petite que 1e-6f, il n'y a pas d'intersection. Concrètement, ce calcul vérifie si le rayon est parallèle ou coplanaire au plan: s'il est parallèle, le rayon ne croisera jamais le chemin du plan; s'il est coplanaire, il le croiserait à l'infini, et il est plus simple d'estimer ce cas comme une non-intersection.

Voici un exemple de comment le coder:
```
float	denom = dot_product(ray->direction, n);
if (fabsf(denom) < 1e-6f)
	return ("pas d'intersection");
```

Il est temps de trouver notre "t"! Ici, il s'obtient par un dot product de, en premier vecteur, la distance entre l'origine du rayon et les coordonnées du plan, et en deuxième vecteur, de la normale. Ce dot product est ensuite divisé par ``denom``.
On vérifie si le ``t`` est compris dans les bornes ``tmin`` et ``tmax``: si ce n'est pas le cas, il n'y a pas d'intersection.

Voici un exemple de comment le coder:
```
float	t = dot_product(vector_minus_vector(ray->origin, plane->coord), n) / denom;
if (t < tmin || t > tmax)
	return ("pas d'intersection");
```

Plus qu'à faire nos derniers calculs, ceux qui nous informent sur le point d'impact. Nous avons déjà la normale ``n`` et le ``t``, ainsi que la forme touchée et sa couleur, reste à trouver le ``hit_vector``. Pour cela, on utilise le même calcul que pour celui de la sphère.

Comme pour la sphère, on lance la fonction qui calculera la couleur finale du point, en fonction de s'il y a eu intersection ou non, si oui avec quelle forme. Et voilà! Vous voyez le plan? 


### Cylindre
Bon. Si vous aviez de la peine à suivre jusqu'ici, il va falloir s'accrocher. Basiquement, on va réutiliser des parts des calculs de la sphère et du plan, dans un ensemble de nouveaux calculs qui font un peu mal à la tête.

Déjà, vu qu'un cylindre a, en quelques sortes, deux formes en une, on va devoir appliquer une formule pour la partie "tuyau" et une autre pour la partie "capsule", qui, au nombre de deux, ferment chaque côté du tuyau. Deux formules pour le prix d'une! On a vraiment gardé le meilleur pour la fin.

Une chose importante à savoir est que les coordonnées du cylindre correspondent au centre de la capsule A. Il est cependant recommandé de commencer par vérifier le tuyau, car cela permet une plus grande précision pour le calcul des capsules. En effet, si le rayon touche le tuyau, on peut réduire le ``tmax``.

#### Tuyau
Le calcul du tuyau utilise, comme la sphère, une fonction quadratique. En revanche, des calculs supplémentaires sont nécessaires afin d'envoyer les bons argument à cette fonction quadratique.

Plus précisément, c'est notre ``a``, notre ``half_b`` et notre ``c`` qui seront calculés à l'aide de 2 nouvelles variables, appelons-les ``dv``, ``xv``.

Tout d'abord, notre ``X`` se calcule de la même façon que pour la sphère, en soustrayant l'origine du rayon aux coordonnées du cylindre.

Ensuite, pour obtenir la valeur de ``xv``, calculons le dot product de ``X`` avec l'inclinaison du cylindre.

Enfin, pour obtenir la valeur de ``dv``, calculons le dot product de la direction du rayon et de l'inclinaison du cylindre.

Notre ``a`` prend alors la valeur du dot product d'un meme vecteur, à savoir la direction du rayon, moins notre ``dv`` au carre.

Notre ``half_b`` quant a lui prend la valeur du dot product de la direction du rayon et de ``X``, moins le produit de ``dv`` par ``xv``. 

Notre ``c`` de son côté prend la valeur du dot product d'une meme variable, à savoir X, moins xv au carre, moins le rayon du cylindre au carre.

Voici à quoi cela peut ressembler:
```
X = vector_minus_vector(cylinder->coord, ray->origin);

dv = dot_product(ray->direction, normalize(cylinder->incline));
xv = dot_product(X, normalize(cylinder->incline));

a = dot_product(ray->direction, ray->direction) - (dv * dv);
half_b = dot_product(ray->direction, X) - (dv * xv);
c = dot_product(X, X) - (xv * xv) - (cylinder->diameter * 0.5f) * (cylinder->diameter * 0.5f);
```

Ensuite, tout comme pour la sphère, nous calculons un discriminant (``discr``) de la même manière, et nous en servons également pour vérifier s'il y n'a pas d'intersection, à la différence que la condition est double: soit le discriminant est inférieur à zéro, soit ``a`` est égal à 0 (ce qui voudrait dire que le rayon est parallèle à l'axe du cylindre et ne touchera donc jamais le tuyau).

Voici un exemple de code:
```
discr = half_b * half_b - a * c;
if (discr < 0.0f || a == 0.0f)
	return ("pas d'intersection");
```

Il nous manque encore notre ``squareroot``, obtenue de la même manière que pour la sphère.
```
squareroot = sqrtf(discr);
```

Toujours sur la même lancée, nous calculerons aussi deux valeurs pour ``t``, une fois en soustrayant ``squareroot``, et l'autre en l'additionnant:
```
t1 = (-half_b - squareroot) / a;
t2 = (-half_b + squareroot) / a;
```

Cependant, au lieu de tester t2 uniquement si t1 est en-dehors des bornes comme pour la sphère, on va cette fois vérifier si t1 puis t2 sont soit l'une soit les deux dans les bornes, et si c'est le cas, on fera pour chaque ``t`` une seconde vérification qui nécessite au préalable le calcul d'une nouvelle variable, ``m``.

La valeur de celle-ci s'obtient en additionnant ``xv`` au produit de ``dv`` et ``t``:
```
m = dv * t + xv;
```

BON. On a nos t. Cette fois, au lieu de vérifier si on est en-dehors des bornes, on va vérifier si on est dedans, et si notre m est valable: plus grand ou égal à zéro, ET plus petit ou égal à la hauteur du cylindre. S'il est valable, on calcule le ``hit_vector`` comme précédemment, puis sa normale. Cette dernière se calcule différemment de celle de la sphère, et nécessite des variables supplémentaires, appelons-les ``tmp1`` et ``tmp2``.

``tmp1`` s'obtient en soustrayant les coordonnées du cylindre au hit vector. ``tmp2`` correspond à la scale de l'inclinaison normalisée du cylindre par ``m``. La normale, enfin, est calculée par la normalisation de la soustraction de ``tmp2`` à ``tmp1``.

Une fois la normale obtenue, il ne nous reste plus qu'à faire en sorte de transmettre les informations nécessaires au calcul de la couleur du pixel. 

Si aucune intersection n'est trouvée, la fonction retourne l'équivalent de "le tuyau de ce cylindre n'est pas sur le chemin de ce rayon". ATTENTION: nous n'avons pas encore vérifié s'il y a intersection avec une ou les deux capsules!

Voici un exemple de comment le coder:
```
t_vector	tmp1;
t_vector	tmp2;
t_vector	n;
int			intersection = 0;

if (t1 >= tmin && t1 <= tmax)
{
	m = dv * t1 + xv;
	if (m >= 0.0f && m <= cylinder->height)
	{
		hit_vector = vector_plus_vector(ray->origin, scale(ray->direction, t1));
		tmp1 = vector_minus_vector(cylinder->coord, hit_vector);
		tmp2 = scale(normalize(cylinder->incline), m);
		n = normalize(vector_minus_vector(tmp1, tmp2));
		update_hit_information(t1, hit_vector, n, tmax);
		intersection = 1;
	}
}
if (t2 >= tmin && t2 <= tmax)
{
	m = dv * t2 + xv;
	if (m >= 0.0f && m <= cylinder->height)
	{
		hit_vector = vector_plus_vector(ray->origin, scale(ray->direction, t2));
		tmp1 = vector_minus_vector(cylinder->coord, hit_vector);
		tmp2 = scale(normalize(cylinder->incline), m);
		n = normalize(vector_minus_vector(tmp1, tmp2));
		update_hit_information(t2, hit_vector, n, tmax);
		intersection = 1;
	}
}
return (intersection);
```


#### Capsules
La formule pour vérifier si la capsule est sur le chemin du rayon est la même pour les deux capsules du cylindre, en revanche!! La normale utilisée pour le calcul change en fonction de quelle capsule il s'agit.

Basiquement, la normale est liée à l'inclinaison. Pour la capsule A, la normale est simplement égale à l'inclinaison normalisée, alors que pour la capsule B, à l'opposé du tuyau, la normale est égale à l'inclinaison * -1 normalisée, pour la rendre négative:
```
capA.n = normalize(cylinder->incline);
capB.n = normalize(scale(cylinder->incline, -1.0f));
```

Les deux capsules n'ont pas non plus le même centre, chacune se trouvant à un autre endroit dans notre monde en 3D. Le centre de la capsule A, comme vu plus haut, correspond en réalité à la position du cylindre. Celui de la capsule B, en revanche, se trouve à l'autre bout du tuyau: il nous faut donc nous déplacer du centre de la capsule A dans la direction de l'inclinaison du cylindre, pendant la hauteur du cylindre.

Voici à quoi le code peut ressembler:
```
capA.center = cylinder->coord;
capB.center = vector_plus_vector(capA.center, scale(cylindre->incline, cylindre_height));
```

Une fois ces précisions apportées, vous pouvez lancer la même fonction pour les deux capsules.

Comme pour le plan, nous avons besoin d'un "denom", et de la même vérification "est-ce que le rayon est parallèle ou coplanaire à la capsule" (si oui, pas d'intersection).

De même, nous calculons le "t" avec la même méthode que pour le plan, et faisons la même vérification "est-ce que le ``t`` est en-dehors des bornes" (si oui, pas d'intersection). Pour rappel, si nous avons précémment touché le tuyau, le ``tmax`` a été changé en conséquence.

Toujours sur la même lancée, nous calculons le ``hit_vector`` de la même manière que pour la sphère et le plan.

Il nous reste encore un test, car pour l'instant, nous avons les mêmes calculs que pour le plan, or, notre capsule ne s'étend pas à l'infini dans toutes les directions depuis son point d'origine! On vérifie alors si le carré de la distance entre le centre de la capsule et le point d'impact est plus grand que le rayon du cylindre au carré.

Voici un exemple de comment le coder:
```
if (dot_product(vector_minus_vector(cap->center, hit_vector)) > (cylinder->diameter * 0.5f) * (cylinder->diameter * 0.5f))
	return ("pas d'intersection");
```

A nouveau, assurez-vous d'envoyer toutes les informations nécessaires à votre fonction qui calculera la couleur finale du pixel, en fonction de quelle forme a été touchée ou non et de son emplacement par rapport à la lumière.

## Calcul de la couleur
Hé mais c'est qu'on a pas mal avancé là! Cependant, nous n'en avons pas terminé. Il nous reste un concept important à voir, ainsi que quelques calculs supplémentaires.

En effet, pour continuer, nous avons besoin de trois informations:
- s'il y a plusieurs points d'impacts sur un même rayon, quel est celui le plus proche de la camera?
- y a-t-il une forme forme entre le point d'impact le plus proche et la lumiere? Si oui, le pixel sera noir.
- sinon, à quelle distance de la lumiere se trouve le point d'impact le plus proche? En fonction de la distance, la couleur du pixel sera plus ou moins claire ou foncée.

### Le t le plus proche
Tout d'abord, assurez-vous que votre programme compare le "t" de chaque nouvelle intersection d'un même rayon, et n'en garde que le plus proche! En effet, un même rayon peut traverser une sphere, et donc la toucher à deux endroits: vous n'allez représenter sur votre fenêtre que le point d'entrée, et non celui de sortie! De même, un même rayon peut traverser un plan puis un cylindre placé derriere lui par exemple, et à nouveau, vous n'êtes interessé-e que par le premier point de contact.

### Calcul de la lumiere
En gros, pour calculer la lumiere, nous allons réutiliser les mêmes fonctions que tout à l'heure, mais avec le point d'impact comme origine du rayon (au lieu de la position de la camera), et la lumiere comme direction (au lieu du pixel).

Eh oui, pour chaque point d'impact conservé (le plus proche), il va falloir à nouveau relancer autant de fonctions "est-ce que cette sphere/ce cylindre/ce plan se trouve sur le chemin de ce rayon" qu'il y a de formes annoncées par la map, à l'exception, pour éviter des erreurs d'affichage liées aux imprécisions des floats, de la forme de laquelle part notre nouveau rayon.

Comme dit plus haut, si le rayon rencontre une autre forme, le pixel sera noir. Dans votre canevas, a l'emplacement du pixel concerne, enregistrez le code couleur "".

Sinon, lancez le calcul de modulation de la couleur.

