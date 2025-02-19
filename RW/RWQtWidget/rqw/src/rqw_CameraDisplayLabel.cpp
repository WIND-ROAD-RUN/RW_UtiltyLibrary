#include"rqw_CameraDisplayLabel.hpp"

#include <QMouseEvent>
#include <QDebug>
#include"opencv2/opencv.hpp"   

namespace rw
{
    namespace rqw
    {
        CameraDisplayLabel::CameraDisplayLabel(QWidget* parent) : QLabel(parent)
        {
            auto cameraIPs = hoec::CameraFactory::checkAllCamera();
            if (cameraIPs.size() == 0)
            {
                throw std::runtime_error("No camera found");
            }
            auto cameraIP = cameraIPs[0];
            _cameraPassive = 
                hoec::CameraFactory::CreatePassiveCamera
            (cameraIP, hoec::CameraTriggerMode::SoftwareTriggered, [this](cv::Mat mat)
                {
                    static int count = 0;
                    this->setText(QString::number(count));
                    count++;
                });
            _cameraPassive->RegisterCallBackFunc();
            _cameraPassive->startMonitor();

        }

        CameraDisplayLabel::~CameraDisplayLabel()
        {
        }

        void CameraDisplayLabel::mousePressEvent(QMouseEvent* event)
        {
            // 处理鼠标按下事件
            qDebug() << "Mouse pressed at position:" << event->pos();
            QLabel::mousePressEvent(event); // 调用基类的实现
        }


    } // namespace rsw
} // namespace rw