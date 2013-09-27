#ifndef FOTOCOPIADORA_H
#define FOTOCOPIADORA_H
#include <pthread.h>
#include<semaphore.h>

class Fotocopiadora
{

    public:
        Fotocopiadora();

        void initAll();
        void insertClient(int id, int number);




};

void *Client();
void *trabajadorFotocopiadora();
void createClient(int id, int number);
void Scheduller();
void createWork();

#endif // FOTOCOPIADORA_H
