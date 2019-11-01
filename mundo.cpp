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
    arbolCompleto = new AVL<Persona>();
    listaPersonasTotales = new ListaDoble<Persona>();
    Thanos = new MundoThanos();

    rangoPaises1 = rangoPaises2 = rangoNombres1 = rangoNombres2
     = rangoApellidos1 = rangoApellidos2 = cantAsesinados
     =rangoCreencias1 = rangoCreencias2 = cantSalvados
     = rangoProfesiones1 = rangoProfesiones2 = 0;

    salvacionesThor= new QList<QString>();
    salvacionesAntMan= new QList<QString>();
    salvacionesIronMan= new QList<QString>();
    eliminacionesNebula= new QList<QString>();
    salvacionesSpiderMan= new QList<QString>();
    eliminacionesBlackD = new QList<QString>();
    eliminacionesEbonyMaw= new QList<QString>();
    eliminacionesMidnight= new QList<QString>();
    eliminacionesCorvusGlaive= new QList<QString>();


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
    else cantPaises= QRandomGenerator::global()->bounded(25,100);


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

    insertarEnArbol();
    generacion++;

}

void Mundo::insertarEnArbol(){
    //INSERTAR PERSONAS DEL ARBOL
    //if(generacion!=0) arbolMundo->;
    arbolMundo = new AVL<Persona>();
    arbolCompleto = new AVL<Persona>();
    QList<Persona*> * listaParaArbol = new QList<Persona*>();
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
    for(int k=0; k<ctdElegidos-1; k++){
        do{
            index = generateRandom(0, cantidadTotal);
            p = listaPersonasTotales->at(index);
            repetido++;
        }
        while(listaParaArbol->contains(p));
        arbolMundo->insertar(p);
        listaParaArbol->append(p);
        repetido--;
    }
    qDebug() << "Repetidos: " + QString::number(repetido);
    qDebug() << "PROMEDIO: " + QString::number(Thanos->promedio / listaPersonasTotales->largo);
    arbolMundo->imprimirNiveles();

    //Ya tenemos en listaParaArbol las n personas para el arbol.
    //Ahora las ordenamos de menor a mayor.
    //quickSort(listaParaArbol);
    //Insertamos las personas al arbol de forma de que quede completo y balanceado.
    //arbolCompleto->root = arbolCompleto->newNodo(listaParaArbol->at(listaParaArbol->size()/2));
    //completarArbol(listaParaArbol, arbolCompleto->root->left, 0, listaParaArbol->size()/2);
    //completarArbol(listaParaArbol, arbolCompleto->root->right, listaParaArbol->size()/2, listaParaArbol->size());
}

void Mundo::completarArbol(QList<Persona*> * lista, Nodo<Persona> * nodo, int min, int max){
    if(min != max){
        int medio = (min+max)/2;
        nodo = arbolCompleto->newNodo(lista->at(medio));
        //qDebug() <<QString::number(medio) +" : "+ nodo->dato->ID;
        completarArbol(lista, nodo->left, min, medio);
        completarArbol(lista, nodo->right, medio, max);
    }
    //else nodo = arbolCompleto->newNodo(lista->at(min));
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
    //agregar Esta Persnaa a cada deportes  pra el mtdo conslta y asi solo buscar un deporte
    nuevaPersona->ctdEjercicioxSemana = deportes->generarVecesxSemana();
    hacerBuenasAcciones(nuevaPersona);
    vivirExperiencias(nuevaPersona);
    hacerlesPecar(nuevaPersona);

    //Finalmente se agrega a la listaPrincipal del mundo
    listaPersonasTotales->insertar(nuevaPersona);
    //Insertar en AVL Para prueba

    //arbolMundo->insertar(nuevaPersona);

}

QString crearListaAmigosTxt(Persona * persona){
    QString listaTxt = "\nAmigos [ ";
    for(int i = 0 ; i<persona->amigos->length();i++){
        listaTxt+=persona->amigos->at(i)->ID+"--";
        listaTxt+=persona->amigos->at(i)->nombre+", ";
    }
        listaTxt+= " ]";
    return  listaTxt;
}

QString crearDeportesTxt(Persona * persona){
    QString listaTxt = "\nDeportes [ ";
    for(int i =0 ; i<persona->deportes->length();i++){
        listaTxt+=persona->deportes->at(i)+", ";
    }
    listaTxt+=" ]";
    return listaTxt;
}

QString crearListaFamiliaTxt(Persona * persona){
    QString listaTxt = "\nFamilia [ ";
    for(int i = 0 ; i<persona->hijos->length();i++){
        listaTxt+=persona->hijos->at(i)->ID+"--"+persona->hijos->at(i)->nombre+"--"+persona->hijos->at(i)->apellido+", ";
    }

    listaTxt+= " ]";
    return  listaTxt;
}

QString crearPecadosTxt(Persona * persona){
    QString listaTxt = "\nPecados: [ ";
    QList<QString> *nombresPecados = new QList<QString>();
    nombresPecados->append("Lujuria");
    nombresPecados->append("Gula");
    nombresPecados->append("Avaricia");
    nombresPecados->append("Pereza");
    nombresPecados->append("Ira");
    nombresPecados->append("Envidia");
    nombresPecados->append("Soberbia");

    for(int i = 0 ; i<7;i++){
        listaTxt+=nombresPecados->at(i)+": "+QString::number(persona->pecados[i])+", ";
    }

    listaTxt+= " ]";
    return  listaTxt;
}

QString crearBuenasAccionesTxt(Persona * persona){
    QString listaTxt = "\nBuenasAcciones [ ";
    QList<QString> *nombresBnasAcc = new QList<QString>();
    nombresBnasAcc->append("Castidad");
    nombresBnasAcc->append("Ayuno");
    nombresBnasAcc->append("Donacion");
    nombresBnasAcc->append("Diligencia");
    nombresBnasAcc->append("Calma");
    nombresBnasAcc->append("Solidaridad");
    nombresBnasAcc->append("HUmildad");

    for(int i = 0 ; i<7;i++){
        listaTxt+=nombresBnasAcc->at(i)+": "+QString::number(persona->buenasAcciones[i])+", ";
    }

    listaTxt+= " ]";
    return  listaTxt;
}

QString crearLogMuerteTxt(Persona * persona){
    QString listaTxt = "\nMuertes [ ";
    for(int i = 0 ; i<persona->logMuerte->length();i++){
        listaTxt+="\t"+persona->logMuerte->at(i)+",  ";
    }

    listaTxt+= "\n ]";
    return  listaTxt;
}


QString crearLogSalvacionTxt(Persona * persona){
    QString listaTxt = "\nSalvaciones [ ";
    for(int i = 0 ; i<persona->logSalvacion->length();i++){
        listaTxt+="\t"+persona->logSalvacion->at(i)+",  ";
    }

    listaTxt+= "\n ]";
    return  listaTxt;
}

QString crearExperienciasTxt(Persona * persona){

    QString listaTxt = "\nExperiencias [ ";
    for(int i = 0 ; i<persona->paisesVisitados->length();i++){

            listaTxt+=persona->paisesVisitados->at(i)+", ";

    }
    listaTxt+= " ]";
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

    NodoDoble<Persona> * pareja = getPersonaRandom();
    int i = 0;
    while( (pareja->dato->pareja != nullptr || pareja->dato->genero == persona->genero) ){//|| (!longevidad->validarEdadPareja(persona, pareja)))){
        if(i >= listaPersonasTotales->largo){
            persona->estadoMarital = "Solter@";
            return;
        }

        if(pareja->siguiente!=nullptr) pareja = pareja->siguiente;
        else pareja = listaPersonasTotales->primerNodo;
        i++;
    }
    persona->pareja = pareja->dato;

    //Si no tiene mas de 20 no es Joven y no puede tener hijos
    if(persona->edad< 20) return;

    int cantHijos = QRandomGenerator::global()->bounded(0,5);
    NodoDoble<Persona> * tmp = getPersonaRandom();
    //agregarMetodo de moverse x nodos en la lista para seleccionar gente random

    int cont = 0, contMax = 0;
    while(cont<cantHijos){
        //Preguntamos primero por verificar para no hacer las otras preguntas
        if( verificarValidezHijos(persona,tmp->dato) &&  ((persona->pais  == tmp->dato->pais || persona->pareja->pais == tmp->dato->pais)  || (persona->apellido == tmp->dato->apellido ||  persona->pareja->apellido == tmp->dato->apellido)) ){
            persona->hijos->append(tmp->dato);

            cont++;
        }

        //Si no hay suficientes personas con ese apellido podria enciclarse entonces que busque un maximo de 30 000 personas
        if(listaPersonasTotales->largo>90000){
            if(contMax>(listaPersonasTotales->largo)/2) return;
        }
        if(contMax>listaPersonasTotales->largo) return;

        contMax++;
        if(tmp->siguiente) tmp = tmp->siguiente;
        else tmp = listaPersonasTotales->primerNodo;
        i++;
    }
}

//Permite saber si puede ser hijo o no
bool Mundo::verificarValidezHijos(Persona * supuestoPadre, Persona * supuestoHijo){

    int rangoPadre = 0 ,rangoHijo = 0;

    //Primero preguntamos si el padre no es ya hijo de su supuesto hijo
    bool esDigno = true;
    for(int i = 0;i<supuestoHijo->hijos->length();i++) if(supuestoPadre == supuestoHijo->hijos->at(i)) esDigno = false;

    if( (!esDigno) || supuestoHijo->ID == supuestoPadre->ID) return false;
    esDigno = false;

    rangoPadre = longevidad->fHash(supuestoPadre->edad);
    rangoHijo = longevidad->fHash(supuestoHijo->edad);

    if(rangoPadre==5 && (rangoHijo == 0|| rangoHijo == 1)) return esDigno = true;
    else if(rangoPadre ==6 && (rangoHijo == 0 || rangoHijo ==1 || rangoHijo == 2|| rangoHijo == 3 )) return esDigno = true;
    else if(rangoPadre ==7 && (rangoHijo == 4|| rangoHijo == 5|| rangoHijo == 6 ))return esDigno = true;
    else if(rangoPadre ==8 && (rangoHijo == 6|| rangoHijo == 7))return esDigno = true;
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
    QString tiempoMuerte = crearTxtTiempo(), logGenerado = "", pareja=" Solter@";
    if(persona->pareja) pareja = " Nombre: "+persona->pareja->nombre+" Apellido: "+persona->pareja->apellido;

    logGenerado+="\n\n\n"+tiempoMuerte+"「ID: "+persona->ID+"」 「Nombre: "+persona->nombre+
            "」 「Apellido: "+persona->apellido+"」 「Pais: "+persona->pais+"」"+" Pareja: "+pareja+"\nFecha de Nacimiento: "+
            QString::number(persona->fechaNacimiento->dia)+"/"+QString::number(persona->fechaNacimiento->mes)+"/"
            +QString::number(persona->fechaNacimiento->anno)+
            crearListaAmigosTxt(persona)+
            crearListaFamiliaTxt(persona)+
            crearExperienciasTxt(persona);

    return  logGenerado;
}

void Mundo::asignarAmigos(Persona* persona){
    int cantAmigos = QRandomGenerator::global()->bounded(0,51);
    NodoDoble<Persona> * extrano = getPersonaRandom();

    int cont = 0;
    int insistir = 0;
    while(cont<cantAmigos){
        if(insistir > listaPersonasTotales->largo/2) return;
        insistir++;
        if(!persona->amigos->contains(extrano->dato)){
            if(persona->pais  == extrano->dato->pais){
                persona->amigos->append(extrano->dato);
                insistir = 0;
                cont++;
            }
            else if(QRandomGenerator::global()->bounded(1,100) <40){
                persona->amigos->append(extrano->dato);

                cont++;
                insistir = 0;
            }
            else {
                bool coinciden = false;
                for(int i = 0;i<extrano->dato->amigos->length();i++){
                    for(int j = 0;j<persona->amigos->length();j++ ){
                        if(persona->amigos->at(j) == extrano->dato->amigos->at(i)){
                            coinciden = true;
                            return;
                        }
                        if(coinciden) return;
                    }
                }
                if(coinciden){
                    persona->amigos->append(extrano->dato);
                    cont++;
                    insistir = 0;
                    coinciden = false;
                }
            }
        }

        if(extrano->siguiente) extrano = extrano->siguiente;
        else extrano = listaPersonasTotales->primerNodo;
    }
}

QList<Persona*> * getFamiliaresDirectos(Persona* persona){
    QList<Persona*> * familiares = new QList<Persona*>;
    if(persona->padre) familiares->append(persona->padre);
    if(persona->madre) familiares->append(persona->madre);
    if(!persona->hijos->isEmpty()){
        for(int i=0; i<persona->hijos->size(); i++)
            familiares->append(persona->hijos->at(i));
    }

    return familiares;

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
    QString textoLog = "",tiempoSalvacion = crearTxtTiempo(), logPersonal;
    //VALIDAR QUE EL NIVEL NO SEA MAYOR QUE LA ALTURA-1
    QList<Persona*> * personasEnNivel = arbolMundo->buscarEnNivel(nivel);
    for(int i=0; i<personasEnNivel->size(); i++){
        Persona * persona = personasEnNivel->at(i);
        QList<Persona*> * familiares = getFamiliaresDirectos(persona);
        for(int f=0; f<familiares->size(); f++){
            Persona * familiar = familiares->at(f);
            for(int a=0; a<familiar->amigos->size(); a++){
                if(!familiar->amigos->at(a)->vivo)cantSalvados++;
                familiar->amigos->at(a)->vivo = true;
                logPersonal =crearLog(familiar->amigos->at(a)) + "\nFue Salvado el "+tiempoSalvacion+" Por el Dios del Trueno. Por ser amigo de " + familiar->nombre + ".Y este familiar de " + persona->nombre;
                textoLog+=logPersonal;
                persona->logSalvacion->append(logPersonal);
                qDebug().noquote() << textoLog;
            }
        }
    }
    salvacionesThor->append(textoLog);
    return   escribirArchivo(textoLog.toStdString());
}

QString Mundo::antMan(int cantHormigas){
    QString textoLog = "",tiempoSalvacion = crearTxtTiempo();
    int max1 =0, max2 = 0 ;
    //QRandom de cantidad de hormigas, hacer recursivamente a esas hromigas una a una
    //recorrer y qrandom (0,2) para ir izquierda o derecha y cuando llegue a una hoja contar sus feromonas
    //las 2 hojas con mas feromonas seran los dos caminos.
    AVL<Persona> * arbolMundoAuxiliar = arbolMundo;
    Nodo<Persona> * tmp = arbolMundoAuxiliar->root;

    for(int i = 0 ; i<cantHormigas;i++){
        tmp->feromonas+=1;

        if (! (tmp->right && tmp->left) ) 2+4;//si llega a una hoja tons listo trayecto hecho
        if(QRandomGenerator::global()->bounded(0,2) == 1) tmp = tmp->right;
        else tmp = tmp->left;

    }

     QList<Nodo<Persona>*> * posiblesCaminos = arbolMundoAuxiliar->aplastarArbol();

     for(int i = 0; i<posiblesCaminos->length();i++){
         if(posiblesCaminos->at(i)->feromonas>max1) max1 = posiblesCaminos->at(i)->feromonas;
     }

     //AAhora max2
     //s


    salvacionesAntMan->append(textoLog);
    return escribirArchivo(textoLog.toStdString());
}

//Recorre el arbol, pregunta si ya pasó por ese nodo. Si no, hace random y depende del resultado salva ese nodo y lo pone true.
//Al terminar el proceso, restaura los valores de los nodos a false.
QString Mundo::ironMan(){
    QString textoLog = "",tiempoSalvacion = crearTxtTiempo();
    QString logPersonal = "";

    //Se usara el aplastarArbol (Lista)
    arbolMundo->aplastarArbol();
    int porcentaje = generateRandom(40, 61);
    double numeroDeSalvadosD = arbolMundo->listaArbol->size() * (porcentaje*0.01);
    int numeroDeSalvados = int(numeroDeSalvadosD);
    QList<Nodo<Persona>*> * arbolPersonas = arbolMundo->aplastarArbol();

    for(int i=0; i<numeroDeSalvados; i++){
        Persona * persona = arbolPersonas->at(i)->dato;
        if(!persona->vivo) cantSalvados++;
        persona->vivo = true;

        logPersonal = crearLog(persona)+
           "\nEl/Ella y su Familia fueron salvados el "+tiempoSalvacion+
           " por Iron Man al estar entre los " + QString::number(numeroDeSalvados) + " nodos del arbol que explotaron";
        textoLog += logPersonal;
        persona->logSalvacion->append(logPersonal);
        textoLog+= ironManAux(arbolPersonas->at(i)->dato, arbolPersonas->at(i)->dato->ID);
    }

    salvacionesIronMan->append(textoLog);
    return escribirArchivo(textoLog.toStdString());
}


QString Mundo::ironManAux(Persona*persona, QString IdFamiliar){
    QString textoLog = "", tiempoMuerte = crearTxtTiempo(), logPersonal;
    QList<Persona*> * familiares = getFamiliaresDirectos(persona);
    for(int f=0; f<familiares->size(); f++){
        Persona * familiar = familiares->at(f);
        if(!familiar->vivo) cantSalvados++;
        familiar->vivo = true;
        logPersonal = crearLog(familiar)+
           "\nFue salvado el "+tiempoMuerte+
           " por Iron Man por ser familia de la persona con ID: " + IdFamiliar;
        textoLog += logPersonal;
        familiar->logSalvacion->append(logPersonal);
        textoLog += ironManAux(familiar, IdFamiliar);
    }
    return textoLog;
}

QString Mundo::spiderMan(){
    QString textoLog = "", tiempoSalvacion = crearTxtTiempo(), logPersonal;
    QList<Nodo<Persona>*> * listaPersonas = arbolMundo->aplastarArbol();
    int ctdNodosRecorridos = generateRandom(0, listaPersonas->size()-1);
    textoLog += "----Recorrido de Spiderman----\n";
    for(int i=0; i<ctdNodosRecorridos-1; i++){
        int index = generateRandom(0, listaPersonas->size());
        //telaranna->append(listaPersonas->at(index)->dato);
        Persona * pp =  listaPersonas->at(index)->dato;
        if(pp != nullptr) textoLog += pp->ID +  "-> ";
        if(listaPersonas->at(index)->right == nullptr && listaPersonas->at(index)->left == nullptr){
            textoLog += "\n LLegó a un nodo! \n";
            NodoDoble<Persona> * nodo = listaPersonasTotales->buscarNodo(listaPersonas->at(index)->dato->ID);
            int ctdSalvados = ctdNodosRecorridos;
            int contador = 0;
            while(contador < ctdSalvados){
                if(nodo == nullptr) nodo = listaPersonasTotales->primerNodo;
                if(!nodo->dato->vivo) cantSalvados++;
                nodo->dato->vivo = true;
                logPersonal = crearLog(nodo->dato)+
                   "\n Fue salvado el " + tiempoSalvacion+
                   " por Spider Man al estar en un rango de " + QString::number(ctdSalvados) + " personas desde una hoja del arbol";
                textoLog += logPersonal;
                nodo->dato->logSalvacion->append(logPersonal);

                nodo = nodo->siguiente;
                contador++;
            }
            textoLog += "\n Vuelve a la telaraña! \n";
        }
    }
    salvacionesSpiderMan->append(textoLog);
    return escribirArchivo(textoLog.toStdString());
}




//---------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------VILLANOS-----------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------





//Muere por haber nacido en el año (anno) y ser del nivel(nivel)
QString Mundo::thanosAnnoYNivel(int anno, int nivel){
    thanosCrearHashTable();
    QList<Persona*> * eliminados = Thanos->matarPorAnnoYNivel(anno, nivel);
    if(eliminados != nullptr) return thanosLogKill(eliminados,"3",nivel,anno);
    return "ERROR";
}

//Murio por ser del nivel (nivel)
QString Mundo::thanosNivel(int nivel){
    thanosCrearHashTable();
    QList<Persona*> * sacrificados = new QList<Persona*>();
    QList<QList<Persona*>*>*eliminados = Thanos->matarPorNivel(nivel);
    if(eliminados != nullptr){
        for(int i=0; i<eliminados->size(); i++){
            for(int j=0; j<eliminados->at(i)->size(); j++){
                sacrificados->append(eliminados->at(i)->at(j));
            }
        }
        return thanosLogKill(sacrificados, "1", nivel, -1);
    }
    return  "ERROR en thanos " ;
}

QString Mundo::thanosLogKill(QList<Persona*> * sacrificados, QString razonMuerte, int nivel, int anno){
    QString textoLog = "", tiempoMuerte = crearTxtTiempo(), logPersonal;
    //Nivel es 1 anno es 2 y ambos seria LA NUMERO 3
    if(razonMuerte == "1") razonMuerte = "pertenecer al nivel: "+QString::number(nivel);
    else if(razonMuerte == "2") razonMuerte = "pertenecer al anno: "+QString::number(anno);
    else razonMuerte = "pertener al nivel: "+QString::number(nivel)+" y ser del anno: "+QString::number(anno);

    for(int i = 0 ; i<sacrificados->length();i++){
        cantAsesinados++;
        sacrificados->at(i)->vivo = false;
        logPersonal = crearLog(sacrificados->at(i))+"\nMurio el "+tiempoMuerte+" aniquilado por Thanos, el increible guerrero, por "+razonMuerte;
        textoLog += logPersonal;
        sacrificados->at(i)->logMuerte->append(logPersonal);
    }
    return escribirArchivo(textoLog.toStdString());
}

//Murio por haber nacido en al año (anno)
QString Mundo::thanosAnno(int anno){
    thanosCrearHashTable();
    QList<Persona*> * sacrificados = new QList<Persona*>();
    QList<QList<Persona*>*>*eliminados = Thanos->matarPorAnno(anno);
    if(eliminados != nullptr){
        for(int i=0; i<eliminados->size(); i++){
            for(int j=0; j<eliminados->at(i)->size(); j++){
                sacrificados->append(eliminados->at(i)->at(j));
            }
        }
        return thanosLogKill(sacrificados, "2", -1, anno);
    }
    return "No deberia haber pasado esto";
}

void Mundo::thanosCrearHashTable(){
    NodoDoble<Persona> * nodoPersona = listaPersonasTotales->atNodo(0);
    while(nodoPersona != nullptr){
        Thanos->agregarPersona(nodoPersona->dato);
        nodoPersona = nodoPersona->siguiente;
    }
}

QString Mundo::nebula(){
    QString textoLog = "", tiempoMuerte = crearTxtTiempo(), logPersonal;
    arbolMundo->aplastarArbol();
    Persona * culpable = arbolMundo->listaArbol->at(generateRandom(0, arbolMundo->listaArbol->size()-1))->dato;
    if(culpable != nullptr){
        //maybe llamar a un metodo secundario
        for(int i=0; i<culpable->amigos->size(); i++){
            culpable->amigos->at(i)->vivo = false;
            logPersonal = crearLog(culpable)+
                    "\nFue asesinado el "+tiempoMuerte+
                    " por Nebula por ser amigo de la persona con ID (Y ÉL SE SALVO!): " + culpable->ID;
            culpable->amigos->at(i)->logMuerte->append(logPersonal);
            textoLog += nebulaAux(culpable->amigos->at(i));
        }

        eliminacionesNebula->append(textoLog);
        qDebug() << textoLog;
    }
    return escribirArchivo(textoLog.toStdString());
}

QString Mundo::nebulaAux(Persona * culpable){
    QString textoLog = "", tiempoMuerte = crearTxtTiempo(), logPersonal;
    for(int i=0; i<culpable->amigos->size(); i++){
        culpable->amigos->at(i)->vivo = false;
        logPersonal = crearLog(culpable)+
                "\nFue asesinado el "+tiempoMuerte+
                " por Nebula por ser amigo de la persona con ID (Y ÉL SE SALVO!): " + culpable->ID;
        culpable->amigos->at(i)->logMuerte->append(logPersonal);
        textoLog += nebulaAux(culpable->amigos->at(i));
    }

    return textoLog;
}

QString Mundo::corvusGlaive(){
    QString textoLog = "",tiempoMuerte = crearTxtTiempo(), logPersonal;
    QList<Persona*> * personasPecadoras = new QList<Persona*>();
    QList<Nodo<Persona>*> * arbolAplastado = arbolMundo->aplastarArbol();

    //Obtenemos el 5%
    for(int i =0;i<heapPecados->index;i++) heapPecados->eliminarPrioridadMax();

    int cantPorEliminar = int((arbolAplastado->length())*(0.05));

    for(int i =0; i<arbolAplastado->length();i++) heapPecados->insertarPrioridadMax(arbolAplastado->at(i)->dato);
    for(int i =0; i<cantPorEliminar+1;i++) personasPecadoras->append(heapPecados->eliminarPrioridadMax());

    for(int i =1; i<personasPecadoras->length();i++){
        cantAsesinados++;
        personasPecadoras->at(i)->vivo = false;
        logPersonal=crearLog(personasPecadoras->at(i))+"\nMurio el "+tiempoMuerte+" aniquilado por Corvus Glaive, por tener una cantidad total de pecados: "+QString::number(personasPecadoras->at(i)->pecadosTotales);
        textoLog+=logPersonal;
        personasPecadoras->at(i)->logMuerte->append(logPersonal);
    }
    eliminacionesCorvusGlaive->append(textoLog);
    qDebug().noquote() << textoLog;
    return escribirArchivo(textoLog.toStdString());
}



QString Mundo::midnight(){
    QString textoLog = "",tiempoMuerte = crearTxtTiempo(), logPersonal;
    QList<Persona*> * personasNoBuenas = new QList<Persona*>(); //No se me ocurrio un mejor nombre \_°-°_/
    QList<Nodo<Persona>*> * arbolAplastado = arbolMundo->aplastarArbol();

    for(int i =0;i<heapBuenasAcciones->index;i++) heapBuenasAcciones->eliminarPrioridadMax();

    int cantPorEliminar = int((arbolAplastado->length())*(0.05));

    for(int i =0; i<arbolAplastado->length();i++) heapBuenasAcciones->insertarPrioridadMin(arbolAplastado->at(i)->dato);
    for(int i =0; i<cantPorEliminar+1;i++) personasNoBuenas->append(heapBuenasAcciones->eliminarPrioridadMin());

    for(int i =1; i<personasNoBuenas->length();i++){
        cantAsesinados++;

        personasNoBuenas->at(i)->vivo = false;
        logPersonal=crearLog(personasNoBuenas->at(i))+"\nMurio el "+tiempoMuerte+" aniquilado por Midnight, por tener una cantidad total de buenas acciones de: "+QString::number(personasNoBuenas->at(i)->buenasAccionesTotales);
        textoLog+=logPersonal;
        personasNoBuenas->at(i)->logMuerte->append(logPersonal);
    }

    eliminacionesMidnight->append(textoLog);
    return escribirArchivo(textoLog.toStdString());
}

/**
 * Del arbol, toma una persona (la del ID del parametro) y busca a todos sus descendientes
 * a todos sus miembros y los mato (persona.vivo=false) y suma la cantAsesinados (1 por cada descendiente)
 * @param IDCulpable
 * @return
 */
QString Mundo::ebonyMaw(int IDCulpable){
    QString textoLog = "", tiempoMuerte = crearTxtTiempo();
    auto nodo = arbolMundo->buscar(QString::number(IDCulpable));

    Persona * victima = nodo==nullptr?listaPersonasTotales->buscar(IDCulpable):nodo->dato;

    if(victima==nullptr) return "Error obteniendo la persona";
    for(Persona*hijo:*victima->hijos){
        textoLog+=ebonyMawAux(hijo, victima->ID);
    }
    eliminacionesEbonyMaw->append(textoLog);
    //Rellenar con lo que hace y meter a textoLog para que se cree al archivo
    return escribirArchivo(textoLog.toStdString());

}

QString Mundo::ebonyMawAux(Persona *victima, QString progenitorId){
    QString textoLog = "", tiempoMuerte = crearTxtTiempo(), logPersonal;
    victima->vivo = false;
    cantAsesinados++;
     logPersonal = crearLog(victima)+
            "\nMurio el "+tiempoMuerte+
            " aniquilado por Ebony Maw por ser familia de la persona con ID: "+progenitorId;
    textoLog+= logPersonal;
    victima->logMuerte->append(logPersonal);
    for(Persona*hijo:*victima->hijos){
        textoLog+=ebonyMawAux(hijo, victima->ID);
    }

    return textoLog;
}

QString Mundo:: blackDwarf(int veces, QString deporte){
    QString::number(veces);
    QList<Persona*> * deportistas = new QList<Persona*>();
    QString textoLog = "", tiempoMuerte = crearTxtTiempo() , vecesQStr = "", logPersonal;

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

        logPersonal= crearLog(deportistas->at(i))+"\nMurio el "+tiempoMuerte+" aniquilado por Black Dwarf por hacer "+
                vecesQStr+" veces "+deporte;
        textoLog+=logPersonal;
        deportistas->at(i)->logMuerte->append(logPersonal);
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

NodoDoble<Persona> * Mundo::getPersonaRandom(){
    int index = generateRandom(0, listaPersonasTotales->largo-1);
    return listaPersonasTotales->atNodo(index);
}

QString Mundo::consultarSalvaciones(){
    QString consulta = "";
    QList<QList<QString>> * salvacionesHeroes = new QList<QList<QString>>();
    QList<QString> * nombresHeroes = new QList<QString>();
    nombresHeroes->append("IronMan");
    nombresHeroes->append("SpiderMan");
    nombresHeroes->append("AntMan");
    nombresHeroes->append("Thor");
    consulta+= "\nLa cantidad total de personas salavadas es: "+QString::number(cantSalvados)+"\n\n";

    salvacionesHeroes->append(*salvacionesThor);
    salvacionesHeroes->append(*salvacionesAntMan);
    salvacionesHeroes->append(*salvacionesIronMan);
    salvacionesHeroes->append(*salvacionesSpiderMan);

    for(int i = 0; i <salvacionesHeroes->length();i++){
        consulta+= "\n\nELIMINACIONES HECHAS POR: "+nombresHeroes->at(i);
        for(int j = 0 ; i<salvacionesHeroes->at(i).length();i++){
            consulta+=salvacionesHeroes->at(i).at(j);
        }
    }

    return escribirArchivo(consulta.toStdString());
}

QString Mundo::consultarEliminaciones(){
    QString consulta= "";
    QList<QList<QString>> * eliminacionesVillanos = new QList<QList<QString>>();
    QList<QString> * nombresVillanos = new QList<QString>();

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
        consulta+= "\n\n\nELIMINACIONES HECHAS POR: "+nombresVillanos->at(i);
        for(int j = 0 ; i<(eliminacionesVillanos->at(i).length()+1);i++){
            consulta+=eliminacionesVillanos->at(i).at(j);
        }
    }
    return escribirArchivo(consulta.toStdString());
}

//VIVOS MUERTOS Y ELIMINADOS
QString Mundo::consultarEstadosHumanos(){
    QString textoConsulta = "";
    return escribirArchivo(textoConsulta.toStdString());
}

//EN CADENA PA BAJO
QString Mundo::consultarAmigosAmigos(QString ID){
    QString textoConsulta = "";
    return escribirArchivo(textoConsulta.toStdString());
}

//Un deporte en especifico
QString Mundo::consultarDeporte(QString deporteBuscado){
    QString textoConsulta = "[ ";
    int indice = deportes->nombresDeportes.indexOf(deporteBuscado);
    QList<Persona*> * listaDeportistas = deportes->deportes->at(indice);
    for(int i = 0 ; i<listaDeportistas->size();i++ ) {
        if(!listaDeportistas->at(i)->deportes->contains(deporteBuscado)) qDebug()<<"\n\nNO LO TENGO NE DEPORTEEEES";
        textoConsulta +=  listaDeportistas->at(i)->nombre+"--"+listaDeportistas->at(i)->ID+", \n";
    }

    return escribirArchivo(textoConsulta.toStdString());
}

//Info de la familia segun ID
QString Mundo::consultarFamiliaID(QString ID){
    QString textoConsulta = "", pareja = "";

    if(!listaPersonasTotales->buscarNodo(ID)) return "Error obteniendo la persona";
    Persona * persona = listaPersonasTotales->buscarNodo(ID)->dato;


    if(persona->pareja) pareja = persona->pareja->nombre;

    for(int i = 0 ;i<persona->hijos->length() ;i++){
        textoConsulta +="\n"+consultarHumanoID(persona->hijos->at(i)->ID)+"\n";
    }
    return escribirArchivo(textoConsulta.toStdString());
}



//Devolver toda la info de un humano segun ID
QString Mundo::consultarHumanoID(QString ID){
    QString textoConsulta = "", vivo = "", madre = "N/A", padre = "N/A";


    if(!listaPersonasTotales->buscarNodo(ID)) return "Error obteniendo la persona";
    Persona * persona = listaPersonasTotales->buscarNodo(ID)->dato;


    if(persona->vivo) vivo = "Vivo";
    else vivo = "Muerto";
    if(persona->madre) {
        madre = persona->madre->nombre;
        padre = persona->padre->nombre;
    }

    textoConsulta+="\n"+crearLog(persona)+"\n La persona se encuentra"+vivo
            +"\nPractica los deportes: "+crearDeportesTxt(persona)+"Un total de: "+QString::number(persona->ctdEjercicioxSemana)+" veces."
            + "\tPais de residencia: "+persona->pais+"\nSu profesion es: "+persona->profesion
            +"\t Estado Marital: "+persona->estadoMarital+" Creencia: "+persona->creencia
            +crearPecadosTxt(persona)+crearBuenasAccionesTxt(persona)
            +crearLogSalvacionTxt(persona)+crearLogMuerteTxt(persona);

    return escribirArchivo(textoConsulta.toStdString());
}

int Mundo::obtainPivot(QList<Persona*>* lista, int min, int max){
    Persona * pivot = lista->at(max);
    int greaterIndex = min-1;
    for(int j=min; j<=max-1; j++){
        if(lista->at(j)->ID < pivot->ID){
            greaterIndex++;
            lista->swapItemsAt(j, greaterIndex);
        }
    }
    lista->swapItemsAt(greaterIndex+1, max);
    return greaterIndex+1;

}

void Mundo::quickSortFunction(QList<Persona*> * lista, int min, int max){
    if(min < max){
        int pivot = obtainPivot(lista, min, max);
        quickSortFunction(lista, min, pivot-1);
        quickSortFunction(lista, pivot+1, max);
    }
}

void Mundo::quickSort(QList<Persona*> * lista){
    quickSortFunction(lista, 0, lista->size()-1);
}

QString Mundo::terminarPartida(){
    QString mensaje = "";
    mensaje += "Cantidad de eliminados: " + QString::number(cantAsesinados);
    mensaje += "\n Cantidad de salvados: " + QString::number(cantSalvados);

    if(cantSalvados >= cantAsesinados){
      mensaje += "\n Los Avengers Ganaron!\n";
    }
    else{
      mensaje += "\n Thanos y los Villanos ganaron!\n";
    }

    return mensaje;
}
