#include"hoec_core_private.h"

#include"opencv2/opencv.hpp"
#include"MvCameraControl.h"
#include "CameraParams.h" 

namespace rw {
    namespace hoec {
        cv::Mat ImageFrameConvert::MVS_ConvertFrameToMat(const MV_FRAME_OUT& frameInfo)
        {
            // 获取图像宽度和高度
            int width = frameInfo.stFrameInfo.nWidth;
            int height = frameInfo.stFrameInfo.nHeight;

            // 获取图像数据指针
            unsigned char* data = frameInfo.pBufAddr;

            // 根据图像像素格式创建cv::Mat
            cv::Mat image;
            if (frameInfo.stFrameInfo.enPixelType == PixelType_Gvsp_Mono8) {
                // 单通道灰度图像
                image = cv::Mat(height, width, CV_8UC1, data);
            }
            else if (frameInfo.stFrameInfo.enPixelType == PixelType_Gvsp_RGB8_Packed) {
                // 三通道RGB图像
                image = cv::Mat(height, width, CV_8UC3, data);
                // OpenCV默认的颜色顺序是BGR，需要转换为RGB
                cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
            }
            else if (frameInfo.stFrameInfo.enPixelType == PixelType_Gvsp_BayerGB8) {
                // Bayer格式图像
                image = cv::Mat(height, width, CV_8UC1, data);
            }
            else if (frameInfo.stFrameInfo.enPixelType == PixelType_Gvsp_HB_RGB8_Packed) {
                // 三通道RGB图像
                image = cv::Mat(height, width, CV_8UC3, data);
                // OpenCV默认的颜色顺序是BGR，需要转换为RGB
                cv::cvtColor(image, image, cv::COLOR_BGR2RGB);

            }
            else {
                std::cerr << "Unsupported pixel format" << std::endl;
                return cv::Mat();
            }

            return image;
        }
    } // namespace hoec

} // namespace rw
