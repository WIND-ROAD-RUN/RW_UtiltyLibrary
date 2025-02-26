#include"hoec_Camera_MVS_private_t.h"
#include"hoec_CameraException.hpp"

#include"opencv2/opencv.hpp"
#include<iostream>

//namespace hoec_Camera_MVS {
//    TEST(Camera_MVS_Test, INIADNDEC_SDC) {
//        EXPECT_EQ(Camera_MVS::initSDK(), true);
//        EXPECT_EQ(Camera_MVS::_isIniSDK, true);
//        EXPECT_EQ(Camera_MVS::unInitSDK(), true);
//        EXPECT_EQ(Camera_MVS::_isIniSDK, false);
//    }
//
//    TEST(Camera_MVS_Test, GET_IP_LIST) {
//        std::cout << Camera_MVS::getCameraIpList().size() << std::endl;
//        for (size_t i = 0; i < Camera_MVS::getCameraIpList().size(); i++)
//        {
//            std::cout << Camera_MVS::getCameraIpList()[i] << std::endl;
//        }
//    }
//
//    TEST(Camera_MVS_Test, GET_INFO_LIST) {
//        std::cout << Camera_MVS::getCameraInfoList().size() << std::endl;
//        for (size_t i = 0; i < Camera_MVS::getCameraInfoList().size(); i++)
//        {
//            std::cout << Camera_MVS::getCameraInfoList()[i].ip << std::endl;
//            std::cout << Camera_MVS::getCameraInfoList()[i].name << std::endl;
//            std::cout << Camera_MVS::getCameraInfoList()[i].mac << std::endl;
//        }
//    }
//
//    TEST(Camera_MVS_Test, CAMERA_ip) {
//        rw::hoec::Camera_MVS camera;
//        camera.setIP("1");
//        EXPECT_EQ(camera.getIP(), "1");
//    }
//
//    TEST(Camera_MVS_Test, camera_connect) {
//        rw::hoec::Camera_MVS::initSDK();
//
//        auto ipList = Camera_MVS::getCameraIpList();
//
//        //创建相机列表
//        std::vector<std::shared_ptr<Camera_MVS>> cameraList;
//        if (!cameraList.size()) {
//            std::cout << "No camera found" << std::endl;
//            EXPECT_EQ(true, true);
//            return;
//        }
//        for (const auto& item : ipList) {
//            auto camera = std::make_shared<Camera_MVS>();
//            camera->setIP(item);
//            cameraList.push_back(camera);
//        }
//        for (auto& item : cameraList) {
//            EXPECT_EQ(item->connectCamera(), true);
//        }
//        cameraList.clear();
//        Camera_MVS::unInitSDK();
//    }
//
//    /**
//     * @brief Test the function setExposureTime in class Camera_MVS can sucessfully set the camera's exposuretime
//     *
//     * @details
//     * Test Steps:
//     * 1. Initialize the camera and the relevant resource
//     * 2. Connect each camera and set the exposuretime
//     * 3. Return expected result and exposuretime is set successfully to the camera
//     *
//     * Expected Result:
//     * 1. Return true when the exposuretime is set successfully and return false in other case
//     * 2. The camera is set the given exposuretime and the images shot by it are in the exposuretime
//     * 3. Run successfully
//     *
//     * Boundary Conditions:
//     * 1. The value of exposuretime cannot be negative number and it has the minninum and maxnum
//     */
//    TEST(Camera_MVS_Test, setExposureTime_isSetSuccessfully) {
//        rw::hoec::Camera_MVS::initSDK();
//
//        //获取相机IP列表
//        auto ipList = Camera_MVS::getCameraIpList();
//
//        //创建相机对象
//        std::vector<std::shared_ptr<Camera_MVS_Active>> cameraList;
//        if (!ipList.size()) {
//            std::cout << "No camera found" << std::endl;
//            EXPECT_EQ(true, true);
//            return;
//        }
//        for (const auto& item : ipList) {
//            auto camera = std::make_shared<Camera_MVS_Active>();
//            camera->setIP(item);
//            cameraList.push_back(std::move(camera));
//        }
//        bool isfirst{ true };
//        for (auto& item : cameraList) {
//            //连接相机
//            EXPECT_EQ(item->connectCamera(), true);
//            EXPECT_EQ(item->setTriggerMode(::CameraTriggerMode::SoftwareTriggered), true);
//            if (isfirst) {
//                EXPECT_EQ(item->setExposureTime(20000), true);
//                isfirst = false;
//            }
//            else {
//                EXPECT_EQ(item->setExposureTime(2000), true);
//                isfirst = true;
//            }
//            item->startMonitor();
//            bool isGet{};
//            auto image = item->getImage(isGet);
//
//            ASSERT_EQ(isGet, true);
//            //cv::imshow("image", image);
//            //cv::waitKey(0);
//            item->stopMonitor();
//        }
//        cameraList.clear();
//        Camera_MVS::unInitSDK();
//    }
//
//    TEST(Camera_MVS_Test, setGain_isSetSuccessfully) {
//        rw::hoec::Camera_MVS::initSDK();
//
//        //获取相机IP列表
//        auto ipList = Camera_MVS::getCameraIpList();
//
//        //创建相机对象
//        std::vector<std::shared_ptr<Camera_MVS_Active>> cameraList;
//        if (!ipList.size()) {
//            std::cout << "No camera found" << std::endl;
//            EXPECT_EQ(true, true);
//            return;
//        }
//        for (const auto& item : ipList) {
//            auto camera = std::make_shared<Camera_MVS_Active>();
//            camera->setIP(item);
//            cameraList.push_back(std::move(camera));
//        }
//        bool isfirst{ true };
//        for (auto& item : cameraList) {
//            //连接相机
//            EXPECT_EQ(item->connectCamera(), true);
//            EXPECT_EQ(item->setTriggerMode(CameraTriggerMode::SoftwareTriggered), true);
//            if (isfirst) {
//                EXPECT_EQ(item->setExposureTime(20000), true);
//                EXPECT_EQ(item->setGain(15), true);
//                isfirst = false;
//            }
//            else {
//                EXPECT_EQ(item->setExposureTime(40000), true);
//                EXPECT_EQ(item->setGain(15), true);
//                isfirst = true;
//            }
//            item->startMonitor();
//            bool isGet{ false };
//            auto image = item->getImage(isGet);
//
//            ASSERT_EQ(isGet, true);
//            //cv::imshow("image", image);
//            //cv::waitKey(0);
//            item->stopMonitor();
//        }
//        cameraList.clear();
//        Camera_MVS::unInitSDK();
//    }
//
//    TEST(Camera_MVS_Test, getExposureTime) {
//        rw::hoec::Camera_MVS::initSDK();
//
//        auto ipList = Camera_MVS::getCameraIpList();
//
//        std::vector<std::shared_ptr<Camera_MVS>> cameraList;
//        if (!cameraList.size()) {
//            std::cout << "No camera found" << std::endl;
//            EXPECT_EQ(true, true);
//            return;
//        }
//        for (auto& item : ipList) {
//            auto camera = std::make_shared<Camera_MVS>();
//            camera->setIP(item);
//            cameraList.push_back(camera);
//        }
//        for (auto& item : cameraList) {
//            EXPECT_EQ(item->connectCamera(), true);
//            EXPECT_EQ(item->setExposureTime(2000), true);
//            EXPECT_EQ(item->getExposureTime(), 2000);
//        }
//        cameraList.clear();
//        Camera_MVS::unInitSDK();
//    }
//
//    TEST(Camera_MVS_Test, getGain) {
//        rw::hoec::Camera_MVS::initSDK();
//
//        auto ipList = Camera_MVS::getCameraIpList();
//
//        std::vector<std::shared_ptr<Camera_MVS_Active>> cameraList;
//        if (!cameraList.size()) {
//            std::cout << "No camera found" << std::endl;
//            EXPECT_EQ(true, true);
//            return;
//        }
//        for (auto& item : ipList) {
//            auto camera = std::make_shared<Camera_MVS_Active>();
//            camera->setIP(item);
//            cameraList.push_back(camera);
//        }
//        for (auto& item : cameraList) {
//            EXPECT_EQ(item->connectCamera(), true);
//            EXPECT_EQ(item->setGain(200), true);
//            EXPECT_EQ(item->getGain(), 200);
//        }
//        cameraList.clear();
//        Camera_MVS::unInitSDK();
//    }
//
//    TEST(Camera_MVS_Test, setSoftwareTriggerMode) {
//        rw::hoec::Camera_MVS::initSDK();
//
//        auto ipList = Camera_MVS::getCameraIpList();
//
//        std::vector<std::shared_ptr<Camera_MVS_Active >> cameraList;
//        if (!ipList.size()) {
//            std::cout << "No camera found" << std::endl;
//            EXPECT_EQ(true, true);
//            return;
//        }
//        for (auto& item : ipList) {
//            auto camera = std::make_shared<Camera_MVS_Active>();
//            camera->setIP(item);
//            cameraList.push_back(camera);
//        }
//        for (auto& item : cameraList) {
//            EXPECT_EQ(item->connectCamera(), true);
//            EXPECT_EQ(item->setTriggerMode(CameraTriggerMode::SoftwareTriggered), true);
//        }
//        cameraList.clear();
//        Camera_MVS::unInitSDK();
//    }
//
//    TEST(Camera_MVS_Test, setHardwareTriggerMode) {
//        rw::hoec::Camera_MVS::initSDK();
//
//        auto ipList = Camera_MVS::getCameraIpList();
//
//        std::vector<std::shared_ptr<Camera_MVS_Active >> cameraList;
//        if (!ipList.size()) {
//            std::cout << "No camera found" << std::endl;
//            EXPECT_EQ(true, true);
//            return;
//        }
//        for (auto& item : ipList) {
//            auto camera = std::make_shared<Camera_MVS_Active>();
//            camera->setIP(item);
//            cameraList.push_back(camera);
//        }
//        for (auto& item : cameraList) {
//            EXPECT_EQ(item->connectCamera(), true);
//            EXPECT_EQ(item->setTriggerMode(CameraTriggerMode::HardwareTriggered), true);
//        }
//        cameraList.clear();
//        Camera_MVS::unInitSDK();
//    }
//
//    TEST(Camera_MVS_Test, setSoftwareTriggerMode_isSuccessfully) {
//        int status = 0;
//        rw::hoec::Camera_MVS::initSDK();
//
//        auto ipList = Camera_MVS::getCameraIpList();
//
//        std::vector<std::shared_ptr<Camera_MVS_Passive>>cameraList;
//        if (!ipList.size()) {
//            std::cout << "No camera found" << std::endl;
//            EXPECT_EQ(true, true);
//            return;
//        }
//        for (const auto& item : ipList) {
//            auto camera = std::make_shared<Camera_MVS_Passive>([&status](cv::Mat a) {
//                std::cout << "We have gotten a image" << std::endl;
//                status = 1;
//                });
//            camera->setIP(item);
//            cameraList.push_back(std::move(camera));
//        }
//        for (auto& item : cameraList) {
//            //连接相机
//            EXPECT_EQ(item->connectCamera(), true);
//            EXPECT_EQ(item->setTriggerMode(CameraTriggerMode::SoftwareTriggered), true);
//            //注册回调函数
//            auto registerResult = item->RegisterCallBackFunc();
//            EXPECT_EQ(registerResult, true);
//            //开始监控
//            EXPECT_EQ(item->startMonitor(), true);
//
//            for (int i = 0; i < 500; i++) {
//                std::this_thread::sleep_for(std::chrono::milliseconds(10));
//                //wait for callback
//            }
//            EXPECT_EQ(status, 1);
//
//            status = 0;
//
//            //停止监控
//            EXPECT_EQ(item->stopMonitor(), true);
//        }
//        cameraList.clear();
//        Camera_MVS::unInitSDK();
//    }
//
//    TEST(Camera_MVS_Test, getSoftwareTriggerMode) {
//        rw::hoec::Camera_MVS::initSDK();
//
//        auto ipList = Camera_MVS::getCameraIpList();
//
//        std::vector<std::shared_ptr<Camera_MVS_Active >> cameraList;
//        if (!ipList.size()) {
//            std::cout << "No camera found" << std::endl;
//            EXPECT_EQ(true, true);
//            return;
//        }
//        for (auto& item : ipList) {
//            auto camera = std::make_shared<Camera_MVS_Active>();
//            camera->setIP(item);
//            cameraList.push_back(camera);
//        }
//        for (auto& item : cameraList) {
//            EXPECT_EQ(item->connectCamera(), true);
//            EXPECT_EQ(item->setTriggerMode(CameraTriggerMode::SoftwareTriggered), true);
//            EXPECT_EQ(item->getMonitorMode(), CameraTriggerMode::SoftwareTriggered);
//        }
//        cameraList.clear();
//        Camera_MVS::unInitSDK();
//    }
//
//    TEST(Camera_MVS_Test, getHardwareTriggerMode)
//    {
//        rw::hoec::Camera_MVS::initSDK();
//        auto ipList = Camera_MVS::getCameraIpList();
//
//        std::vector<std::shared_ptr<Camera_MVS_Active >> cameraList;
//        if (!ipList.size()) {
//            std::cout << "No camera found" << std::endl;
//            EXPECT_EQ(true, true);
//            return;
//        }
//        for (auto& item : ipList) {
//            auto camera = std::make_shared<Camera_MVS_Active>();
//            camera->setIP(item);
//            cameraList.push_back(camera);
//        }
//        for (auto& item : cameraList) {
//            EXPECT_EQ(item->connectCamera(), true);
//            EXPECT_EQ(item->setTriggerMode(CameraTriggerMode::HardwareTriggered), true);
//            EXPECT_EQ(item->getMonitorMode(), CameraTriggerMode::HardwareTriggered);
//        }
//        cameraList.clear();
//        Camera_MVS::unInitSDK();
//    }
//
//    TEST(Camera_MVS_Test, setTriggerLine) {
//        rw::hoec::Camera_MVS::initSDK();
//
//        auto ipList = Camera_MVS::getCameraIpList();
//
//        std::vector<std::shared_ptr<Camera_MVS_Active >> cameraList;
//        if (!ipList.size()) {
//            std::cout << "No camera found" << std::endl;
//            EXPECT_EQ(true, true);
//            return;
//        }
//        for (auto& item : ipList) {
//            auto camera = std::make_shared<Camera_MVS_Active>();
//            camera->setIP(item);
//            cameraList.push_back(camera);
//        }
//        //bool issecond{ false };
//        for (auto& item : cameraList) {
//            EXPECT_EQ(item->connectCamera(), true);
//            EXPECT_EQ(item->setTriggerLine(0), true);
//        }
//        cameraList.clear();
//        Camera_MVS::unInitSDK();
//    }
//
//    TEST(Camera_MVS_Test, getTriggerLine)
//    {
//        rw::hoec::Camera_MVS::initSDK();
//
//        auto ipList = Camera_MVS::getCameraIpList();
//
//        std::vector<std::shared_ptr<Camera_MVS_Active >> cameraList;
//        if (!ipList.size()) {
//            std::cout << "No camera found" << std::endl;
//            EXPECT_EQ(true, true);
//            return;
//        }
//        for (auto& item : ipList) {
//            auto camera = std::make_shared<Camera_MVS_Active>();
//            camera->setIP(item);
//            cameraList.push_back(camera);
//        }
//        //bool issecond{ false };
//        for (auto& item : cameraList) {
//            EXPECT_EQ(item->connectCamera(), true);
//            EXPECT_EQ(item->setTriggerLine(0), true);
//            EXPECT_EQ(item->getTriggerLine(), 0);
//        }
//        cameraList.clear();
//        Camera_MVS::unInitSDK();
//    }
//
//    TEST(Camera_MVS_Active_Test, CAMERA_CONNECT) {
//        //使用前初始化SDK也即相机模块
//        rw::hoec::Camera_MVS_Active::initSDK();
//
//        //获取相机IP列表
//        auto ipList = Camera_MVS_Active::getCameraIpList();
//        //创建相机对象
//        std::vector<std::shared_ptr<Camera_MVS_Active>> cameraList;
//        if (!ipList.size()) {
//            std::cout << "No camera found" << std::endl;
//            EXPECT_EQ(true, true);
//            return;
//        }
//        for (const auto& item : ipList) {
//            auto camera = std::make_shared<Camera_MVS_Active>();
//            camera->setIP(item);
//            cameraList.push_back(std::move(camera));
//        }
//        for (auto& item : cameraList) {
//            //连接相机
//            EXPECT_EQ(item->connectCamera(), true);
//        }
//        cameraList.clear();
//        Camera_MVS_Active::unInitSDK();
//    }
//
//    TEST(Camera_MVS_Active_Test, monitor) {
//        //使用前初始化SDK也即相机模块
//        rw::hoec::Camera_MVS_Active::initSDK();
//        //获取相机IP列表
//        auto ipList = Camera_MVS_Active::getCameraIpList();
//        //创建相机对象
//        std::vector<std::shared_ptr<Camera_MVS_Active>> cameraList;
//        if (!ipList.size()) {
//            std::cout << "No camera found" << std::endl;
//            EXPECT_EQ(true, true);
//            return;
//        }
//        for (const auto& item : ipList) {
//            auto camera = std::make_shared<Camera_MVS_Active>();
//            camera->setIP(item);
//            cameraList.push_back(std::move(camera));
//        }
//        for (auto& item : cameraList) {
//            //连接相机
//            EXPECT_EQ(item->connectCamera(), true);
//            //开始监控
//            EXPECT_EQ(item->startMonitor(), true);
//
//            bool isget = false;
//            auto image = item->getImage(isget);
//            EXPECT_EQ(!isget, image.empty());
//            //停止监控
//            EXPECT_EQ(item->stopMonitor(), true);
//        }
//        cameraList.clear();
//        Camera_MVS_Active::unInitSDK();
//
//    }
//
//    TEST(Camera_MVS_Passive_Test, registerUserCallBack) {
//        int status = 0;
//        //使用前初始化SDK也即相机模块
//        rw::hoec::Camera_MVS_Passive::initSDK();
//        //获取相机IP列表
//        auto ipList = Camera_MVS_Passive::getCameraIpList();
//        //创建相机对象
//        std::vector<std::shared_ptr<Camera_MVS_Passive>> cameraList;
//        if (!ipList.size()) {
//            std::cout << "No camera found" << std::endl;
//            EXPECT_EQ(true, true);
//            return;
//        }
//        for (const auto& item : ipList) {
//            auto camera = std::make_shared<Camera_MVS_Passive>([&status](cv::Mat a) {
//                std::cout << "999999" << std::endl;
//                status = 1;
//                });
//            camera->setIP(item);
//            cameraList.push_back(std::move(camera));
//        }
//        for (auto& item : cameraList) {
//            //连接相机
//            EXPECT_EQ(item->connectCamera(), true);
//            EXPECT_EQ(item->setTriggerMode(CameraTriggerMode::SoftwareTriggered), true);
//            //注册回调函数
//            auto registerResult = item->RegisterCallBackFunc();
//            EXPECT_EQ(registerResult, true);
//            //开始监控
//            EXPECT_EQ(item->startMonitor(), true);
//
//            for (int i = 0; i < 500; i++) {
//                std::this_thread::sleep_for(std::chrono::milliseconds(10));
//                //wait for callback
//            }
//            EXPECT_EQ(status, 1);
//
//            status = 0;
//
//            //停止监控
//            EXPECT_EQ(item->stopMonitor(), true);
//        }
//        //...其他操作
//        //使用相机后释放SDK
//        cameraList.clear();
//        Camera_MVS_Passive::unInitSDK();
//    }
//}


namespace  hoec_Camera_MVS
{
    TEST(hoec_Camera_MVS, sdk)
    {
        try
        {
            rw::hoec::Camera_MVS::initSDK();
        }
        catch (const CameraInitError& e)
        {
            std::cout << e.what() << '\n';
            FAIL();
        }

        try
        {
            rw::hoec::Camera_MVS::unInitSDK();
        }
        catch (const CameraInitError& e)
        {
            std::cout << e.what() << '\n';
            FAIL();
        }

        SUCCEED();
    }

    TEST(hoec_Camera_MVS, CheckIplist)
    {
        Camera_MVS::getCameraIpList();
    }

    TEST(heoc_Camera_MVS, PassiveActiveConstruct)
    {
        Camera_MVS_Active cameraActive;
        Camera_MVS_Passive cameraPassive;
    }

    TEST(heoc_Camera_MVS, PassiveActiveConnect)
    {
        auto ipList = Camera_MVS::getCameraIpList();
        if (ipList.size() == 0)
        {
            std::cout << "Please connect the camera before test" << '\n';
            SUCCEED();
            return;
        }

        std::cout << "Will test camera by one" << '\n';
        {
            Camera_MVS_Active cameraActive;
            cameraActive.setIP(ipList[0]);

            try
            {
                cameraActive.connectCamera();
            }
            catch (const CameraConnectionError& e)
            {
                std::cout << e.what() << '\n';
                FAIL();
            }

            auto cameraInfo = cameraActive.getCameraInfo();
            std::cout << cameraInfo.ip << '\n';
            std::cout << cameraInfo.name << '\n';
            std::cout << cameraInfo.mac << '\n';

        }


        {
            Camera_MVS_Passive cameraPassive;
            cameraPassive.setIP(ipList[0]);

            try
            {
                cameraPassive.connectCamera();
            }
            catch (const CameraConnectionError& e)
            {
                std::cout << e.what() << '\n';
                FAIL();
            }

            auto cameraInfo = cameraPassive.getCameraInfo();
            std::cout << cameraInfo.ip << '\n';
            std::cout << cameraInfo.name << '\n';
            std::cout << cameraInfo.mac << '\n';

        }

        SUCCEED();

    }

    TEST(heoc_Camera_MVS, PassiveActiveMonitor)
    {
        auto ipList = Camera_MVS::getCameraIpList();
        if (ipList.size() == 0)
        {
            std::cout << "Please connect the camera before test" << '\n';
            SUCCEED();
            return;
        }

        std::cout << "Will test camera by one" << '\n';
        {
            Camera_MVS_Active cameraActive;
            cameraActive.setIP(ipList[0]);

            try
            {
                cameraActive.connectCamera();
            }
            catch (const CameraConnectionError& e)
            {
                std::cout << e.what() << '\n';
                FAIL();
            }

            try
            {
                cameraActive.startMonitor();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                cameraActive.stopMonitor();
            }
            catch (const CameraMonitorError& e)
            {
                std::cout << e.what() << '\n';
                FAIL();
            }


        }


        {
            Camera_MVS_Passive cameraPassive;
            cameraPassive.setIP(ipList[0]);

            try
            {
                cameraPassive.connectCamera();
            }
            catch (const CameraConnectionError& e)
            {
                std::cout << e.what() << '\n';
                FAIL();
            }

            try
            {
                cameraPassive.startMonitor();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                cameraPassive.stopMonitor();
            }
            catch (const CameraMonitorError& e)
            {
                std::cout << e.what() << '\n';
                FAIL();
            }

        }

        SUCCEED();

    }

    TEST(heoc_Camera_MVS, PassiveActiveMonitorError)
    {
        auto ipList = Camera_MVS::getCameraIpList();
        if (ipList.size() == 0)
        {
            std::cout << "Please connect the camera before test" << '\n';
            SUCCEED();
            return;
        }

        std::cout << "Will test camera by one" << '\n';
        {
            Camera_MVS_Active cameraActive;
            cameraActive.setIP(ipList[0]);

            try
            {
                cameraActive.connectCamera();
            }
            catch (const CameraConnectionError& e)
            {
                std::cout << e.what() << '\n';
                FAIL();
            }

            try
            {
                cameraActive.startMonitor();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));

                try
                {
                    cameraActive.startMonitor();
                    FAIL() << "Do not allow startMonitor twice";
                }
                catch (const CameraMonitorError& e)
                {
                    SUCCEED();
                }
            }
            catch (const CameraMonitorError& e)
            {
                std::cout << e.what() << '\n';
                FAIL();
            }


        }


        {
            Camera_MVS_Passive cameraPassive;
            cameraPassive.setIP(ipList[0]);

            try
            {
                cameraPassive.connectCamera();
            }
            catch (const CameraConnectionError& e)
            {
                std::cout << e.what() << '\n';
                FAIL();
            }

            try
            {
                cameraPassive.startMonitor();
                try
                {
                    cameraPassive.startMonitor();
                    FAIL() << "Do not allow startMonitor twice";
                }
                catch (const CameraMonitorError& e)
                {
                    SUCCEED();
                }
            }
            catch (const CameraMonitorError& e)
            {
                std::cout << e.what() << '\n';
                FAIL();
            }

        }

        SUCCEED();

    }

    TEST(heoc_Camera_MVS, PassiveActiveSet)
    {
        auto ipList = Camera_MVS::getCameraIpList();
        if (ipList.size() == 0)
        {
            std::cout << "Please connect the camera before test" << '\n';
            SUCCEED();
            return;
        }

        std::cout << "Will test camera by one" << '\n';

        {
            Camera_MVS_Active cameraActive;
            cameraActive.setIP(ipList[0]);

            try
            {
                cameraActive.connectCamera();
            }
            catch (const CameraConnectionError& e)
            {
                std::cout << e.what() << '\n';
                FAIL();
            }

            try
            {
                cameraActive.startMonitor();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));

            }
            catch (const CameraMonitorError& e)
            {
                std::cout << e.what() << '\n';
                FAIL();
            }


            try
            {
                cameraActive.setExposureTime(2000);
                cameraActive.setGain(10);
                cameraActive.setTriggerLine(0);
                //cameraActive.setIOTime(2000); //实现还有问题
                cameraActive.setTriggerMode(CameraTriggerMode::SoftwareTriggered);
            }
            catch (const CameraSettingError& e)
            {
                std::cout << e.what() << '\n';
                FAIL();
            }


            try
            {
                auto exposureTime = cameraActive.getExposureTime();
                EXPECT_EQ(exposureTime, 2000);

                auto gain = cameraActive.getGain();
                EXPECT_EQ(gain, 10);

                /*auto ioTime = cameraActive.getIOTime();
                EXPECT_EQ(ioTime, 2000);*/

                auto triggerMode = cameraActive.getMonitorMode();
                EXPECT_EQ(triggerMode, CameraTriggerMode::SoftwareTriggered);

                auto triggerLine = cameraActive.getTriggerLine();
                EXPECT_EQ(triggerLine, 0);
            }
            catch (const CameraRetrievalError& e)
            {
                std::cout << e.what() << '\n';
                FAIL();
            }


            try
            {
                cameraActive.stopMonitor();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));

            }
            catch (const CameraMonitorError& e)
            {
                std::cout << e.what() << '\n';
                FAIL();
            }

        }


        {
            Camera_MVS_Passive cameraPassive;
            cameraPassive.setIP(ipList[0]);

            try
            {
                cameraPassive.connectCamera();
            }
            catch (const CameraConnectionError& e)
            {
                std::cout << e.what() << '\n';
                FAIL();
            }

            try
            {
                cameraPassive.startMonitor();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            catch (const CameraMonitorError& e)
            {
                std::cout << e.what() << '\n';
                FAIL();
            }

            try
            {
                cameraPassive.setExposureTime(2000);
                cameraPassive.setGain(10);
                cameraPassive.setTriggerLine(0);
                //cameraActive.setIOTime(2000); //实现还有问题
                cameraPassive.setTriggerMode(CameraTriggerMode::SoftwareTriggered);
            }
            catch (const CameraSettingError& e)
            {
                std::cout << e.what() << '\n';
                FAIL();
            }

            try
            {
                auto exposureTime = cameraPassive.getExposureTime();
                EXPECT_EQ(exposureTime, 2000);

                auto gain = cameraPassive.getGain();
                EXPECT_EQ(gain, 10);

                /*             auto ioTime = cameraPassive.getIOTime();
                             EXPECT_EQ(ioTime, 2000);*/

                auto triggerMode = cameraPassive.getMonitorMode();
                EXPECT_EQ(triggerMode, CameraTriggerMode::SoftwareTriggered);

                auto triggerLine = cameraPassive.getTriggerLine();
                EXPECT_EQ(triggerLine, 0);
            }
            catch (const CameraRetrievalError& e)
            {
                std::cout << e.what() << '\n';
                FAIL();
            }


            try
            {
                cameraPassive.stopMonitor();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));

            }
            catch (const CameraMonitorError& e)
            {
                std::cout << e.what() << '\n';
                FAIL();
            }


        }

        SUCCEED();

    }

    TEST(heoc_Camera_MVS, ActiveTakePicture)
    {
        auto ipList = Camera_MVS::getCameraIpList();
        if (ipList.size() == 0)
        {
            std::cout << "Please connect the camera before test" << '\n';
            SUCCEED();
            return;
        }

        std::cout << "Will test camera by one" << '\n';
        Camera_MVS_Active cameraActive;
        cameraActive.setIP(ipList[0]);

        try
        {
            cameraActive.connectCamera();
        }
        catch (const CameraConnectionError& e)
        {
            std::cout << e.what() << '\n';
            FAIL();
        }

        try
        {
            cameraActive.startMonitor();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        catch (const CameraMonitorError& e)
        {
            std::cout << e.what() << '\n';
            FAIL();
        }

        try
        {
            auto imageGet = cameraActive.getImage();
            auto size = imageGet.size();
            EXPECT_GT(size.width, 0);
            EXPECT_GT(size.height, 0);

            cv::waitKey(0);
        }
        catch (const CameraRetrievalError& e)
        {
            std::cout << e.what() << '\n';
            FAIL();
        }



        SUCCEED();

    }

    TEST(heoc_Camera_MVS, PassiveTakePicture)
    {
        auto ipList = Camera_MVS::getCameraIpList();
        if (ipList.size() == 0)
        {
            std::cout << "Please connect the camera before test" << '\n';
            SUCCEED();
            return;
        }

        std::cout << "Will test camera by one" << '\n';
        Camera_MVS_Passive cameraPassive([](cv::Mat mat)
            {
                std::cout << mat.size().width << '\n';
                std::cout << mat.size().height << '\n';
                std::cout << "We have gotten a image" << '\n';
            });
        cameraPassive.setIP(ipList[0]);

        try
        {
            cameraPassive.connectCamera();
        }
        catch (const CameraConnectionError& e)
        {
            std::cout << e.what() << '\n';
            FAIL();
        }

        try
        {
            cameraPassive.RegisterCallBackFunc();
            cameraPassive.startMonitor();
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        }
        catch (const CameraMonitorError& e)
        {
            std::cout << e.what() << '\n';
            FAIL();
        }



        SUCCEED();

    }

}
