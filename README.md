# ToF_3D
This student project is a comprehensive application written in C, that leverages the VL53L5CX Time of Flight (ToF) sensor in conjunction with the LPC55S69 microcontroller. The project is designed to explore the capabilities of the ToF sensor and demonstrate its potential in real-world applications.

## How To Use

After the build process is complete, proceed to install the application on your microcontroller. The sensor will undergo a brief initialization process, after which it should promptly display a live image on the LCD screen. Note that the sensor is capable of reading data solely in the form of an 8x8 pixel matrix.

Users have the option to select from a range of interpolation modes, to enhance the result image, including:

* Color Bilinear
* Color Nearest
* Color Bicubic
* Grey Bilinear
* Grey Nearest
* Grey Bicubic

Additionally, user can adjust the minimum and maximum distances for the sensor to display the data.

### Prerequisites

To ensure successful execution of the application, the following prerequisites must be met:

* NPX microcontroller for running the application
* Proper pin configuration
* Time-of-Flight (ToF) sensor
* Incremental encoder
* LCD screen

## Built With

* [MCUXpresso IDE](https://www.nxp.com/design/software/development-software/mcuxpresso-software-and-tools-/mcuxpresso-integrated-development-environment-ide:MCUXpresso-IDE)
* [LPC55S69](https://www.nxp.com/products/processors-and-microcontrollers/arm-microcontrollers/general-purpose-mcus/lpc5500-cortex-m33/high-efficiency-arm-cortex-m33-based-microcontroller-family:LPC55S6x)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
