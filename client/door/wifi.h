#include <memory>
#include "secrets.h"

class WifiConnection {
    public:
        bool setup();
        void loop();
        bool is_connected();
        static std::unique_ptr<WifiConnection> create();
};
