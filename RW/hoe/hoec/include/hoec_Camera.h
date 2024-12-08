#ifndef HOEC_ICAMERA_H_
#define HOEC_ICAMERA_H_

#include <string>
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
        };

        class Camera
            : public ICamera
        {
            
        };
    }
}

#endif