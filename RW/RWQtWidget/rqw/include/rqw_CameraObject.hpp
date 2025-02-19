#pragma once

#include"hoec_CameraFactory.hpp"
#include"hoec_Camera.hpp"

#include<memory>

#include<QObject>
#include<QString>
#include<QVector>

#include<opencv2/opencv.hpp>

namespace rw {
    namespace rqw {
        struct CameraMetaData
        {
            QString ip;
            QString provider;
        };


        enum class CameraObjectTrigger
        {
            Hardware,
            Software
        };

        QVector<CameraMetaData> CheckCameraList();

        class CameraPassiveObject : public QObject
        {
            Q_OBJECT
        private:
            std::unique_ptr<hoec::CameraPassive> _cameraPassive;
        public:
            CameraPassiveObject(QObject* parent = nullptr);
            ~CameraPassiveObject() override;
        public:
            void startMonitor() const;
            void stopMonitor() const;
        public:
            void initCamera(const CameraMetaData & cameraMetaData, CameraObjectTrigger triggerMode);
        signals:
            void frameCaptured(cv::Mat frame); 
        };

    } // namespace rqw

} // namespace rw
