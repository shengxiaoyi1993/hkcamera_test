# 海康相机SDK使用说明

## 应用场景
- 作为车底及配套监控系统的一部分
- 车辆到达时需要车牌相机抓图及识别出车牌识别结果
- 相机作为IPC和ITS接入监控系统，其中IPC需要能检测能否被连接，ITS需要能够被检测到长连接的状态
- 能够获取到rtsp流的url，用于实时视频的播放


## 需求分析

- 检查长连接状态
- 建立长连接
- 手动获取截图
- 检测到车牌时，以回调函数方式传出识别结果和图片
- 断开长连接
- 检测相机是否能够被连接
- 获取相机的rtsp流地址
- 多台相机同时工作，互不干扰

## 测试设备说明
- 海康车牌相机（标签上写的DUNLOP ,IR NETWORK CAMERA ）
- 相机周期性测试图片中是否有车牌，若有则通过回调函数获取（图片和车牌信息）
- 用sdk主动获取图片时，没有车牌识别的结果
## 设计
### 接口设计

```
class HKCamera(std::string ip){
private:
static int _count;
LONG _userid;
LONG _loginhandl;
std::string _platelicense;

void hksdk_init();//仅当第一个HKCamera对象被初始化时调用该函数
void hksdk_uint();//仅当最后一个HKCamera对被析构时调用该函数

public:
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

int getPlateImageAndSave(std::string path_pate,std::string path_plateblock,vector<int> rect,int waittime);

}

```


## 生命周期

~~~mermaid
graph TD
  start("HKCamera camera") --> judgefirst{"first HKCamera?"}
  judgefirst--yes-->hksdk_init
  
  judgefirst--no-->makeuse("makeuse")
  hksdk_init-->makeuse
  makeuse-->judgelast{"judgelast"}
  judgelast--yes-->hksdk_uint
  judgelast--no-->waitlast

~~~


## 项目编译方法
- win10 下msys2 编译使用
```
cd build/
mkdir build
cd build
cmake ../ -G "Unix Makefiles"
make 
./api_test.exe
```
## 结语
- 本项目对于海康相机的使用仅限于若干简单功能（截图，车牌识别，获取rtsp流地址等），对于项目中有出入的地方请多包涵


