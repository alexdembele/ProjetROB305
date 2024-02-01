#include <cstring>
#include <iostream>
#include <cstdlib>
void incr(unsigned int nLoops, double* pCounter)
{
    for(unsigned int u=0; u< nLoops; u++)
    {
        *pCounter+=1;
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <nombre_entier>" << std::endl;
        return 1;
    }

    // Convertir l'argument en entier
    unsigned int nLoops = (unsigned int)std::atoi(argv[1]);
    
    double counter = 0;

    incr(nLoops, &counter);
    std::cout << "Valeur finale du counter : " << counter << std::endl;

    return 0 ;
}