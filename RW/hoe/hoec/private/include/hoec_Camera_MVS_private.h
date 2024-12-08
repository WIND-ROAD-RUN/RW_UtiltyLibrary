#ifndef HOEC_CAMERA_MVS_PRIVATE_H_
#define HOEC_CAMERA_MVS_PRIVATE_H_

#include"opencv2/opencv.hpp"

#include"hoec_Camera.h"

#include<vector>
#include<string>

namespace rw {
    namespace hoec {
        class Camera_MVS {
        public:
            Camera_MVS();
            virtual ~Camera_MVS();
        public:
            static bool _isIniSDK;
            static std::vector<std::string> getCameraIpList();
            static std::vector<CameraInfo> getCameraInfoList();
            static bool initSDK();
            static bool uninitSDK();
        public:
            void setIP(const std::string& ip);
            std::string getIP() const;
        public:
            bool connectCamera();
        public:
            bool startMonitor();
            bool stopMonitor();
        public:
            CameraInfo getCameraInfo() const;
            void setCameraInfo(const CameraInfo& cameraInfo);
        public:
            bool setExposureTime(size_t value);
            bool setGain(size_t value);
            bool setMonitorMode(CameraMonitorMode mode);
            bool setIOTime(size_t value);
        public:
            size_t getExposureTime();
            size_t getGain();
            size_t getIOTime();
            CameraMonitorMode getMonitorMode();
        private:
            std::string m_ip;
            CameraInfo m_cameraInfo;
        protected:
            void* m_cameraHandle{ nullptr };
        private:
            bool _isMonitor{ false };

        };

        class Camera_MVS_Active 
            :public Camera_MVS {
 
        public:
            Camera_MVS_Active();
            ~Camera_MVS_Active();
        public:
            cv::Mat getImage(bool& isget);
       
        };




    } // namespace hoec

} // namespace rw


#endif // !HOEC_CAMERA_MVS_PRIVATE_H_
