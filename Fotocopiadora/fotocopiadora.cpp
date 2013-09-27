#include "fotocopiadora.h"

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<linux/unistd.h>
#include<sys/syscall.h>
#include <unistd.h>

#include <QString>
#include <iostream>
#include <getopt.h>

using std::cout;
using std::endl;
sem_t semInitClient;
sem_t semEndClient;

pthread_mutex_t lockTurn;
int _Turno;

int _SizeClients;     // Cantidad maxima de clientes permitidos para cada fila
int _TeachersQueue[20]; // Cola de profesores
int _IdTeacher;       // Id del profesor que esta atendiendo
int _StudentsQueue[20]; // Cola de estudiantes
int _IdStudent;       // Id del estudiante que esta atendiendo

Fotocopiadora::Fotocopiadora()
{
    _Turno = 0;
}

/**
  Crea hilos de acuerdo a su id
  */
void Fotocopiadora::insertClient(int id, int number){

    createClient(id, number);
}

/**
  Clientes
  */
void *Client(void *arg){

    while(1){
        //cout <<" sergio "<< endl;
    }
}

/**
  Se crean los clientes"
  */
void createClient(int id, int number){

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_t threadClient[number];

    for (int i=0; i < number; i++){

        int thread_id = (int)syscall(__NR_gettid);

        if(id == 0){ // Se va a agregar un estudiante
            _StudentsQueue[_IdStudent] = thread_id;
            //cout <<thread_id<< endl;
            _IdStudent ++;
        }
        else{ // Se va a agregar un profesor
            _TeachersQueue[_IdTeacher] = thread_id;
            //cout <<thread_id<< endl;
            _IdTeacher ++;
        }

        pthread_create(&threadClient[i], &attr, &Client, NULL);
        sem_post(&semInitClient); // up
    }
    //pthread_join(threadClient, NULL);
}

/**
  Trabajador de la fotocopiadora q va a decidir cual cliente atender
  */
void *trabajadorFotocopiadora(void *arg){

    while(1){
        sem_wait(&semInitClient); //Down
        Scheduller();
        sem_wait(&semEndClient);
    }
}

/**
  Se crea el trabajador de la fotocopiadora
  */
void createWork(){
    pthread_attr_t attrr;
    pthread_attr_init(&attrr);
    pthread_t threadWork;
    pthread_create(&threadWork, &attrr, &trabajadorFotocopiadora, NULL);
    pthread_join(threadWork, NULL);
}

/**
  Planificador de cual cliente atenter
  */
void Scheduller(){
    pthread_mutex_lock(&lockTurn);

    pthread_mutex_unlock(&lockTurn);
}


void printerPaper(){

    sem_post(&semEndClient); //Up
    pthread_exit(NULL);
}


/**
  Iniciar todos los párametros
  */
void Fotocopiadora::initAll(){

    _SizeClients = 20;
    _IdTeacher = 0;
    //_IdStudent = 0;
    //_TeachersQueue[_SizeClients];
    //_StudentsQueue[_SizeClients];

    for(int i=0; i < _SizeClients; i++){
        _TeachersQueue[i] = 0;
        _StudentsQueue[i] = 0;
    }

    insertClient(0,3);

    //pthread_mutex_init(&lockTurn,NULL);
    //createWork();

}
