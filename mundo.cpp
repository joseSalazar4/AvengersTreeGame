#include "mundo.h"

//Agregar metodo para enviar correos

Mundo::Mundo()
{
    //Nulos y ceros
    generacion = 0;
    arbolMundo = new AVL<Persona>();
    listaPersonasTotales = new ListaDoble<Persona>();

    //El metodo lee el archivo, extrae y coloca directamente en los arrays la informacion
    leerArchivo("Apellidos.txt",apellidos);
    leerArchivo("Creencias.txt",creencias);
    leerArchivo("NombresH.txt",nombresHombres);
    leerArchivo("NombresM.txt",nombresMujeres);
    leerArchivo("Profesiones.txt",profesiones);
}

void Mundo::hacerlesPecar(Persona* persona){
    persona->pecadosTotales = 0;
    for(int j = 0; j<7;j++){
        persona->pecados[j]+= QRandomGenerator::global()->bounded(1,100);
        persona->pecadosTotales+= persona->pecados[j];
    }
}

//Tnto el metodo de arriba como el de abajo en window.cpp pero con un FOR

void Mundo::hacerBuenasAcciones(Persona* persona){
    persona->buenasAccionesTotales = 0;
    for(int j = 0; j<7;j++){
        persona->buenasAcciones[j]+= QRandomGenerator::global()->bounded(1,100);
        persona->buenasAccionesTotales+= persona->buenasAcciones[j];
    }
}

void Mundo::crearPoblacion(int cantSolicitada){
    //La mayor parte de las veces no sera la primera vez entonces preguntamos al inicio.
    for(int i = 0 ; i<cantSolicitada;i++){
        crearPersona();
    }

    if(generacion!=0){
        NodoDoble<Persona> * tmp = listaPersonasTotales->primerNodo;
        for(int i =0;i<listaPersonasTotales->largo;i++){
            asignarFamilia(tmp->dato);
            asignarAmigos(tmp->dato);
            tmp = tmp->siguiente;
        }
    }
    generacion++;
}

void Mundo::crearPersona(){
    Persona * nuevaPersona = new Persona();
    //Genero
    if(QRandomGenerator::global()->bounded(0,1) == 0) nuevaPersona->genero = "mujer";
    else nuevaPersona->genero = "hombre";

    //IDs
    nuevaPersona->ID = QString::number(registroIds->generarId());

    //Lectura de archivos
    nuevaPersona->pais = paises[QRandomGenerator::global()->bounded(0,99)];
    nuevaPersona->creencia = creencias[QRandomGenerator::global()->bounded(0,13)];
    nuevaPersona->apellido = apellidos[QRandomGenerator::global()->bounded(0,999)];
    nuevaPersona->profesion = profesiones[QRandomGenerator::global()->bounded(0,50)];
    if(nuevaPersona->genero == "mujer") nuevaPersona->nombre = nombresMujeres[QRandomGenerator::global()->bounded(0,499)];
    else nuevaPersona->nombre = nombresHombres[QRandomGenerator::global()->bounded(0,499)];

    //Acciones y edades
    nuevaPersona->fechaNacimiento = new FechaNacimiento();
    nuevaPersona->edad = longevidad->obtenerEdad(nuevaPersona);
    hacerBuenasAcciones(nuevaPersona);
    hacerlesPecar(nuevaPersona);
    listaPersonasTotales->insertar(nuevaPersona);

}
void Mundo::asignarFamilia(Persona* persona){
    int cantAmigos = QRandomGenerator::global()->bounded(0,51);
    NodoDoble<Persona> * tmp = listaPersonasTotales->primerNodo;
    //agregarMetodo de moverse x nodos en la lista para seleccionar gente random

    for(int i = 0 ;i<cantAmigos;i++){
        if(persona->pais  == tmp->dato->pais){
          tmp->dato->amigos->append(tmp->dato);
        }
    }

}
void Mundo::asignarAmigos(Persona* persona){
    int cantAmigos = QRandomGenerator::global()->bounded(0,51);
    NodoDoble<Persona> * tmp = listaPersonasTotales->primerNodo;
    //agregarMetodo de moverse x nodos en la lista para seleccionar gente random

    int cont = 0;
    while(cont<cantAmigos){
        if(persona->pais  == tmp->dato->pais){
          tmp->dato->amigos->append(tmp->dato);
          cont++;
        }
        else if(QRandomGenerator::global()->bounded(1,100) <40){
            tmp->dato->amigos->append(tmp->dato);
            cont++;
        }

        else {
            bool coinciden = false;
            Persona * tmp2 = tmp->dato->amigos->first();
            for(int i = 0;i<tmp->dato->amigos->length();i++){

                if(persona->amigos){

                    return;
                }
                tmp2; //recorrer ambas listas de los amimgos de uno y los de esa persona
                        //y econtrar similitudes

            }
            if(coinciden)
            cont++;
        }
    }
}

void Mundo::thor(){

}

void Mundo::nebula(int IDCulpable){
    Persona * culpable = listaPersonasTotales->buscar(IDCulpable);
    //maybe llamar a un metodo secundario
}

void Mundo::antMan(){

}

void Mundo::ironMan(){
    //Recorre el arbol, pregunta si ya pasó por ese nodo. Si no, hace random y depende del resultado salva ese nodo y lo pone true.
}            //Al terminar el proceso, restaura los valores de los nodos a false.

void Mundo::midnight(){

}

void Mundo::ebonyMaw(int IDCulpable){
    Persona * culpable = listaPersonasTotales->buscar(IDCulpable);  //modificar para que sea * menor

}
void Mundo::spiderMan(){

}

void Mundo::blackDwarf(){

}

void Mundo::corvusGlaive(){

}

void Mundo::leerArchivo(QString nombreArchivo, QString datosRecolectados[]){

    QFile file(nombreArchivo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))  return ;
    QTextStream inputFile(&file);

    int contador = 0;
    while (!inputFile.atEnd()) {
        QString linea = inputFile.readLine();
        datosRecolectados[contador] = linea;
        contador++;
    }
}

 QString Mundo::escribirArchivo(std::string textoLog){

    //Creamos el objeto para leer el archivo
    std::ofstream herramientaArchivo;
    std::string nombreArchivo;

    //Pedimos el tiempo de la compu
    const time_t current = time(nullptr);
    tm *local_time = localtime(&current);

    //Armamos el cuerpo del archivo aunque no creo que este metodo lo haga pero aca
    //se muestra como se hace
    herramientaArchivo.open (nombreArchivo);
    herramientaArchivo << textoLog;

    //aqui solo le ponemos la variable ocn todo el texto ya construido
    herramientaArchivo.close();

    //Construimos el nombre del archivo
    nombreArchivo+= std::to_string(1900 + local_time->tm_year);
    nombreArchivo+="-";
    nombreArchivo+=std::to_string(1 + local_time->tm_mon);
    nombreArchivo+="-";
    nombreArchivo+=std::to_string(local_time->tm_mday);
    nombreArchivo+="_";
    nombreArchivo+=std::to_string(local_time->tm_hour);
    nombreArchivo+=std::to_string(local_time->tm_min);
    nombreArchivo+=std::to_string(1 + local_time->tm_sec);
    nombreArchivo+=".txt";

    //Convertimos de string a QString
    QString nombreArchivoMod = QString::fromStdString(nombreArchivo);
    return nombreArchivoMod;
}




