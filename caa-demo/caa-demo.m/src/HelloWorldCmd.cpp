#include "HelloWorldCmd.h"

#include "CATCreateExternalObject.h"
CATCreateClass(HelloWorldCmd);

HelloWorldCmd::HelloWorldCmd() : CATCommand(NULL, "HelloWorldCmd")
{
    RequestStatusChange(CATCommandMsgRequestExclusiveMode);
}

HelloWorldCmd::~HelloWorldCmd()
{
}

CATStatusChangeRC HelloWorldCmd::Activate(CATCommand *iFromClient, CATNotification *iEvtDat)
{

    RequestDelayedDestruction();
    return (CATStatusChangeRCCompleted);
}

CATStatusChangeRC HelloWorldCmd::Desactivate(CATCommand *iFromClient, CATNotification *iEvtDat)
{
    RequestDelayedDestruction();
    return (CATStatusChangeRCCompleted);
}

CATStatusChangeRC HelloWorldCmd::Cancel(CATCommand *iFromClient, CATNotification *iEvtDat)
{
    RequestDelayedDestruction();
    return (CATStatusChangeRCCompleted);
}
