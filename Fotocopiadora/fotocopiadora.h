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

void *Client(void *arg);
void *trabajadorFotocopiadora();
void createClient(int id, int number);
void Scheduller();
void createWork();
void *printerPaper(int id);

#endif // FOTOCOPIADORA_H
