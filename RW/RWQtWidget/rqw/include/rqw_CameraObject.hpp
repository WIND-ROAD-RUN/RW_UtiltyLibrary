#pragma once

#include<memory>

#include"rqw_CameraObjectCore.hpp"

#include<opencv2/opencv.hpp>

#include<QVector>
#include<QObject>

namespace rw {
    namespace hoec
    {
        class CameraPassive;
    }

    namespace rqw {

        class CameraPassiveObject : public QObject
        {
            Q_OBJECT
        private:
            std::unique_ptr<hoec::CameraPassive> _cameraPassive;
            CameraMetaData _cameraMetaData;
        public:
            CameraPassiveObject(const CameraPassiveObject&) = delete;
            CameraPassiveObject& operator=(const CameraPassiveObject&) = delete;
            CameraPassiveObject(CameraPassiveObject&&) = delete;
            CameraPassiveObject& operator=(CameraPassiveObject&&) = delete;
        public:
            CameraPassiveObject(QObject* parent = nullptr);
            ~CameraPassiveObject() override;
        public:
            void startMonitor() const;
            void stopMonitor() const;
        public:
            void initCamera(const CameraMetaData& cameraMetaData, CameraObjectTrigger triggerMode);
        signals:
            void frameCaptured(cv::Mat frame);
            void frameCapturedWithMetaData(cv::Mat frame, CameraMetaData cameraMetaData);
            void frameCapturedWithoutArgs();
        };

    } // namespace rqw

} // namespace rw
