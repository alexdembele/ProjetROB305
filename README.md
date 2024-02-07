# ProjetROB305

***Compilation*** 

Cloner ce projet dans un dossier
En parallèle de ce projet, créer un dossier build

cd ../  
mkdir build  
cd build  

Compiler les programmes dont vous avez besoins dans le build  
Compilation avec g++ ../projetROB305/(*).cpp -lrt -lpthread  

***Description des codes***

- timespec.cpp contient des méthodes pour gérer de manière plus pratique les temps timespec de posix. 

- Timer.cpp contient les méthodes de la classe Timer, il contient aussi un main pour tester le compteur décrémental.  

- p_thread.cpp est une implémentation basique d'un thread en parallèle.  

- cpuTest implémente une sorte de multi-threading avec ou sans mutex.

***Execution code***

- Timer.cpp : "./nom_du_fichier (int : nombre de seconde)" il est possible de spécifier le nombre de seconde du decompte, il est à 10 par défaut  

- p_thread.cpp : "./nom_du_fichier

- cpuTest.cpp : 
  

  


***Rendu des TDs***

- Timer.ccp/hpp correspondent au TD3b. 
    
        Les constructeurs et destructeurs ainsi que les méthodes start et stop doivent pouvoir être utilisé en dehors de la classe donc ils sont publics. La méthode callback ne doit être accessible uniquement par la classe et ses dérivés donc c'est protected. La méthode call_callback ne peut être appelé que dans la classe donc elle est privé.  
        La méthode call_callback sert à activer callback lorque qu'un signal est reçu.
        La méthode callback et le destructeur peuvent être à redéfinir dans les classes dérivés de Timer, donc on les définis comme virtual.

 
- cpuTest.cpp correspond au TD1c et TD2a/b

        Pour le TD1c on exécute le code avec 1 thread. A chaque fois, le compteur atteint la valeur attendu. 
        Pour le TD2a/b on exécute le code avec plusieurs threads et en activant ou non le mutex. On constate que sans mutex le compteur n'atteint pas la valeur attendu. Cela s'explique par l'accès concurrent de plusieurs thread à la même variable partagé, sans protection. Si on demande à p threads de compter jusqu'à n chacun sur le même compteur, on s'attends à obtenir p*n comme valeur final, cependant cette valeur est bien inférieur en pratique. Par exemple, poiur p = 3 et n = 10000 on obtient une valeur finale entre 11000 et 16000 ce qui est loin de 30000. C'est pour résoudre ce problème qu'on utilise un mutex. 
        En utilisant le mutex, on a la bonne valeur finale pour le compteur. Cependant, le temps d'exécution s'allonge considérablement. Par exemple, pour p = 3 et n = 10000, on passe de 1ms à 27 ms, presque un facteur 30 ! Cette explosion du temps d'exécution vient de la mise en attente des threads pour accéder à la variable partagée et au passage du mutex entre les threads. 

- timespec.cpp/hpp et timespecTest.cpp correspondent au TD1a 

        Les méthodes sur les timespec sont utilisés dans tous les autres programmes pour traiter les temps posix.
        Pour tester ces méthodes, il suffit d'exécuter timespecTest.cpp, si aucune annonce d'erreur d'assertion est affiché dans le terminal et qu'il est marqué que tous les tests ont réussis, alors les fonctions passent les tests avec succès.



    


