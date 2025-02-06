#ifndef CDM_MESSAGE_H_
#define CDM_MESSAGE_H_

#include <string>
#include <vector>
#include <memory>


namespace rw
{
    namespace cdm
    {
        class Message_factory;
        class Message_core;
        class Message_text;
        class Message_image;
        class Message_video;
    }
}

namespace rw
{
    namespace cdm
    {
        enum class MessageType
        {
            TEXT,
            IMAGE,
            VIDEO
        };

        class MessageFactory
        {
            static std::shared_ptr<Message_core> createMessage(MessageType type);
        };

        class Message
        {
        private:
            std::vector<std::shared_ptr<Message_core>> _messageList;
        };

    }

}

#endif // !CDM_MESSAGE_H_
