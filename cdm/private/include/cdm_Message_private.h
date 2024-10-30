#ifndef CDM_MESSAGE_PRIVATE_H_
#define CDM_MESSAGE_PRIVATE_H_

#include"cdm_Message.h"

namespace rw {
    namespace cdm {
        class Message_core {


        };

        class Message_text
            :public Message_core {


        };

        class Message_image
            :public Message_core {

        };

        class Message_video
            :public Message_core {

        };
    }
}

#endif // !CDM_MESSAGE_PRIVATE_H_


