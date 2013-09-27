#ifndef FOTOCOPIADORA_H
#define FOTOCOPIADORA_H
#include <pthread.h>
#include<semaphore.h>

class Fotocopiadora
{

    public:
        Fotocopiadora();

        void initAll();
        void insertClient(int id);



        int _SizeClients;     // Cantidad maxima de clientes permitidos para cada fila
        int _TeachersQueue[]; // Cola de profesores
        int _IdTeacher;       // Id del profesor que esta atendiendo
        int _StudentsQueue[]; // Cola de estudiantes
        int _IdStudent;       // Id del estudiante que esta atendiendo
};

void *Client();
void createClient();
void Scheduller();

#endif // FOTOCOPIADORA_H
