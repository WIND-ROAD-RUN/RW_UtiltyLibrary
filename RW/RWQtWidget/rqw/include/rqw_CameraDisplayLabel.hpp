#pragma once

#include"rqw_CameraObject.hpp"

#include <memory>
#include <QLabel>

namespace rw {
    namespace rqw {

        class CameraDisplayLabel : public QLabel
        {
            Q_OBJECT
        private:
            std::unique_ptr<CameraPassiveObject> _cameraPassive;
        public:
            explicit CameraDisplayLabel(QWidget* parent = nullptr);
            ~CameraDisplayLabel() override;

        public slots:
            void onFrameCapturedWithMetaData(cv::Mat frame, CameraMetaData cameraMetaData);
        };




    } // namespace rsw

} // namespace rw
