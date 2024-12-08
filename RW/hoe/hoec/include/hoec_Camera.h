#ifndef HOEC_ICAMERA_H_
#define HOEC_ICAMERA_H_

#include <string>
#include<functional>

namespace cv {
    class Mat;
}
namespace rw
{
    namespace hoec
    {
        struct CameraInfo
        {
            std::string ip;
            std::string name;
            std::string mac;
        };

        enum class CameraTakePictureMode
        {
            Active,
            Passive
        };

        enum class CameraMonitorMode
        {
            SoftwareTriggered,
            HardwareTriggered,
        };

        enum class CameraProvider
        {
            MVS
        };

        class ICamera
        {
        public:
            virtual ~ICamera() = default;
            ICamera() = default;
            ICamera(ICamera&&) = delete;
            ICamera& operator=(ICamera&&) = delete;

            ICamera(const ICamera&) = delete;
            ICamera& operator=(const ICamera&) = delete;
        public:
            virtual void setIP(const std::string &ip) = 0;
            virtual std::string getIP() const = 0;

        public:
            virtual bool connectCamera() = 0;

        public:
            virtual bool startMonitor() = 0;
            virtual bool stopMonitor() = 0;

        public:
            virtual bool setExposureTime(size_t value) = 0;
            virtual bool setGain(size_t value) = 0;
            virtual bool setMonitorMode(CameraMonitorMode mode) = 0;
            virtual bool setIOTime(size_t value) = 0;

            virtual size_t getExposureTime()=0;
            virtual size_t getGain()=0;
            virtual size_t getIOTime()=0;
            virtual CameraMonitorMode getMonitorMode()=0;
        };

        class ICameraActive
            : public ICamera
        {
        public:
            virtual cv::Mat getImage(bool& isget)=0;
            virtual cv::Mat getImage() = 0;
        };

        class ICameraPassive
            : public ICamera
        {
        public:
            using UserToCallBack = std::function<void(cv::Mat)>;
        public:
            virtual bool RegisterCallBackFunc()=0;

        };

        class Camera
            : public ICamera
        {
            
        };
    }
}

#endif