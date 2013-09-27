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

pthread_mutex_t lockTurn;

Fotocopiadora::Fotocopiadora()
{
    initAll();
}

/**
  Crea hilos de acuerdo a su id
  */
void Fotocopiadora::insertClient(int id){

    int thread_id = (int)syscall(__NR_gettid);

    if(id == 0){ // Se va a agregar un estudiante
        _StudentsQueue[_IdStudent] = thread_id;
        _IdStudent ++;
    }
    else{ // Se va a agregar un profesor
        _TeachersQueue[_IdTeacher] = thread_id;
        _IdTeacher ++;
    }

    createClient();
}

/**
  Clientes
  */
void *Client(void *arg){
    cout << "Serrgio"<< endl;
}

/**
  Se crean los clientes
  */
void createClient(){

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_t threadClient;
    pthread_create(&threadClient, &attr, &Client, NULL);
    sem_post(&semInitClient); // up

    pthread_join(threadClient, NULL);
}

/**
  Trabajador de la fotocopiadora q va a decidir cual cliente atender
  */
void trabajadorFotocopiadora(){

    while(1){
        sem_wait(&semInitClient); //Down
        Scheduller();
    }
}

void Scheduller(){
    pthread_mutex_lock(&lockTurn);

    pthread_mutex_unlock(&lockTurn);
}

/**
  Iniciar todos los párametros
  */
void Fotocopiadora::initAll(){

    _SizeClients = 20;
    _IdTeacher = 0;
    _IdStudent = 0;
    _TeachersQueue[_SizeClients];
    _StudentsQueue[_SizeClients];

    for(int i=0; i < _SizeClients; i++){
        _TeachersQueue[i] = 0;
        _StudentsQueue[i] = 0;
    }

    pthread_mutex_init(&lockTurn,NULL);
}
