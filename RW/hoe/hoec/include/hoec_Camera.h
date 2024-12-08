#ifndef HOEC_ICAMERA_H_
#define HOEC_ICAMERA_H_

#include <string>
#include<functional>

namespace cv {
    class Mat;
}
namespace rw
{
    namespace hoec
    {
        struct CameraInfo
        {
            std::string ip;
            std::string name;
            std::string mac;
        };

        

        /**
         * @brief This enum class is used to specify the mode of taking a picture.
         *
         * This enum class is used to specify the mode of taking a picture. The mode is mutually exclusive
         */
        enum class CameraTakePictureMode
        {
            // Take a picture in the active mode.
            // When use this mode, If you want to get a picture, you should call the getImage() function.
            Active,

            // Take a picture in the passive mode.
            // When use this mode, If you want to get a picture, you should register a callback function.
            // When the camera get a picture, the callback function will be called.
            // The callback function has default realization, you can also register your own callback function 
            //when you construct the camera object.
            Passive
        };

        /**
         * @brief This enum class is used to specify the mode of monitoring the camera.
         *
         * This enum class is used to specify the mode of monitoring the camera. The mode is mutually exclusive
         */
        enum class CameraMonitorMode
        {
            // Monitor the camera in the software triggered mode.
            // When use this mode, the camera will be monitored by the software trigger.
            // You can set frame rate or get a picture by calling the getImage() function.
            SoftwareTriggered,

            // Monitor the camera in the hardware triggered mode.
            // When use this mode, the camera will be monitored by the hardware trigger.
            // You can set the trigger line and trigger mode by calling the setTriggerLine() function.
            HardwareTriggered,
        };

        /**
         * @brief This enum class is used to specify the provider of the camera.
         *
         * This enum class is used to specify the provider of the camera. The provider is mutually exclusive
         */
        enum class CameraProvider
        {
            // The camera is provided by the HIKVISION.
            MVS
        };


        /**
         * @brief This class is used to provide the interface of the camera.
         *
         * For different camera providers, you should implement the ICamera interface.
         */
        class ICamera
        {
        public:

            /**
             * @brief Destructor
             *
             * For destructor,you should guarantee that when object is destructed,
             *all hardware resource of the camera should be released.
             */
            virtual ~ICamera() = default;

            /**
             * @brief Constructor
             *
             * For constructor,you should guarantee that when object is constructed,
             *all hardware resource of the camera has been ready such as initialize SDK resource.
             */
            ICamera() = default;


            /**
             * @brief Delete the copy constructor and copy assignment operator.
             *
             * The camera object is entity object,they are global unique,for each camera object, 
             *it take over every hardware resource of the camera.
             */
            ICamera(ICamera&&) = delete;
            ICamera& operator=(ICamera&&) = delete;
            ICamera(const ICamera&) = delete;
            ICamera& operator=(const ICamera&) = delete;
        public:

            /**
             *@Parameters:
             *  - ip: the ip of the camera
             *@Methods:
             *  Set the ip of the camera.
             *@Returns: void
             *
             *@Throws:
             *
             */
            virtual void setIP(const std::string &ip) = 0;

            /**
             *@Parameters:
             *
             *@Methods:
             *  Get the ip of the camera.
             *@Returns: the ip of the camera
             *
             *@Throws:
             *
             */
            virtual std::string getIP() const = 0;

        public:

            /**
             *@Parameters:
             *  void
             *@Methods:
             *  Connect the camera
             *@Returns: types
             *
             *@Throws:
             *
             */
            virtual bool connectCamera() = 0;

        public:
            virtual bool startMonitor() = 0;
            virtual bool stopMonitor() = 0;

        public:
            virtual bool setExposureTime(size_t value) = 0;
            virtual bool setGain(size_t value) = 0;
            virtual bool setMonitorMode(CameraMonitorMode mode) = 0;
            virtual bool setIOTime(size_t value) = 0;
            virtual bool setTriggerLine(size_t lineIndex) = 0;

            virtual size_t getExposureTime()=0;
            virtual size_t getGain()=0;
            virtual size_t getIOTime()=0;
            virtual CameraMonitorMode getMonitorMode()=0;
            virtual size_t getTriggerLine() = 0;

        };

        class ICameraActive
            : public ICamera
        {
        public:
            virtual cv::Mat getImage(bool& isget)=0;
            virtual cv::Mat getImage() = 0;
        };

        class ICameraPassive
            : public ICamera
        {
        public:
            using UserToCallBack = std::function<void(cv::Mat)>;
        public:
            virtual bool RegisterCallBackFunc()=0;

        };

        class Camera
            : public ICamera
        {
            
        };
    }
}

#endif