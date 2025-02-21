#include "rqw_CameraObject.hpp"

#include"hoec_CameraFactory.hpp"
#include"hoec_Camera.hpp"

namespace rw
{
    namespace rqw
    {

        CameraPassiveObject::CameraPassiveObject(QObject* parent)
        {
        }

        CameraPassiveObject::~CameraPassiveObject()
        = default;

        void CameraPassiveObject::startMonitor() const
        {
            _cameraPassive->startMonitor();
        }

        void CameraPassiveObject::stopMonitor() const
        {
            _cameraPassive->stopMonitor();
        }

        void CameraPassiveObject::setExposureTime(size_t value) const
        {
            _cameraPassive->setExposureTime(value);
        }

        void CameraPassiveObject::setGain(size_t value) const
        {
            _cameraPassive->setGain(value);
        }

        void CameraPassiveObject::setIOTime(size_t value) const
        {
            _cameraPassive->setIOTime(value);
        }

        void CameraPassiveObject::setTriggerMode(CameraObjectTrigger mode) const
        {
            hoec::CameraTriggerMode hoecTrigger;
            if (mode == CameraObjectTrigger::Hardware)
            {
                hoecTrigger = hoec::CameraTriggerMode::HardwareTriggered;
            }
            else
            {
                hoecTrigger = hoec::CameraTriggerMode::SoftwareTriggered;
            }
            _cameraPassive->setTriggerMode(hoecTrigger);
        }

        void CameraPassiveObject::setTriggerLine(size_t lineIndex) const
        {
            _cameraPassive->setTriggerLine(lineIndex);
        }

        size_t CameraPassiveObject::getExposureTime() const
        {
            return _cameraPassive->getExposureTime();
        }

        size_t CameraPassiveObject::getGain() const
        {
            return _cameraPassive->getGain();
        }

        size_t CameraPassiveObject::getIOTime() const
        {
            return _cameraPassive->getIOTime();
        }

        CameraObjectTrigger CameraPassiveObject::getMonitorMode() const
        {
            hoec::CameraTriggerMode hoecTrigger = _cameraPassive->getMonitorMode();
            if (hoecTrigger == hoec::CameraTriggerMode::HardwareTriggered)
            {
                return CameraObjectTrigger::Hardware;
            }
            else
            {
                return CameraObjectTrigger::Software;
            }
        }

        size_t CameraPassiveObject::getTriggerLine() const
        {
            return _cameraPassive->getTriggerLine();
        }

        void CameraPassiveObject::initCamera(const CameraMetaData & cameraMetaData, CameraObjectTrigger triggerMode)
        {
            _cameraMetaData = cameraMetaData;
            hoec::CameraIP hoecCameraIp;
            hoecCameraIp.ip = cameraMetaData.ip.toStdString();
            hoecCameraIp.provider = hoec::from_string(cameraMetaData.provider.toStdString());

            hoec::CameraTriggerMode hoecTrigger;
            if (triggerMode == CameraObjectTrigger::Hardware)
            {
                hoecTrigger = hoec::CameraTriggerMode::HardwareTriggered;
            }
            else
            {
                hoecTrigger = hoec::CameraTriggerMode::SoftwareTriggered;
            }

            _cameraPassive = hoec::CameraFactory::CreatePassiveCamera(hoecCameraIp, hoecTrigger, [this](cv::Mat  mat)
                {
                    cv::Mat matCopy;
                    mat.copyTo(matCopy);
                    emit frameCaptured(std::move(mat));
                    emit frameCapturedWithoutArgs();
                    emit frameCapturedWithMetaData(std::move(matCopy), _cameraMetaData);
                });

            _cameraPassive->RegisterCallBackFunc();
        }
    } // namespace rqw
} // namespace rw
