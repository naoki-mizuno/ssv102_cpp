#ifndef SSV102_H_
#define SSV102_H_

#include <serial/serial.h>
#include <nmea_msgs/Sentence.h>

#include <algorithm>
#include <map>
#include <unordered_map>
#include <unordered_set>

class SSV102 {
public:
    /* Serial port timeout in ms */
    static const unsigned READ_WRITE_TIMEOUT_MS = 250;

    /* Constructors, Destructor, and Assignment operators {{{ */
    /**
     * Construct a serial reader/writer for a port
     */
    SSV102(const std::string& port, const unsigned baud);

    // Copy constructor (deleted)
    SSV102(const SSV102& other) = delete;

    // Move constructor (deleted)
    SSV102(SSV102&& other) = delete;

    // Destructor
    ~SSV102();

    // Assignment operator (deleted)
    SSV102&
    operator=(const SSV102& other) = delete;

    // Move assignment operator (deleted)
    SSV102&
    operator=(SSV102&& other) = delete;
    /* }}} */

    /**
     * Connects to the ssV-102
     *
     * \throw serial::PortNotOpenedException
     */
    void
    connect();

    /**
     * Sends the JASC commands to the GPS, which sets the data rate fields
     *
     * \param[in] msg the message type such as GPHDT, GPGGA, etc. Check the
     *                manual for a full list of available message names.
     *  \param[in] rate the refresh rate in hertz. 0 means to disable.
     */
    void
    send_jasc(const std::string& msg, int rate);

    /**
     * Sends JASC for each message given
     *
     * Used for passing rosparam parameters.
     *
     * \param[in] args pair of message name and data refresh rate.
     */
    void
    send_jasc(const std::map<std::string, std::string>& args);

    /**
     * Sends JASC for each message given
     *
     * \param[in] args pair of message name and data refresh rate.
     */
    void
    send_jasc(const std::unordered_map<std::string, int>& args);


    /**
     * Reads a line from the device and trims the trailing CRLF
     */
    std::string
    read_sentence();

private:
    serial::Serial serial;
};

#endif /* end of include guard */
