#include "mundo.h"

//Agregar metodo para enviar correos

Mundo::Mundo()
{
    //Nulos y ceros
    generacion = 0;
    arbolMundo = new AVL<Persona>();
    listaPersonasTotales = new ListaDoble<Persona>();
    rangoPaises1 = rangoPaises2 = rangoNombres1 = rangoNombres2
            = rangoApellidos1 = rangoApellidos2 = rangoCreencias1
            = rangoCreencias2 = rangoProfesiones1 = rangoProfesiones2 = 0;

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
    arbolMundo->imprimirArbol(); //Prueba

    for(int i = 0; i<9; i++){
        qDebug() << "       Rango "+QString::number(i);
        for(int j= 0; j<longevidad->tablaRangoEtario[i]->size(); j++){
            Persona * p = longevidad->tablaRangoEtario[i]->at(j);
            qDebug().noquote() << p->nombre + ": "+ QString::number(p->edad) + "\n";
        }
    }

    //Prueba de obtener persona random
    qDebug() << "Prueba de personas Random";
    for(int k=0; k<10; k++){
        Persona *pn= getPersonaRandom();
        qDebug().noquote() << pn->nombre + "\n";
    }
}

QString crearListaAmigosTxt(Persona * persona){

    QString listaTxt = "Amigos  [ ";
    for(int i = 0 ; i<persona->amigos->length();i++){
        listaTxt+=persona->amigos->at(i)->ID+"--";
        listaTxt+=persona->amigos->at(i)->nombre+", ";
    }
    listaTxt = " ]";
    return  listaTxt;
}

QString crearListaFamiliaTxt(Persona * persona){

    QString listaTxt = "Familia  [ ";
    for(int i = 0 ; i<persona->hijos->length();i++){
        listaTxt+=persona->hijos->at(i)->ID+"--";
        listaTxt+=persona->hijos->at(i)->nombre+", ";
    }
    listaTxt = " ]";
    return  listaTxt;
}

QString crearExperienciasTxt(Persona * persona){

    QString listaTxt = "Experiencias  [ ";
    for(int i = 0 ; i<persona->hijos->length();i++){
        listaTxt+="";
    }
    listaTxt = " ]";
    return  listaTxt;
}

void Mundo::crearPersona(){
    Persona * nuevaPersona = new Persona();

    //Genero
    if(QRandomGenerator::global()->bounded(0,1) == 0) nuevaPersona->genero = "mujer";
    else nuevaPersona->genero = "hombre";

    //IDs
    nuevaPersona->ID = QString::number(registroIds->generarId());

    //Lectura de archivos
    int n = QRandomGenerator::global()->bounded(rangoPaises1,rangoPaises2);
    nuevaPersona->pais = paises[n];
    nuevaPersona->creencia = creencias[QRandomGenerator::global()->bounded(rangoCreencias1,rangoCreencias2)];
    nuevaPersona->apellido = apellidos[QRandomGenerator::global()->bounded(rangoApellidos1,rangoApellidos2)];
    nuevaPersona->profesion = profesiones[QRandomGenerator::global()->bounded(rangoProfesiones1,rangoProfesiones2)];
    if(nuevaPersona->genero == "mujer") nuevaPersona->nombre = nombresMujeres[QRandomGenerator::global()->bounded(rangoNombres1,rangoNombres2)];
    else nuevaPersona->nombre = nombresHombres[QRandomGenerator::global()->bounded(rangoNombres1,rangoNombres2)];

    //Acciones, edades y deportes
    nuevaPersona->fechaNacimiento = new FechaNacimiento();
    nuevaPersona->edad = longevidad->obtenerEdad(nuevaPersona);
    nuevaPersona->deportes = deportes->generarDeportes(nuevaPersona);
    hacerBuenasAcciones(nuevaPersona);
    hacerlesPecar(nuevaPersona);

    //Finalmente se agrega a la listaPrincipal del mundo
    listaPersonasTotales->insertar(nuevaPersona);
    //Insertar en AVL Para prueba
    arbolMundo->insertar(nuevaPersona);
    qDebug() << "Nueva Persona";

}
void Mundo::asignarFamilia(Persona* persona){
    //Preguntar si estara soltero o en otro estado
    int estadoMarit = QRandomGenerator::global()->bounded(0,2);

    if(estadoMarit == 2) persona->estadoMarital = "Casad@";
    else if (estadoMarit == 1)persona->estadoMarital = "Separad@";
    else persona->estadoMarital = "Solter@";

    //Soltero es no tener hijos
    if(persona->estadoMarital == "Solter@") return;

    Persona * pareja = getPersonaRandom();
    while(pareja->pareja != nullptr && pareja->genero!=persona->genero){
        pareja = getPersonaRandom();
    }

    persona->pareja = pareja;

    //Si no tiene mas de 20 no es Joven y no puede tener hijos
    if(persona->edad< 20) return;

    int cantHijos = QRandomGenerator::global()->bounded(0,4);
    Persona * tmp = getPersonaRandom();
    //agregarMetodo de moverse x nodos en la lista para seleccionar gente random

    int cont = 0, contMax = 0;
    while(cont<cantHijos){
        //Preguntamos primero por verificar para no hacer las otras preguntas
        if(verificarValidezHijos(persona,tmp) && (persona->pais  == tmp->pais || persona->pareja->pais == tmp->pais)  &&
                (persona->apellido == tmp->apellido ||  persona->pareja->apellido == tmp->apellido)){

            tmp->amigos->append(tmp);
            cont++;
        }
        //Si no hay suficientes personas con ese apellido podria enciclarse entonces que busque un maximo de 30 000 personas
        if(contMax>30000) return;
        contMax++;
        tmp =  getPersonaRandom();
    }
}


//Permite saber si puede ser hijo o no
bool Mundo::verificarValidezHijos(Persona * supuestoPadre, Persona * supuestoHijo){

    int rangoPadre = 0 ,rangoHijo = 0;

    //Primero preguntamos si el padre no es ya hijo de su supuesto hijo
    bool esDigno = true;
    for(int i = 0;i<supuestoHijo->hijos->length();i++){
        if(supuestoPadre == supuestoHijo->hijos->at(i)) esDigno = false;
    }
    if(!esDigno) return esDigno;

    esDigno = false;

    //Revisar los rangos pero como?
    for(int i = 0;i<9;i++){ //recorrer rango etario y revisar si es muy joven o  muy viejo para ser su hijo
        if(longevidad->tablaRangoEtario[i]->contains(supuestoHijo))rangoHijo = i;
    }


    for(int i = 0;i<9;i++){ //recorrer rango etario y revisar si es muy joven o  muy viejo para ser su hijo
        if(longevidad->tablaRangoEtario[i]->contains(supuestoPadre))rangoPadre = i;
    }

    if(rangoPadre==5 && (rangoHijo == 0|| rangoHijo == 1)) return esDigno = true;
    else if(rangoPadre ==6 && (rangoHijo == 0 || rangoHijo ==1 || rangoHijo == 2|| rangoHijo == 3 )) return esDigno = true;
    else if(rangoPadre ==7 && (rangoHijo == 4|| rangoHijo == 5|| rangoHijo == 6 ))return esDigno = true;
    else if(rangoPadre ==8 && (rangoHijo == 6|| rangoHijo == 7))return esDigno = true;
    else qDebug()<<"ERROR EN LA EDAD DEL PADRE!!!!!!!\n\nALERTAAAA\\n\nATENCIONNNN";

    return esDigno;
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
        root->dato->madre;
        root->dato->padre;
        root->dato->hijos;
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

QString Mundo::antMan(int cantHormigas){



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

QString Mundo:: blackDwarf(int veces, QString deporte){
    Nodo<Persona> * persona = this->arbolMundo->root;
    QList<Persona> * deportistas = {};
    QString textoLog = "", tiempoMuerte = "", vecesQStr = "";
    QString::number(veces);
    std::string tiempoMuerteSTD = "";
    const time_t current = time(nullptr);
    tm *local_time = localtime(&current);

    //STD::STRING
    tiempoMuerteSTD+= std::to_string(1900 + local_time->tm_year);
    tiempoMuerteSTD+="-";
    tiempoMuerteSTD+=std::to_string(1 + local_time->tm_mon);
    tiempoMuerteSTD+="-";
    tiempoMuerteSTD+=std::to_string(local_time->tm_mday);
    tiempoMuerteSTD+=" ";
    tiempoMuerteSTD+=std::to_string(local_time->tm_hour);
    tiempoMuerteSTD+=":";
    tiempoMuerteSTD+=std::to_string(local_time->tm_min);
    tiempoMuerteSTD+=":";
    tiempoMuerteSTD+=std::to_string(1 + local_time->tm_sec);
    tiempoMuerteSTD+="  ";

    //Convertir solo una vez y dejarlo asi para el for
    tiempoMuerte = QString::fromStdString(tiempoMuerteSTD);
    vecesQStr = QString::number(veces);

    //Recorrer el arbol  y hacer esto

    if(persona->dato->deportes->contains(deporte) && persona->dato->ctdEjercicioxSemana == veces){
        deportistas->append(*persona->dato);
    }
    for(int i=0;i<(deportistas->length()/2);i++){
        *persona->dato  = deportistas->at(i);
        persona->dato->vivo = false;

        textoLog+=tiempoMuerte+"Humano: "+persona->dato->ID+
                "  "+persona->dato->nombre+"\n"+persona->dato->pais+" "+
                crearListaAmigosTxt(persona->dato)+"\nPareja: "+persona->dato->pareja->nombre+" "+
                crearListaFamiliaTxt(persona->dato)+crearExperienciasTxt(persona->dato)+
                "\nMurio el "+tiempoMuerte+" aniquilado por Black Dwarf por hacer "+vecesQStr
                +" veces "+deporte;
    }

    //Rellenar con lo que hace y meter a textoLog para que se cree al archivo
    return escribirArchivo(textoLog.toStdString());
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

int Mundo::generateRandom(int min, int max){
    std::uniform_int_distribution<int> dist(min, max);
    int numRandom = dist(*QRandomGenerator::global());
    return numRandom;

}
Persona* Mundo::getPersonaRandom(){
    int index = generateRandom(0, listaPersonasTotales->largo-1);
    return listaPersonasTotales->at(index);
}



