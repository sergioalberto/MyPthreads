#include "fotocopiadora.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include <iostream>

using std::cout;
using std::endl;
sem_t semInitClient;
sem_t semEndClient;
sem_t lockTurn;

int _Turno;   // Cual hilo se esta atendiendo
int _IdThread; // Id glogal de hilos
int _SizeClients;     // Cantidad maxima de clientes permitidos para cada fila
int _TeachersQueue[20]; // Cola de profesores
int _IdTeacher;       // Id del profesor que esta atendiendo
int _StudentsQueue[20]; // Cola de estudiantes
int _IdStudent;       // Id del estudiante que esta atendiendo

Fotocopiadora::Fotocopiadora()
{
    _Turno = 1000;
    _IdThread = 0;
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

    int message;
    message = (int) arg;

    while(1){
        //cout <<message<< endl;
        //if (message == 1)
        printf("");

        if(_Turno == message){
            printerPaper(message);
        }
    }
    //return (void*)(1);
}


/**
  Imprime lo q el cliente quiera
  */
void *printerPaper(int id){

    printf("Imprimiendo %d ...\n", id);

    //sleep(1);
    //sem_post(&semEndClient); // Up
    sem_post(&semEndClient); // up -> aporta tickets
    pthread_exit(NULL);
    //return (void*)(1);
}


/**
  Se crean los clientes"
  */
void createClient(int id, int number){

    //pthread_attr_t attr;
    //pthread_attr_init(&attr);

    pthread_t threadClient[number];

    for (int i=0; i < number; i++){

        if(id == 0){ // Se va a agregar un estudiante
            _StudentsQueue[_IdStudent] = _IdThread;
            _IdStudent ++;
        }
        else{ // Se va a agregar un profesor
            _TeachersQueue[_IdTeacher] = _IdThread;
            _IdTeacher ++;
        }

        pthread_create(&threadClient[i], NULL, &Client, (void*) _IdThread);
        _IdThread ++;
        //pthread_detach(threadClient[i]);
    }

    //for(int i=0; i < number; i++){
      //  pthread_join(threadClient[i], NULL);
    //}
}

/**
  Trabajador de la fotocopiadora q va a decidir cual cliente atender
  */
void *trabajadorFotocopiadora(void *arg){

    while(1){
        //printf("Scheduler ...");
        sem_wait(&semInitClient); //Down -> pide tickets, sino se durme
        Scheduller();
        sem_post(&semInitClient);
        sem_wait(&semEndClient);
    }
}

/**
  Se crea el trabajador de la fotocopiadora
  */
void createWork(){
    //pthread_attr_t attrr;
    //pthread_attr_init(&attrr);
    pthread_t threadWork;
    pthread_create(&threadWork, NULL, &trabajadorFotocopiadora, NULL);

    //pthread_join(threadWork, NULL);
}

/**
  Planificador de cual cliente atenter
  */
void Scheduller(){
    sem_wait(&lockTurn);
    if (_Turno == 1000){
        _Turno = 0;
    }
    else{
        _Turno ++;
    }
    sem_post(&lockTurn);
}

/**
  Iniciar todos los párametros
  */
void Fotocopiadora::initAll(){

    _SizeClients = 20;
    _IdTeacher = 0;
    _IdStudent = 0;
    _IdThread = 1;
    _Turno = 1000;

    //_TeachersQueue[_SizeClients];
    //_StudentsQueue[_SizeClients];

    for(int i=0; i < _SizeClients; i++){
        _TeachersQueue[i] = 0;
        _StudentsQueue[i] = 0;
    }

    sem_init(&lockTurn,0,1);
    sem_init(&semInitClient,0,1);
    sem_init(&semEndClient,0,1);

    //
    createWork();

    //insertClient(0,4);
    //pthread_mutex_destroy(&lockTurn); // Desinicializa el mutex

}
