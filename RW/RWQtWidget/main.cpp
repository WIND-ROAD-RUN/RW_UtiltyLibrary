#include <QApplication>
#include <QPushButton>
#include <QMessageBox>
#include<QDialog>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QDialog dialog;
    dialog.setWindowTitle("Hello, world!");
    dialog.exec();

    return app.exec();
}