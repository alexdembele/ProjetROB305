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
