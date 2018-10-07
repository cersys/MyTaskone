#include "comregist.h"

regWindow *Comregist::p_reg = NULL;

Comregist::Comregist()
{

}

void Comregist::initreg(){
    p_reg = new regWindow();
}
