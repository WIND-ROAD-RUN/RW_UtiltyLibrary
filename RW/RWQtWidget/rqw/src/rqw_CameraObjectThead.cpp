#include"rqw_CameraObjectThead.hpp"

namespace rw
{
    namespace rqw
    {
        CameraPassiveThread::CameraPassiveThread(QObject* parent)
            :QThread(parent), _cameraObject(nullptr)
        {
        }

        CameraPassiveThread::~CameraPassiveThread()
        {
            stopMonitor();
            quit();
            wait();
            delete _cameraObject;
        }

        void CameraPassiveThread::initCamera(const rw::rqw::CameraMetaData& cameraMetaData,
            rw::rqw::CameraObjectTrigger triggerMode)
        {
            if (_cameraObject)
            {
                delete _cameraObject;
            }
            if (!_cameraObject)
            {
                _cameraObject = new rw::rqw::CameraPassiveObject();
                connect(_cameraObject, &rw::rqw::CameraPassiveObject::frameCaptured, this, &CameraPassiveThread::frameCaptured);
                connect(_cameraObject, &rw::rqw::CameraPassiveObject::frameCapturedWithMetaData, this, &CameraPassiveThread::frameCapturedWithMetaData);
                connect(_cameraObject, &rw::rqw::CameraPassiveObject::frameCapturedWithoutArgs, this, &CameraPassiveThread::frameCapturedWithoutArgs);
                _cameraObject->initCamera(cameraMetaData, triggerMode);
            }
        }

        void CameraPassiveThread::startMonitor()
        {
            if (!this->isRunning())
            {
                //this->start();
            }
            if (_cameraObject)
            {
                _cameraObject->startMonitor();
            }
        }

        void CameraPassiveThread::stopMonitor()
        {
            if (_cameraObject)
            {
                _cameraObject->stopMonitor();
                delete _cameraObject;
                _cameraObject = nullptr;
            }
        }

        void CameraPassiveThread::run()
        {
            exec();
        }
    } // namespace rqw
} // namespace rw