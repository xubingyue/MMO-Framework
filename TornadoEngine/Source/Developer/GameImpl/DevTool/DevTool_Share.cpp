/*
Author: Gudakov Ramil Sergeevich a.k.a. Gauss 
Гудаков Рамиль Сергеевич 
Contacts: [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/

#include "DevTool_Share.h"
#include "ListModules.h"

#include "Components.h"
#include "ModuleLogic.h"
#include "ModuleGraphicEngine.h"
#include "ModuleAloneGUI.h"
#include "ModuleMMOEngineClient.h"
#include "ModuleMMOEngineSlave.h"
#include "ModuleMMOEngineMaster.h"
#include "ModuleMMOEngineSuperServer.h"
#include "ModulePhysicEngine.h"
#include "ModuleSoundEngine.h"
#include "ModuleTimer.h"
#include "ModuleDatabase.h"

#include "ParserXMLResource.h"

#include <boost/foreach.hpp>

#include "GraphicEngine_Ogre_MyGUI.h"
#include "EventGameEngine.h"

namespace nsDevTool_Share
{
  // для именования модулей в конвейере для Ядра
  // сделано так с целью присутствия в коде имени модуля единожды
#define NAME_MODULE(enumID) ""#enumID

#define NAME_ID(X) NAME_MODULE(X),X

  const char* sFileResources = "Resources.xml";

  const char* sCore           = "Core";
  const char* sSkin           = "Skin";
  const char* sConveyer       = "Conveyer";
  const char* sItems          = "Items";
}

using namespace nsListModules;

TDevTool_Share::TDevTool_Share()
{
  InitMapModules();
}
//-----------------------------------------------------------------------
TDevTool_Share::~TDevTool_Share()
{
  BOOST_FOREACH(TMapIntPtrModuleVT& vtID_Ptr, mMapID_PtrModules)
    delete vtID_Ptr.second;
}
//-----------------------------------------------------------------------
void TDevTool_Share::Init()
{
  // загрузка и разбор XML файла (ресурсы)
  TParserXMLResource parser;
  std::string file = nsDevTool_Share::sFileResources;
  bool res = parser.Work(file);

  TResourcesGraphicEngine mGraphicEngine_Resources;
  TResources mGame_Resources;
  TResources mGUI_Resources;
  TResources mGameEngine_Resources;

  parser.GetResultGame(mGame_Resources);
  parser.GetResultGameEngine(mGameEngine_Resources);
  parser.GetResultGUI(mGUI_Resources);
  parser.GetResultGraphicEngine(mGraphicEngine_Resources);
  
  mPluginsCfg = mGraphicEngine_Resources.GetPluginsCfg();

  mGame_Resources.GetResource(mListRGame);
  mGameEngine_Resources.GetResource(mListRGameEngine);
  mGUI_Resources.GetResource(mListRGUI);
  mGraphicEngine_Resources.GetResource(mListRGraphicEngine);

  BOOST_FOREACH(TResources::TPairStrStr& pairNameType, mListRGame)
  {
    if(pairNameType.second==nsDevTool_Share::sItems)
    {
      mPathItems = pairNameType.first;
      break;
    }
  }
}
//-----------------------------------------------------------------------
IModule* TDevTool_Share::GetModuleByName(const char* sName)
{
  int id = FindIDByNameModule(sName);
  TModuleDev* pModule = FindPtrModuleByID(id);
  if(pModule)
    return pModule;

  pModule = GetModuleByID(id);
  pModule->SetID(id);
  pModule->SetName(sName);
  Add(id,pModule);
  return pModule;
}
//-----------------------------------------------------------------------
void TDevTool_Share::InitMapModules()
{
  Add(NAME_ID(GraphicEngine)       );
  Add(NAME_ID(AloneGUI)            );
  Add(NAME_ID(MMOEngineClient)     );
  Add(NAME_ID(MMOEngineSlave)      );
  Add(NAME_ID(MMOEngineMaster)     );
  Add(NAME_ID(MMOEngineSuperServer));
  Add(NAME_ID(Logic)               );
  Add(NAME_ID(PhysicEngine)        );
  Add(NAME_ID(SoundEngine)         );
  Add(NAME_ID(DataBase)            );
  Add(NAME_ID(Timer)               );
}
//-----------------------------------------------------------------------
int TDevTool_Share::FindIDByNameModule(std::string name)
{
  TMapStrIntIt fit = mMapNameID_Modules.find(name);
  if(fit==mMapNameID_Modules.end())
    return Undef;
  return fit->second;
}
//-----------------------------------------------------------------------
TModuleDev* TDevTool_Share::FindPtrModuleByID(int id)
{
  TMapIntPtrModuleIt fit = mMapID_PtrModules.find(id);
  if(fit==mMapID_PtrModules.end())
    return NULL;
  return fit->second;
}
//-----------------------------------------------------------------------
void TDevTool_Share::Add(int id, TModuleDev* pModule)
{
  if(pModule)
    mMapID_PtrModules.insert(TMapIntPtrModuleVT(id, pModule));
}
//-----------------------------------------------------------------------
void TDevTool_Share::Add(std::string name, int id)
{
  mMapNameID_Modules.insert(TMapStrIntVT(name, id));
}
//-----------------------------------------------------------------------
std::string TDevTool_Share::GetFileDescConveyer()
{
  BOOST_FOREACH(TResources::TPairStrStr& pairNameType, mListRGameEngine)
  {
    if(pairNameType.second==nsDevTool_Share::sConveyer)
      return pairNameType.first;
  }
  BL_FIX_BUG();
  return "";
}
//-----------------------------------------------------------------------
void TDevTool_Share::EventGameEngine(int id, const char* sDesc)
{
  switch(id)
  {
    case nsGameEngine::eAfterCreateDevTool:
      Init();
      break;
    case nsGameEngine::eAfterCreateModules:
    // назначить логике компоненты
      SetComponentsForLogic();
      break;
    case nsGameEngine::eStartThreads:
      break;
    case nsGameEngine::eStopThreads:
      break;
    case nsGameEngine::eStopThreadsEnd:
      break;
    case nsGameEngine::eParseFileConveyerError:
    {
      int a = 0;
    }
      break;
    case nsGameEngine::eModuleNotMade:
      break;
    case nsGameEngine::eThreadsNotExist:
      break;
  }
}
//-----------------------------------------------------------------------
void TDevTool_Share::SetupGraphicEngine(TModuleDev* pModule)
{
  TModuleGraphicEngine* pGE = (TModuleGraphicEngine*)pModule;
  // настройка перед запуском
  pGE->GetGE()->InitOGRE(mPluginsCfg);
  // пути для ресурсов графического движка
  BOOST_FOREACH(TResources::TPairStrStr& pairNameType, mListRGraphicEngine)
    pGE->GetGE()->AddResource(pairNameType.first, pairNameType.second);
  // оболочка и ядро для GUI
  std::string sSkin, sCore;
  std::set<std::string> setXmlDelegate;
  BOOST_FOREACH(TResources::TPairStrStr& pairNameType, mListRGUI)
  {
    if(pairNameType.second==nsDevTool_Share::sCore)
      sCore = pairNameType.first;
    if(pairNameType.second==nsDevTool_Share::sSkin)
      sSkin = pairNameType.first;
  }
  BL_ASSERT(sCore.length() && sSkin.length());
  pGE->GetGE()->InitMyGUI(sCore, sSkin);
}
//-----------------------------------------------------------------------
void TDevTool_Share::SetComponentsForLogic()
{
  TComponents components;
  components.pGraphicEngine   		 = (TModuleGraphicEngine*)  		 FindPtrModuleByID(GraphicEngine);
  components.pAloneGUI        		 = (TModuleAloneGUI*)  		       FindPtrModuleByID(AloneGUI);;
  components.pMMOEngineClient 		 = (TModuleMMOEngineClient*)		 FindPtrModuleByID(MMOEngineClient);
  components.pMMOEngineSlave  		 = (TModuleMMOEngineSlave*) 		 FindPtrModuleByID(MMOEngineSlave);
  components.pMMOEngineMaster 		 = (TModuleMMOEngineMaster*)		 FindPtrModuleByID(MMOEngineMaster);
  components.pMMOEngineSuperServer = (TModuleMMOEngineSuperServer*)FindPtrModuleByID(MMOEngineSuperServer);
  components.pPhysicEngine         = (TModulePhysicEngine*)        FindPtrModuleByID(PhysicEngine);
  components.pSoundEngine          = (TModuleSoundEngine*)				 FindPtrModuleByID(SoundEngine);
  components.pDataBase             = (TModuleDataBase*)						 FindPtrModuleByID(DataBase);
  components.pTimer                = (TModuleTimer*)   						 FindPtrModuleByID(Timer);

  // ищем логику
  TModuleLogic* pLogic = (TModuleLogic*)FindPtrModuleByID(Logic);
  if(pLogic)
  {
    int id_logic = pLogic->GetID();
    components.SetLogicID(id_logic);
    pLogic->SetComponents(components);
    pLogic->GetFGI()->Init_XML(mPathItems);
#ifdef _DEBUG
    pLogic->GetFGI()->ReloadFromStorageAll_XML();
#else
    // карта сама по цепочке ("раскрутит") загрузит итэмы
    pLogic->GetFGI()->ReloadFromStorageByType_XML(TFactoryGameItem::Map);
    pLogic->GetFGI()->ReloadFromStorageByType_XML(TFactoryGameItem::Model);
    pLogic->GetFGI()->ReloadFromStorageByType_XML(TFactoryGameItem::Shape);
#endif
    pLogic->InitLog();
    pLogic->ParseCmd(mVecArg);
  }
  else 
    {BL_FIX_BUG();}
}
//-----------------------------------------------------------------------
void TDevTool_Share::SetVectorParam(std::vector<std::string>& vecArg)
{
  mVecArg = vecArg;
}
//-----------------------------------------------------------------------
TModuleDev* TDevTool_Share::GetModuleByID(int id)
{
  TModuleDev* pModule = NULL;
  switch(id)
  {
    // ядро
    case Logic: pModule = GetModuleLogic();                                      break;
    // периферия
    case GraphicEngine:          pModule = new TModuleGraphicEngine;// единственный модуль, который требуется настраивать в том же потоке
      ((TModuleGraphicEngine*)pModule)->GetCBSetup()->Register(&TDevTool_Share::SetupGraphicEngine,this);
      break;
    case AloneGUI:               pModule = new TModuleAloneGUI;                  break;
    case PhysicEngine:           pModule = new TModulePhysicEngine;              break;
    case MMOEngineClient:        pModule = new TModuleMMOEngineClient;           break;
    case MMOEngineSlave:         pModule = new TModuleMMOEngineSlave;            break;
    case MMOEngineMaster:        pModule = new TModuleMMOEngineMaster;           break;
    case MMOEngineSuperServer:   pModule = new TModuleMMOEngineSuperServer;      break;
    case SoundEngine:            pModule = new TModuleSoundEngine;               break;
    case DataBase:               pModule = new TModuleDataBase;                  break;
    case Timer:                  pModule = new TModuleTimer;                     break;
    default:BL_FIX_BUG();
  }
  return pModule;
}
//-----------------------------------------------------------------------