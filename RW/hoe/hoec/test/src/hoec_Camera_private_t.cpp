#include"hoec_Camera_private_t.h"



namespace hoec_Camera_MVS {
    TEST(CAMERA_MVS,INIADNDEC_SDC) {
        EXPECT_EQ(Camera_MVS::initSDK(), true);
        EXPECT_EQ(Camera_MVS::isIniSDK,true);
        EXPECT_EQ(Camera_MVS::uninitSDK(), true);
        EXPECT_EQ(Camera_MVS::isIniSDK, false);
    }

    TEST(CAMERA_MVS, GET_IP_LIST) {
        std::cout << Camera_MVS::getCameraIpList().size()<<std::endl;
        for (size_t i = 0; i < Camera_MVS::getCameraIpList().size(); i++)
        {
            std::cout << Camera_MVS::getCameraIpList()[i] << std::endl;
        }
    }

    TEST(CAMERA_MVS, GET_INFO_LIST) {
        std::cout << Camera_MVS::getCameraInfoList().size()<<std::endl;
        for (size_t i = 0; i < Camera_MVS::getCameraInfoList().size(); i++)
        {
            std::cout << Camera_MVS::getCameraInfoList()[i].ip << std::endl;
            std::cout << Camera_MVS::getCameraInfoList()[i].name << std::endl;
            std::cout << Camera_MVS::getCameraInfoList()[i].mac << std::endl;
        }
    }

    TEST(CAMERAMVS, CAMERA_ip) {
        rw::hoec::Camera_MVS camera;
        camera.setIP("1");
        EXPECT_EQ(camera.getIP(), "1");
    }

    TEST(CAMERAMVS, CAMERA_CONNECT) {
        Camera_MVS::initSDK();

        auto ipList = Camera_MVS::getCameraIpList();
        std::vector<std::shared_ptr<Camera_MVS>> cameraist;
        if (!ipList.size()) {
            std::cout << "No camera found" << std::endl;
            EXPECT_EQ(true,true);
            return;
        }
        for (const auto & item:ipList) {
            auto camera = std::make_shared<Camera_MVS>();
            camera->setIP(item);
            cameraist.push_back(std::move(camera));
        }
        for (auto& item : cameraist) {
            EXPECT_EQ(item->connectCamera(), true);
        }

        Camera_MVS::uninitSDK();
    }
}