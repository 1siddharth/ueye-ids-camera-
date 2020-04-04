#include <iostream>
#include <stdio.h>
#include <stddef.h>
#include "ueye.h"
#include <stdlib.h>
#include <string>
#include <thread>
#include <chrono>
#include <bits/stdc++.h>
#include<cwchar>


using namespace std;
HIDS hCam = 0;
int width;
int height;
int main()
{
int i=1;
HIDS hCam = 1;
INT nRet = is_InitCamera(&hCam, NULL);

if (nRet != IS_SUCCESS)
{
 cout<<"not found";
}
else
{
cout<<"thik hai";	
}





INT col = is_SetColorMode ( hCam, IS_CM_BGR8_PACKED);
UINT nPixelClockDefault;
 
nRet = is_PixelClock(hCam, IS_PIXELCLOCK_CMD_GET_DEFAULT,(void*)&nPixelClockDefault, sizeof(nPixelClockDefault));	                   
if (nRet == IS_SUCCESS)
{
  nRet = is_PixelClock(hCam, IS_PIXELCLOCK_CMD_SET,(void*)&nPixelClockDefault, sizeof(nPixelClockDefault));                       
}
double dEnable = 1;
int ret = is_SetAutoParameter (hCam, IS_SET_ENABLE_AUTO_GAIN, &dEnable, 0);
double nominal = 128;
int rret = is_SetAutoParameter (hCam, IS_SET_AUTO_REFERENCE, &nominal, 0);

UINT nCaps = 8;
 nRet = is_Exposure(hCam, IS_EXPOSURE_CMD_GET_EXPOSURE_DEFAULT, (void*)&nCaps, sizeof(nCaps));
 
char strCamFileName[256];
int nnRet;
UINT count;
UINT bytesNeeded = sizeof(IMAGE_FORMAT_LIST);
nnRet = is_ImageFormat(hCam, IMGFRMT_CMD_GET_NUM_ENTRIES, &count, sizeof(count));
bytesNeeded += (count - 1) * sizeof(IMAGE_FORMAT_INFO);
void* ptr = malloc(bytesNeeded);

IMAGE_FORMAT_LIST* pformatList = (IMAGE_FORMAT_LIST*) ptr;
pformatList->nSizeOfListEntry = sizeof(IMAGE_FORMAT_INFO);
pformatList->nNumListElements = count;

nRet = is_ImageFormat(hCam, IMGFRMT_CMD_GET_LIST, pformatList, bytesNeeded);
char* pMem = NULL;
int memID = 0;

IMAGE_FORMAT_INFO formatInfo;

for (int i = 0; i < count; i++)
{
	if(pformatList->FormatInfo[i].nFormatID == 6)
	{
	cout<<endl<<"found format"<<endl;
    formatInfo = pformatList->FormatInfo[i];
     width = formatInfo.nWidth;
    height = formatInfo.nHeight;
     
    nRet = is_ImageFormat(hCam, IMGFRMT_CMD_SET_FORMAT, &formatInfo.nFormatID, sizeof(formatInfo.nFormatID));
    
    if (nRet != IS_SUCCESS)
{
 cout<<"format not set";
}
else
{
cout<<" ye bhi thik hai";	
}
    
}

}

	int bitspixel=24;
	char* ppcImgMem;
	int pid;
	int acc= is_AllocImageMem (hCam, width, height, bitspixel,  &ppcImgMem,  &pid);
	if(acc != IS_SUCCESS)
{
    cout<<endl<<"Cannot Initialize"<<endl;

}
else
{

cout<<endl<<" Initialized"<<endl;
}
int rat = is_SetImageMem (hCam, ppcImgMem, pid);
	if(rat == IS_SUCCESS)
{
    cout<<endl<<"image memory set"<<endl;

}
   is_SetExternalTrigger ( hCam, IS_SET_TRIGGER_SOFTWARE);
 char *ppcImg;	
 while(i>0)
 {
 	
this_thread::sleep_for(chrono::milliseconds(2000));
  int s=is_FreezeVideo(hCam, IS_WAIT);
  if (s == IS_SUCCESS)
  {
  	INT savee= is_GetImageMem ( hCam, (VOID**) &ppcImg);
  	if(savee == IS_SUCCESS)
{
    cout<<endl<<"getting image"<<endl;

}

  }
  IMAGE_FILE_PARAMS ImageFileParams;
 
  UINT nID = (UINT)pid;
  ImageFileParams.pnImageID =&nID;
  ImageFileParams.ppcImageMem = &ppcImg;
  
  cout<<"checkpoint2"<<endl;
 
  int ll=+i;
  cout<<ll<<endl;
  string lll=to_string(ll);

  string doo("C:\\Users\\Desktop\\testids");
  doo.append(lll);
  
  string dooo(".jpg");
  doo.append(dooo);
  
    wchar_t* a;
wstring str = wstring(doo.begin(), doo.end());
    a= _wcsdup(str.c_str());;
  ImageFileParams.pwchFileName =a;
  ImageFileParams.nFileType = IS_IMG_JPG;
  ImageFileParams.nQuality = 80;
  int st = is_ImageFile(hCam, IS_IMAGE_FILE_CMD_SAVE, (void*)&ImageFileParams, sizeof(ImageFileParams));
  cout<<"done"<<endl;
   i++;
}
  int end = is_ExitCamera(hCam);
 if (end == IS_SUCCESS)
 {
 	
 cout<<"Closing Camera"<<endl;
}
 		
	return 0;
}
