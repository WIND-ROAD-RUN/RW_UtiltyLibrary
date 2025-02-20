#pragma once

#include"rqw_CameraObject.hpp"

#include<QThread>

namespace rw {
    namespace rqw {
        class CameraPassiveThread : public QThread
        {
            Q_OBJECT
        public:
            explicit CameraPassiveThread(QObject* parent = nullptr);
            ~CameraPassiveThread();

            void initCamera(const rw::rqw::CameraMetaData& cameraMetaData, rw::rqw::CameraObjectTrigger triggerMode);
            void startMonitor();
            void stopMonitor();

        signals:
            void frameCaptured(cv::Mat frame);
            void frameCapturedWithMetaData(cv::Mat frame, rw::rqw::CameraMetaData cameraMetaData);
            void frameCapturedWithoutArgs();

        protected:
            void run() override;

        private:
            rw::rqw::CameraPassiveObject* _cameraObject;
        };


    } // namespace rqw

} // namespace rw
