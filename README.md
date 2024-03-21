# ProjetROB305

***Auteur***
Alex Dembélé

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

- Timer.cpp contient les méthodes de la classe Timer  

- Mutex.cpp contient une classe reprenant les fonctionnalités des Mutex Posix et des classes dérivés permettant de supervisé et locké les mutex.  Il y a aussi une implémentation de la clsse Sémaphore

- PosixThread.cpp contient les méthodes reprenant les fonctionnalités des Thread Posix . (Elle n'a pas l'air fonctionnelle sur les temps d'exécution)

- p_thread.cpp est une implémentation basique d'un thread en parallèle.  

- cpuTest.cpp implémente une sorte de multi-threading avec ou sans mutex. 

- TD1a.cpp fait une série de test basique sur les fonctions sur les timespecs.

- TD1b.cpp implémente un simple compteur avec une fréquence 2Hz avec posix.

- TD3a.cpp test la classe Chrono et permet de le faire sur une mesure de 1s. 

- TD3b.cpp implémente un test de la classe Timer sur un compteur décrémental.

- TD4a.cpp implémente des tests sur la classe Thread. On remarque avec ce code qu'il y a un problème.

- TD4b.cpp reprend cpuTest.cpp mais avec nos classe de Mutex

- TD4c.cpp implémente un test simple d'échange de jeton avec la classe Sémaphore

***Execution code***

- TD3b.cpp : "./nom_du_fichier (int : nombre_de_seconde)" il est possible de spécifier le nombre de seconde du decompte, il est à 10 par défaut  

- p_thread.cpp : "./nom_du_fichier"

- cpuTest.cpp : "./nom_du_fichier   int : compteur    int : nombre_de_thread    (char : "protected")" il faut écrire exactement protected pour activer le mutex

- TD4b.cpp : comme cputest.cpp

- Tous les autres TD**.cpp : "./nom_du_fichier"
  

  


***Rendu des TDs***
- TD1a.cpp correspond au TD1a 

    Les méthodes sur les timespec sont utilisés dans tous les autres programmes pour traiter les temps posix.
    Pour tester ces méthodes, il suffit d'exécuter TD1a.cpp, si aucune annonce d'erreur d'assertion est affiché dans le terminal et qu'il est marqué que tous les tests ont réussis, alors les fonctions passent les tests avec succès.

- TD1b correspond au TD1b

    On lance un thread posix qui compte jusqu'à 15 et la gestion du temps est simplifié grâce aux fonctions sur les timespecs.



 
- cpuTest.cpp correspond au TD1c et TD2a/b

    Pour le TD1c on exécute le code avec 1 thread. A chaque fois, le compteur atteint la valeur attendu. 
    Pour le TD2a/b on exécute le code avec plusieurs threads et en activant ou non le mutex. On constate que sans mutex le compteur n'atteint pas la valeur attendu. Cela s'explique par l'accès concurrent de plusieurs thread à la même variable partagé, sans protection. Si on demande à p threads de compter jusqu'à n chacun sur le même compteur, on s'attends à obtenir p*n comme valeur final, cependant cette valeur est bien inférieur en pratique. Par exemple, poiur p = 3 et n = 10000 on obtient une valeur finale entre 11000 et 16000 ce qui est loin de 30000. C'est pour résoudre ce problème qu'on utilise un mutex. 
    En utilisant le mutex, on a la bonne valeur finale pour le compteur. Cependant, le temps d'exécution s'allonge considérablement. Par exemple, pour p = 3 et n = 10000, on passe de 1ms à 27 ms, presque un facteur 30 ! Cette explosion du temps d'exécution vient de la mise en attente des threads pour accéder à la variable partagée et au passage du mutex entre les threads.

- TD3a correspond au TD3a 

    On test simplement si le chronomètre fonction bien en mettant en pause le thread principal pendant une durée donnée et en mesurant cette durée avec le chronomètre.

- TD3b correspond au TD3b. 
    
    Les constructeurs et destructeurs ainsi que les méthodes start et stop doivent pouvoir être utilisé en dehors de la classe donc ils sont publics. La méthode callback ne doit être accessible uniquement par la classe et ses dérivés donc c'est protected. La méthode call_callback ne peut être appelé que dans la classe donc elle est privé.  
    La méthode call_callback sert à activer callback lorque qu'un signal est reçu.
    La méthode callback et le destructeur peuvent être à redéfinir dans les classes dérivés de Timer, donc on les définis comme virtual.

- TD4a.cpp correspond au TD4a
    
    J'ai des seg fault dans le main, je pesne que c'est dû à des problèmes de définition et calcul de stop_time et start_time.En effet, quand j'affiche l'exec_time, j'obtiens 1e+17 ms, le stop_time doit être mal défini !

- TD4b.cpp correspond au TD4b

    J'ai repris le programme de cpuTest.cpp en remplaçant les Mutex avec ma propre classe. Le fonctionnement du programme est le même que cpuTest 

- TD4c.cpp correspond au TD4c

    J'ai programmé (avec GPT) un échange de jeton avec sémaphore. Comme ma classe Thread n'est pas forcément fonctionnelle, je ne l'ai pas utilisé ici. L'échange de jeton affiché dans le terminal semble bizzare mais à la fin on a le bon nombre de jeton !



    


