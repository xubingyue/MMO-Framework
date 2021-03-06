/*
Author: Gudakov Ramil Sergeevich a.k.a. Gauss 
Гудаков Рамиль Сергеевич 
Contacts: [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/

#ifndef TerrainItemH
#define TerrainItemH

#include "BaseItem.h"
#include <vector>

#ifdef WIN32
#pragma pack(push, 1)
#endif

struct DllExport TTerrainItem : public TBaseItem
{
  struct DllExport TLOD
  {
    float distance;// максимальная дистанция
    std::string color;
    std::string normal;
  };
  typedef std::vector<TLOD> TVecLOD;

  struct DllExport TPoint
  {
    float x;
    float y;
    float h;
    float u;
    float v;
  };

  typedef std::vector<TPoint> TVecPoint;


  float mWidth;
  float mLength;

  TVecLOD   mGraphic;
  TVecPoint mHeightMap;

  TTerrainItem(std::string& name);
}_PACKED;

#if defined( WIN32 )
#pragma pack(pop)
#endif

#endif
