# TD1D

***Compilation*** 

Dans le dossier build : g++ ../projetROB305/TD1d/*.cpp -lrt -lpthread 

***Exécution***  
Dans le dossier build : ./a.out 

***Rendu des TDs***

    Le TD1d a pour but une régression linéaire. On estime que la valeur finale du compteur est fonction affine du temps l(t) = a * t + b. 
    On cherche donc a estimer a et b à partir de plusieurs mesures. Ici, on ne prends que 2 points de mesures avec des exécutions de 4s et 6s.
    On constate que la calibration n'est pas correcte, elle est souvent sous estimé (on veut un temps d'exécution de 5s et on obtient un temps de 4+s). 2 points de mesures ne sont donc pas suffisant. Pour effctuer cette la mesure des points on fait tourner en boucle un compteur et on le stop avec un booléen pStop qui doit être globale et volatile. 

    
   




