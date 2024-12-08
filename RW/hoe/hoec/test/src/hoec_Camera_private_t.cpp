#include"hoec_Camera_private_t.h"

#include"opencv2/opencv.hpp"

namespace hoec_Camera_MVS_refactor {
    TEST(CAMERA_MVS,INIADNDEC_SDC) {
        EXPECT_EQ(Camera_MVSToBeRefactor::initSDK(), true);
        EXPECT_EQ(Camera_MVSToBeRefactor::isIniSDK,true);
        EXPECT_EQ(Camera_MVSToBeRefactor::uninitSDK(), true);
        EXPECT_EQ(Camera_MVSToBeRefactor::isIniSDK, false);
    }

    TEST(CAMERA_MVS, GET_IP_LIST) {
        std::cout << Camera_MVSToBeRefactor::getCameraIpList().size()<<std::endl;
        for (size_t i = 0; i < Camera_MVSToBeRefactor::getCameraIpList().size(); i++)
        {
            std::cout << Camera_MVSToBeRefactor::getCameraIpList()[i] << std::endl;
        }
    }

    TEST(CAMERA_MVS, GET_INFO_LIST) {
        std::cout << Camera_MVSToBeRefactor::getCameraInfoList().size()<<std::endl;
        for (size_t i = 0; i < Camera_MVSToBeRefactor::getCameraInfoList().size(); i++)
        {
            std::cout << Camera_MVSToBeRefactor::getCameraInfoList()[i].ip << std::endl;
            std::cout << Camera_MVSToBeRefactor::getCameraInfoList()[i].name << std::endl;
            std::cout << Camera_MVSToBeRefactor::getCameraInfoList()[i].mac << std::endl;
        }
    }

    TEST(CAMERAMVS, CAMERA_ip) {
        rw::hoec::Camera_MVSToBeRefactor camera;
        camera.setIP("1");
        EXPECT_EQ(camera.getIP(), "1");
    }

    TEST(CAMERAMVS, CAMERA_CONNECT) {
        //使用前初始化SDK也即相机模块
        rw::hoec::Camera_MVSToBeRefactor::initSDK();

        //获取相机IP列表
        auto ipList = Camera_MVSToBeRefactor::getCameraIpList();
        //创建相机对象
        std::vector<std::shared_ptr<Camera_MVSToBeRefactor>> cameraist;
        if (!ipList.size()) {
            std::cout << "No camera found" << std::endl;
            EXPECT_EQ(true,true);
            return;
        }
        for (const auto & item:ipList) {
            auto camera = std::make_shared<Camera_MVSToBeRefactor>();
            camera->setIP(item);
            cameraist.push_back(std::move(camera));
        }
        for (auto& item : cameraist) {
            //连接相机
            EXPECT_EQ(item->connectCamera(), true);
        }
        //...其他操作
        //使用相机后释放SDK

        Camera_MVSToBeRefactor::uninitSDK();
    }

    TEST(CAMERAMVS, monitor) {
        //使用前初始化SDK也即相机模块
        rw::hoec::Camera_MVSToBeRefactor::initSDK();
        //获取相机IP列表
        auto ipList = Camera_MVSToBeRefactor::getCameraIpList();
        //创建相机对象
        std::vector<std::shared_ptr<Camera_MVSToBeRefactor>> cameraist;
        if (!ipList.size()) {
            std::cout << "No camera found" << std::endl;
            EXPECT_EQ(true, true);
            return;
        }
        for (const auto& item : ipList) {
            auto camera = std::make_shared<Camera_MVSToBeRefactor>();
            camera->setIP(item);
            cameraist.push_back(std::move(camera));
        }
        for (auto& item : cameraist) {
            //连接相机
            EXPECT_EQ(item->connectCamera(), true);
            //开始监控
            EXPECT_EQ(item->startMonitor(), true);

            bool isget = false;
            auto image=item->getImage(isget);
            EXPECT_EQ(!isget, image.empty());
            //停止监控
            EXPECT_EQ(item->stopMonitor(), true);
        }
        //...其他操作
        //使用相机后释放SDK
        Camera_MVSToBeRefactor::uninitSDK();
    
    }
}