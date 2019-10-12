cmake_minimum_required(VERSION 2.8)
message("PROJECT_SOURCE_DIR:${PROJECT_SOURCE_DIR}")
message("CMAKE_BINARY_DIR:${CMAKE_BINARY_DIR}")

project(api_test)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
add_executable(api_test ${PROJECT_SOURCE_DIR}/../src/HKCamera.cpp ${PROJECT_SOURCE_DIR}/../src/main.cpp )
#add_executable(api_test ${PROJECT_SOURCE_DIR}/../src/main.cpp)
include_directories(${PROJECT_SOURCE_DIR}/../../incEn)
link_directories(${PROJECT_SOURCE_DIR}/../../lib/)
target_link_libraries(api_test
${PROJECT_SOURCE_DIR}/../../lib/HCNetSDKCom/AnalyzeData.dll
${PROJECT_SOURCE_DIR}/../../lib/HCNetSDKCom/AudioIntercom.dll
${PROJECT_SOURCE_DIR}/../../lib/HCNetSDKCom/HCAlarm.dll
${PROJECT_SOURCE_DIR}/../../lib/HCNetSDKCom/HCCoreDevCfg.dll
${PROJECT_SOURCE_DIR}/../../lib/HCNetSDKCom/HCDisplay.dll
${PROJECT_SOURCE_DIR}/../../lib/HCNetSDKCom/HCGeneralCfgMgr.dll
${PROJECT_SOURCE_DIR}/../../lib/HCNetSDKCom/HCIndustry.dll
${PROJECT_SOURCE_DIR}/../../lib/HCNetSDKCom/HCPlayBack.dll
${PROJECT_SOURCE_DIR}/../../lib/HCNetSDKCom/HCPreview.dll
${PROJECT_SOURCE_DIR}/../../lib/HCNetSDKCom/HCVoiceTalk.dll
${PROJECT_SOURCE_DIR}/../../lib/HCNetSDKCom/libiconv2.dll
${PROJECT_SOURCE_DIR}/../../lib/HCNetSDKCom/OpenAL32.dll
${PROJECT_SOURCE_DIR}/../../lib/HCNetSDKCom/StreamTransClient.dll
${PROJECT_SOURCE_DIR}/../../lib/HCNetSDKCom/SystemTransform.dll
${PROJECT_SOURCE_DIR}/../../lib/AudioRender.dll
${PROJECT_SOURCE_DIR}/../../lib/D3DCompiler_43.dll
${PROJECT_SOURCE_DIR}/../../lib/d3dx9_43.dll
${PROJECT_SOURCE_DIR}/../../lib/EagleEyeRender.dll
${PROJECT_SOURCE_DIR}/../../lib/GdiPlus.dll
${PROJECT_SOURCE_DIR}/../../lib/HCCore.dll
${PROJECT_SOURCE_DIR}/../../lib/HCNetSDK.dll
${PROJECT_SOURCE_DIR}/../../lib/HWDecode.dll
${PROJECT_SOURCE_DIR}/../../lib/libmmd.dll
${PROJECT_SOURCE_DIR}/../../lib/MP_Render.dll
${PROJECT_SOURCE_DIR}/../../lib/PlayCtrl.dll
${PROJECT_SOURCE_DIR}/../../lib/SuperRender.dll
${PROJECT_SOURCE_DIR}/../../lib/YUVProcess.dll
)
