#include "Addin.h"

#include "CATCommandHeader.h"
MacDeclareHeader(AddinHeader);
CATImplementClass(Addin, Implementation, CATBaseUnknown, CATnull);

Addin::Addin() : CATBaseUnknown()
{
}

Addin::~Addin()
{
}

void Addin::CreateCommands()
{
new AddinHeader ("HelloWorld", "caa-demo", "HelloWorldCmd", (void *)NULL, CATFrmAvailable);
}

CATCmdContainer *Addin::CreateToolbars()
{
NewAccess(CATCmdContainer, toolbar, toolbar);
AddToolbarView(toolbar, 1, Top);

NewAccess(CATCmdStarter, HelloWorld, o_HelloWorld);
SetAccessCommand(HelloWorld, "HelloWorld");


SetAccessChild(toolbar, HelloWorld);

return toolbar;
}

// TIE or TIEchain definitions
#include "TIE_CATIAfrGeneralWksAddin.h"
TIE_CATIAfrGeneralWksAddin(Addin);

// Methods implementation