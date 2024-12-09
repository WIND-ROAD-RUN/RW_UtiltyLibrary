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
             *  Connect the camera,in this call, it whill exclusive the camera resource,and open
             * device. It also initialize the camera resource and get the camera handle.
             *@Returns: bool
             *  If connect the camera successfully, return true,otherwise return false.
             *@Throws:
             *
             */
            virtual bool connectCamera() = 0;

        public:

            /**
             *@Parameters:
             *  void
             *@Methods:
             *  Start the camera monitor, the camera will start to monitor the image.
             *@Returns: bool
             *  If start the camera monitor successfully, return true,otherwise return false.
             *@Throws:
             *
             *@Warning:
             * If you want stop the camera monitor,you can call the stopMonitor() function 
             *or destruct the camera object which will stop the camera monitor automatically.
             */
            virtual bool startMonitor() = 0;

            /**
             *@Parameters:
             *  void
             *@Methods:
             *  Stop the camera monitor, the camera will stop to monitor the image.
             *@Returns: bool
             *  If stop the camera monitor successfully, return true,otherwise return false.
             *@Throws:
             *
             */
            virtual bool stopMonitor() = 0;

        public:

            /**
             *@Parameters:
             *  - value: The value of the exposure time you want to set.
             *@Methods:
             *  Set the exposure time of the camera.
             *@Returns: bool
             *  If set the exposure time successfully, return true,otherwise return false.
             *@Throws:
             *
             *@Warning:
             * For some camera, the exposure time has a range, you should set the value in the range.
             *For this function,we guarantee that when you set the exposure,whatever the value is,if 
             *the value will be agreed,it will return true,otherwise return false.
             */
            virtual bool setExposureTime(size_t value) = 0;

            /**
             *@Parameters:
             *  - value: The value of the gain you want to set.
             *@Methods:
             *  set the gain of the camera.
             *@Returns: bool
             *  If set the gain successfully, return true,otherwise return false.
             *@Throws:
             *
             *@Warning:
             * For some camera, the gain has a range, you should set the value in the range.
             *For this function,we guarantee that when you set the gain,whatever the value is,if
             *the value will be agreed,it will return true,otherwise return false.
             */
            virtual bool setGain(size_t value) = 0;


            /**
             *@Parameters:
             *  - mode: The mode of the camera monitor you want to set.
             *      type: CameraMonitorMode
             *@Methods:
             *  Set the monitor mode of the camera.
             *@Returns: bool
             *  If set the monitor mode successfully, return true,otherwise return false.
             *@Throws:
             *
             */
            virtual bool setMonitorMode(CameraMonitorMode mode) = 0;

            /**
             *@Parameters:
             *  - value: The value of the IO time you want to set.
             *@Methods:
             *  Set the IO time of the camera.
             *@Returns: bool
             *  If set the IO time successfully, return true,otherwise return false.
             *@Throws:
             *
             */
            virtual bool setIOTime(size_t value) = 0;


            /**
             *@Parameters:
             *  - lineIndex: The index of the trigger line you want to set.
             *@Methods:
             *  Set the trigger line of the camera which will be used in the hardware trigger mode.
             *@Returns: bool
             *  If set the trigger line successfully, return true,otherwise return false.
             *@Throws:
             *
             */
            virtual bool setTriggerLine(size_t lineIndex) = 0;


            /**
             *@Parameters:
             *  void
             *@Methods:
             *  Get the exposure time of the camera.
             *@Returns: void
             *
             *@Throws:
             *
             */
            virtual size_t getExposureTime()=0;

            /**
             *@Parameters:
             *  void
             *@Methods:
             *  Get the gain of the camera.
             *@Returns: void
             *
             *@Throws:
             *
             */
            virtual size_t getGain()=0;

            /**
             *@Parameters:
             *  void
             *@Methods:
             *  Get the IO time of the camera.
             *@Returns: void
             *
             *@Throws:
             *
             */
            virtual size_t getIOTime()=0;

            /**
             *@Parameters:
             *  void
             *@Methods:
             *  Get the monitor mode of the camera.
             *@Returns: void
             *
             *@Throws:
             *
             */
            virtual CameraMonitorMode getMonitorMode()=0;

            /**
             *@Parameters:
             *  void
             *@Methods:
             *  Get the trigger line of the camera.
             *@Returns: void
             *
             *@Throws:
             *
             */
            virtual size_t getTriggerLine() = 0;

        };

        class ICameraActive
            : public ICamera
        {
        public:

            /**
             *@Parameters:
             *  - isget: the flag of the image is get or not
             *@Methods:
             *  Get the image from the camera.
             *@Returns: cv::mat
             *  For all camera, the image is a cv::mat object.
             *@Throws:
             *
             */
            virtual cv::Mat getImage(bool& isget)=0;

            /**
             *@Parameters:
             *  void
             *@Methods:
             *  Get the image from the camera.
             *@Returns: cv::mat
             *  For all camera, the image is a cv::mat object.
             *@Throws:
             *
             */
            virtual cv::Mat getImage() = 0;
        };

        class ICameraPassive
            : public ICamera
        {
        public:

            /**
             * @brief User defined callback function
             *
             * When the camera get a picture, the callback function will be called.
             */
            using UserToCallBack = std::function<void(cv::Mat)>;
        public:

            /**
             *@Parameters:
             *  void
             *@Methods:
             *  Register the callback function.
             *@Returns: bool
             *  If register the callback function successfully, return true,otherwise return false.
             *@Throws:
             *
             */
            virtual bool RegisterCallBackFunc()=0;

        };

        class Camera
            : public ICamera
        {
            
        };
    }
}

#endif