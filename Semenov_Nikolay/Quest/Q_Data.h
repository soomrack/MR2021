#ifndef Q_DATA_Q_DATA_H
#define Q_DATA_Q_DATA_H

#include "S:\Code_Vault\CLionProjects\Q_API\Q_API.h"

class Q_Ticket: public Ticket {
public:	Q_Ticket() {};
    ~Q_Ticket() {};
};

class A_Quest : public Quest {
public:
    A_Quest() = default;;
    ~A_Quest() = default;;
};

A_Quest init_quest();
#endif //Q_DATA_Q_DATA_H
