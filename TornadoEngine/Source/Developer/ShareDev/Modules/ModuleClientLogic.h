/*
Author: Gudakov Ramil Sergeevich a.k.a. Gauss 
Гудаков Рамиль Сергеевич 
Contacts: [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/

#ifndef ModuleClientLogicH
#define ModuleClientLogicH

#include "ModuleLogic.h"
#include "InputCmdDevTool.h"
#include <boost/smart_ptr/scoped_ptr.hpp>

#include "GP_AggregationScenario_Client.h"

class DllExport TModuleClientLogic : public TModuleLogic
{
protected:
  TInputCmdDevTool               mInputCmd;

  boost::scoped_ptr<TGP_AggregationScenario_Client> mAggregationScenario_Client;

public:
  TModuleClientLogic();

  virtual bool WorkInherit();
  virtual void ParseCmd(std::vector<std::string>& arg);
protected:
  virtual bool WorkClient() = 0;
};

#endif
