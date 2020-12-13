
#include"litteral.h"
#include <QString>
QString Entier::versString() const {
    return QString::number(entier);
}

QString Reel::versString() const {
    return QString::number(reel);
}

QString Rationnel::versString() const {
    return QString::number(numerateur)+QString::number(denominateur);
}

