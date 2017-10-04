#include <memory>

class WifiConnection {
    const char* ssid = "Mojave";
    const char* password = "2856d18b84c94ab1b1e3";
    public:
        bool setup();
        bool is_connected();
        static std::unique_ptr<WifiConnection> create();
};
