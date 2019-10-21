//
// Created by jose on 10/16/19.
//

#include <iostream>
#include <fstream>
#include <string>
#include "qfile.h"
#include "QTextStream"
#include "qlist.h"
#include "Persona.h"
#include"string"
#include "QRandomGenerator"
#include "qdebug.h"

//Esto debe de utilizarse para la generacion de archivos
void escribirArchivo(std::string nombreArchivo){
    std::ofstream myfile;
    myfile.open (nombreArchivo);
    myfile << "NO me dejare vencer no los dejare llevarme.\n NUnca nadie meva a dominar no yo voy a pelear";
     //aqui solo le ponemos la variable ocn todo el texto ya construido
    myfile.close();
}

void leerArchivo(QString nombreArchivo){
    QString datosRecolectados[999];
    QFile file(nombreArchivo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))  return ;
    QTextStream inputFile(&file);
    qDebug()<<"EStoy con el archivo: "+nombreArchivo;
    int contador = 0;
    while (!inputFile.atEnd()) {
        QString linea = inputFile.readLine();
        datosRecolectados[contador] = linea;
        contador++;
    }
    contador=0;
    while(contador<100){
        int platoAleatorio = QRandomGenerator::global()->bounded(1, 10);
        qDebug()<<datosRecolectados[platoAleatorio];
    }
//
}
