/*
Based on Miranda plugin template, originally by Richard Hughes
http://miranda-icq.sourceforge.net/

Miranda IM: the free IM client for Microsoft Windows

Copyright 2000-2006 Miranda ICQ/IM project,
all portions of this codebase are copyrighted to the people
listed in contributors.txt.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

/************************************************************************/
/*  Author: Artem Shpynov aka FYR     mailto:shpynov@nm.ru              */
/*  icons by Angeli-Ka                                                  */
/*  January 12, 2006													*/
/************************************************************************/


//Start of header
// Native include
#include <windows.h>
#include <stdio.h>

//required Miranda SDK (files are in include subfolder)
#include "include/newpluginapi.h"
#include "include/m_cluiframes.h"
#include "include/m_database.h"

//required iconlib header (not in Miranda SDK)
#include "include/m_icolib.h"

//resource definition header  
#include "resource.h"

//Fingerprint services definition header
#include "m_fingerprint.h"

//Definition from other Miranda IM SDK
#define ME_SYSTEM_MODULESLOADED       "Miranda/System/ModulesLoaded"
#define ME_SYSTEM_OKTOEXIT            "Miranda/System/OkToExitEvent"
#define ME_OPT_INITIALISE             "Opt/Initialise"
#define MS_UTILS_PATHTORELATIVE       "Utils/PathToRelative"
#define MS_PROTO_GETCONTACTBASEPROTO  "Proto/GetContactBaseProto"
#define MS_LANGPACK_TRANSLATESTRING   "LangPack/TranslateString"
#define Translate(s)   ((char*)CallService(MS_LANGPACK_TRANSLATESTRING,0,(LPARAM)(s)))

// End of SDK headers include

HANDLE hExtraImageListRebuild;       // hook event handle for ME_CLIST_EXTRA_LIST_REBUILD
HANDLE hExtraImageApply;             // hook event handle for ME_CLIST_EXTRA_IMAGE_APPLY
HANDLE hContactSettingChanged;       // hook event handle for ME_DB_CONTACT_SETTINGCHANGED
HANDLE hOptInitialise;	    	     // hook event handle for ME_OPT_INITIALISE
HANDLE hModulesLoaded;
HANDLE hSystemOKToExit;			     // hook event handle for ME_SYSTEM_OKTOEXIT
HANDLE compClientServ=NULL;
HANDLE getClientIcon=NULL;

int OnExtraIconListRebuild(WPARAM wParam, LPARAM lParam);
int OnExtraImageApply(WPARAM wParam, LPARAM lParam);
int OnContactSettingChanged(WPARAM wParam, LPARAM lParam);
int OnOptInitialise(WPARAM wParam, LPARAM lParam);
int OnModulesLoaded(WPARAM wParam, LPARAM lParam);
int OnSystemOKToExit(WPARAM wParam, LPARAM lParam);
int ServiceSameClients(WPARAM wParam, LPARAM lParam);
int ServiceGetClientIcon(WPARAM wParam, LPARAM lParam);

int ApplyFingerprintImage(HANDLE hContact,char *MirVer);
BOOL __inline WildCompare(char * name, char * mask);
BOOL WildCompareProc(char * name, char * mask);
HICON LoadIconFromExternalFile(char *filename,int i,BOOL UseLibrary,BOOL registerit,char *IconName,int flag,char *Description,int internalidx);


typedef struct _knfpMask 
{
  char * szIconName;
  char * szMask;
  char * szClientDescription;
  char * szIconFileName;
  int    iIconIndex;
  BYTE    registeredIndex;
  int	SectionFlag;
}KN_FP_MASK;

//Including of fingerprint masks
#include "fingerprints.h"
//End of header

HINSTANCE g_hInst;
PLUGINLINK *pluginLink;


PLUGININFO pluginInfo={
  sizeof(PLUGININFO),
    "Fingerprint",
    PLUGIN_MAKE_VERSION(0,0,0,25),
    "Fingerprint (client version) icons module set extra icon of your buddyes according to their client version",
    "Artem Shpynov, Angeli-Ka",
    "shpynov@nm.ru",
    "© 2006 Artem V. Shpynov, Angeli-Ka",
    "http://shpynov.nm.ru/alpha/",
    0,		//not transient
    0		//doesn't replace anything built-in
};

BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{
  g_hInst=hinstDLL;
  return TRUE;
}

__declspec(dllexport) PLUGININFO* MirandaPluginInfo(DWORD mirandaVersion)
{
  return &pluginInfo;
}

int __declspec(dllexport) Load(PLUGINLINK *link)
{
  pluginLink=link;
  hModulesLoaded=HookEvent(ME_SYSTEM_MODULESLOADED,OnModulesLoaded);
  hSystemOKToExit=HookEvent(ME_SYSTEM_OKTOEXIT,OnSystemOKToExit); 
  compClientServ=CreateServiceFunction(MS_FP_SAMECLIENTS,ServiceSameClients);
  getClientIcon=CreateServiceFunction(MS_FP_GETCLIENTICON,ServiceGetClientIcon);
  return 0;
}

int __declspec(dllexport) Unload(void)
{
  return 0;
}


/*
*  OnModulesLoaded
*  Hook necessary events here
*/
int OnModulesLoaded(WPARAM wParam, LPARAM lParam)
{
  CallService("Update/RegisterFL", (WPARAM)2594, (LPARAM)&pluginInfo);
  //Hook necessary events
  hExtraImageListRebuild =  HookEvent(ME_CLIST_EXTRA_LIST_REBUILD,OnExtraIconListRebuild);
  hExtraImageApply =        HookEvent(ME_CLIST_EXTRA_IMAGE_APPLY, OnExtraImageApply);
  hContactSettingChanged =  HookEvent(ME_DB_CONTACT_SETTINGCHANGED, OnContactSettingChanged);
  hOptInitialise=			HookEvent(ME_OPT_INITIALISE, OnOptInitialise);	
  return 0;
}

/*
*   OnSystemOKToExit
*   Unhook events here (this is valid place to unhook all events to prevent crash on exiting)
*/
int OnSystemOKToExit(WPARAM wParam, LPARAM lParam)
{
  //Unhook events
  UnhookEvent(hExtraImageListRebuild);
  UnhookEvent(hExtraImageApply);
  UnhookEvent(hContactSettingChanged);
  UnhookEvent(hOptInitialise);
  UnhookEvent(hSystemOKToExit);
  UnhookEvent(hModulesLoaded);
  DestroyServiceFunction(compClientServ);
  DestroyServiceFunction(getClientIcon);
  return 0;
}


/*  ApplyFingerprintImage
*   1)Try to find appropriate mask
*   2)Register icon in extraimage list if not yet registered (0xFF)
*   3)Set ExtraImage for contact
*/
int ApplyFingerprintImage(HANDLE hContact,char *MirVer)
{
  int i=-1;
  if (MirVer) 
  {
    i=0;
    while (i<DEFAULT_KN_FP_MASK_COUNT)
    {
      if(WildCompare(MirVer,def_kn_fp_mask[i].szMask)) break;
      i++;
    }
    if (i<DEFAULT_KN_FP_MASK_COUNT && (def_kn_fp_mask[i].registeredIndex==0xFF))
    {
      KN_FP_MASK * mask=&(def_kn_fp_mask[i]);
	  HICON hIcon=LoadIconFromExternalFile(mask->szIconFileName,-mask->iIconIndex,TRUE,TRUE,mask->szIconName,mask->SectionFlag,mask->szClientDescription,mask->iIconIndex);       
      mask->registeredIndex=(hIcon)?CallService(MS_CLIST_EXTRA_ADD_ICON,(WPARAM)hIcon,0):0xFF;		
    }
  }
  if (hContact)
  {
    IconExtraColumn iec;
    iec.cbSize=sizeof(IconExtraColumn);
    iec.hImage=(HANDLE)((i<DEFAULT_KN_FP_MASK_COUNT && i!=-1)?def_kn_fp_mask[i].registeredIndex:-1);
    iec.ColumnType=EXTRA_ICON_CLIENT;
    CallService(MS_CLIST_EXTRA_SET_ICON,(WPARAM)hContact,(LPARAM)&iec);
    return 0;
  }
  return 0;
}
/* 
*  OnExtraIconListRebuild
*  Set all registered indexes in array to 0xFF (unregistered icon)
*/
int OnExtraIconListRebuild(WPARAM wParam, LPARAM lParam)
{ 
  int i;	
  for(i=0; i<DEFAULT_KN_FP_MASK_COUNT; i++)	
    def_kn_fp_mask[i].registeredIndex=0xFF;
  return 0;
}
/*
*   OnExtraImageApply
*   Try to get MirVer value from db for contact and if success calls ApplyFingerprintImage
*/
int OnExtraImageApply(WPARAM wParam, LPARAM lParam)
{
  HANDLE hContact=(HANDLE)wParam;
  if (!hContact) return 0;
  //else
  {
    DBVARIANT dbv;
    char * szProto;  
    szProto=(char*)CallService(MS_PROTO_GETCONTACTBASEPROTO,(WPARAM)hContact,0);
    if (szProto &&!DBGetContactSettingTString(hContact,szProto,"MirVer",&dbv) && (dbv.type==DBVT_ASCIIZ||dbv.type==DBVT_UTF8 ||dbv.type==DBVT_WCHAR ))
    {
      ApplyFingerprintImage(hContact,dbv.ptszVal);
      DBFreeVariant(&dbv);
    }
    else
      ApplyFingerprintImage(hContact,NULL); 
  }
  return 0;
}
/*
*   OnContactSettingChanged
*   if contact settings changed apply new image or remove it
*/
int OnContactSettingChanged(WPARAM wParam, LPARAM lParam)
{
  DBCONTACTWRITESETTING *cws = (DBCONTACTWRITESETTING*)lParam;
  if ((HANDLE)wParam == NULL)	return 0;
  if (cws && cws->szSetting && !strcmp(cws->szSetting,"MirVer"))
	  if (cws->value.type==DBVT_ASCIIZ)
		  ApplyFingerprintImage((HANDLE)wParam,cws->value.pszVal);
	  else if (cws->value.type==DBVT_UTF8 || cws->value.type==DBVT_WCHAR)
		  ApplyFingerprintImage((HANDLE)wParam,cws->value.ptszVal);	
	  else
		  ApplyFingerprintImage((HANDLE)wParam,NULL);
  return 0;
}

/*
*   LoadIconFromExternalFile
*   If iconlib module presents register icon there
*   Regiister and return icon within iconlib 
*   or from resourse
*/
//   TO DO: Extracting icons from clienticons.dll or other external files require futher
//   destroying of icon... need to add field to list, modify it and remove icon on unload
//   Otherwise it will cause gdi resources leaking.
//   So nowtime it is commented out

HICON LoadIconFromExternalFile(char *filename,int i,BOOL UseLibrary,BOOL registerit,char *IconName, int flag, char *Description,int internalidx)
{
  char szPath[MAX_PATH],szMyPath[MAX_PATH];//, szFullPath[MAX_PATH],*str;
  HICON hIcon=NULL;
  SKINICONDESC sid={0};
  char * SectName;
  switch (flag&0x0F)
  {
  case 1:	SectName="Client Icons/ICQ";		break;
  case 2:	SectName="Client Icons/JABBER";		break;
  case 3:	SectName="Client Icons/AIM";		break;
  case 4:	SectName="Client Icons/Mobile";		break;
  case 5:	SectName="Client Icons/Other";		break;
  case 6:	SectName="Client Icons/Miranda";	break;
  default:  SectName="Client Icons";
  }
  GetModuleFileNameA(g_hInst, szMyPath, MAX_PATH);
  CallService(MS_UTILS_PATHTORELATIVE, (WPARAM)szMyPath, (LPARAM)szPath);
  /*
  str=strrchr(szPath,'\\');
  if(str!=NULL) *str=0;
  if (filename)
  _snprintf(szFullPath, sizeof(szFullPath), "%s,%d",  filename, i);
  else
  _snprintf(szFullPath, sizeof(szFullPath), "%s\\Icons\\%s,%d", szPath, "clienticons.dll", i);    	
  if (!UseLibrary||!ServiceExists(MS_SKIN2_ADDICON))
  {
  char *comma;
  char file[MAX_PATH],fileFull[MAX_PATH];
  int n;
  HICON hIcon;
  lstrcpynA(file,szFullPath,sizeof(file));
  comma=strrchr(file,',');
  if(comma==NULL) n=0;
  else {n=atoi(comma+1); *comma=0;}
  CallService(MS_UTILS_PATHTOABSOLUTE, (WPARAM)file, (LPARAM)fileFull);
  hIcon=NULL;
  ExtractIconExA(fileFull,n,NULL,&hIcon,1);
  }
  else
  */
  if (ServiceExists(MS_SKIN2_ADDICON)&&UseLibrary)
  {
    if (registerit&&IconName!=NULL&&SectName!=NULL)	
    {
      char buf[255]={0};
      sid.cbSize = sizeof(sid);
      sid.pszSection = Translate(SectName);				
      sid.pszName=IconName;
      sid.pszDescription=Description;
      sid.pszDefaultFile=szPath;
      sid.iDefaultIndex=-internalidx;
	  sid.cx=sid.cy=16;
      CallService(MS_SKIN2_ADDICON, 0, (LPARAM)&sid);
    }
    hIcon=((HICON)CallService(MS_SKIN2_GETICON, 0, (LPARAM)IconName));
  }
  if (!hIcon) 
	  hIcon=LoadIcon(g_hInst, MAKEINTRESOURCE(internalidx));
  return hIcon;
}

/*
*   WildCompare 
*   Compare 'name' string with 'mask' strings.
*   Masks can contain '*' or '?' wild symbols
*   Asterics '*' symbol covers 'empty' symbol too e.g WildCompare("Tst","T*st*"), returns TRUE 
*   In order to handle situation 'at least one any sybol' use "?*" combination:
*   e.g WildCompare("Tst","T?*st*"), returns FALSE, but both WildCompare("Test","T?*st*") and
*   WildCompare("Teeest","T?*st*") return TRUE.
*
*   Function is 'dirt' case insensitive (it is ignore 5th bit (0x20) so it is no difference
*   beetween some symbols. But it is faster than valid converting to uppercase.
*
*   Mask can contain several submasks. In this case each submask (including first)
*   should start from '|' e.g: "|first*submask|second*mask".
*/
BOOL __inline WildCompare(char * name, char * mask)
{

  if (*mask!='|') return WildCompareProc(name,mask);
  //else
  {
    int s=1,e=1;
    char * temp;
    while (mask[e]!='\0')
    {
      s=e;
      while(mask[e]!='\0' && mask[e]!='|') e++;
      temp=(char*)malloc(e-s+1);
      memcpy(temp,mask+s,e-s);
      temp[e-s]='\0';
      if (WildCompareProc(name,temp)) 
      {
        free(temp);
        return TRUE;
      }
      free(temp);
      if (mask[e]!='\0') e++;
      else return FALSE;
    }
    return FALSE;

  }
}

BOOL WildCompareProc(char * name, char * mask)
{
  char * last='\0';
  for(;; mask++, name++)
  {
    if(*mask != '?' && (*mask&223) != (*name&223)) break;
    if(*name == '\0') return ((BOOL)!*mask);
  }
  if(*mask != '*') return FALSE;
  for(;; mask++, name++)
  {      
    while(*mask == '*')
    {    
      last = mask++;
      if(*mask == '\0') return ((BOOL)!*mask);   /* true */
    }
    if(*name == '\0') return ((BOOL)!*mask);      /* *mask == EOS */
    if(*mask != '?' && (*mask&223)  != (*name&223) ) name -= (size_t)(mask - last) - 1, mask = last;
  }
}

/*
*   OnOptInitialise
*   We don't register all icons, but registering it as soon as it required. So to works correctly
*   on Iconlib icons settings page we should register all unused icons in it. 
*   Much more better is to have also "Unregister icons" in icon lib... To unregister all icons and 
*   reregister it in order to have icons in options in valid order, not in order of their first usage.
*   Also it would be better to have "unregister icons" on icon lib changed to minimize GDI resources
*   usage.
*/

int OnOptInitialise(WPARAM wParam, LPARAM lParam)
{
  // need to register all icolib icons
  if (ServiceExists(MS_SKIN2_ADDICON))
  {
    int i;
    for (i=0; i<DEFAULT_KN_FP_MASK_COUNT; i++)
    {
      KN_FP_MASK * mask=(KN_FP_MASK*)&def_kn_fp_mask[i];
      if (mask) LoadIconFromExternalFile(mask->szIconFileName,-mask->iIconIndex,TRUE,TRUE,mask->szIconName,mask->SectionFlag,mask->szClientDescription,mask->iIconIndex);
    }
  }
  return 0;
}
/*
*   ServiceGetClientIcon
*   MS_FP_GETCLIENTICON service implementation.
*	wParam - char * MirVer value to get client for.
*   lParam - int noCopy - if wParam is equal to "1"  will return icon handler without copiing icon.
*/
int ServiceGetClientIcon(WPARAM wParam, LPARAM lParam)
{
	char *	MirVer	=(char*)wParam;	// MirVer value to get client for.
	int		NoCopy	=(int)  lParam;	// noCopy
	HICON	hIcon	=NULL;			// returned HICON
	if (MirVer)		
	{
		int i=0;
		while (i<DEFAULT_KN_FP_MASK_COUNT)
		{
			if(WildCompare(MirVer,def_kn_fp_mask[i].szMask)) break;
			i++;
		}
		if (i<DEFAULT_KN_FP_MASK_COUNT)
		{
			KN_FP_MASK * mask=&(def_kn_fp_mask[i]);
			hIcon=LoadIconFromExternalFile(mask->szIconFileName,-mask->iIconIndex,TRUE,TRUE,mask->szIconName,mask->SectionFlag,mask->szClientDescription,mask->iIconIndex);       
		}
	}
	if (hIcon && !NoCopy) 
		return (int)CopyIcon(hIcon);

	return (int)hIcon;
}

/*
 *   ServiceSameClient
 *   MS_FP_SAMECLIENTS service implementation.
 *	 wParam - char * first MirVer value 
 *   lParam - char * second MirVer value 
 *	 return pointer to char string - client desription (do not destroy) if clients are same
 */
int ServiceSameClients(WPARAM wParam, LPARAM lParam)
{
	char *	MirVerFirst	=(char*)wParam;	// MirVer value to get client for.
	char *	MirVerSecond=(char*)lParam;	// MirVer value to get client for.
	int firstIndex, secondIndex;
	BOOL Result=FALSE;
	firstIndex=secondIndex=0;
	if (!MirVerFirst || !MirVerSecond) return (int)NULL;  //one of its is not null
	while (firstIndex<DEFAULT_KN_FP_MASK_COUNT)
	{
		if(WildCompare(MirVerFirst,def_kn_fp_mask[firstIndex].szMask)) break;
		firstIndex++;
	}
	while (secondIndex<DEFAULT_KN_FP_MASK_COUNT)
	{
		if(WildCompare(MirVerSecond,def_kn_fp_mask[secondIndex].szMask)) break;
		secondIndex++;
	}
	if (firstIndex==secondIndex && firstIndex<DEFAULT_KN_FP_MASK_COUNT) 
		return (int)def_kn_fp_mask[firstIndex].szClientDescription;
	return (int)NULL;	
}
