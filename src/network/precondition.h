#ifndef PRECONDITION_H
#define PRECONDITION_H
#include <exception>
#include "PreconditionFailException.h"

#define precondition(attr) if (!(attr)) { throw PreconditionFailException(#attr); }

#endif
