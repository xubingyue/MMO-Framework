/*
Author: Gudakov Ramil Sergeevich a.k.a. Gauss 
Гудаков Рамиль Сергеевич 
Contacts: [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/

#ifndef MaterialItemH
#define MaterialItemH

#include <vector>
#include "BaseItem.h"

struct DllExport TMaterialItem : public TBaseItem
{
  struct TLOD
  {
    float distance;// максимальная дистанция
    std::string color;
    std::string normal;
  };
  typedef std::vector<TLOD>    TVecLOD;
  typedef std::vector<TVecLOD> TVecVariant;

  struct TPhysic
  {
    float density;
    float elasticity;
    float friction;
  };

  TVecVariant mGraphic;
  TPhysic mPhysic;

  TMaterialItem(std::string& name);
};

#endif