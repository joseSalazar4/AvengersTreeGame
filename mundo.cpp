#include "mundo.h"
#include <math.h>
#include <cmath>
//Agregar metodo para enviar correos

Mundo::Mundo()
{
    //Nulos y ceros
    generacion = 0;
    heapPecados = new Heap();
    heapBuenasAcciones = new Heap();
    arbolMundo = new AVL<Persona>();
    listaPersonasTotales = new ListaDoble<Persona>();

    rangoPaises1 = rangoPaises2 = rangoNombres1 = rangoNombres2
     = rangoApellidos1 = rangoApellidos2 = cantAsesinados
     =rangoCreencias1 = rangoCreencias2 = cantSalvados
     = rangoProfesiones1 = rangoProfesiones2 = 0;

    salvacionesThor= new QList<QString>;
    salvacionesAntMan= new QList<QString>;
    salvacionesIronMan= new QList<QString>;
    eliminacionesNebula= new QList<QString>;
    salvacionesSpiderMan= new QList<QString>;
    eliminacionesBlackD = new QList<QString>;
    eliminacionesEbonyMaw= new QList<QString>;
    eliminacionesMidnight= new QList<QString>;
    eliminacionesCorvusGlaive= new QList<QString>;


    //El metodo lee el archivo, extrae y coloca directamente en los arrays la informacion
    leerArchivo(":/Archivos/Paises.txt",paises);
    leerArchivo(":/Archivos/Apellidos.txt",apellidos);
    leerArchivo(":/Archivos/Creencias.txt",creencias);
    leerArchivo(":/Archivos/NombresH.txt",nombresHombres);
    leerArchivo(":/Archivos/NombresM.txt",nombresMujeres);
    leerArchivo(":/Archivos/Profesiones.txt",profesiones);
}

void Mundo::encontrarContinente(Persona * persona){
    for(int i = 0 ; i<5 ; i++){
        if(continentes->at(i).contains(persona->pais)) persona->continente = continentes->at(i).at(0);
    }
}

void Mundo::hacerlesPecar(Persona* persona){
    persona->pecadosTotales = 0;
    for(int j = 0; j<7;j++){
        persona->pecados[j]+= QRandomGenerator::global()->bounded(1,100);
        persona->pecadosTotales+= persona->pecados[j];

    }
    qDebug()<<persona->pecadosTotales;
}

//Tnto el metodo de arriba como el de abajo en window.cpp pero con un FOR

void Mundo::hacerBuenasAcciones(Persona* persona){
    persona->buenasAccionesTotales = 0;
    for(int j = 0; j<7;j++){
        persona->buenasAcciones[j]+= QRandomGenerator::global()->bounded(1,100);
        persona->buenasAccionesTotales+= persona->buenasAcciones[j];
    }
}

void Mundo::vivirExperiencias(Persona * persona){
    int cantExperiencias = QRandomGenerator::global()->bounded(0,99), cantPaises = 0;
    if(cantExperiencias<30) cantPaises= QRandomGenerator::global()->bounded(0,2);
    else if(cantExperiencias <55) cantPaises= QRandomGenerator::global()->bounded(2,10);
    else if(cantExperiencias <75) cantPaises= QRandomGenerator::global()->bounded(10,15);
    else if(cantExperiencias <90) cantPaises= QRandomGenerator::global()->bounded(16,25);
    else cantPaises= cantPaises = QRandomGenerator::global()->bounded(25,100);


    for(int i = 0; i<cantPaises;i++){
        QString paisVisitado = paises[QRandomGenerator::global()->bounded(0,99)];
        if(!persona->paisesVisitados->contains(paisVisitado)) persona->paisesVisitados->append(paisVisitado);
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


    //INSERTAR PERSONAS DEL ARBOL
    if(generacion!=0) delete(arbolMundo);
    arbolMundo = new AVL<Persona>;
    int cantidadTotal = listaPersonasTotales->largo;
    int cantidadParaArbol = cantidadTotal/100;
    int ctdElegidos = 0;
    for (int i=0; ctdElegidos < cantidadParaArbol; i++){
        ctdElegidos = int(pow(2,i));
    }

    int index;
    qDebug() << "Cantidada total: " + QString::number(cantidadTotal);

    qDebug() << "Cantidada para arbol: " + QString::number(ctdElegidos);

    Persona * p;
    int repetido = 0;
    for(int k=0; k<ctdElegidos; k++){
        do{
            index = generateRandom(0, cantidadTotal);
            p = listaPersonasTotales->at(index);
            repetido++;
        }
        while(arbolMundo->estaEnElArbol(p->ID));
        arbolMundo->insertar(p);
        repetido--;
    }

    qDebug() << "Repetidos: " + QString::number(repetido);

    generacion++;
}

void Mundo::crearPersona(){
    Persona * nuevaPersona = new Persona();

    //Genero
    if(QRandomGenerator::global()->bounded(0,2) == 0) nuevaPersona->genero = "mujer";
    else nuevaPersona->genero = "hombre";

    //IDs
    nuevaPersona->ID = QString::number(registroIds->generarId());

    //Lectura de archivos
    nuevaPersona->pais = paises[QRandomGenerator::global()->bounded(rangoPaises1,rangoPaises2+1)];
    nuevaPersona->creencia = creencias[QRandomGenerator::global()->bounded(rangoCreencias1,rangoCreencias2+1)];
    nuevaPersona->apellido = apellidos[QRandomGenerator::global()->bounded(rangoApellidos1,rangoApellidos2+1)];
    nuevaPersona->profesion = profesiones[QRandomGenerator::global()->bounded(rangoProfesiones1,rangoProfesiones2+1)];
    if(nuevaPersona->genero == "mujer") nuevaPersona->nombre = nombresMujeres[QRandomGenerator::global()->bounded(rangoNombres1,rangoNombres2+1)];
    else nuevaPersona->nombre = nombresHombres[QRandomGenerator::global()->bounded(rangoNombres1,rangoNombres2+1)];

    //Acciones, edades y deportes
    nuevaPersona->fechaNacimiento = new FechaNacimiento();
    nuevaPersona->edad = longevidad->obtenerEdad(nuevaPersona);
    nuevaPersona->deportes = deportes->generarDeportes(nuevaPersona);
    nuevaPersona->ctdEjercicioxSemana = deportes->generarVecesxSemana();
    hacerBuenasAcciones(nuevaPersona);
    vivirExperiencias(nuevaPersona);
    hacerlesPecar(nuevaPersona);

    //Finalmente se agrega a la listaPrincipal del mundo
    listaPersonasTotales->insertar(nuevaPersona);
    //Insertar en AVL Para prueba
    arbolMundo->insertar(nuevaPersona);
    qDebug()<<nuevaPersona->nombre+"\n";
}

QString crearListaAmigosTxt(Persona * persona){
    //EL if dentro del for es para que en el ultimo elemento no le meta una coma.
    QString listaTxt = "\nAmigos [ ";
    for(int i = 0 ; i<persona->amigos->length();i++){
        listaTxt+=persona->amigos->at(i)->ID+"--";
        if((i+1) == persona->amigos->length()) {
            listaTxt+=persona->amigos->at(i)->nombre;
            return  listaTxt;
        }
        listaTxt+=persona->amigos->at(i)->nombre+", ";
    }
    listaTxt += " ]";
    return  listaTxt;
}

QString crearListaFamiliaTxt(Persona * persona){
        //EL if dentro del for es para que en el ultimo elemento no le meta una coma.
    QString listaTxt = "\nFamilia [ ";
    for(int i = 0 ; i<persona->hijos->length();i++){
        listaTxt+=persona->hijos->at(i)->ID+"--";
        if((i+1) == persona->amigos->length()){
            listaTxt+=persona->hijos->at(i)->nombre;
            return listaTxt;
        }
        listaTxt+=persona->hijos->at(i)->nombre+", ";
    }
    listaTxt += " ]";
    return  listaTxt;
}

QString crearExperienciasTxt(Persona * persona){

    QString listaTxt = "\nExperiencias [ ";
    for(int i = 0 ; i<persona->paisesVisitados->length();i++){
        if((i+1) == persona->paisesVisitados->length())  {
            listaTxt+=persona->paisesVisitados->at(i);
            return listaTxt;
        }
        listaTxt+=persona->paisesVisitados->at(i)+", ";
    }
    listaTxt += " ]";
    return  listaTxt;
}

void Mundo::asignarFamilia(Persona* persona){
    //Preguntar si estara soltero o en otro estado
    int estadoMarit = QRandomGenerator::global()->bounded(0,3);

    if(estadoMarit == 2) persona->estadoMarital = "Casad@";
    else if (estadoMarit == 1)persona->estadoMarital = "Separad@";
    else persona->estadoMarital = "Solter@";

    //Soltero es no tener hijos
    if(persona->estadoMarital == "Solter@") return;

    Persona * pareja = getPersonaRandom();
    int i = 0;
    while((pareja->pareja != nullptr || pareja->genero == persona->genero )){//|| (!longevidad->validarEdadPareja(persona, pareja)))){
        if(i >= 1000){
            persona->estadoMarital = "Solter@";
            qDebug()<<"NO ENCONTRE PAREJA";
            return;
        }

        pareja = getPersonaRandom();
        i++;
    }
    persona->pareja = pareja;
    qDebug()<<"ENCONTRE PAREJA";

    //Si no tiene mas de 20 no es Joven y no puede tener hijos
    if(persona->edad< 20) return;

    int cantHijos = QRandomGenerator::global()->bounded(0,5);
    Persona * tmp = getPersonaRandom();
    //agregarMetodo de moverse x nodos en la lista para seleccionar gente random

    int cont = 0, contMax = 0;
    while(cont<cantHijos){
        qDebug() << "Cantidad de hijos";
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

QString Mundo::crearTxtTiempo(){
    const time_t current = time(nullptr);
    tm *local_time = localtime(&current);

    std::string tiempo = "";
    //STD::STRING
    tiempo+= std::to_string(1900 + local_time->tm_year);
    tiempo+="-";
    tiempo+=std::to_string(1 + local_time->tm_mon);
    tiempo+="-";
    tiempo+=std::to_string(local_time->tm_mday);
    tiempo+=" ";
    tiempo+=std::to_string(local_time->tm_hour);
    tiempo+=":";
    tiempo+=std::to_string(local_time->tm_min);
    tiempo+=":";
    tiempo+=std::to_string(1 + local_time->tm_sec);
    tiempo+="  ";
    return QString::fromStdString(tiempo);
}

QString Mundo::crearLog(Persona *persona){
    QString tiempoMuerte = crearTxtTiempo(), logGenerado = "";

    logGenerado+="\n\n\n"+tiempoMuerte+"「ID:"+persona->ID+"」 「Nombre: "+persona->nombre+
            "」 「Apellido: "+persona->apellido+"」 「Pais: "+persona->pais+"」"+
            crearListaAmigosTxt(persona)+crearListaFamiliaTxt(persona)+
            crearExperienciasTxt(persona);

    return  logGenerado;
}

void Mundo::asignarAmigos(Persona* persona){
    int cantAmigos = QRandomGenerator::global()->bounded(0,51);
    Persona * extrano = listaPersonasTotales->primerNodo->dato;
    //agregarMetodo de moverse x nodos en la lista para seleccionar gente random

    int cont = 0;
    int insistir = 0;
    while(cont<cantAmigos){
        if(insistir > 100) return;
        insistir++;
        if(!persona->amigos->contains(extrano)){
            if(persona->pais  == extrano->pais){
                persona->amigos->append(extrano);
                qDebug() << "Asignando amigos";
                cont++;
                insistir = 0;
            }
            else if(QRandomGenerator::global()->bounded(1,100) <40){
                persona->amigos->append(extrano);

                qDebug() << "Asignando amigos";
                cont++;
                insistir = 0;
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
                    insistir = 0;
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


//
//
//                                                           PERSONAJES:
//                                                        HEROES Y VILLLANOS
//




//---------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------SUPER-HEROES-----------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------

QString Mundo::thor(int nivel){
    Nodo<Persona> * root = arbolMundo->root;

    QString textoLog = "",tiempoSalvacion = crearTxtTiempo();


    salvacionesThor->append(textoLog);
    return   escribirArchivo(textoLog.toStdString());

}

QString Mundo::antMan(int cantHormigas){

    QString textoLog = "",tiempoSalvacion = crearTxtTiempo();
    salvacionesAntMan->append(textoLog);

    return escribirArchivo(textoLog.toStdString());
}

QString Mundo::ironMan(){
    //Recorre el arbol, pregunta si ya pasó por ese nodo. Si no, hace random y depende del resultado salva ese nodo y lo pone true.
    //Al terminar el proceso, restaura los valores de los nodos a false.

    QString textoLog = "",tiempoSalvacion = crearTxtTiempo();
    salvacionesIronMan->append(textoLog);


    return escribirArchivo(textoLog.toStdString());
}

QString Mundo::spiderMan(){

    QString textoLog = "",tiempoSalvacion = crearTxtTiempo();

    salvacionesSpiderMan->append(textoLog);
    return escribirArchivo(textoLog.toStdString());
}

//---------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------VILLANOS-----------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------


QString Mundo::nebula(int IDCulpable){
    Persona * culpable = listaPersonasTotales->buscar(IDCulpable);
    QString textoLog = "",tiempoMuerte = crearTxtTiempo();
    //maybe llamar a un metodo secundario


    eliminacionesNebula->append(textoLog);
    return escribirArchivo(textoLog.toStdString());
}

QString Mundo::corvusGlaive(){
    QString textoLog = "",tiempoMuerte = crearTxtTiempo();
    QList<Persona*> * personasPecadoras = new QList<Persona*>;
    QList<Nodo<Persona>*> * arbolAplastado = arbolMundo->aplastarArbol();

    //Obtenemos el 5%
    int cantPorEliminar = int((arbolAplastado->length())*(0.05));

    for(int i =0; i<arbolAplastado->length();i++) heapPecados->insertarPrioridadMax(arbolAplastado->at(i)->dato);
    for(int i =0; i<cantPorEliminar;i++) personasPecadoras->append(heapPecados->eliminarPrioridadMax());

    for(int i =0; i<personasPecadoras->length();i++){
        cantAsesinados++;
        personasPecadoras->at(i)->vivo = false;
        textoLog+=crearLog(personasPecadoras->at(i))+"\nMurio el "+tiempoMuerte+" aniquilado por Corvus Glaive, por tener una cantidad total de pecados: "+QString::number(personasPecadoras->at(i)->pecadosTotales);
    }
    eliminacionesCorvusGlaive->append(textoLog);

    return escribirArchivo(textoLog.toStdString());
}

QString Mundo::midnight(){
    QString textoLog = "",tiempoMuerte = crearTxtTiempo();
    QList<Persona*> * personasNoBuenas = new QList<Persona*>; //No se me ocurrio un mejor nombre \_°-°_/
    QList<Nodo<Persona>*> * arbolAplastado = arbolMundo->aplastarArbol();

    int cantPorEliminar = int((arbolAplastado->length())*(0.05));

    for(int i =0; i<arbolAplastado->length();i++) heapBuenasAcciones->insertarPrioridadMin(arbolAplastado->at(i)->dato);
    for(int i =0; i<cantPorEliminar;i++) personasNoBuenas->append(heapBuenasAcciones->eliminarPrioridadMin());

    for(int i =0; i<personasNoBuenas->length();i++){
        cantAsesinados++;
        personasNoBuenas->at(i)->vivo = false;
        textoLog+=crearLog(personasNoBuenas->at(i))+"\nMurio el "+tiempoMuerte+" aniquilado por Midnight, por tener una cantidad total de buenas acciones de: "+QString::number(personasNoBuenas->at(i)->buenasAccionesTotales);
    }
    qDebug() << textoLog;
    eliminacionesMidnight->append(textoLog);
    return escribirArchivo(textoLog.toStdString());
}

QString Mundo::ebonyMaw(int IDCulpable){
    Persona * victima = new  Persona();
    QString textoLog = "", tiempoMuerte = crearTxtTiempo(), pareja = "N/A";

    QList<Persona*> * familiaresSalados = new QList<Persona*>;


    //->vivo = false;
    //textoLog+= crearLog(deportistas->at(i))+"\nMurio el "+tiempoMuerte+" aniquilado por Ebony Maw por ser familia de la persona con ID: "+
    QString::number(IDCulpable);


    eliminacionesEbonyMaw->append(textoLog);
    //Rellenar con lo que hace y meter a textoLog para que se cree al archivo
    return escribirArchivo(textoLog.toStdString());

}

QString Mundo:: blackDwarf(int veces, QString deporte){
    QString::number(veces);
    QList<Persona*> * deportistas = new QList<Persona*>();
    QString textoLog = "", tiempoMuerte = crearTxtTiempo() , vecesQStr = "";

    //Convertir solo una vez y dejarlo asi para el for
    vecesQStr = QString::number(veces);

    //Recorrer el arbol  y hacer esto
    QList<Nodo<Persona>*> * arbolAplastado = arbolMundo->aplastarArbol();

    for(int i = 0 ;i<arbolAplastado->length();i++){
        if(arbolAplastado->at(i)->dato->deportes->contains(deporte) && arbolAplastado->at(i)->dato->ctdEjercicioxSemana == veces)
            deportistas->append(arbolAplastado->at(i)->dato);
    }

    for(int i=0;i<(deportistas->length()/2);i++){
        deportistas->at(i)->vivo = false;

        QString pareja = "N/A";
        if (deportistas->at(i)->pareja) pareja = deportistas->at(i)->pareja->nombre;
        cantAsesinados++;

        textoLog+= crearLog(deportistas->at(i))+"\nMurio el "+tiempoMuerte+" aniquilado por Black Dwarf por hacer "+
                vecesQStr+" veces "+deporte;

    }
    eliminacionesBlackD->append(textoLog);

    //Rellenar con lo que hace y meter a textoLog para que se cree al archivo
    return escribirArchivo(textoLog.toStdString());
}

QString Mundo:: escribirArchivo(std::string textoLog){

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

QString Mundo::consultarSalvaciones(){
    QString consulta = "";
    QList<QList<QString>> * salvacionesHeroes = new QList<QList<QString>>;
    consulta+= "\nLa cantidad total de personas salavadas es: "+QString::number(cantSalvados)+"\n\n";

    salvacionesHeroes->append(*salvacionesThor);
    salvacionesHeroes->append(*salvacionesAntMan);
    salvacionesHeroes->append(*salvacionesIronMan);
    salvacionesHeroes->append(*salvacionesSpiderMan);

    for(int i = 0; i <salvacionesHeroes->length();i++){
        for(int j = 0 ; i<salvacionesHeroes->at(i).length();i++){
            consulta+=salvacionesHeroes->at(i).at(j);
        }
    }

    return escribirArchivo(consulta.toStdString());
}

QString Mundo::consultarEliminaciones(){
    QString consulta= "";
    QList<QList<QString>> * eliminacionesVillanos = new QList<QList<QString>>;
    QList<QString> * nombresVillanos = new QList<QString>;

    nombresVillanos->append("Black Dwarf");
    nombresVillanos->append("Nebula");
    nombresVillanos->append("Midnight");
    nombresVillanos->append("EbonyMaw");
    nombresVillanos->append("CorvusGlaive");
    consulta+= "\nLa cantidad total de personas asesinadas es: "+QString::number(cantAsesinados)+"\n\n";
    eliminacionesVillanos->append(*eliminacionesBlackD);
    eliminacionesVillanos->append(*eliminacionesNebula);
    eliminacionesVillanos->append(*eliminacionesMidnight);
    eliminacionesVillanos->append(*eliminacionesEbonyMaw);
    eliminacionesVillanos->append(*eliminacionesCorvusGlaive);

    //ELIMINAR
    for(int i = 0; i <5;i++){
        consulta+= "\n\nELIMINACIONES HECHAS POR: "+nombresVillanos->at(i);

        for(int j = 0 ; i<(eliminacionesVillanos->at(i).length()+1);i++){
            consulta+=eliminacionesVillanos->at(i).at(j);
        }
    }
    return escribirArchivo(consulta.toStdString());
}
