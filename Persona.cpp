//
// Created by jose on 10/16/19.
//
#include"Persona.h"
//Esto debe de utilizarse para la generacion de archivos
QString Persona::escribirArchivo(){

    //Creamos el objeto para leer el archivo
    std::ofstream myfile;
    std::string nombreArchivo;

    //Pedimos el tiempo de la compu
    const time_t current = time(nullptr);
    tm *local_time = localtime(&current);
    
    //Construimos el nombre del archivo
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

    //Armamos el cuerpo del archivo aunque no creo que este metodo lo haga pero aca
    //se muestra como se hace
    myfile.open (nombreArchivo);
    myfile << "NO me dejare vencer no los dejare llevarme.\n NUnca nadie meva a dominar no yo voy a pelear SEEEEEEH";
     //aqui solo le ponemos la variable ocn todo el texto ya construido
    myfile.close();

    //Convertimos de string a QString
    QString nombreArchivoMod = QString::fromStdString(nombreArchivo);
    return nombreArchivoMod;
}

void leerArchivo(QString nombreArchivo){
    //Este es el array statico que se generara al leer los 5 archivos tons esto debe ir en un
    //metodo que lea apellidos hombres mujeres y demas.
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
    //PODRIA RECIBIR UN PARAMETRO UN QSTRING ARRAY[] Y le metemos los valores a esa misma
    //Por lo que nos ahorramos pasos y ya el array que se paso queda completo.
}
