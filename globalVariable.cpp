#include "globalVariable.h"

QMutex globalVariable::mutex[4];
dataNote* globalVariable::first[4];
