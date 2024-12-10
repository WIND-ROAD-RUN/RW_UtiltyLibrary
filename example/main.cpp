#include<QImage>
#include<QWidget>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QMainWindow>
#include <iostream>
#include <vector>
#include <QPixmap>
#include <QTimer>
#include <QVBoxLayout>
#include "hoec_Camera_MVS_private.h"

using namespace rw::hoec;

//class MainWindow :public QMainWindow {
//	Q_OBJECT
//public:
//	MainWindow(QWidget *parent = nullptr);
//	~MainWindow();
//private:
//	QLabel* label;
//	QPushButton* btnOK;
//	QTimer* timer;
//	std::vector<std::shared_ptr<Camera_MVS_Active>> cameraList;
//	std::shared_ptr<Camera_MVS_Active> mycamera;
//private slots:
//	void disp();
//	void start();
//	void stop();
//};
//
//MainWindow::MainWindow(QWidget* parent ) {
//	btnOK = new QPushButton("开始采集",this);
//	label = new QLabel(this);
//	QVBoxLayout* layout = new QVBoxLayout;
//
//	layout->addWidget(btnOK);
//	layout->addWidget(label);
//
//	// 创建中心 widget 并设置其布局
//	QWidget* centralWidget = new QWidget(this);
//	centralWidget->setLayout(layout);
//	setCentralWidget(centralWidget);
//	
//	Camera_MVS::initSDK();
//	auto ipList = Camera_MVS::getCameraIpList();
//	if (!ipList.size()) {
//		std::cout << "No camera found" << std::endl;
//	}
//	for (auto item : ipList) {
//		auto camera = std::make_shared<Camera_MVS_Active>();
//		camera->setIP(item);
//		cameraList.push_back(camera);
//	}
//	mycamera = cameraList[0];
//	auto result = mycamera->connectCamera();
//	if (!result) {
//		std::cout << "Failed to connect the camera" << std::endl;
//	}
//	mycamera->setTriggerMode(CameraTrrigerMode::TriggerMode_OFF);
//	mycamera->setExposureTime(10000);
//	mycamera->setGain(20);
//
//	timer = new QTimer(this);
//
//	connect(btnOK, &QPushButton::clicked, this, &MainWindow::start);
//	
//	//camera->stopMonitor();
//}
//
////static bool isstart{ false };
//
//void MainWindow::disp() {
//		bool isGet{ false };
//		auto image = mycamera->getImage(isGet);
//		if (isGet) {
//			QImage disImage = QImage(image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
//			label->setPixmap(QPixmap::fromImage(disImage));
//		}
//		else {
//			std::cout << "Failed to get image" << std::endl;
//		}
//}
//
//void MainWindow::start()
//{
//	timer->start(10);
//	mycamera->startMonitor();
//	btnOK->setText("停止采集");
//	connect(timer,&QTimer::timeout, this, &MainWindow::disp);
//	connect(btnOK, &QPushButton::clicked, this, &MainWindow::stop);
//}
//
//void MainWindow::stop()
//{
//	timer->stop();
//	mycamera->stopMonitor();
//	btnOK->setText("开始采集");
//	disconnect(timer, &QTimer::timeout, this, &MainWindow::disp);
//	connect(btnOK, &QPushButton::clicked, this, &MainWindow::start);
//}
//
//MainWindow::~MainWindow() {
//	Camera_MVS::uninitSDK();
//}

class MainWindow :public QMainWindow {
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private:
	QLabel* label;
	QPushButton* btnOK;
	std::vector<std::shared_ptr<Camera_MVS_Passive>> cameraList;
	std::shared_ptr<Camera_MVS_Passive> mycamera;
};

MainWindow::MainWindow(QWidget *parent) {
	label = new QLabel(this);
	btnOK = new QPushButton("开始采集", this);
	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(label);
	layout->addWidget(btnOK);

	QWidget* centralwidget = new QWidget(this);
	centralwidget->setLayout(layout);
	setCentralWidget(centralwidget);

	Camera_MVS::initSDK();
	auto ipList = Camera_MVS_Active::getCameraIpList();
	if (!ipList.size()) {
		std::cout << "No camera found" << std::endl;
	}
	for (auto item : ipList) {
		auto camera = std::make_shared<Camera_MVS_Passive>([this](cv::Mat a) {
			QImage disImage = QImage(a.data, a.cols, a.rows, a.step, QImage::Format_RGB888);
			label->setPixmap(QPixmap::fromImage(disImage));
			});
		camera->setIP(item);
		cameraList.push_back(camera);
	}
	mycamera = cameraList[0];
	auto result = mycamera->connectCamera();
	if (!result) {
		std::cout << "Failed to connect camera" << std::endl;
	} 
	mycamera->setTriggerMode(CameraTrrigerMode::TriggerMode_OFF);
	mycamera->setExposureTime(20000);
	mycamera->setGain(20);
	
	result = mycamera->RegisterCallBack();
	if (!result) {
		std::cout << "Failed to register image callback" << std::endl;
	}
	 
	mycamera->startMonitor();


}

MainWindow::~MainWindow() {}

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	MainWindow m;
	m.resize(500, 500);
	m.show();

	return a.exec();
}


#include "main.moc"
