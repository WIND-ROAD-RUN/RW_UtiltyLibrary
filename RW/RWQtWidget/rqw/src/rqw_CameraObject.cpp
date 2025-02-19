#include "rqw_CameraObject.hpp"

namespace rw
{
    namespace rqw
    {
        QVector<CameraMetaData> CheckCameraList()
        {
            auto stdCameraIpList=hoec::CameraFactory::checkAllCamera();
            QVector<CameraMetaData> cameraIpList;
            for (auto & cameraIp: stdCameraIpList)
            {
                CameraMetaData cameraMetaData;
                cameraMetaData.ip = QString::fromStdString(cameraIp.ip);
                cameraMetaData.provider = QString::fromStdString(hoec::to_string(cameraIp.provider));
                cameraIpList.push_back(cameraMetaData);
            }

            return cameraIpList;
        }

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

        void CameraPassiveObject::initCamera(const CameraMetaData & cameraMetaData, CameraObjectTrigger triggerMode)
        {
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
                    emit frameCaptured(std::move(mat));
                });

            _cameraPassive->RegisterCallBackFunc();
        }
    } // namespace rqw
} // namespace rw
