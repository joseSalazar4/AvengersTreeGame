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
#include "qdebug.h"

//Esto debe de utilizarse para la generacion de archivos
void escribirArchivo(std::string nombreArchivo){
    std::ofstream myfile;
    myfile.open (nombreArchivo);
    myfile << "Writing this to a file.\n"; //aqui solo le ponemos la variable ocn todo el texto ya construido
    myfile << "NO me dejare vencer no los dejare llevarme.\n NUnca nadie meva a dominar no yo voy a pelear";
    myfile.close();
}

void leerArchivo(QString nombreArchivo){
    QFile file(nombreArchivo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))  return;
    QTextStream inputFile(&file);
    qDebug()<<"EStoy con el archivo: "+nombreArchivo;
    while (!inputFile.atEnd()) {
        QString linea = inputFile.readLine();
        //lista->insertarFinal(linea)

    //Ahora esto se adapta para leer los archivos y separarlo en funciones...
    //... que asignen a las listas de personas nombres y profeciones bla bla
    }
}
