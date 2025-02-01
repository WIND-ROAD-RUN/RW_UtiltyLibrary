#include"hoec_Camera.h"

#include"hoec_Camera_private.h"

namespace rw {
    namespace hoec {
        void ICamera::setIP(const std::string& ip)
        {
            this->_ip = ip;
        }

        std::string ICamera::getIP() const
        {
            return _ip;
        }


        CameraInfo ICamera::getCameraInfo()
        {
            return _cameraInfo;
        }

        void ICamera::setCameraInfo(const CameraInfo& cameraInfo)
        {
            _cameraInfo = cameraInfo;
        }
    }
}