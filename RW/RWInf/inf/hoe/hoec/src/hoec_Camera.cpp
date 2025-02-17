#include"hoec_Camera.hpp"

#include"hoec_Camera_private.hpp"

namespace rw {
    namespace hoec {
        void ICamera::setIP(const std::string& ip)
        {
            _ip = ip;
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

        bool CameraActive::connectCamera()
        {
            _camera->setIP(_ip);
            return _camera->connectCamera();
        }

        bool CameraActive::startMonitor()
        {
            return _camera->startMonitor();
        }

        bool CameraActive::stopMonitor()
        {
            return _camera->stopMonitor();
        }

        bool CameraActive::setExposureTime(size_t value)
        {
            return _camera->setExposureTime(value);
        }

        bool CameraActive::setGain(size_t value)
        {
            return _camera->setGain(value);
        }

        bool CameraActive::setIOTime(size_t value)
        {
            return _camera->setIOTime(value);
        }

        bool CameraActive::setTriggerMode(CameraTriggerMode mode)
        {
            return _camera->setTriggerMode(mode);
        }

        bool CameraActive::setTriggerLine(size_t lineIndex)
        {
            return _camera->setTriggerLine(lineIndex);
        }

        size_t CameraActive::getExposureTime()
        {
            return _camera->getExposureTime();
        }

        size_t CameraActive::getGain()
        {
            return _camera->getGain();
        }

        size_t CameraActive::getIOTime()
        {
            return _camera->getIOTime();
        }

        CameraTriggerMode CameraActive::getMonitorMode()
        {
            return _camera->getMonitorMode();
        }

        size_t CameraActive::getTriggerLine()
        {
            return _camera->getTriggerLine();
        }

        cv::Mat CameraActive::getImage(bool& isGet)
        {
            return _cameraActive->getImage(isGet);
        }

        cv::Mat CameraActive::getImage()
        {
            return _cameraActive->getImage();
        }

        void CameraActive::setCameraProvider(CameraProvider provider)
        {
            _provider = provider;
        }

        CameraProvider CameraActive::getCameraProvider() const
        {
            return _provider;
        }

        CameraActive::CameraActive(ICamera* camera, ICameraActive* cameraActive)
        {
            _camera = camera;
            _cameraActive = cameraActive;
        }

        CameraActive::~CameraActive()
        {
            if (_camera)
            {
                delete _camera;
                _camera = nullptr;
            }
            _cameraActive = nullptr;
        }

        bool CameraPassive::connectCamera()
        {
            _camera->setIP(_ip);
            return _camera->connectCamera();
        }

        bool CameraPassive::startMonitor()
        {
            return _camera->startMonitor();
        }

        bool CameraPassive::stopMonitor()
        {
            return _camera->startMonitor();
        }

        bool CameraPassive::setExposureTime(size_t value)
        {
            return _camera->setExposureTime(value);
        }

        bool CameraPassive::setGain(size_t value)
        {
            return _camera->setGain(value);
        }

        bool CameraPassive::setIOTime(size_t value)
        {
            return _camera->setIOTime(value);
        }

        bool CameraPassive::setTriggerMode(CameraTriggerMode mode)
        {
            return _camera->setTriggerMode(mode);
        }

        bool CameraPassive::setTriggerLine(size_t lineIndex)
        {
            return _camera->setTriggerLine(lineIndex);
        }

        size_t CameraPassive::getExposureTime()
        {
            return _camera->getExposureTime();
        }

        size_t CameraPassive::getGain()
        {
            return _camera->getGain();
        }

        size_t CameraPassive::getIOTime()
        {
            return _camera->getIOTime();
        }

        CameraTriggerMode CameraPassive::getMonitorMode()
        {
            return _camera->getMonitorMode();
        }

        size_t CameraPassive::getTriggerLine()
        {
            return _camera->getTriggerLine();
        }

        bool CameraPassive::RegisterCallBackFunc()
        {
            return _cameraPassive->RegisterCallBackFunc();
        }

        void CameraPassive::setCameraProvider(CameraProvider provider)
        {
            _provider = provider;
        }

        CameraProvider CameraPassive::getCameraProvider() const
        {
            return _provider;
        }

        CameraPassive::CameraPassive(ICamera* camera, ICameraPassive* cameraPassive, UserToCallBack userToCallBack)
        {
            _camera = camera;
            _cameraPassive = cameraPassive;
            _userToCallBack = userToCallBack;

        }

        CameraPassive::~CameraPassive()
        {
            if (_camera)
            {
                delete _camera;
                _camera = nullptr;
            }
            _cameraPassive = nullptr;
        }
    }
}