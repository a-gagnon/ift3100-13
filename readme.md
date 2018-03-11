IFT-3100-13

Setup:
Les librairies externes prennent beaucoup de place.
Il faut aller chercher la librairie openFrameworks sur http://openframeworks.cc . Télécharger la version 0.9.8 pour Windows/Visual Studio 2015. Ensuite, l'extraire dans le dossier /src/libs/.

Afin de compiler notre projet, il est nécessaire d’avoir Visual Studio 2015 (ou plus récent), et d’avoir le Platform toolset Visual Studio 2015(v140).  Puisque nous utilisons GitHub et qu’ils ont certaines restrictions quant à la taille maximale de fichiers, il est nécessaire d’ajouter manuellement la librairie openFrameworks dans l’arborescence de notre code source. Nous utilisons la version 0.9.8, disponible sur http://openframeworks.cc  dans la section des téléchargements. Une fois téléchargé, il suffit d’extraire le contenu et le mettre dans le dossier /src/libs/. Si tout a été fait correctement, le chemin suivant devrait être valide :
src/libs/of_v0.9.8_vs_release/libs/openFrameworksCompiled/project/vs
Une fois cette étape terminée, il faut tout simplement ouvrir la solution Visual Studio située dans le répertoire Workspace. À l’intérieur de l’application, il est très important de vérifier que la compilation se fait avec la stratégie x86 en débug. Compiler le projet intitulé « ProjetEquipe13 ». Dans la séquence, celui-ci va aussi compiler le projet openFrameworks puisque notre projet a une dépendance directe sur celui-
