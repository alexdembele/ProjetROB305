# TD2A

***Compilation*** 

Dans le dossier build : g++ ../projetROB305/TD2a/*.cpp -lrt -lpthread 

***Exécution***  
Dans le dossier build : ./a.out \<valeur finale du compteur (int)> \<nombre de thread>

***Rendu des TDs***

    On reprends la fonction qui implémente un compteur, mais on va incrémenter ce compteur avec plusieurs thread. En exécutant le programme, on constate que la valeur finale du compteur n'est plus la valeur attendu et que le temps d'exécution est un tout petit pu plus lent. C'est normal, il y a un accès concurrent à la même variable ce qui cause des problèmes de cohérence. Par exemple, pour 3 tâches incrémentant le compteur chacune de 10 000 on s'attend à avoir 30 000 comme valeur finale mais on obtient en général environ 16 700. Cela souligne le problèeme d'accès conccurent.

    
   




