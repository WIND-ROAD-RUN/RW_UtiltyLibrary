#pragma once

#include"hoec_Camera.hpp"
#include"hoec_CameraFactory.hpp"

#include <memory>

#include <QLabel>

namespace rw {
    namespace rqw {

        class CameraDisplayLabel : public QLabel
        {
            Q_OBJECT
        private:
            std::unique_ptr<hoec::CameraPassive> _cameraPassive;
        public:
            explicit CameraDisplayLabel(QWidget* parent = nullptr);
            ~CameraDisplayLabel();
        
        protected:
            void mousePressEvent(QMouseEvent* event) override;
        };



    } // namespace rsw

} // namespace rw
