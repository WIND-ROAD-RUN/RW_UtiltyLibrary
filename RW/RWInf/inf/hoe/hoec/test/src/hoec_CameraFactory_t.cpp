#include"hoec_CameraFactory_t.hpp"

#include"opencv2/opencv.hpp"

TEST(hoec_CameraFactoryClass, apicreateCamera)
{

    auto cameras = CameraFactory::checkAllCamera();
    if (cameras.size() == 0) {
        std::cout << "No camera found" << std::endl;
        SUCCEED();
        return;
    }

    auto camera = CameraFactory::CreateActiveCamera(cameras[0], CameraTriggerMode::SoftwareTriggered);
    if (camera == nullptr) {
        std::cout << "Failed to create camera" << std::endl;
        FAIL();
    }
}

TEST(hoec_CameraFactoryClass, apiStartMonitor)
{

    auto cameras = CameraFactory::checkAllCamera();
    if (cameras.size() == 0) {
        std::cout << "No camera found" << std::endl;
        SUCCEED();
        return;
    }

    auto camera = CameraFactory::CreateActiveCamera(cameras[0], CameraTriggerMode::SoftwareTriggered);
    if (camera == nullptr) {
        std::cout << "Failed to create camera" << std::endl;
        FAIL();
    }

    auto result=camera->startMonitor();
    EXPECT_EQ(result, true);
}

TEST(hoec_CameraFactoryClass, apiStopMonitor)
{

    auto cameras = CameraFactory::checkAllCamera();
    if (cameras.size() == 0) {
        std::cout << "No camera found" << std::endl;
        SUCCEED();
        return;
    }

    auto camera = CameraFactory::CreateActiveCamera(cameras[0], CameraTriggerMode::SoftwareTriggered);
    if (camera == nullptr) {
        std::cout << "Failed to create camera" << std::endl;
        FAIL();
    }

    auto stopResult = camera->stopMonitor();
    EXPECT_EQ(stopResult, false);

    auto result = camera->startMonitor();
    EXPECT_EQ(result, true);

    stopResult = camera->stopMonitor();
    EXPECT_EQ(stopResult, true);
}

TEST(hoec_CameraFactoryClass, createCamera)
{

    auto cameras = CameraFactory::checkAllCamera();
    if (cameras.size()==0) {
        std::cout << "No camera found" << std::endl;
        SUCCEED();
        return;
    }

    auto camera = CameraFactory::CreateActiveCamera(cameras[0],CameraTriggerMode::SoftwareTriggered);
    if (camera == nullptr) {
        std::cout << "Failed to create camera" << std::endl;
        FAIL();
    }

    camera->startMonitor();
    auto image=camera->getImage();
    if (image.empty()) {
        std::cout << "Failed to get image" << std::endl;
        FAIL();
    }
   
}

TEST(hoec_CameraFactoryClass, apiMonitorMode)
{

    auto cameras = CameraFactory::checkAllCamera();
    if (cameras.size() == 0) {
        std::cout << "No camera found" << std::endl;
        SUCCEED();
        return;
    }

    auto camera = CameraFactory::CreateActiveCamera(cameras[0], CameraTriggerMode::SoftwareTriggered);
    if (camera == nullptr) {
        std::cout << "Failed to create camera" << std::endl;
        FAIL();
    }

    auto result = camera->startMonitor();
    EXPECT_EQ(result, true);

    EXPECT_EQ(camera->getMonitorMode(), CameraTriggerMode::SoftwareTriggered);
}

TEST(hoec_CameraFactoryClass, apiSetAndGet)
{

    auto cameras = CameraFactory::checkAllCamera();
    if (cameras.size() == 0) {
        std::cout << "No camera found" << std::endl;
        SUCCEED();
        return;
    }

    auto camera = CameraFactory::CreateActiveCamera(cameras[0], CameraTriggerMode::SoftwareTriggered);
    if (camera == nullptr) {
        std::cout << "Failed to create camera" << std::endl;
        FAIL();
    }

    auto result = camera->startMonitor();
    EXPECT_EQ(result, true);

    EXPECT_EQ(camera->getMonitorMode(), CameraTriggerMode::SoftwareTriggered);

    camera->setExposureTime(100);
    camera->setGain(100);
    camera->setIOTime(100);

    auto exposureTime = camera->getExposureTime();
    EXPECT_EQ(exposureTime, 100);
    auto gain = camera->getGain();
    EXPECT_EQ(gain, 100);
    auto ioTime = camera->getIOTime();
    EXPECT_EQ(ioTime, 100);
      
}