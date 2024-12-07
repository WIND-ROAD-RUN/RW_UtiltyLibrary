#include"hoec_Camera_private_t.h"

#include"opencv2/opencv.hpp"

namespace hoec_Camera_MVS {
    //TEST(CAMERA_MVS,INIADNDEC_SDC) {
    //    EXPECT_EQ(Camera_MVS::initSDK(), true);
    //    EXPECT_EQ(Camera_MVS::isIniSDK,true);
    //    EXPECT_EQ(Camera_MVS::uninitSDK(), true);
    //    EXPECT_EQ(Camera_MVS::isIniSDK, false);
    //}

    //TEST(CAMERA_MVS, GET_IP_LIST) {
    //    std::cout << Camera_MVS::getCameraIpList().size()<<std::endl;
    //    for (size_t i = 0; i < Camera_MVS::getCameraIpList().size(); i++)
    //    {
    //        std::cout << Camera_MVS::getCameraIpList()[i] << std::endl;
    //    }
    //}

    //TEST(CAMERA_MVS, GET_INFO_LIST) {
    //    std::cout << Camera_MVS::getCameraInfoList().size()<<std::endl;
    //    for (size_t i = 0; i < Camera_MVS::getCameraInfoList().size(); i++)
    //    {
    //        std::cout << Camera_MVS::getCameraInfoList()[i].ip << std::endl;
    //        std::cout << Camera_MVS::getCameraInfoList()[i].name << std::endl;
    //        std::cout << Camera_MVS::getCameraInfoList()[i].mac << std::endl;
    //    }
    //}

    //TEST(CAMERAMVS, CAMERA_ip) {
    //    rw::hoec::Camera_MVS camera;
    //    camera.setIP("1");
    //    EXPECT_EQ(camera.getIP(), "1");
    //}

    //TEST(CAMERAMVS, CAMERA_CONNECT) {
    //    //使用前初始化SDK也即相机模块
    //    rw::hoec::Camera_MVS::initSDK();

    //    //获取相机IP列表
    //    auto ipList = Camera_MVS::getCameraIpList();
    //    //创建相机对象
    //    std::vector<std::shared_ptr<Camera_MVS>> cameraist;
    //    if (!ipList.size()) {
    //        std::cout << "No camera found" << std::endl;
    //        EXPECT_EQ(true,true);
    //        return;
    //    }
    //    for (const auto & item:ipList) {
    //        auto camera = std::make_shared<Camera_MVS>();
    //        camera->setIP(item);
    //        cameraist.push_back(std::move(camera));
    //    }
    //    for (auto& item : cameraist) {
    //        //连接相机
    //        EXPECT_EQ(item->connectCamera(), true);
    //    }
    //    //...其他操作
    //    //使用相机后释放SDK

    //    Camera_MVS::uninitSDK();
    //}


    TEST(opencv_, demo) {
        cv::Mat img = cv::imread(R"(C:\Users\34615\Desktop\test.png)");
        if (img.empty()) {
            std::cerr << "无法读取图像文件" << std::endl;
        }
        cv::imshow("image", img);
        cv::waitKey(0);

        cv::Mat gray;
        cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
        cv::imshow("gray", gray);
        cv::waitKey(0);

        cv::Mat edge;
        cv::Canny(gray, edge, 100, 200);
        cv::imshow("edge", edge);
        cv::waitKey(0);

        cv::Mat blur;
        cv::GaussianBlur(img, blur, cv::Size(5, 5), 0);
        cv::imshow("blur", blur);
        cv::waitKey(0);

        cv::destroyAllWindows();

    }
}