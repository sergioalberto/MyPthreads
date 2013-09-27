#include "fotocopiadora.h"
#include <pthread.h>

Fotocopiadora::Fotocopiadora()
{

}

void createClient(){

}

void Fotocopiadora::initClients(){

    _SizeClients = 20;
    _TeachersQueue[_SizeClients];
    _StudentsQueue[_SizeClients];

    for(int i=0; i < _SizeClients; i++){
        _TeachersQueue[i] = 0;
        _StudentsQueue[i] = 0;
    }
}
