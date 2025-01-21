#include"tdp_TransactionHandle.h"

namespace rw {
    namespace tdp {
    
    }
    std::string to_string(tdp::TransactionType type) {
        switch (type)
        {
        case tdp::TransactionType::VERIFY:
            return "VERIFY";
        default:
            throw std::invalid_argument("Unknown TransactionType");
        }
    }

    tdp::TransactionType to_TransactionType(const std::string& s) {
        if (s == "VERIFY") {
            return tdp::TransactionType::VERIFY;
        }
        else {
            throw std::invalid_argument("Unknown TransactionType");
        }
    
    }
}