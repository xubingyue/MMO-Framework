/*
Author: Gudakov Ramil Sergeevich a.k.a. Gauss 
Гудаков Рамиль Сергеевич 
Contacts: [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/

#include "IXML.h"

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <boost/lexical_cast.hpp>

using namespace std;

bool IXML::AddChildSection(const char* childName, int num, const char* name)
{
  RET_FALSE(EnterSection(childName, num));
    RET_FALSE(AddSection(name));
  RET_FALSE(LeaveSection());
  return true;
}
//------------------------------------------------------------------
bool IXML::RemoveChildSection(const char* childName, int numChild, const char* name, int num)
{
  RET_FALSE(EnterSection(childName, numChild));
    RET_FALSE(RemoveSection(name,num));
  RET_FALSE(LeaveSection());
  return true;
}
//------------------------------------------------------------------
//------------------------------------------------------------------
bool IXML::ReadDouble(const char* name, int num, double& v)
{
  string s = ReadSection(name, num);
  if(s.length()==0)
    return false;
  v = boost::lexical_cast<double>(s.data());

  if(errno==ERANGE)
    return false;
  return true;
}
//------------------------------------------------------------------
bool IXML::ReadFloat(const char* name, int num, float & v)
{
  string s = ReadSection(name, num);
  if(s.length()==0)
    return false;
  v = boost::lexical_cast<float>(s.data());

  if(errno==ERANGE)
    return false;
  return true;
}
//------------------------------------------------------------------
bool IXML::ReadInt(const char* name, int num, int & v)
{
  string s = ReadSection(name, num);
  if(s.length()==0)
    return false;
  v = boost::lexical_cast<int>(s.data());
  return true;
}
//------------------------------------------------------------------
bool IXML::ReadUint(const char* name, int num, unsigned int & v)
{
  string s = ReadSection(name, num);
  if(s.length()==0)
    return false;
  v = boost::lexical_cast<int>(s.data());
  return true;
}
//------------------------------------------------------------------
bool IXML::ReadFloat3(const char* name, int num, float * v3)// разделитель или "space" или ";"
{
  string s = ReadSection(name, num);
  int size = s.length();
  if(size==0)
    return false;
  if(sscanf(s.data(),"%f;%f;%f",&v3[0],&v3[1],&v3[2])!=3) return false;

  return true;
}
//------------------------------------------------------------------
bool IXML::ReadFloat4(const char* name, int num, float * v4)
{
  string s = ReadSection(name, num);
  int size = s.length();
  if(size==0)
    return false;
  if(sscanf(s.data(),"%f;%f;%f;%f",&v4[0],&v4[1],&v4[2],&v4[3])!=4) return false;

  return true;
}
//------------------------------------------------------------------
bool IXML::ReadDouble(int index, double& v)
{
  string s = ReadSection(index);
  if(s.length()==0)
    return false;
  v = boost::lexical_cast<double>(s.data());
  return true;
}
//------------------------------------------------------------------
bool IXML::ReadFloat(int index, float & v)
{
  string s = ReadSection(index);
  if(s.length()==0)
    return false;
  v = boost::lexical_cast<float>(s.data());
  return true;
}
//------------------------------------------------------------------
bool IXML::ReadInt(int index, int & v)
{
  string s = ReadSection(index);
  if(s.length()==0)
    return false;
  v = boost::lexical_cast<int>(s.data());
  return true;
}
//------------------------------------------------------------------
bool IXML::ReadUint(int index, unsigned int & v)
{
  string s = ReadSection(index);
  if(s.length()==0)
    return false;
  v = boost::lexical_cast<int>(s.data());
  return true;
}
//------------------------------------------------------------------
bool IXML::ReadFloat3(int index, float * v3)// разделитель или "space" или ";"
{
  string s = ReadSection(index);
  int size = s.length();
  if(size==0)
    return false;
  if(sscanf(s.data(),"%f;%f;%f",&v3[0],&v3[1],&v3[2])!=3) return false;

  return true;
}
//------------------------------------------------------------------
bool IXML::ReadFloat4(int index, float * v4)
{
  string s = ReadSection(index);
  int size = s.length();
  if(size==0)
    return false;
  if(sscanf(s.data(),"%f;%f;%f;%f",&v4[0],&v4[1],&v4[2],&v4[3])!=4) return false;

  return true;
}
//------------------------------------------------------------------
//------------------------------------------------------------------
bool IXML::WriteDouble(const char* name, int num, double v)
{
  std::string s = boost::lexical_cast<std::string>(v);
  return WriteSection(name, num, s);
}
//------------------------------------------------------------------
bool IXML::WriteFloat(const char* name, int num, float v)
{
  char s[100];
  sprintf(s,"%f",v);
  return WriteSection(name, num, string(s));
}
//------------------------------------------------------------------
bool IXML::WriteInt(const char* name, int num, int v)
{
  char s[100];
  sprintf(s,"%d",v);
  return WriteSection(name, num, string(s));
}
//------------------------------------------------------------------
bool IXML::WriteUint(const char* name, int num, unsigned int v)
{
  char s[100];
  sprintf(s,"%u",v);
  return WriteSection(name, num, string(s));
}
//------------------------------------------------------------------
bool IXML::WriteFloat3(const char* name, int num, float* v3)// разделитель ";"
{
  char s[100];
  sprintf(s,"%f;%f;%f",v3[0],v3[1],v3[2]);
  return WriteSection(name, num, string(s));
}
//------------------------------------------------------------------
bool IXML::WriteFloat4(const char* name, int num, float* v4)
{
  char s[100];
  sprintf(s,"%f;%f;%f;%f",v4[0],v4[1],v4[2],v4[3]);
  return WriteSection(name, num, string(s));
}
//------------------------------------------------------------------
bool IXML::WriteDouble(int index, double v)
{
  std::string s = boost::lexical_cast<std::string>(v);
  return WriteSection(index, string(s));
}
//------------------------------------------------------------------
bool IXML::WriteFloat(int index, float v)
{
  char s[100];
  sprintf(s,"%f",v);
  return WriteSection(index, string(s));
}
//------------------------------------------------------------------
bool IXML::WriteInt(int index, int v)
{
  char s[100];
  sprintf(s,"%d",v);
  return WriteSection(index, string(s));
}
//------------------------------------------------------------------
bool IXML::WriteUint(int index, unsigned int v)
{
  char s[100];
  sprintf(s,"%u",v);
  return WriteSection(index, string(s));
}
//------------------------------------------------------------------
bool IXML::WriteFloat3(int index, float* v3)// разделитель ";"
{
  char s[100];
  sprintf(s,"%f;%f;%f",v3[0],v3[1],v3[2]);
  return WriteSection(index, string(s));
}
//------------------------------------------------------------------
bool IXML::WriteFloat4(int index, float* v4)
{
  char s[100];
  sprintf(s,"%f;%f;%f;%f",v4[0],v4[1],v4[2],v4[3]);
  return WriteSection(index, string(s));
}
//------------------------------------------------------------------
