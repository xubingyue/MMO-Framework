/*
Author: Gudakov Ramil Sergeevich a.k.a. Gauss 
Гудаков Рамиль Сергеевич 
Contacts: [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/

#ifndef ModuleGraphicEngineH
#define ModuleGraphicEngineH

#include <boost/smart_ptr/scoped_ptr.hpp>

#include "CallBackRegistrator.h"
#include "ModuleComponent.h"
#include "GraphicEngine_Ogre_MyGUI.h"

class TGraphicEngine_Ogre_MyGUI;

class DllExport TModuleGraphicEngine : public TModuleComponent
{
	boost::scoped_ptr<TGraphicEngine_Ogre_MyGUI> mGE;

  TCallBackRegistrator1<TModuleDev*> mCBSetup;
  TCallBackRegistrator0              mCBStopEvent; 
public:
  TModuleGraphicEngine();

  virtual void StartEvent();
  virtual bool WorkInherit();
  virtual void StopEvent();

  TGraphicEngine_Ogre_MyGUI* GetGE();

  // графический движок требуется настраивать в том же потоке, в котором он работает
  TCallBackRegistrator1<TModuleDev*>* GetCBSetup();

  TCallBackRegistrator0* GetCBStopEvent();
protected:
};

#endif
