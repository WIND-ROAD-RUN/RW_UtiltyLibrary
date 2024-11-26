#include"hoec_Camera_private.h"

namespace rw{
    namespace hoec {
        void Camera_MVS::setIP(const std::string &ip)
        {
            this->m_ip = ip;
        }

        std::string Camera_MVS::getIP() const
        {
            return m_ip;
        }

        bool Camera_MVS::connectCamera()
        {
            //TODO: 连接相机
            return false;
        }

        bool Camera_MVS::startMonitor()
        {
            //TODO: 开始监控
            return false;
        }

        bool Camera_MVS::stopMonitor()
        {
            //TODO: 停止监控
            return false;
        }

        bool Camera_MVS::setExposureTime(size_t value)
        {
            //TODO: 设置曝光时间
            return false;
        }

        bool Camera_MVS::setGain(size_t value)
        {
            //TODO: 设置增益
            return false;
        }

        bool Camera_MVS::setMonitorMode(CameraMonitorMode mode)
        {
            //TODO: 设置监控模式
            return false;
        }

        bool Camera_MVS::setIOTime(size_t value)
        {
            //TODO: 设置IO时间
            return false;
        }
    }
}