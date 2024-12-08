#include "hoec_Camera.h"

#include"opencv2/opencv.hpp"

#include<vector>
namespace rw
{
    namespace hoec
    {

        class Camera_MVSToBeRefactor
        {
        public:
            std::function<void(cv::Mat)> userCallBack;
        public:
            static bool isIniSDK;
            static std::vector<std::string> getCameraIpList();
            static std::vector<CameraInfo> getCameraInfoList();
            static bool initSDK();
            static bool uninitSDK();
        public:
            cv::Mat getImage(bool & isget);
        public:
            Camera_MVSToBeRefactor();
            ~Camera_MVSToBeRefactor();
        private:
            void* m_cameraHandle{nullptr};
        private:
            CameraInfo m_cameraInfo;

        public:
            CameraInfo getCameraInfo() const;

            void setCameraInfo(const CameraInfo& cameraInfo);
        private:
            std::string m_ip;

        public:
            void setIP(const std::string& ip);

            std::string getIP() const;
        public:
            int getExposureTime();
        public:
            bool connectCamera();
        private:
            bool _isMonitor{ false };
        public:
            bool startMonitor();

            bool stopMonitor();
        public:
            bool setExposureTime(size_t value);
            bool setGain(size_t value);
            bool setMonitorMode(CameraMonitorMode mode);
            bool setIOTime(size_t value);
        };

    }
}