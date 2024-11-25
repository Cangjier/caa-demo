#ifndef HelloWorldCmd_H
#define HelloWorldCmd_H

#include "CATCommand.h"

class HelloWorldCmd : public CATCommand
{
public:
    HelloWorldCmd();
    virtual ~HelloWorldCmd();

    virtual CATStatusChangeRC Activate(
        CATCommand *iFromClient,
        CATNotification *iEvtDat);

    virtual CATStatusChangeRC Desactivate(
        CATCommand *iFromClient,
        CATNotification *iEvtDat);

    virtual CATStatusChangeRC Cancel(
        CATCommand *iFromClient,
        CATNotification *iEvtDat);
};
#endif