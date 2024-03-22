# TD3B

***Compilation*** 

Dans le dossier build : g++ ../projetROB305/TD3b/*.cpp -lrt -lpthread 

***Exécution***  
Dans le dossier build : ./a.out (\<début décompte (int)>)

***Rendu des TDs***

    On test notre classe Timer en faisant un décompte, on peut choisir le début du décompte par paramètre. 
    Les constructeurs et destructeurs ainsi que les méthodes start et stop doivent pouvoir être utilisé en dehors de la classe donc ils sont publics. La méthode callback ne doit être accessible uniquement par la classe et ses dérivés donc c'est protected. La méthode call_callback ne peut être appelé que dans la classe donc elle est privé.  
    La méthode call_callback sert à activer callback lorque qu'un signal est reçu.
    La méthode callback et le destructeur peuvent être à redéfinir dans les classes dérivés de Timer, donc on les définis comme virtual.
    


    
   




