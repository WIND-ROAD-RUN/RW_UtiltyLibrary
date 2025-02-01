#include"hoec_Camera_MVS_private_t.h"

#include"opencv2/opencv.hpp"

namespace hoec_Camera_MVS {
	TEST(Camera_MVS_Test, INIADNDEC_SDC) {
		EXPECT_EQ(Camera_MVS::initSDK(), true);
		EXPECT_EQ(Camera_MVS::_isIniSDK, true);
		EXPECT_EQ(Camera_MVS::unInitSDK(), true);
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

	TEST(Camera_MVS_Test, camera_connect) {
		rw::hoec::Camera_MVS::initSDK();

		auto ipList = Camera_MVS::getCameraIpList();

		//创建相机列表
		std::vector<std::shared_ptr<Camera_MVS>> cameraList;
		if (!cameraList.size()) {
			std::cout << "No camera found" << std::endl;
			EXPECT_EQ(true, true);
			return;
		}
		for (const auto& item : ipList) {
			auto camera = std::make_shared<Camera_MVS>();
			camera->setIP(item);
			cameraList.push_back(camera);
		}
		for (auto& item : cameraList) {
			EXPECT_EQ(item->connectCamera(), true);
		}
		cameraList.clear();
		Camera_MVS::unInitSDK();
	}

	/**
	 * @brief Test the function setExposureTime in class Camera_MVS can sucessfully set the camera's exposuretime
	 *
	 * @details
	 * Test Steps:
	 * 1. Initialize the camera and the relevant resource
	 * 2. Connect each camera and set the exposuretime
	 * 3. Return expected result and exposuretime is set successfully to the camera
	 *
	 * Expected Result:
	 * 1. Return true when the exposuretime is set successfully and return false in other case
	 * 2. The camera is set the given exposuretime and the images shot by it are in the exposuretime
	 * 3. Run successfully
	 *
	 * Boundary Conditions:
	 * 1. The value of exposuretime cannot be negative number and it has the minninum and maxnum
	 */
	TEST(Camera_MVS_Test, setExposureTime_isSetSuccessfully) {
		rw::hoec::Camera_MVS::initSDK();

		//获取相机IP列表
		auto ipList = Camera_MVS::getCameraIpList();

		//创建相机对象
		std::vector<std::shared_ptr<Camera_MVS_Active>> cameraList;
		if (!ipList.size()) {
			std::cout << "No camera found" << std::endl;
			EXPECT_EQ(true, true);
			return;
		}
		for (const auto& item : ipList) {
			auto camera = std::make_shared<Camera_MVS_Active>();
			camera->setIP(item);
			cameraList.push_back(std::move(camera));
		}
		bool isfirst{ true };
		for (auto& item : cameraList) {
			//连接相机
			EXPECT_EQ(item->connectCamera(), true);
			EXPECT_EQ(item->setTriggerMode(::CameraTrrigerMode::SoftwareTriggered), true);
			if (isfirst) {
				EXPECT_EQ(item->setExposureTime(20000), true);
				isfirst = false;
			}
			else {
				EXPECT_EQ(item->setExposureTime(2000), true);
				isfirst = true;
			}
			item->startMonitor();
			bool isGet{};
			auto image = item->getImage(isGet);

			ASSERT_EQ(isGet, true);
			//cv::imshow("image", image);
			//cv::waitKey(0);
			item->stopMonitor();
		}
		cameraList.clear();
		Camera_MVS::unInitSDK();
	}

	TEST(Camera_MVS_Test, setGain_isSetSuccessfully) {
		rw::hoec::Camera_MVS::initSDK();

		//获取相机IP列表
		auto ipList = Camera_MVS::getCameraIpList();

		//创建相机对象
		std::vector<std::shared_ptr<Camera_MVS_Active>> cameraList;
		if (!ipList.size()) {
			std::cout << "No camera found" << std::endl;
			EXPECT_EQ(true, true);
			return;
		}
		for (const auto& item : ipList) {
			auto camera = std::make_shared<Camera_MVS_Active>();
			camera->setIP(item);
			cameraList.push_back(std::move(camera));
		}
		bool isfirst{ true };
		for (auto& item : cameraList) {
			//连接相机
			EXPECT_EQ(item->connectCamera(), true);
			EXPECT_EQ(item->setTriggerMode(CameraTrrigerMode::SoftwareTriggered), true);
			if (isfirst) {
				EXPECT_EQ(item->setExposureTime(20000), true);
				EXPECT_EQ(item->setGain(15), true);
				isfirst = false;
			}
			else {
     				EXPECT_EQ(item->setExposureTime(40000), true);
				EXPECT_EQ(item->setGain(15), true);
				isfirst = true;
			}
			item->startMonitor();
			bool isGet{false};
			auto image = item->getImage(isGet);

			ASSERT_EQ(isGet, true);
			//cv::imshow("image", image);
			//cv::waitKey(0);
			item->stopMonitor();
		}
		cameraList.clear();
		Camera_MVS::unInitSDK();
	}

	TEST(Camera_MVS_Test, getExposureTime) {
		rw::hoec::Camera_MVS::initSDK();

		auto ipList = Camera_MVS::getCameraIpList();

		std::vector<std::shared_ptr<Camera_MVS>> cameraList;
		if (!cameraList.size()) {
			std::cout << "No camera found" << std::endl;
			EXPECT_EQ(true, true);
			return;
		}
		for (auto& item : ipList) {
			auto camera = std::make_shared<Camera_MVS>();
			camera->setIP(item);
			cameraList.push_back(camera);
		}
		for (auto& item : cameraList) {
			EXPECT_EQ(item->connectCamera(), true);
			EXPECT_EQ(item->setExposureTime(2000), true);
			EXPECT_EQ(item->getExposureTime(), 2000);
		}
		cameraList.clear();
		Camera_MVS::unInitSDK();
	}

	TEST(Camera_MVS_Test, getGain) {
		rw::hoec::Camera_MVS::initSDK();

		auto ipList = Camera_MVS::getCameraIpList();

		std::vector<std::shared_ptr<Camera_MVS_Active>> cameraList;
		if (!cameraList.size()) {
			std::cout << "No camera found" << std::endl;
			EXPECT_EQ(true, true);
			return;
		}
		for (auto& item : ipList) {
			auto camera = std::make_shared<Camera_MVS_Active>();
			camera->setIP(item);
			cameraList.push_back(camera);
		}
		for (auto& item : cameraList) {
			EXPECT_EQ(item->connectCamera(), true);
			EXPECT_EQ(item->setGain(200), true);
			EXPECT_EQ(item->getGain(), 200);
		}
		cameraList.clear();
		Camera_MVS::unInitSDK();
	}

	TEST(Camera_MVS_Test, setSoftwareTriggerMode) {
		rw::hoec::Camera_MVS::initSDK();

		auto ipList = Camera_MVS::getCameraIpList();

		std::vector<std::shared_ptr<Camera_MVS_Active >> cameraList;
		if (!ipList.size()) {
			std::cout << "No camera found" << std::endl;
			EXPECT_EQ(true, true);
			return;
		}
		for (auto& item : ipList) {
			auto camera = std::make_shared<Camera_MVS_Active>();
			camera->setIP(item);
			cameraList.push_back(camera);
		}
		for (auto& item : cameraList) {
			EXPECT_EQ(item->connectCamera(), true);
			EXPECT_EQ(item->setTriggerMode(CameraTrrigerMode::SoftwareTriggered), true);
		}
		cameraList.clear();
		Camera_MVS::unInitSDK();
	}

	TEST(Camera_MVS_Test, setHardwareTriggerMode) {
		rw::hoec::Camera_MVS::initSDK();

		auto ipList = Camera_MVS::getCameraIpList();

		std::vector<std::shared_ptr<Camera_MVS_Active >> cameraList;
		if (!ipList.size()) {
			std::cout << "No camera found" << std::endl;
			EXPECT_EQ(true, true);
			return;
		}
		for (auto& item : ipList) {
			auto camera = std::make_shared<Camera_MVS_Active>();
			camera->setIP(item);
			cameraList.push_back(camera);
		}
		for (auto& item : cameraList) {
			EXPECT_EQ(item->connectCamera(), true);
			EXPECT_EQ(item->setTriggerMode(CameraTrrigerMode::HardwareTriggered), true);
		}
		cameraList.clear();
		Camera_MVS::unInitSDK();
	}

	TEST(Camera_MVS_Test, setSoftwareTriggerMode_isSuccessfully) {
		int status = 0;
		rw::hoec::Camera_MVS::initSDK();

		auto ipList = Camera_MVS::getCameraIpList();

		std::vector<std::shared_ptr<Camera_MVS_Passive>>cameraList;
		if (!ipList.size()) {
			std::cout << "No camera found" << std::endl;
			EXPECT_EQ(true, true);
			return;
		}
		for (const auto& item : ipList) {
			auto camera = std::make_shared<Camera_MVS_Passive>([&status](cv::Mat a) {
				std::cout << "We have gotten a image" << std::endl;
				status = 1;
				});
			camera->setIP(item);
			cameraList.push_back(std::move(camera));
		}
		for (auto& item : cameraList) {
			//连接相机
			EXPECT_EQ(item->connectCamera(), true);
			EXPECT_EQ(item->setTriggerMode(CameraTrrigerMode::SoftwareTriggered), true);
			//注册回调函数
			auto registerResult = item->RegisterCallBackFunc();
			EXPECT_EQ(registerResult, true);
			//开始监控
			EXPECT_EQ(item->startMonitor(), true);

			for (int i = 0; i < 500; i++) {
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
				//wait for callback
			}
			EXPECT_EQ(status, 1);

			status = 0;

			//停止监控
			EXPECT_EQ(item->stopMonitor(), true);
		}
		cameraList.clear();
		Camera_MVS::unInitSDK();
	}

	TEST(Camera_MVS_Test,my_SetHardwareTriggerMode)
	{
		int status = 0;
		std::mutex mtx;
		std::condition_variable cv;
		bool callback_called = false;

		rw::hoec::Camera_MVS::initSDK();

		auto ipList = Camera_MVS::getCameraIpList();

		std::vector<std::shared_ptr<Camera_MVS_Passive>> cameraList;
		if (ipList.empty()) {
			std::cout << "No camera found" << std::endl;
			EXPECT_EQ(true, true);
			return;
		}

		for (const auto& item : ipList) {
			auto camera = std::make_shared<Camera_MVS_Passive>([&status, &cv, &mtx, &callback_called](cv::Mat a) {
				std::cout << "We have gotten an image" << std::endl;
				status = 1;
				{
					std::lock_guard<std::mutex> lock(mtx);
					callback_called = true;
				}
				cv.notify_one();
				});
			camera->setIP(item);
			cameraList.push_back(std::move(camera));
		}

		for (auto& item : cameraList) {
			EXPECT_EQ(item->connectCamera(), true);
			EXPECT_EQ(item->setTriggerMode(CameraTrrigerMode::HardwareTriggered), true);
			auto registerResult = item->RegisterCallBackFunc();
			EXPECT_EQ(registerResult, true);
			EXPECT_EQ(item->startMonitor(), true);

			std::unique_lock<std::mutex> lock(mtx);
			cv.wait_for(lock, std::chrono::seconds(5), [&callback_called]() { return callback_called; });
			EXPECT_EQ(status, 1);

			callback_called = false;
			status = 0;

			EXPECT_EQ(item->stopMonitor(), true);
		}

		cameraList.clear();
		Camera_MVS::unInitSDK();
	}

	TEST(Camera_MVS_Test, setHardwareTriggerMode_isSuccessfully)
	{
		int status = 0;
		rw::hoec::Camera_MVS::initSDK();

		auto ipList = Camera_MVS::getCameraIpList();

		std::vector<std::shared_ptr<Camera_MVS_Passive>>cameraList;
		if (!ipList.size()) {
			std::cout << "No camera found" << std::endl;
			EXPECT_EQ(true, true);
			return;
		}
		for (const auto& item : ipList) {
			auto camera = std::make_shared<Camera_MVS_Passive>([&status](cv::Mat a) {
				std::cout << "We have gotten a image" << std::endl;
				status = 1;
				});
			camera->setIP(item);
			cameraList.push_back(std::move(camera));
		}
		for (auto& item : cameraList) {
			//连接相机
			EXPECT_EQ(item->connectCamera(), true);
			EXPECT_EQ(item->setTriggerMode(CameraTrrigerMode::HardwareTriggered), true);
			//注册回调函数
			auto registerResult = item->RegisterCallBackFunc();
			EXPECT_EQ(registerResult, true);
			//开始监控
			EXPECT_EQ(item->startMonitor(), true);

			for (int i = 0; i < 500; i++) {
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
				//wait for callback
			}
			EXPECT_EQ(status, 1);

			status = 0;

			//停止监控
			EXPECT_EQ(item->stopMonitor(), true);
		}
		cameraList.clear();
		Camera_MVS::unInitSDK();
	}

	TEST(Camera_MVS_Test, getSoftwareTriggerMode) {
		rw::hoec::Camera_MVS::initSDK();

		auto ipList = Camera_MVS::getCameraIpList();

		std::vector<std::shared_ptr<Camera_MVS_Active >> cameraList;
		if (!ipList.size()) {
			std::cout << "No camera found" << std::endl;
			EXPECT_EQ(true, true);
			return;
		}
		for (auto& item : ipList) {
			auto camera = std::make_shared<Camera_MVS_Active>();
			camera->setIP(item);
			cameraList.push_back(camera);
		}
		for (auto& item : cameraList) {
			EXPECT_EQ(item->connectCamera(), true);
			EXPECT_EQ(item->setTriggerMode(CameraTrrigerMode::SoftwareTriggered), true);
			EXPECT_EQ(item->getMonitorMode(), CameraTrrigerMode::SoftwareTriggered);
		}
		cameraList.clear();
		Camera_MVS::unInitSDK();
	}

	TEST(Camera_MVS_Test, getHardwareTriggerMode)
	{
		rw::hoec::Camera_MVS::initSDK();
		auto ipList = Camera_MVS::getCameraIpList();

		std::vector<std::shared_ptr<Camera_MVS_Active >> cameraList;
		if (!ipList.size()) {
			std::cout << "No camera found" << std::endl;
			EXPECT_EQ(true, true);
			return;
		}
		for (auto& item : ipList) {
			auto camera = std::make_shared<Camera_MVS_Active>();
			camera->setIP(item);
			cameraList.push_back(camera);
		}
		for (auto& item : cameraList) {
			EXPECT_EQ(item->connectCamera(), true);
			EXPECT_EQ(item->setTriggerMode(CameraTrrigerMode::HardwareTriggered), true);
			EXPECT_EQ(item->getMonitorMode(), CameraTrrigerMode::HardwareTriggered);
		}
		cameraList.clear();
		Camera_MVS::unInitSDK();
	}

	TEST(Camera_MVS_Test, setTriggerLine) {
		rw::hoec::Camera_MVS::initSDK();

		auto ipList = Camera_MVS::getCameraIpList();

		std::vector<std::shared_ptr<Camera_MVS_Active >> cameraList;
		if (!ipList.size()) {
			std::cout << "No camera found" << std::endl;
			EXPECT_EQ(true, true);
			return;
		}
		for (auto& item : ipList) {
			auto camera = std::make_shared<Camera_MVS_Active>();
			camera->setIP(item);
			cameraList.push_back(camera);
		}
		//bool issecond{ false };
		for (auto& item : cameraList) {
			EXPECT_EQ(item->connectCamera(), true);
			EXPECT_EQ(item->setTriggerLine(0), true);
		}
		cameraList.clear();
		Camera_MVS::unInitSDK();
	}

	TEST(Camera_MVS_Test, getTriggerLine)
	{
		rw::hoec::Camera_MVS::initSDK();

		auto ipList = Camera_MVS::getCameraIpList();

		std::vector<std::shared_ptr<Camera_MVS_Active >> cameraList;
		if (!ipList.size()) {
			std::cout << "No camera found" << std::endl;
			EXPECT_EQ(true, true);
			return;
		}
		for (auto& item : ipList) {
			auto camera = std::make_shared<Camera_MVS_Active>();
			camera->setIP(item);
			cameraList.push_back(camera);
		}
		//bool issecond{ false };
		for (auto& item : cameraList) {
			EXPECT_EQ(item->connectCamera(), true);
			EXPECT_EQ(item->setTriggerLine(0), true);
			EXPECT_EQ(item->getTriggerLine(), 0);
		}
		cameraList.clear();
		Camera_MVS::unInitSDK();
	}

	TEST(Camera_MVS_Active_Test, CAMERA_CONNECT) {
		//使用前初始化SDK也即相机模块
		rw::hoec::Camera_MVS_Active::initSDK();

		//获取相机IP列表
		auto ipList = Camera_MVS_Active::getCameraIpList();
		//创建相机对象
		std::vector<std::shared_ptr<Camera_MVS_Active>> cameraList;
		if (!ipList.size()) {
			std::cout << "No camera found" << std::endl;
			EXPECT_EQ(true, true);
			return;
		}
		for (const auto& item : ipList) {
			auto camera = std::make_shared<Camera_MVS_Active>();
			camera->setIP(item);
			cameraList.push_back(std::move(camera));
		}
		for (auto& item : cameraList) {
			//连接相机
			EXPECT_EQ(item->connectCamera(), true);
		}
		cameraList.clear();
		Camera_MVS_Active::unInitSDK();
	}

	TEST(Camera_MVS_Active_Test, monitor) {
		//使用前初始化SDK也即相机模块
		rw::hoec::Camera_MVS_Active::initSDK();
		//获取相机IP列表
		auto ipList = Camera_MVS_Active::getCameraIpList();
		//创建相机对象
		std::vector<std::shared_ptr<Camera_MVS_Active>> cameraList;
		if (!ipList.size()) {
			std::cout << "No camera found" << std::endl;
			EXPECT_EQ(true, true);
			return;
		}
		for (const auto& item : ipList) {
			auto camera = std::make_shared<Camera_MVS_Active>();
			camera->setIP(item);
			cameraList.push_back(std::move(camera));
		}
		for (auto& item : cameraList) {
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
		cameraList.clear();
		Camera_MVS_Active::unInitSDK();

	}

	TEST(Camera_MVS_Passive_Test, registerUserCallBack) {
		int status = 0;
		//使用前初始化SDK也即相机模块
		rw::hoec::Camera_MVS_Passive::initSDK();
		//获取相机IP列表
		auto ipList = Camera_MVS_Passive::getCameraIpList();
		//创建相机对象
		std::vector<std::shared_ptr<Camera_MVS_Passive>> cameraList;
		if (!ipList.size()) {
			std::cout << "No camera found" << std::endl;
			EXPECT_EQ(true, true);
			return;
		}
		for (const auto& item : ipList) {
			auto camera = std::make_shared<Camera_MVS_Passive>([&status](cv::Mat a) {
				std::cout << "999999" << std::endl;
				status = 1;
				});
			camera->setIP(item);
			cameraList.push_back(std::move(camera));
		}
		for (auto& item : cameraList) {
			//连接相机
			EXPECT_EQ(item->connectCamera(), true);
			EXPECT_EQ(item->setTriggerMode(CameraTrrigerMode::SoftwareTriggered), true);
			//注册回调函数
			auto registerResult = item->RegisterCallBackFunc();
			EXPECT_EQ(registerResult, true);
			//开始监控
			EXPECT_EQ(item->startMonitor(), true);

			for (int i = 0; i < 500; i++) {
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
		cameraList.clear();
		Camera_MVS_Passive::unInitSDK();
	}
}