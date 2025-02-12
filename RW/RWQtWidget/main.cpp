#include <QApplication>
#include <QPushButton>
#include <QMessageBox>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // 创建一个按钮
    QPushButton button("Click Me");
    button.resize(200, 100);

    // 连接按钮的点击信号到一个槽函数
    QObject::connect(&button, &QPushButton::clicked, [&]() {
        QMessageBox::information(nullptr, "Message", "Button Clicked!");
        });

    // 显示按钮
    button.show();

    return app.exec();
}