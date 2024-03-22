# TD2B

***Compilation*** 

Dans le dossier build : g++ ../projetROB305/TD2b/*.cpp -lrt -lpthread 

***Exécution***  
Dans le dossier build : ./a.out \<valeur finale du compteur (int)> \<nombre de thread> (\<protected>)

***Rendu des TDs***

    On améliore le TD2a en rajoutant un mutex pour protéger la variable partagé. On constate que lorsqu'on active le mutex, en rajoutant protected en paramètre, le compteur à bien la bonne valeur à la fin de l'exécution, mais le temps d'exécution est grandement augmenté à cause de la prise et le relâchement du mutex. 

    
   




