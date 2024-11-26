#include "Addin.h"
#include "Tidy_GBKString.h"
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
    Tidy::GBKString hello = "helloworld";
new AddinHeader ("HelloWorld", "CaaDemo", "HelloWorldCmd", (void *)NULL, CATFrmAvailable);
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