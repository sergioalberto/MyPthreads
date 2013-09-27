#ifndef FOTOCOPIADORA_H
#define FOTOCOPIADORA_H
#include <pthread.h>

class Fotocopiadora
{

    public:
        Fotocopiadora();

        void initAll();
        void insertClient(int id);
        void *Client();


        int _SizeClients;     // Cantidad maxima de clientes permitidos para cada fila
        int _TeachersQueue[]; // Cola de profesores
        int _IdTeacher;       // Id del profesor que esta atendiendo
        int _StudentsQueue[]; // Cola de estudiantes
        int _IdStudent;       // Id del estudiante que esta atendiendo
};

void createClient();

#endif // FOTOCOPIADORA_H
