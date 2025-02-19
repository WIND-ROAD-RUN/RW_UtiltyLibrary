#include"rqw_CameraDisplayLabel.hpp"

#include <QMouseEvent>
#include <QDebug>
#include"opencv2/opencv.hpp"
#include<QThread>

namespace rw
{
    namespace rqw
    {
        CameraDisplayLabel::CameraDisplayLabel(QWidget* parent) : QLabel(parent)
        {
            auto cameraList=CheckCameraList();
            if (cameraList.size() < 0)
            {
                return;
            }

            CameraMetaData & cameraMetaData = cameraList[0];
            _cameraPassive = std::make_unique<CameraPassiveObject>(this);
            _cameraPassive->initCamera(cameraMetaData, CameraObjectTrigger::Software);
            connect(_cameraPassive.get(), &CameraPassiveObject::frameCapturedWithMetaData, this, &CameraDisplayLabel::onFrameCapturedWithMetaData);
            _cameraPassive->startMonitor();
        }

        CameraDisplayLabel::~CameraDisplayLabel()
        {
        }

        void CameraDisplayLabel::onFrameCapturedWithMetaData(cv::Mat frame, CameraMetaData cameraMetaData)
        {
            static int count = 0;
            QString text = QString("Frame captured: %1").arg(count++);
            QString framInfo = QString("Frame Info: %1").arg(cameraMetaData.ip);
            QString framSize = QString("Frame Size: %1x%2").arg(frame.cols).arg(frame.rows);
            text += QString("\n") + framInfo + QString("\n") + framSize;
            setText(text);

            cv::Mat rgbFrame;
            cv::cvtColor(frame, rgbFrame, cv::COLOR_BGR2RGB);
            QImage img = QImage((const unsigned char*)(rgbFrame.data), rgbFrame.cols, rgbFrame.rows, QImage::Format_RGB888);
            setPixmap(QPixmap::fromImage(img));
        }
    } // namespace rsw
} // namespace rw