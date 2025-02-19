#include <QApplication>
#include <QPushButton>
#include <QMessageBox>
#include<QDialog>

#include"rqw_CameraDisplayLabel.hpp"
#include"rqw_CameraDisplayLabel.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    rw::rqw::CameraDisplayLabel label;
    label.setText("Hello World");
    label.show();


    return app.exec();
}