#include <QApplication>
#include <QDir>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QCoreApplication::addLibraryPath(QCoreApplication::applicationDirPath() + "/plugins");
    // 其他代码
    return app.exec();
}
