#ifndef HOEC_CAMERA_MVS_PRIVATE_H_
#define HOEC_CAMERA_MVS_PRIVATE_H_

#include"opencv2/opencv.hpp"

#include"hoec_Camera.h"

#include<vector>
#include<string>
#include<functional>

struct _MV_FRAME_OUT_INFO_EX_;
typedef struct _MV_FRAME_OUT_INFO_EX_ MV_FRAME_OUT_INFO_EX;

namespace rw {
    namespace hoec {
        class Camera_MVS:
            public ICamera {
        public:
            Camera_MVS();
            ~Camera_MVS() override;
        public:
            static bool _isIniSDK;
            static std::vector<std::string> getCameraIpList();
            static std::vector<CameraInfo> getCameraInfoList();
            static bool initSDK();
            static bool unInitSDK();
        public:
            bool connectCamera() override;
        public:
            bool startMonitor() override;
            bool stopMonitor() override;
        public:
            bool setExposureTime(size_t value) override;
            bool setGain(size_t value) override;
            bool setIOTime(size_t value) override;
            bool setTriggerMode(CameraTrrigerMode mode) override;
            bool setTriggerLine(size_t lineIndex) override;
        public:
            size_t getExposureTime() override;
            size_t getGain() override;
            size_t getIOTime() override;
            CameraTrrigerMode getMonitorMode() override;
            size_t getTriggerLine() override;
        private:
            std::string m_ip;
            CameraInfo m_cameraInfo;
        protected:
            void* m_cameraHandle{ nullptr };
        private:
            bool _isMonitor{ false };
            CameraTrrigerMode triggerMode;
        };

        class Camera_MVS_Active
            :public Camera_MVS,public ICameraActive {
        public:
            Camera_MVS_Active();
            ~Camera_MVS_Active() override;
        public:
            cv::Mat getImage(bool& isGet) override;
            cv::Mat getImage() override;
        };

        class Camera_MVS_Passive
            :public Camera_MVS,public ICameraPassive{
        public:
            using UserToCallBack = std::function<void(cv::Mat)>;
        private:
            UserToCallBack _userToCallBack;
        public:
            Camera_MVS_Passive(UserToCallBack userToCallback = [](cv::Mat mat) {
                std::cout << "No callback function" << std::endl;
                return;
                });
            ~Camera_MVS_Passive() override;
        public:
            bool RegisterCallBackFunc() override;
        public:

            static void __stdcall ImageCallBackFunc(unsigned char* pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser);
        };

    } // namespace hoec

} // namespace rw


#endif // !HOEC_CAMERA_MVS_PRIVATE_H_
