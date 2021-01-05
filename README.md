# AnyCloud Wi-Fi Bluetooth Tester

This application integrates the Command Console Library including Wi-Fi iPerf and Bluetooth BLE functionality. You can use this application to characterize the Wi-Fi/BLE functionality and performance.

## Requirements

- [ModusToolbox® software](https://www.cypress.com/products/modustoolbox-software-environment) v2.2

- Programming Language: C

- Supported Toolchains: Arm® GCC, IAR

- Associated Parts: All [PSoC® 6 MCU](http://www.cypress.com/PSoC6) parts with SDIO, CYW43012, CYW4343W

## Dependent Assets

- [Command Console Library](http://github.com/cypresssemiconductorco/command-console)

- [Wi-Fi Connection Manager Library](http://github.com/cypresssemiconductorco/wifi-connection-manager)

- [Bluetooth FreeRTOS Library](http://github.com/cypresssemiconductorco/bluetooth-freertos)

## Supported Kits

- [PSoC 6 Wi-Fi BT Prototyping Kit](https://www.cypress.com/CY8CPROTO-062-4343W) (CY8CPROTO-062-4343W) - Default target

- [PSoC 62S2 Wi-Fi BT Pioneer Kit](https://www.cypress.com/CY8CKIT-062S2-43012) (CY8CKIT-062S2-43012)


## Hardware Setup

This example uses the board's default configuration. See the kit user guide to ensure that the board is configured correctly.


## Software Setup

- Install a terminal emulator if you don't have one. Instructions in this document use [Tera Term](https://ttssh2.osdn.jp/index.html.en)

- [iPerf 2.0.13](https://sourceforge.net/projects/iperf2/files/) (supported on Ubuntu, macOS, and Windows)


## Using the Wi-Fi Bluetooth Tester

1. Download and unzip this repository onto your local machine, or clone the repository.

2. Open a CLI terminal and navigate to the application folder (ModusToolbox 2.2 should be installed).

   On Linux and macOS, you can use any terminal application. On Windows, open the **modus-shell** app from the Start menu.

3. Import the required libraries by executing the `make getlibs` command.


## Operation

1. Modify the `WIFI_SSID` and `WIFI_KEY` macros in *main.c* to match with those of the Wi-Fi network that you want to connect to.

2. Configure the TCP window size in iPerf before building the application. See the Command Console library's [Readme.md](https://github.com/cypresssemiconductorco/command-console/blob/master/README.md) for instructions on how to configure the TCP window size.

3. Open a terminal program and select the KitProg3 COM port. Set the serial port parameters to 8N1 and 115200 baud.

4. Program the board.

   From the terminal, execute the `make program` command to build and program the application using the default toolchain to the default target. You can specify a target and toolchain manually:

   ```
   make program TARGET=<BSP> TOOLCHAIN=<toolchain>
   ```

   Example:
   ```
   make program TARGET=CY8CKIT-062S2-43012 TOOLCHAIN=GCC_ARM
   ```

   **Note:** Before building the application, ensure that the *deps* folder contains the BSP file (*TARGET_xxx.lib*) corresponding to the TARGET. Execute the `make getlibs` command to fetch the BSP contents before building the application.

   After programming, the application starts automatically. Observe the messages on the UART terminal, and wait for the device to make the required connections.

5. The application will connect to the configured Wi-Fi Access Point (AP) and obtain the IP address. When the device is ready, the `>` prompt will appear.

## Setting up iPerf on the Host

1. Install [iPerf 2.0.13](https://sourceforge.net/projects/iperf2/files/) on the host.

2. Go to the iPerf installation directory and launch the terminal (command prompt for Windows, terminal shell for macOS or Ubuntu).


## Setting up the LE CoC Application on CYW920719B2Q40EVB-01 Peer Device

1. Build the [le_coc](https://github.com/cypresssemiconductorco/mtb-examples-CYW920719B2Q40EVB-01-btsdk-ble/tree/master/ble/le_coc) application to run LE Connection-oriented Channel (CoC) on the peer device. This is part of the ModusToolbox BTSDK.

2. See [Building Code Examples](https://github.com/cypresssemiconductorco/mtb-examples-CYW920719B2Q40EVB-01-btsdk-ble#building-code-examples) for build and installation instructions.

**Note:** Ensure that the LE CoC application is configured to run without pairing enabled, using the client control setting.


### Run iPerf (Client and Server) Against a Remote Peer Device

See [Running iPerf Client and Server Against a Remote Peer Device](http://github.com/cypresssemiconductorco/command-console##run-iperf-client-and-server-against-a-remote-peer-device).


### Run BLE Commands Against a Remote Peer Device

A remote peer device can be the LE CoC application on a CYW20719B2Q40EVB-01 kit.

See [Running BLE Commands Against a Remote Peer Device](http://github.com/cypresssemiconductorco/command-console#run-ble-commands-against-a-remote-peer-device).

## Additional Information

- [Command Console Library API Reference Guide](https://cypresssemiconductorco.github.io/command-console/api_reference_manual/html/index.html)

- [AnyCloud Wi-Fi Bluetooth Tester Version](./version.txt)
