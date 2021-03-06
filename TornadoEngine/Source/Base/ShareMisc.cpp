/*
Author: Gudakov Ramil Sergeevich a.k.a. Gauss 
Гудаков Рамиль Сергеевич 
Contacts: [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/

#include "ShareMisc.h"
#include "BL_Debug.h"
#include "FileOperation.h"
#ifdef WIN32
	#include <windows.h>
	#include <conio.h>
	#include <fcntl.h>
	#include <io.h>
	#include <wchar.h>
	#include <stdio.h>
#else
#endif

int GetCountCoreCPU()
{
	int countCore = 1;
#ifdef WIN32
	SYSTEM_INFO siSysInfo;
	GetSystemInfo(&siSysInfo);
	countCore = siSysInfo.dwNumberOfProcessors;
#else
  countCore = 1;// доделать
#endif
	return countCore;
}
//--------------------------------------------------
static bool g_flgConsoleExist = false;
void CreateConsole()
{
  if(g_flgConsoleExist) 
    return;
#ifdef WIN32
	BOOL resAllocConsole = AllocConsole();
  if(resAllocConsole==false)
    return;
	// Out
  int hCrt = _open_osfhandle((long) GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
	FILE *hf = _fdopen( hCrt, "w" );
	*stdout = *hf;
#endif
  g_flgConsoleExist = true;
}
//--------------------------------------------------
void DeleteConsole()
{
#ifdef WIN32
  BOOL resFreeConsole = FreeConsole(); 
  BL_ASSERT(resFreeConsole);
#endif
  g_flgConsoleExist = false;
}
//--------------------------------------------------
bool IsConsoleExist()
{
  return g_flgConsoleExist;
}
//--------------------------------------------------
bool SetCurrentPathByFile(char* sPathFile)
{
  // иногда вызов происходит под отладкой, менять путь, чтобы был доступ к файлу с указанием ресурсов.
  char sAbsPath[1000];
  if(FindAbsPath(sPathFile, sAbsPath, sizeof(sAbsPath))==false)
  {
    BL_MessageBug(sPathFile);
    return false;
  }
  UpPath(sAbsPath);// нужен путь к папке, а не к файлу
  if(SetCurrentPath(std::string(sAbsPath))==false)
  {
    BL_MessageBug(sPathFile);
    return false;
  }
  return true;
}
//--------------------------------------------------
