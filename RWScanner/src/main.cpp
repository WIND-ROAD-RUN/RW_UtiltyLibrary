#include"hoec_Camera.hpp"
#include"hoec_CameraFactory.hpp"

#include"opencv2/opencv.hpp"

#include<iostream>

using namespace rw::hoec;

int main() {
    auto cameraList = rw::hoec::CameraFactory::checkAllCamera();
    
    if (cameraList.size()==0) {
        return 0;
    }

    CameraPassive::UserToCallBack a;

    auto camera = rw::hoec::CameraFactory::CreateActiveCamera(cameraList[0], rw::hoec::CameraTriggerMode::SoftwareTriggered);
    auto b=camera->getImage();
    cv::imshow("test", b);


    return 0;
}