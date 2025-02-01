#include <openvino/openvino.hpp>
#include <iostream>

int main() {
    try {
        // 初始化OpenVINO核心对象
        ov::Core core;

        // 获取支持的设备列表
        auto available_devices = core.get_available_devices();

        // 打印支持的设备列表
        std::cout << "Available devices:" << std::endl;
        for (const auto& device : available_devices) {
            std::cout << "  " << device << std::endl;
        }
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}