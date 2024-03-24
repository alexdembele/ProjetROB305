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
Compilation avec g++ ../projetROB305/TD__/*.cpp -lrt -lpthread  

Le dossier inc contient les headers, le dossier src contient les cpp associés aux headers pour les méthodes de classes. Les dossier TD__ contiennent tous les codes nécessaires pour réaliser un TD. Un même code est donc présent plusieurs fois dans ce repos, c'est pour des simplications de compilations. 

***Description des codes***

- -> Pour le code associé à un TD, lire le READ_ME associé

- timespec.cpp contient des méthodes pour gérer de manière plus pratique les temps timespec de posix. 

- Timer.cpp contient les méthodes de la classe Timer  

- Mutex.cpp contient une classe reprenant les fonctionnalités des Mutex Posix et des classes dérivés permettant de supervisé et locké les mutex.  Il y a aussi une implémentation de la classe Sémaphore.

- Fifo.hpp contient les méthodes pour la classe Fifo

- PosixThread.cpp contient les méthodes reprenant les fonctionnalités des Thread Posix . 

- Chrono.cpp contient les méthodes de la classe Chrono

- Inversion.cpp implémente une classe dérivé de Thread qui permettrait de tester l'inversion de priorité. 

- cpuLoop contient des codes pour les méthodes de Calibration de temps et d'exécution de boucle de comptage avec la classe Looper

- Les headers associés sont les .hpp dans le dossier inc


***Execution code***

- Pour exécuter un code, il faut en général faire ./a.out, certains TD nécessitent de rajouter des paramètres. Lorsque c'est le cas c'est précisé dans le README associé. 

  


