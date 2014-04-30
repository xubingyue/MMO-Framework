/*
Author: Gudakov Ramil Sergeevich a.k.a. Gauss 
������� ������ ��������� 
Contacts: [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/

#ifndef FileInfoHDDH
#define FileInfoHDDH

#include <stdio.h>
#include <string>

#include "TypeDef.h"


class SHARE_EI TFileInfoHDD
{
protected:
  std::string sPath;
  FILE* pFile;
public:

	TFileInfoHDD();
	virtual ~TFileInfoHDD();

	virtual bool ReOpen(char* path, bool append = false) = 0;
	virtual bool IsOpen();
 	virtual void Close();

	void GetName(std::string& path_name);
	void GetPath(std::string& path_name);
	void GetFullPathName(std::string& path_name);
};

#endif
