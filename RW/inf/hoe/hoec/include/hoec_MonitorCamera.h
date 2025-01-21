// #ifndef MONITORCAMERA_H_
// #define MONITORCAMERA_H_

// struct MonitorCameraUtility
// {
//     static std::vector<std::string> checkAllConnectCamera();
// };

// class MonitorCamera : public QObject
// {
//     Q_OBJECT

// private:
//     std::string m_ip{};
//     void *m_handle{nullptr}; // Camera handle

// public:
//     MonitorCamera();

//     ~MonitorCamera();

//     void setIp(const std::string &ip) { m_ip = ip; }

//     std::string getIp() { return m_ip; }

//     bool connectCamera();

//     void startAcquisition();

//     void stopAcquisition();

//     bool setExposureTime(int exposureTime);

//     bool setGain(int gain);

//     bool setHardwareTriggeredAcquisition();

//     bool setSoftwareTriggeredAcquisition();

//     int setIOStart(int time);

// signals:
//     void ImgCallBackSignal(unsigned char *pData, MV_FRAME_OUT_INFO_EX *pFrameInfo);

// private:
//     static void __stdcall ImageCallback(unsigned char *pData, MV_FRAME_OUT_INFO_EX *pFrameInfo, void *pUser);
// };

// #endif // !MONITORCAMERA_H_