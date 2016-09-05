#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H

#include <QMutex>
#include "dataNote.h"

class globalVariable{
	public:
		static QMutex mutex[4];
		static dataNote *first[4];
};

#endif
