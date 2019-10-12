#ifndef HKCAMERA
#define  HKCAMERA

#include<vector>
#include<string>
#include<iostream>
#include"HCNetSDK.h"


class HKCamera{

public:

  HKCamera(std::string ip);

  ~HKCamera();


//check whether can connect to this camera or not
bool isAvailable();
//change or reset the ip of the camera
int setCameraIP(std::string ip);
//check whether the login status of camera
bool isConnected();
//to login
int login(std::string username,std::string password,int port);
//to logout
int logout();
int getImageAndSave(std::string path);
int getRtspOfCamera(std::string& rtsp_main,std::string& rtsp_sub);

int getPlateImageAndSave(std::string &path_pate,
  std::string &path_plateblock,
  std::vector<int> &rect,
  int waittime);

//  int hk_callback_saveimage(LONG lCommand, NET_DVR_ALARMER *pAlarmer, char *pAlarmInfo, DWORD dwBufLen, void* pUser);

int _block[4];
std::string _platelicense;
std::string _path_plate;
std::string _path_plateblock;
LONG _userid;


private:

LONG _loginhandl;
std::string _ip;
int port;
std::string _username;
std::string _password;


void hksdk_init();//仅当第一个HKCamera对象被初始化时调用该函数
void hksdk_uint();//仅当最后一个HKCamera对被析构时调用该函数





};

int hk_callback_saveimage(LONG lCommand, NET_DVR_ALARMER *pAlarmer,
                           char *pAlarmInfo, DWORD dwBufLen, void* pUser);

 void hk_callback_error(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser);


#endif
