#include "Persistence.h"

Persistence &Persistence::getPersistence(){
    static Persistence instance;
    return instance;
}
