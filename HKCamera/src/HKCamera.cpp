

#include"HKCamera.h"
#include<vector>
#include<string>
#include<iostream>
using namespace std;

static int _count ;


HKCamera::HKCamera(std::string ip){
    if(0 == _count)
    {
        hksdk_init();
        cout<<"first to use HKCamera"<<endl;
        cout<<"new _count:"<<_count<<endl;
    }

    _count++;
    _ip=ip;


}


HKCamera::~HKCamera(){
    _count--;
    cout<<"del _count:"<<_count<<endl;
    if(0 == _count)
    {
        hksdk_uint();
        cout<<"last to use HKCamera"<<endl;
    }

}

//仅当第一个HKCamera对象被初始化时调用该函数
void HKCamera::hksdk_init(){
    NET_DVR_Init();
    NET_DVR_SetConnectTime(2000, 1);
    NET_DVR_SetReconnect(10000, true);
}



void HKCamera::hksdk_uint(){
    NET_DVR_Cleanup();
}


//check whether can connect to this camera or not
bool HKCamera::isAvailable(){
  if(_userid>=0){
    return true;
  }
  else{
    int flag_login=login(_username,_password,port);
    if(flag_login>=0){
      logout();
      return true;
    }
    else{
      return false;
    }
  }
}



//change or reset the ip of the camera
int HKCamera::setCameraIP(std::string ip){
  _ip=ip;
  return 0;

}
//check whether the login status of camera
bool HKCamera::isConnected(){
  if(_userid>=0){
    return true;
  }
  else{
    return false;
  }

}
//to login
int HKCamera::login(std::string username,std::string password,int port){

    //Login parameter, including device IP address, user name, password and so on.
    NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
    //Synchronous login mode
    struLoginInfo.bUseAsynLogin = 0;
    //Device IP address
    strcpy(struLoginInfo.sDeviceAddress, _ip.c_str());
    //Device service port
    struLoginInfo.wPort = 8000;
    //User name
    strcpy(struLoginInfo.sUserName, username.c_str());
    //Password
    strcpy(struLoginInfo.sPassword, password.c_str());

    //Device information, output parameter
    NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};

    LONG lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);

    if(lUserID < 0)
    {


        return lUserID;
    }
    else
    {
      NET_DVR_SetExceptionCallBack_V30(0, NULL,hk_callback_error, this);

        _userid=lUserID;
        return 0;


    }

}
//to logout
int HKCamera::logout(){
    if(_userid<0){
        return -1;
    }
    else{
      _userid=-1;
        return NET_DVR_Logout(_userid);
    }

}

int HKCamera::getImageAndSave(std::string path){
  if(_userid>=0){
    NET_DVR_JPEGPARA strPicPara = {0};
    strPicPara.wPicQuality = 2;
    strPicPara.wPicSize = 0;
    const char* constc = nullptr;
    constc=path.c_str();
    char* c = nullptr;
    c= const_cast<char*>(constc);
    if (!NET_DVR_CaptureJPEGPicture(_userid, 1, &strPicPara,c )) {
      printf("NET_DVR_CaptureJPEGPicture error, %d\n", NET_DVR_GetLastError());
      return -1;
    }
    return 0;

  }
  return -1;
}

int HKCamera::getRtspOfCamera(std::string& rtsp_main,std::string& rtsp_sub){

if(_userid>=0){
  rtsp_main= "rtsp://"+_username+":"+_password+"@"+_ip+"/h264/ch1/main/av_stream";
  rtsp_sub= "rtsp://"+_username+":"+_password+"@"+_ip+"/h264/ch1/sub/av_stream";
  return 0;
}

return -1;


}



int HKCamera::getPlateImageAndSave(std::string &path_plate,
                                   std::string &path_plateblock,
                                   std::vector<int> &rect,
                                   int waittime){

if(_userid>=0){
  _path_plate=path_plate;
  _path_plateblock=path_plateblock;
  //Set alarm callback function
LONG lHandle = NET_DVR_SetDVRMessageCallBack_V31(hk_callback_saveimage, this);

//Enable arming
NET_DVR_SETUPALARM_PARAM struSetupParam={0};
struSetupParam.dwSize=sizeof(NET_DVR_SETUPALARM_PARAM);
struSetupParam.byLevel = 1; //Arming level: 0- level 1 (high), 1- level 2 (medium)
struSetupParam.byAlarmInfoType = 1; //Uploaded alarm types: 0- History alarm (NET_DVR_PLATE_RESULT), 1- Real-time alarm (NET_ITS_PLATE_RESULT)
lHandle = NET_DVR_SetupAlarmChan_V41(_loginhandl,&struSetupParam);

if (lHandle < 0)
{
    return -1;
}


// QMutex mutex;
// QWaitCondition sleep;
// mutex.lock();
// sleep.wait(&mutex, 60000);
// mutex.unlock();

Sleep(waittime); //Wait to receive data

rect.clear();
rect.push_back(_block[0]);
rect.push_back(_block[1]);
rect.push_back(_block[2]);
rect.push_back(_block[3]);

NET_DVR_CloseAlarmChan_V30(lHandle);
return 0;

}
else{
  return -1;
}

}


int hk_callback_saveimage(LONG lCommand, NET_DVR_ALARMER *pAlarmer,
                           char *pAlarmInfo, DWORD dwBufLen, void* pUser){
    cout<<"hk_callback_saveimage"<<endl;

    HKCamera *pcamera=(HKCamera*)pUser;

    LPNET_ITS_PLATE_RESULT result = (LPNET_ITS_PLATE_RESULT)pAlarmInfo;

    // NET_DVR_JPEGPARA strPicPara = {0};
    // strPicPara.wPicQuality = 2;
    // strPicPara.wPicSize = 0;

  for(int npic=0;npic<result->dwPicNum;npic++){
      if(result->dwPicNum !=0 ){
          FILE* fp = fopen(pcamera->_path_plate.c_str(), "wb");
          if(fp != NULL){
              fwrite(result->struPicInfo[npic].pBuffer,
                     result->struPicInfo[npic].dwDataLen, 1, fp);
              fclose(fp);
          }

      }
  }

  NET_DVR_PLATE_INFO plate = result->struPlateInfo;
pcamera->_platelicense=plate.sLicense;


  int imagewidth=1920;
  int imageheight=1080;

  pcamera->_block[0]=plate.struPlateRect.fX*imagewidth;
  pcamera->_block[1]=plate.struPlateRect.fY*imageheight;
  pcamera->_block[2]=(plate.struPlateRect.fX+plate.struPlateRect.fWidth)*imagewidth;
  pcamera->_block[3]=(plate.struPlateRect.fY+plate.struPlateRect.fHeight)*imageheight;



  return 0;

}

void hk_callback_error(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser){
    cout<<"dwType:"<<dwType<<endl;
    cout<<"lUserID:"<<lUserID<<endl;
    cout<<"lHandle:"<<lHandle<<endl;
    HKCamera *pcamera=(HKCamera*)pUser;

    if(dwType == 0x8000 || dwType == 0x8006){
      pcamera->_userid=-1;
    }
    else if(dwType == 0x8017 ){
      pcamera->_userid=0;
    }

    return ;
}
