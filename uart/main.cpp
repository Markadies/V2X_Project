
#include "server.hpp"

int main(int argc, const char** argv) {
    Server ser(1234);
    ser.accept_client();
    ser.send("hello world from server\n");
    ser.shutdoown();
    return 0;
}