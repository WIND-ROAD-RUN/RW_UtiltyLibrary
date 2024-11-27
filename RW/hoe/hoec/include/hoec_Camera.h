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

        enum class CameraMonitorMode
        {
            HARDWARE,
            SOFTWARE
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
        private:
        
        public:
            void setIP(const std::string &ip);
            std::string getIP() const;

        public:
            bool connectCamera();

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

#endif