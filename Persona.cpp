//
// Created by jose on 10/16/19.
//
#include"Persona.h"
//Esto debe de utilizarse para la generacion de archivos
QString Persona::escribirArchivo(){
    std::ofstream myfile;
    std::string nombreArchivo;

    const time_t current = time(nullptr);
    std::cout << "Number of seconds elapsed since January 1, 1990:" << current << std::endl;
    tm *local_time = localtime(&current);
    
    nombreArchivo+= std::to_string(1900 + local_time->tm_year);
    nombreArchivo+="-";
    nombreArchivo+=std::to_string(1 + local_time->tm_mon);
    nombreArchivo+="-";
    nombreArchivo+=std::to_string(local_time->tm_mday);
    nombreArchivo+="_";
    nombreArchivo+=std::to_string(1 + local_time->tm_hour);
    nombreArchivo+=std::to_string(1 + local_time->tm_min);
    nombreArchivo+=std::to_string(1 + local_time->tm_sec);
    nombreArchivo+=".txt";


    myfile.open (nombreArchivo);
    myfile << "NO me dejare vencer no los dejare llevarme.\n NUnca nadie meva a dominar no yo voy a pelear SEEEEEEH";
     //aqui solo le ponemos la variable ocn todo el texto ya construido
    myfile.close();

    QString nombreArchivoMod = QString::fromStdString(nombreArchivo);

    qDebug()<<nombreArchivoMod;
    return nombreArchivoMod;
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
