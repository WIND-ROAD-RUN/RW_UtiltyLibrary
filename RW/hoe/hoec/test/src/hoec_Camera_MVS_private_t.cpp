#include"hoec_Camera_MVS_private_t.h"

#include"opencv2/opencv.hpp"
namespace hoec_Camera_MVS {
    TEST(Camera_MVS_Test, INIADNDEC_SDC) {
        EXPECT_EQ(Camera_MVS::initSDK(), true);
        EXPECT_EQ(Camera_MVS::_isIniSDK, true);
        EXPECT_EQ(Camera_MVS::uninitSDK(), true);
        EXPECT_EQ(Camera_MVS::_isIniSDK, false);
    }

    TEST(Camera_MVS_Test, GET_IP_LIST) {
        std::cout << Camera_MVS::getCameraIpList().size() << std::endl;
        for (size_t i = 0; i < Camera_MVS::getCameraIpList().size(); i++)
        {
            std::cout << Camera_MVS::getCameraIpList()[i] << std::endl;
        }
    }

    TEST(Camera_MVS_Test, GET_INFO_LIST) {
        std::cout << Camera_MVS::getCameraInfoList().size() << std::endl;
        for (size_t i = 0; i < Camera_MVS::getCameraInfoList().size(); i++)
        {
            std::cout << Camera_MVS::getCameraInfoList()[i].ip << std::endl;
            std::cout << Camera_MVS::getCameraInfoList()[i].name << std::endl;
            std::cout << Camera_MVS::getCameraInfoList()[i].mac << std::endl;
        }
    }

    TEST(Camera_MVS_Test, CAMERA_ip) {
        rw::hoec::Camera_MVS camera;
        camera.setIP("1");
        EXPECT_EQ(camera.getIP(), "1");
    }

    TEST(Camera_MVS_Active_Test, CAMERA_CONNECT) {
        //使用前初始化SDK也即相机模块
        rw::hoec::Camera_MVS_Active::initSDK();

        //获取相机IP列表
        auto ipList = Camera_MVS_Active::getCameraIpList();
        //创建相机对象
        std::vector<std::shared_ptr<Camera_MVS_Active>> cameraist;
        if (!ipList.size()) {
            std::cout << "No camera found" << std::endl;
            EXPECT_EQ(true, true);
            return;
        }
        for (const auto& item : ipList) {
            auto camera = std::make_shared<Camera_MVS_Active>();
            camera->setIP(item);
            cameraist.push_back(std::move(camera));
        }
        for (auto& item : cameraist) {
            //连接相机
            EXPECT_EQ(item->connectCamera(), true);
        }
        //...其他操作
        //使用相机后释放SDK

        Camera_MVS_Active::uninitSDK();
    }

    TEST(Camera_MVS_Active_Test, monitor) {
        //使用前初始化SDK也即相机模块
        rw::hoec::Camera_MVS_Active::initSDK();
        //获取相机IP列表
        auto ipList = Camera_MVS_Active::getCameraIpList();
        //创建相机对象
        std::vector<std::shared_ptr<Camera_MVS_Active>> cameraist;
        if (!ipList.size()) {
            std::cout << "No camera found" << std::endl;
            EXPECT_EQ(true, true);
            return;
        }
        for (const auto& item : ipList) {
            auto camera = std::make_shared<Camera_MVS_Active>();
            camera->setIP(item);
            cameraist.push_back(std::move(camera));
        }
        for (auto& item : cameraist) {
            //连接相机
            EXPECT_EQ(item->connectCamera(), true);
            //开始监控
            EXPECT_EQ(item->startMonitor(), true);

            bool isget = false;
            auto image = item->getImage(isget);
            EXPECT_EQ(!isget, image.empty());
            //停止监控
            EXPECT_EQ(item->stopMonitor(), true);
        }
        //...其他操作
        //使用相机后释放SDK
        Camera_MVS_Active::uninitSDK();

    }

    TEST(Camera_MVS_Passive_Test, registerUserCallBack) {
        int status = 0;
        //使用前初始化SDK也即相机模块
        rw::hoec::Camera_MVS_Passive::initSDK();
        //获取相机IP列表
        auto ipList = Camera_MVS_Passive::getCameraIpList();
        //创建相机对象
        std::vector<std::shared_ptr<Camera_MVS_Passive>> cameraist;
        if (!ipList.size()) {
            std::cout << "No camera found" << std::endl;
            EXPECT_EQ(true, true);
            return;
        }
        for (const auto& item : ipList) {
            auto camera = std::make_shared<Camera_MVS_Passive>([&status](cv::Mat a) {
                 status = 1;
                });
            camera->setIP(item);
            cameraist.push_back(std::move(camera));
        }
        for (auto& item : cameraist) {
            //连接相机
            EXPECT_EQ(item->connectCamera(), true);
            //注册回调函数
            auto registerResult=item->RegisterCallBack();
            EXPECT_EQ(registerResult, true);
            //开始监控
            EXPECT_EQ(item->startMonitor(), true);

            for (int i = 0; i < 500;i++) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                //wait for callback
            }
            EXPECT_EQ(status, 1);

            status = 0;

            //停止监控
            EXPECT_EQ(item->stopMonitor(), true);
        }
        //...其他操作
        //使用相机后释放SDK
        Camera_MVS_Passive::uninitSDK();
    }
}