#ifndef REGISTROIDS_H
#define REGISTROIDS_H
#include <QString>
#include <QList>
#include <QRandomGenerator>
struct RegistroIds{
    QList<QString> registro[10][10];
    int MIN = 0;
    int MAX = 9999999;

public:
    // Llamar a esta funcion a la hora de crear un humano y requerir un ID válido
    // Generará un numero random de 0 - 9 999 999
    // Validará su disponibilidad y si es así lo retornará para ser agregado a los datos de la persona.
    // De lo contrario generará otro numero random y  lo validará hasta que encuentre uno disponible.
    int generarId();

private:
    int generateRandom();
    QString convertirAString(int id);
    bool validarId(QString id);

};

int RegistroIds::generarId(){
    int id;
    do{
        id = generateRandom();

    }while(!validarId(convertirAString(id)));
    return id;
}

QString RegistroIds::convertirAString(int id){
    QString numero = "0000000"; //7 digitos (El valor máximo es 9 999 999)
    QString ID = QString::number(id);
    int i = ID.length();
    numero.insert(7-i, ID); //Rellena el string numero con el string del entero -> EJ: id = 765 --> return: 0 000 765
    return numero;
}

bool RegistroIds::validarId(QString id){
    int i = id.at(0).digitValue();
    int j = id.at(1).digitValue();
    QList<QString> lista = registro[i][j];
    for(int k = 0; k<lista.size(); k++)
        if(id == lista.at(k)) return false;
    lista.append(id);
    return true;
}

int RegistroIds::generateRandom(){
    std::uniform_int_distribution<int> dist(MIN,MAX);
    int id = dist(*QRandomGenerator::global());
    return id;
}

#endif // REGISTROIDS_H
