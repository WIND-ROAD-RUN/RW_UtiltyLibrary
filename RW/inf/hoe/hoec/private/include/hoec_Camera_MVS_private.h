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
        class Camera_MVS {
        public:
            Camera_MVS();
            virtual ~Camera_MVS();
        public:
            static bool _isIniSDK;
            static std::vector<std::string> getCameraIpList();
            static std::vector<CameraInfo> getCameraInfoList();
            static bool initSDK();
            static bool uninitSDK();
        public:
            void setIP(const std::string& ip);
            std::string getIP() const;
        public:
            bool connectCamera();
        public:
            bool startMonitor();
            bool stopMonitor();
        public:
            CameraInfo getCameraInfo() const;
            void setCameraInfo(const CameraInfo& cameraInfo);
        public:
            bool setExposureTime(size_t value);
            bool setGain(size_t value);
            bool setIOTime(size_t value);
            bool setTriggerMode(CameraTrrigerMode mode);
            bool setTriggerLine(size_t lineIndex);
        public:
            size_t getExposureTime();
            size_t getGain();
            size_t getIOTime();
            CameraTrrigerMode getMonitorMode();
            size_t getTriggerLine();
            void* getCameraHandle() const;
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
            :public Camera_MVS {
        public:
            Camera_MVS_Active();
            ~Camera_MVS_Active();
        public:
            cv::Mat getImage(bool& isget);
       
        };

        class Camera_MVS_Passive
            :public Camera_MVS {
        public:
            using UserToCallBack = std::function<void(cv::Mat)>;
        private:
            UserToCallBack _userToCallBack;
        public:
            Camera_MVS_Passive(UserToCallBack userToCallback = [](cv::Mat mat) {
                std::cout << "No callback function" << std::endl;
                return;
                });
            ~Camera_MVS_Passive();
        public:
            bool RegisterCallBack();
        public:

            static void __stdcall ImageCallBackFunc(unsigned char* pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser);
        };

    } // namespace hoec

} // namespace rw


#endif // !HOEC_CAMERA_MVS_PRIVATE_H_
