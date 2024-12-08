#include"hoec_Camera_private.h"

#include"hoec_core_private.h"

#include"MvCameraControl.h"
#include"CameraParams.h"

#include<algorithm>
#include<iostream>

namespace rw{
    namespace hoec {
        bool Camera_MVSToBeRefactor::isIniSDK = false;

        Camera_MVSToBeRefactor::Camera_MVSToBeRefactor() {
        }

        Camera_MVSToBeRefactor::~Camera_MVSToBeRefactor() {
            //先停止采集
            if (_isMonitor) {
                stopMonitor();
            }
            //关闭相机
            if (m_cameraHandle) {
                MV_CC_CloseDevice(m_cameraHandle);
                MV_CC_DestroyHandle(m_cameraHandle);
            }
        }
        void Camera_MVSToBeRefactor::setIP(const std::string &ip)
        {
            this->m_ip = ip;
        }

        std::string Camera_MVSToBeRefactor::getIP() const
        {
            return m_ip;
        }

        bool Camera_MVSToBeRefactor::connectCamera()
        {
            MV_CC_DEVICE_INFO_LIST deviceList;
            memset(&deviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));

            if (MV_CC_EnumDevices(MV_GIGE_DEVICE, &deviceList) != MV_OK) {
                std::cerr << "Failed to enumerate devices" << std::endl;
                return false;
            }

            MV_CC_DEVICE_INFO * targetDevice=nullptr;
            for (unsigned int i = 0; i < deviceList.nDeviceNum; ++i) {
                auto pDeviceInfo = deviceList.pDeviceInfo[i];
                if (pDeviceInfo->nTLayerType == MV_GIGE_DEVICE) {
                    // 获取设备的 IP 地址
                    unsigned int ip = pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentIp;
                    std::string ipStr = std::to_string((ip >> 24) & 0xFF) + "." +
                        std::to_string((ip >> 16) & 0xFF) + "." +
                        std::to_string((ip >> 8) & 0xFF) + "." +
                        std::to_string(ip & 0xFF);
                    if (ipStr==m_ip) {
                        targetDevice = pDeviceInfo;
                        break;
                    }
                }
            }
            if (!targetDevice) {
                std::cerr << "Failed to find target device" << std::endl;
                return false;
            }

            
            //是否可以独占访问
            auto canAccessible=MV_CC_IsDeviceAccessible(targetDevice, MV_ACCESS_Exclusive);
            if (canAccessible != true) {
                std::cerr << "Failed to access device" << std::endl;
                return false;
            }

            //创建句柄
            auto creatHandleResult=MV_CC_CreateHandle(&m_cameraHandle, targetDevice);
            if (creatHandleResult!=MV_OK) {
                std::cerr << "Failed to create handle with:"<<creatHandleResult << std::endl;
                return false;
            }

            //独占打开设备
            auto openDeviceResult = MV_CC_OpenDevice(m_cameraHandle,MV_ACCESS_Exclusive);
            if (openDeviceResult != MV_OK) {
                std::cerr << "Failed to open device with:" << openDeviceResult << std::endl;
                return false;
            }

            return true;
        }

        bool Camera_MVSToBeRefactor::startMonitor()
        {
            if (_isMonitor) { 
                std::cerr << "Monitor has already started" << std::endl;
                return false;
            }

            auto result=MV_CC_StartGrabbing(m_cameraHandle);
            if (result != MV_OK) {
                std::cerr << "Failed to stop grabbing with:" << result << std::endl;
                return false;
            }
            _isMonitor = true;
            return true;
        }

        bool Camera_MVSToBeRefactor::stopMonitor()
        {
            if (!_isMonitor) {
                std::cerr << "Monitor has already stopped" << std::endl;
                return false;
            }
            auto result = MV_CC_StopGrabbing(m_cameraHandle);
            if (result != MV_OK) {
                std::cerr << "Failed to stop grabbing with:" << result << std::endl;
                return false;
            }
            _isMonitor = false;
            return true;
        }

        bool Camera_MVSToBeRefactor::setExposureTime(size_t value)
        {
            //TODO: 设置曝光时间
            return false;
        }

        bool Camera_MVSToBeRefactor::setGain(size_t value)
        {
            //TODO: 设置增益
            return false;
        }

        bool Camera_MVSToBeRefactor::setMonitorMode(CameraMonitorMode mode)
        {
            //TODO: 设置监控模式
            return false;
        }

        bool Camera_MVSToBeRefactor::setIOTime(size_t value)
        {
            //TODO: 设置IO时间
            return false;
        }
        
        int Camera_MVSToBeRefactor::getExposureTime() {
            if (!m_cameraHandle) {
                return -1;
            }
            MV_ALL_MATCH_INFO allMatchInfo;
            MV_CC_GetAllMatchInfo(m_cameraHandle, &allMatchInfo);
            return allMatchInfo.nInfoSize;
        }

        std::vector<std::string> Camera_MVSToBeRefactor::getCameraIpList() {
            MV_CC_DEVICE_INFO_LIST deviceList;
            memset(&deviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));

            // 枚举设备
            if (MV_CC_EnumDevices(MV_GIGE_DEVICE, &deviceList) != MV_OK) {
                return std::vector<std::string>();
            }

            std::vector<std::string> ipList;
            for (unsigned int i = 0; i < deviceList.nDeviceNum; ++i) {
                MV_CC_DEVICE_INFO* pDeviceInfo = deviceList.pDeviceInfo[i];
                if (pDeviceInfo->nTLayerType == MV_GIGE_DEVICE) {
                    // 获取设备的 IP 地址
                    unsigned int ip = pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentIp;
                    std::string ipStr = std::to_string((ip >> 24) & 0xFF) + "." +
                                        std::to_string((ip >> 16) & 0xFF) + "." +
                                        std::to_string((ip >> 8) & 0xFF) + "." +
                                        std::to_string(ip & 0xFF);
                    ipList.push_back(ipStr);
                }
            }

            return ipList;
        }

        std::vector<CameraInfo> Camera_MVSToBeRefactor::getCameraInfoList() {
            MV_CC_DEVICE_INFO_LIST deviceList;
            memset(&deviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
            // 枚举设备
            if (MV_CC_EnumDevices(MV_GIGE_DEVICE, &deviceList) != MV_OK) {
                return std::vector<CameraInfo>();
            }
            std::vector<CameraInfo> cameraInfoList;
            for (unsigned int i = 0; i < deviceList.nDeviceNum; ++i) {
                MV_CC_DEVICE_INFO* pDeviceInfo = deviceList.pDeviceInfo[i];
                if (pDeviceInfo->nTLayerType == MV_GIGE_DEVICE) {
                    CameraInfo cameraInfo;
                    // 获取设备的 IP 地址
                    unsigned int ip = pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentIp;
                    cameraInfo.ip = std::to_string((ip >> 24) & 0xFF) + "." +
                        std::to_string((ip >> 16) & 0xFF) + "." +
                        std::to_string((ip >> 8) & 0xFF) + "." +
                        std::to_string(ip & 0xFF);
                    cameraInfo.name = std::string("MVS") + std::to_string(pDeviceInfo->nMajorVer)+std::to_string(pDeviceInfo->nMinorVer);
                    cameraInfo.mac = std::to_string(pDeviceInfo->nMacAddrHigh)+std::to_string(pDeviceInfo->nMacAddrLow);
                    cameraInfoList.push_back(cameraInfo);
                }
            }
            return cameraInfoList;
        }

        bool Camera_MVSToBeRefactor::initSDK() {
            Camera_MVSToBeRefactor::isIniSDK = true;
            auto result = MV_CC_Initialize();
            if (result==MV_OK) {
                return true;
            }
            else {
                std::cerr << "Failed to initialize SDK" << std::endl;
                return false;
            }
        }

        bool Camera_MVSToBeRefactor::uninitSDK() {
            Camera_MVSToBeRefactor::isIniSDK = false;
            auto result = MV_CC_Finalize();
            if (result == MV_OK) {
                return true;
            }
            else {
                std::cerr << "Failed to uninitialize SDK" << std::endl;
                return false;
            }
        }

        cv::Mat Camera_MVSToBeRefactor::getImage(bool & isget)
        {
            MV_FRAME_OUT frameInfo;
            auto getResult = MV_CC_GetImageBuffer(m_cameraHandle, &frameInfo, 1000);
            if (getResult != MV_OK) {
                std::cerr << "Failed to get image buffer with:" << getResult << std::endl;
                isget = false;
                return cv::Mat();
            }
            cv::Mat image = ImageFrameConvert::MVS_ConvertFrameToMat(frameInfo);
            if (image.empty())
            {
                std::cerr << "Failed to convert frame to mat" << std::endl;
                isget = false;
                return cv::Mat();
            }
            isget = true;
            auto freeResult = MV_CC_FreeImageBuffer(m_cameraHandle, &frameInfo);
            if (freeResult != MV_OK) {
                std::cerr << "Failed to free image buffer with:" << freeResult << std::endl;
                return cv::Mat();
            }
            return image;
        }
    }
}