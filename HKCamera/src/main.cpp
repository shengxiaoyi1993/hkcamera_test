#include <stdio.h>
#include <iostream>
#include<string>
#include "Windows.h"
#include"HKCamera.h"
using namespace std;

int main()
{

  string ip="192.168.1.64";
  HKCamera camera(ip);
  HKCamera camera0(ip);
  bool flag_login=camera.login("admin","admin123",8000);
  cout<<"flag_login:"<<flag_login<<endl;

  int flag_status=camera.isConnected();
  cout<<"flag_status:"<<flag_status<<endl;



  string rtsp_main;
  string rtsp_sub;
  int flag_getrtsp=camera.getRtspOfCamera(rtsp_main,rtsp_sub);
  cout<<"flag_getrtsp:"<<flag_getrtsp<<endl;
  cout<<"rtsp_main:"<<rtsp_main<<endl;
  cout<<"rtsp_sub:"<<rtsp_sub<<endl;

string path_image="201910120927_image.jpg";
  int flag_getimage=camera.getImageAndSave(path_image);
  cout<<"flag_getimage:"<<flag_getimage<<endl;


  string path_plate="201910120927_plate.jpg";
  string path_plateblock="201910120927_plateblock.jpg";
  vector<int> block;
    int flag_getplate=camera.getPlateImageAndSave(
      path_image,
      path_plateblock,
      block,
      240000
    );
    cout<<"flag_getplate:"<<flag_getplate<<endl;
    cout<<"block:";
    for(int i=0;i<block.size();i++){
      cout<<block[i]<<" ";
    }
    cout<<endl;


  int flag_logout= camera.logout();
  cout<<"flag_logout:"<<flag_logout<<endl;

   flag_status=camera.isConnected();
  cout<<"flag_status:"<<flag_status<<endl;





  // Sleep(240000); //Wait to receive data

  // HKCamera camera("192.168.1.64");

  return 0;
}
