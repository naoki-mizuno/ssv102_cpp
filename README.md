# ssV-102 Driver

This is a wrapper driver for the Hemisphere ssV-102 GPS. This device has two
GPS antennas, which allows it to calculate the heading. The driver utilizes
the `nmea_navsat_driver` for parsing GGA sentences.

## Dependencies

- `serial`
- `nmea_navsat_driver`

## License

MIT License

## Author

Naoki Mizuno
