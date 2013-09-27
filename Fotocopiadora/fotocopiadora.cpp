#include "fotocopiadora.h"

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<linux/unistd.h>
#include<sys/syscall.h>
#include <unistd.h>

#include <QString>
#include <iostream>
#include <getopt.h>

using std::cout;
using std::endl;

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

void *Client(void *arg){
    cout << "Serrgio"<< endl;
}

void createClient(){
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_t threadClient;
    pthread_create(&threadClient, &attr, &Client, NULL);

    pthread_join(threadClient, NULL);
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
}
