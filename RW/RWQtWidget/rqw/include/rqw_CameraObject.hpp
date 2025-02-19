#pragma once

#include<memory>

#include<QObject>
#include<QString>
#include<QVector>

#include<opencv2/opencv.hpp>

namespace rw {
    namespace hoec
    {
        class CameraPassive;
    }

    namespace rqw {

        struct CameraMetaData
        {
            QString ip{ "Undefined" };
            QString provider{ "Undefined" };
        public:
            CameraMetaData() = default;
            CameraMetaData(QString ip, QString provider)
                :ip(std::move(ip)), provider(std::move(provider))
            {
            }

            CameraMetaData(const CameraMetaData& other)
                :ip(other.ip), provider(other.provider)
            {
            }

            CameraMetaData& operator=(const CameraMetaData& other)
            {
                ip = other.ip;
                provider = other.provider;
                return *this;
            }

            CameraMetaData(CameraMetaData&& other) noexcept
                :ip(std::move(other.ip)), provider(std::move(other.provider))
            {
            }

            CameraMetaData& operator=(CameraMetaData&& other) noexcept
            {
                ip = std::move(other.ip);
                provider = std::move(other.provider);
                return *this;
            }

            ~CameraMetaData() = default;

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
