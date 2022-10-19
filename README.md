# Equations linéaires

**Collection d'algorithmes correspondants aux différentes méthodes de résolution de systèmes linéaires (Gauss, Jacobi, Gauss-Seidel). Joint à ce projet un compte-rendu rédigé en LaTeX, disponible au format PDF.**

*Ce projet est réalisé dans le cadre du cours d'Application en Ingénierie et Programmation Numérique dispensé à l'UCA en 2ème année d'Informatique.*

**Syntaxe d'appel du programme:**

Une fois le programme complié, voici la syntaxe afin de l'exécuter:

./tp [méthode_de_résolution] (det)

avec pour les méthodes de résolution: 
- G: Méthode Gauss
- J: Méthode Jacobi
- GS: Méthode Gauss-Seidel

et (det) un argument optionnel permettant de faire appel à la version détaillé de la méthode 

*(gcc: pensez à bien utiliser l'argument -lm lors de votre compilation => utilisation de la fonction sqrtf())*

**Mode détaillé:**

Crée trois fichiers .log afin de retracer/analyser les opérations effectuées par les méthodes mais également de suivre l'évolution de la matrice/du vecteur au fur et à mesure de l'avancée de l'algorithme. Ces trois fichiers sont situés dans le sous-répertoire *bin/*.

**Lien du Dépot GitHub**

https://github.com/LaiPe/equations-lineaires
