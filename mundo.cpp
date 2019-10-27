#include "mundo.h"

//Agregar metodo para enviar correos

Mundo::Mundo()
{
    //Nulos y ceros
    generacion = 0;
    arbolMundo = new AVL<Persona>();
    listaPersonasTotales = new ListaDoble<Persona>();

    //El metodo lee el archivo, extrae y coloca directamente en los arrays la informacion
    leerArchivo(":/Archivos/Paises.txt",paises);
    leerArchivo(":/Archivos/Apellidos.txt",apellidos);
    leerArchivo(":/Archivos/Creencias.txt",creencias);
    leerArchivo(":/Archivos/NombresH.txt",nombresHombres);
    leerArchivo(":/Archivos/NombresM.txt",nombresMujeres);
    leerArchivo(":/Archivos/Profesiones.txt",profesiones);
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
    Deportes * deportes = new Deportes();
    Persona * nuevaPersona = new Persona();

    //Genero
    if(QRandomGenerator::global()->bounded(0,1) == 0) nuevaPersona->genero = "mujer";
    else nuevaPersona->genero = "hombre";

    //IDs
    nuevaPersona->ID = QString::number(registroIds->generarId());

    //Lectura de archivos
    nuevaPersona->pais = paises[QRandomGenerator::global()->bounded(rangoPaises1,rangoPaises2)];
    nuevaPersona->creencia = creencias[QRandomGenerator::global()->bounded(rangoCreencias2,rangoCreencias2)];
    nuevaPersona->apellido = apellidos[QRandomGenerator::global()->bounded(rangoApellidos1,rangoApellidos2)];
    nuevaPersona->profesion = profesiones[QRandomGenerator::global()->bounded(rangoProfesiones1,rangoProfesiones2)];
    if(nuevaPersona->genero == "mujer") nuevaPersona->nombre = nombresMujeres[QRandomGenerator::global()->bounded(rangoNombres1,rangoNombres2)];
    else nuevaPersona->nombre = nombresHombres[QRandomGenerator::global()->bounded(rangoNombres1,rangoNombres2)];

    //Acciones, edades y deportes
    nuevaPersona->fechaNacimiento = new FechaNacimiento();
    nuevaPersona->edad = longevidad->obtenerEdad(nuevaPersona);
    deportes->generarDeportes(nuevaPersona);
    hacerBuenasAcciones(nuevaPersona);
    hacerlesPecar(nuevaPersona);

    //Finalmente se agrega a la listaPrincipal del mundo
    listaPersonasTotales->insertar(nuevaPersona);

}
void Mundo::asignarFamilia(Persona* persona){
    int cantAmigos = QRandomGenerator::global()->bounded(0,51);
    Persona * tmp = listaPersonasTotales->primerNodo->dato;
    //agregarMetodo de moverse x nodos en la lista para seleccionar gente random

    for(int i = 0 ;i<cantAmigos;i++){
        if(persona->pais  == tmp->pais){
            tmp->amigos->append(tmp);
        }
    }
}
void Mundo::asignarAmigos(Persona* persona){
    int cantAmigos = QRandomGenerator::global()->bounded(0,51);
    Persona * extrano = listaPersonasTotales->primerNodo->dato;
    //agregarMetodo de moverse x nodos en la lista para seleccionar gente random

    int cont = 0;
    while(cont<cantAmigos){
        if(!persona->amigos->contains(extrano)){
            if(persona->pais  == extrano->pais){
                persona->amigos->append(extrano);
                cont++;
            }
            else if(QRandomGenerator::global()->bounded(1,100) <40){
                persona->amigos->append(extrano);
                cont++;
            }

            else {
                bool coinciden = false;
                QList<Persona*>  * amigosExtrano = extrano->amigos;
                QList<Persona*> * amigosPersona = persona->amigos;
                for(int i = 0;i<extrano->amigos->length();i++){
                    for(int j = 0;j<persona->amigos->length();j++ ){
                        if(amigosPersona[j] == amigosExtrano[i]){
                            coinciden = true;
                            return;
                        }
                        if(coinciden) return;
                    }
                }

                if(coinciden){
                    persona->amigos->append(extrano);
                    cont++;
                    coinciden = false;
                }
            }
        }
        continue;
    }
}

//METODO que permite irse a los nodos de un nivel.
void irANivel(Nodo<Persona> * root, int nivel){
    if (root == nullptr)
        return;
    if (nivel == 1) {
        //Aqui salva a los amigs de la fam
        root->dato.madre;
        root->dato.padre;
        root->dato.hijos;
    }
    else if (nivel > 1)
    {
        irANivel(root->left, nivel-1);
        irANivel(root->right, nivel-1);
    }
}

QString Mundo::thor(int nivel){
    Nodo<Persona> * root = arbolMundo->root;


    std::string textoLog = "";
    //Rellenar con lo que hace y meter a textoLog para que se cree al archivo
    return   escribirArchivo(textoLog);

}

QString Mundo::nebula(int IDCulpable){
    Persona * culpable = listaPersonasTotales->buscar(IDCulpable);
    //maybe llamar a un metodo secundario


    std::string textoLog = "";
    //Rellenar con lo que hace y meter a textoLog para que se cree al archivo
    return escribirArchivo(textoLog);
}

QString Mundo::antMan(){


    std::string textoLog = "";
    //Rellenar con lo que hace y meter a textoLog para que se cree al archivo
    return escribirArchivo(textoLog);
}

QString Mundo::ironMan(){
    //Recorre el arbol, pregunta si ya pasó por ese nodo. Si no, hace random y depende del resultado salva ese nodo y lo pone true.
    //Al terminar el proceso, restaura los valores de los nodos a false.


    std::string textoLog = "";
    //Rellenar con lo que hace y meter a textoLog para que se cree al archivo
    return escribirArchivo(textoLog);
}

QString Mundo::midnight(){

    std::string textoLog = "";
    //Rellenar con lo que hace y meter a textoLog para que se cree al archivo
    return escribirArchivo(textoLog);
}

QString Mundo::ebonyMaw(int IDCulpable){
    Persona * culpable = listaPersonasTotales->buscar(IDCulpable);  //modificar para que sea * menor


    std::string textoLog = "";
    //Rellenar con lo que hace y meter a textoLog para que se cree al archivo
    return escribirArchivo(textoLog);

}
QString Mundo::spiderMan(){

    std::string textoLog = "";
    //Rellenar con lo que hace y meter a textoLog para que se cree al archivo
    return escribirArchivo(textoLog);
}

QString Mundo::blackDwarf(){

    std::string textoLog = "ESto en teoria hizo el metodo y envio el correo/nConteste a sunuy";
    //Rellenar con lo que hace y meter a textoLog para que se cree al archivo
    return escribirArchivo(textoLog);
}

QString Mundo::corvusGlaive(){
    std::string textoLog = "";
    //Rellenar con lo que hace y meter a textoLog para que se cree al archivo
    return escribirArchivo(textoLog);
}


QString Mundo::escribirArchivo(std::string textoLog){

    //Creamos el objeto para leer el archivo
    std::ofstream herramientaArchivo;
    std::string nombreArchivo = "";

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
    nombreArchivo+=std::to_string(local_time->tm_hour);
    nombreArchivo+=std::to_string(local_time->tm_min);
    nombreArchivo+=std::to_string(1 + local_time->tm_sec);
    nombreArchivo+=".txt";

    herramientaArchivo.open (nombreArchivo);
    herramientaArchivo << textoLog;
    herramientaArchivo.close();


    //Convertimos de string a QString
    QString nombreArchivoMod = QString::fromStdString(nombreArchivo);
    return nombreArchivoMod;
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



