#include "comlogin.h"

login *Comlogin::p_login = NULL;

Comlogin::Comlogin()
{

}

void Comlogin::Initlogin(){
    p_login = new login();
}
