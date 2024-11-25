#ifndef AddinH
#define AddinH

#include "CATIAfrGeneralWksAddin.h"
#include "CATBaseUnknown.h"
#include "CATCreateWorkshop.h"
#include "CATCmdContainer.h"

class Addin : public CATBaseUnknown
{
  CATDeclareClass;

public:
  Addin();
  virtual ~Addin();
  void CreateCommands();
  CATCmdContainer *CreateToolbars();

private:
  Addin(Addin &);
  Addin &operator=(Addin &);
};

//-----------------------------------------------------------------------

#endif
