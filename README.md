# ssV-102 Driver

This is a wrapper driver for the Hemisphere ssV-102 GPS. This device has two
GPS antennas, which allows it to calculate the heading. The driver utilizes
the `nmea_navsat_driver` for parsing GGA sentences.

## Dependencies

- [serial](http://wiki.ros.org/serial)
- [nmea_navsat_driver](http://wiki.ros.org/nmea_navsat_driver)

## Parameters

- `port`: the port which the ssV-102 is connected to
- `baudrate`: baud rate of the device
- `jascs`: dictionary of the message type and the rate
- `frame_id``: frame id of the message

## Subscribed topics

None

## Published topics

- `nmea_sentence`: used by `nmea_navsat_driver`

Published by `nmea_navsat_driver`:

- `fix`
- `vel`
- `time_reference`
- `heading`: https://github.com/ros-drivers/nmea_navsat_driver/pull/25

See the `nmea_navsat_driver` wiki page for more details on the topics.

## License

MIT License

## Author

Naoki Mizuno
