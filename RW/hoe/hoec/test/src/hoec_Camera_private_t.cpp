#include"hoec_Camera_private_t.h"

namespace hoec_Camera_MVS {
    TEST(CAMERAMVS, CAMERA) {
        rw::hoec::Camera_MVS camera;
        camera.setIP("1");
        EXPECT_EQ(camera.getIP(),"1");
    }

}