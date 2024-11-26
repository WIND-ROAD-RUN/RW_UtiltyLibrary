#include "hoec_Camera.h"

namespace rw
{
    namespace hoec
    {
        class Camera_MVS
            : public ICamera
        {
        private:
            std::string m_ip;
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