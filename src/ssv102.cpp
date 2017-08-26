#include <ssv102/ssv102.h>

SSV102::SSV102(const std::string& port,
               const unsigned baud)
{
    serial.setPort(port);
    serial.setBaudrate(baud);
    serial.setTimeout(serial::Timeout::max(),
                      READ_WRITE_TIMEOUT_MS,
                      0,
                      READ_WRITE_TIMEOUT_MS,
                      0);
}

SSV102::~SSV102()
{
    serial.close();
}

void
SSV102::connect() {
    serial.open();
}

void
SSV102::send_jasc(const std::string& msg, int rate) {
    serial.write("$JASC," + msg + "," + std::to_string(rate) + "\r\n");
}

void
SSV102::send_jasc(const std::map<std::string, std::string>& args) {
    for (const auto& msg_pair : args) {
        std::string msg;
        std::string rate;
        std::tie(msg, rate) = msg_pair;

        send_jasc(msg, std::atoi(rate.c_str()));
    }
}

void
SSV102::send_jasc(const std::unordered_map<std::string, int>& args) {
    for (const auto& msg_pair : args) {
        std::string msg;
        int rate;
        std::tie(msg, rate) = msg_pair;

        send_jasc(msg, rate);
    }
}

std::string
SSV102::read_sentence() {
    std::string line = "";
    while (line == "") {
        line = serial.readline();

        // Trim CRLF
        while (line.back() == '\r' || line.back() == '\n') {
            line.pop_back();
        }
    }

    return line;
}
