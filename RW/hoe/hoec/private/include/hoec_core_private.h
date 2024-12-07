#ifndef HOEC_CORE_PRIVATE_H_
#define HOEC_CORE_PRIVATE_H_

struct _MV_FRAME_OUT_;
typedef struct _MV_FRAME_OUT_ MV_FRAME_OUT;

namespace cv {
    class Mat;
}

namespace rw {
    namespace hoec {
        struct ImageFrameConvert
        {
            static cv::Mat MVS_ConvertFrameToMat(const MV_FRAME_OUT& frameInfo);
        };
    } // namespace hoec

} // namespace rw


#endif // !HOEC_CORE_PRIVATE_H_
