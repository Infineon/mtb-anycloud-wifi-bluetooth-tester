# AnyCloud Wi-Fi Bluetooth Tester
This application integrates command console library including Wi-Fi iPerf and Bluetooth BLE functionality. Using this application, the user can characterize the Wi-Fi/BLE functionality and performance.

## Requirements
- [ModusToolbox® software](https://www.cypress.com/products/modustoolbox-software-environment) v2.2
- Programming Language: C
- Supported Toolchains: Arm® GCC, IAR
- Associated Parts: All [PSoC® 6 MCU](http://www.cypress.com/PSoC6) parts with SDIO, CYW43012, CYW4343W

## Dependent assets
- [Command Console Library](http://github.com/cypresssemiconductorco/command-console)
- [Wi-Fi Middleware Core Library](http://github.com/cypresssemiconductorco/wifi-mw-core)
- [Bluetooth FreeRTOS Library](http://github.com/cypresssemiconductorco/bluetooth-freertos)

## Supported kits
- [PSoC 6 Wi-Fi BT Prototyping Kit](https://www.cypress.com/CY8CPROTO-062-4343W) (CY8CPROTO-062-4343W) - Default target

- [PSoC 62S2 Wi-Fi BT Pioneer Kit](https://www.cypress.com/CY8CKIT-062S2-43012) (CY8CKIT-062S2-43012)

## Hardware setup
This example uses the board's default configuration. See the kit user guide to ensure that the board is configured correctly.

## Software setup
- Install a terminal emulator if you don't have one. Instructions in this document use [Tera Term](https://ttssh2.osdn.jp/index.html.en)

- [iPerf 2.0.13](https://sourceforge.net/projects/iperf2/files/) (Supported on Ubuntu, macOS and Windows)

## Using the Wi-Fi Bluetooth Tester

1. Download and unzip this repository onto your local machine, or clone the repository.

2. Open a CLI terminal and navigate to the application folder (ModusToolbox 2.2 should be installed).

   On Linux and macOS, you can use any terminal application. On Windows, open the **modus-shell** app from the Start menu.

3. Import the required libraries by executing the `make getlibs` command.

## Operation

1. Modify the macros `WIFI_SSID` and `WIFI_KEY` in *main.c* to match with those of the Wi-Fi network that you want to connect to.

2. Open a terminal program and select the KitProg3 COM port. Set the serial port parameters to 8N1 and 115200 baud.

3. Program the board.

   - **Using CLI:**

      From the terminal, execute the `make program` command to build and program the application using the default toolchain to the default target. You can specify a target and toolchain manually:
      ```
      make program TARGET=<BSP> TOOLCHAIN=<toolchain>
      ```
      
      Example:
      ```
      make program TARGET=CY8CKIT-062S2-43012 TOOLCHAIN=GCC_ARM
      ```
      
        **Note:** Before building the application, ensure that the *deps* folder contains the BSP file (*TARGET_xxx.lib*) corresponding to the TARGET. Execute the `make getlibs` command to fetch the BSP contents before building the application.

   After programming, the application starts automatically. Observe the messages on the UART terminal, and wait for the device to make all the required connections.

4. The application will connect to the configured Wi-Fi Access Point and obtain the IP address. When the device is ready, `>` prompt will appear.

## Setting up iPerf on the host

1. Install [iPerf 2.0.13](https://sourceforge.net/projects/iperf2/files/) on the host.

2. Go to iPerf installation directory and launch the terminal (command prompt for Windows, terminal shell for macOS or Ubuntu).

## Setting up LE COC application on CYW920719B2Q40EVB-01 peer device

1. To run LE COC on the peer device you need to build [le_coc](https://github.com/cypresssemiconductorco/mtb-examples-CYW920719B2Q40EVB-01-btsdk-ble/tree/master/ble/le_coc) , that is part of ModusToolbox BTSDK.

2. Refer to [Building code examples](https://github.com/cypresssemiconductorco/mtb-examples-CYW920719B2Q40EVB-01-btsdk-ble#building-code-examples) section for build and installation instructions.

*Note: Ensure that the LE COC application is configured to run without pairing enabled, using the setting in client control.*

### Instructions to run iPerf (client and server) against a remote peer device
See [Running iPerf client and server against a remote peer device](http://github.com/cypresssemiconductorco/command-console##run-iperf-client-and-server-against-a-remote-peer-device)

### Instruction to run BLE commands against a remote peer device (such as LE CoC application on a CYW20719B2Q40EVB-01 kit)
See [Running BLE commands against a remote peer device](http://github.com/cypresssemiconductorco/command-console#run-ble-commands-against-a-remote-peer-device)

## Additional Information
- [Command Console Library API Reference Guide](https://cypresssemiconductorco.github.io/command-console/api_reference_manual/html/index.html)

- [AnyCloud Wi-Fi Bluetooth Tester Version](./version.txt)

