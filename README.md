# Wi-Fi Bluetooth® tester

This application integrates the command console library including Wi-Fi iPerf and Bluetooth® Low Energy functionality. You can use this application to characterize the Wi-Fi/Bluetooth® LE functionality and performance. This application provides a console interface to test Wi-Fi and ble commands.

See the command console library [Readme.md](https://github.com/Infineon/command-console/blob/master/README.md) for more information.

## Requirements

- [ModusToolbox&trade; software](https://www.infineon.com/cms/en/design-support/tools/sdk/modustoolbox-software/)

- Programming language: C

- Supported toolchains: Arm® GCC, ARMC6, IAR

- Associated parts: All [PSoC&trade; 6 MCU](https://www.infineon.com/cms/en/product/microcontroller/32-bit-psoc-arm-cortex-microcontroller/psoc-6-32-bit-arm-cortex-m4-mcu/) parts with SDIO, [AIROC™ CYW43012 Wi-Fi & Bluetooth® combo chip](https://www.infineon.com/dgdl/Infineon-CYW43012_Single-Chip%2CUltra-Low_IEEE_802.11n-compliant_802.11ac-friendly_MAC_Baseband_Radio_with_Bluetooth_5.0_for_IoT-AdditionalTechnicalInformation-v14_00-EN.pdf?fileId=8ac78c8c7d0d8da4017d0ee89f18715f&utm_source=cypress&utm_medium=referral&utm_campaign=202110_globe_en_all_integration-datasheet), [AIROC™ CYW4343W Wi-Fi & Bluetooth® combo chip](https://www.infineon.com/dgdl/Infineon-CYW4334WKUBGT-DataSheet-v11_00-EN.pdf?fileId=8ac78c8c7d0d8da4017d0ee1f02f680f&utm_source=cypress&utm_medium=referral&utm_campaign=202110_globe_en_all_integration-datasheet)

## Supported toolchains (make variable 'TOOLCHAIN')

- GNU Arm® embedded compiler v11.3.1 (`GCC_ARM`) - Default value of `TOOLCHAIN`
- Arm compiler v6.16 (`ARM`)
- IAR C/C++ compiler v9.30 (`IAR`)

## Supported kits (make variable 'TARGET')

- [PSoC&trade; 6 Wi-Fi Bluetooth® prototyping kit (CY8CPROTO-062-4343W) - Default target](https://www.infineon.com/cms/en/product/evaluation-boards/cy8cproto-062-4343w/)

- [PSoC&trade; 62S2 Wi-Fi Bluetooth® pioneer kit (CY8CKIT-062S2-43012)](https://www.infineon.com/cms/en/product/evaluation-boards/cy8ckit-062s2-43012/)

- [PSoC&trade; 62S2 evaluation kit (CY8CEVAL-062S2-LAI-4373M2)](https://www.infineon.com/cms/en/product/evaluation-boards/cy8ceval-062s2/)

- [PSoC&trade; 62S2 evaluation kit (CY8CEVAL-062S2-MUR-43439M2)](https://www.infineon.com/cms/en/product/evaluation-boards/cy8ceval-062s2/)

- [CYW943907AEVAL1F evaluation kit (CYW943907AEVAL1F)](https://www.infineon.com/cms/en/product/evaluation-boards/cyw943907aeval1f)

- [CYW954907AEVAL1F evaluation kit (CYW954907AEVAL1F)](https://www.infineon.com/cms/en/product/evaluation-boards/cyw954907aeval1f)

- [XMC7200D-E272K8384 kit (KIT_XMC72_EVK_MUR_43439M2)](https://www.infineon.com/cms/en/product/evaluation-boards/kit_xmc72_evk/)

## Hardware setup

This example uses the board's default configuration. See the kit user guide to ensure that the board is configured correctly.

**Note:** The PSoC&trade; 6 Bluetooth&reg; LE pioneer kit (CY8CKIT-062-BLE) and the PSoC&trade; 6 Wi-Fi Bluetooth&reg; pioneer kit (CY8CKIT-062-WIFI-BT) ship with KitProg2 installed. The ModusToolbox&trade; software requires KitProg3. Before using this code example, make sure that the board is upgraded to KitProg3. The tool and instructions are available in the [Firmware Loader](https://github.com/Infineon/Firmware-loader) GitHub repository. If you do not upgrade, you will see an error like "unable to find CMSIS-DAP device" or "KitProg firmware is out of date".

## Software setup

- Install a terminal emulator if you don't have one. Instructions in this document use [Tera Term](https://ttssh2.osdn.jp/index.html.en)

- Setting up iPerf on the host

  - [iPerf 2.0.13](https://sourceforge.net/projects/iperf2/files/) (supported on Ubuntu, macOS, and Windows)

  - Go to the iPerf installation directory and launch the terminal (command prompt for Windows, terminal shell for macOS or Ubuntu).

- Setting up the LE CoC application on the [CYW920719B2Q40EVB-01](%) peer device

  - On the ModusToolbox&trade; project creator, select the device CYW920719B2Q40EVB-01 and create a LE Connection Oriented Channel application

  - Build the [le_coc](https://github.com/Infineon/mtb-examples-CYW920719B2Q40EVB-01-btsdk-ble/tree/master/ble/le_coc) application to run LE connection-oriented channel (CoC) on the peer device. This is part of the ModusToolbox&trade; BTSDK.

  - See [Building the code examples](https://github.com/Infineon/mtb-examples-CYW920719B2Q40EVB-01-btsdk-ble#building-code-examples) for build and installation instructions.

  **Note:** Ensure that the LE CoC application is configured to run without pairing enabled, using the client control setting.

## Using the _Wi-Fi Bluetooth® tester_

Create the project and open it using one of the following:

<details><summary><b>In Eclipse IDE for ModusToolbox&trade; software</b></summary>

1. Click the **New Application** link in the **Quick Panel** (or, use **File** > **New** > **ModusToolbox&trade; Application**). This launches the [Project Creator](https://www.infineon.com/ModusToolboxProjectCreator) tool.

2. Pick a kit supported by the code example from the list shown in the **Project Creator - Choose Board Support Package (BSP)** dialog.

   When you select a supported kit, the example is reconfigured automatically to work with the kit. To work with a different supported kit later, use the [Library Manager](https://www.infineon.com/ModusToolboxLibraryManager) to choose the BSP for the supported kit. You can use the Library Manager to select or update the BSP and firmware libraries used in this application. To access the Library Manager, click the link from the **Quick Panel**.

   You can also just start the application creation process again and select a different kit.

   If you want to use the application for a kit not listed here, you may need to update the source files. If the kit does not have the required resources, the application may not work.

3. In the **Project Creator - Select Application** dialog, choose the example by enabling the checkbox.

4. (Optional) Change the suggested **New Application Name**.

5. The **Application(s) Root Path** defaults to the Eclipse workspace which is usually the desired location for the application. If you want to store the application in a different location, you can change the *Application(s) Root Path* value. Applications that share libraries should be in the same root path.

6. Click **Create** to complete the application creation process.

For more details, see the [Eclipse IDE for ModusToolbox&trade; software user guide](https://www.infineon.com/MTBEclipseIDEUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/docs_{version}/mt_ide_user_guide.pdf*).

</details>

<details><summary><b>In command-line interface (CLI)</b></summary>

ModusToolbox&trade; software provides the Project Creator as both a GUI tool and the command line tool, "project-creator-cli". The CLI tool can be used to create applications from a CLI terminal or from within batch files or shell scripts. This tool is available in the *{ModusToolbox&trade; software install directory}/tools_{version}/project-creator/* directory.

Use a CLI terminal to invoke the "project-creator-cli" tool. On Windows, use the command line "modus-shell" program provided in the ModusToolbox&trade; software installation instead of a standard Windows command-line application. This shell provides access to all ModusToolbox&trade; software tools. You can access it by typing `modus-shell` in the search box in the Windows menu. In Linux and macOS, you can use any terminal application.

The "project-creator-cli" tool has the following arguments:

Argument | Description | Required/optional
---------|-------------|-----------
`--board-id` | Defined in the `<id>` field of the [BSP](https://github.com/Infineon?q=bsp-manifest&type=&language=&sort=) manifest | Required
`--app-id`   | Defined in the `<id>` field of the [CE](https://github.com/Infineon?q=ce-manifest&type=&language=&sort=) manifest | Required
`--target-dir`| Specify the directory in which the application is to be created if you prefer not to use the default current working directory | Optional
`--user-app-name`| Specify the name of the application if you prefer to have a name other than the example's default name | Optional

<br />

The following example clones the "[mtb-wifi-bluetooth-tester](https://github.com/Infineon/mtb-wifi-bluetooth-tester)" application with the desired name "Wi-Fi_Bluetooth_tester" configured for the *CY8CPROTO-062-4343W* BSP into the specified working directory, *C:/mtb_projects*:

   ```
   project-creator-cli --board-id CY8CPROTO-062-4343W --app-id mtb-wifi-bluetooth-tester --user-app-name Wi-Fi_Bluetooth_tester --target-dir "C:/mtb_projects"
   ```

**Note:** The project-creator-cli tool uses the `git clone` and `make getlibs` commands to fetch the repository and import the required libraries. For details, see the "Project creator tools" section of the [ModusToolbox&trade; software user guide](https://www.infineon.com/MTBEclipseIDEUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/docs_{version}/mtb_user_guide.pdf*).

To work with a different supported kit later, use the [Library Manager](https://www.infineon.com/ModusToolboxLibraryManager) to choose the BSP for the supported kit. You can invoke the Library Manager GUI tool from the terminal using `make library-manager` command or use the Library Manager CLI tool "library-manager-cli" to change the BSP.

The "library-manager-cli" tool has the following arguments:

Argument | Description | Required/optional
---------|-------------|-----------
`--add-bsp-name` | Name of the BSP that should be added to the application | Required
`--set-active-bsp` | Name of the BSP that should be as active BSP for the application | Required
`--add-bsp-version`| Specify the version of the BSP that should be added to the application if you do not wish to use the latest from manifest | Optional
`--add-bsp-location`| Specify the location of the BSP (local/shared) if you prefer to add the BSP in a shared path | Optional

<br />

Following example adds the CY8CKIT-062S2-43012 BSP to the already created application and makes it the active BSP for the app:

   ```
   library-manager-cli --project "C:/mtb_projects/Wi-Fi_Bluetooth_tester" --add-bsp-name CY8CKIT-062S2-43012 --add-bsp-version "latest-v4.X" --add-bsp-location "local"

   library-manager-cli --project "C:/mtb_projects/Wi-Fi_Bluetooth_tester" --set-active-bsp CY8CKIT-062S2-43012
   ```

</details>

<details><summary><b>In third-party IDEs</b></summary>

Use one of the following options:

- **Use the standalone [Project Creator](https://www.infineon.com/ModusToolboxProjectCreator) tool:**

   1. Launch Project Creator from the Windows Start menu or from *{ModusToolbox&trade; software install directory}/tools_{version}/project-creator/project-creator.exe*.

   2. In the initial **Choose Board Support Package** screen, select the BSP, and click **Next**.

   3. In the **Select Application** screen, select the appropriate IDE from the **Target IDE** drop-down menu.

   4. Click **Create** and follow the instructions printed in the bottom pane to import or open the exported project in the respective IDE.

<br />

- **Use command-line interface (CLI):**

   1. Follow the instructions from the **In command-line interface (CLI)** section to create the application.

   2. Export the application to a supported IDE using the `make <ide>` command.

   3. Follow the instructions displayed in the terminal to create or import the application as an IDE project.

For a list of supported IDEs and more details, see the "Exporting to IDEs" section of the [ModusToolbox&trade; software user guide](https://www.infineon.com/ModusToolboxUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/docs_{version}/mtb_user_guide.pdf*).

</details>

## Operation

1. Connect the board to your PC using the provided USB cable through the KitProg3 USB connector.

2. Modify the `WIFI_SSID` and `WIFI_KEY` macros in *main.c* to match with those of the Wi-Fi network that you want to connect to.

3. To join a Wi-Fi network of a specific band, update the `WIFI_BAND` macro in *main.c* as follows:

   `CY_WCM_WIFI_BAND_2_4GHZ` : 2.4-GHz band
   `CY_WCM_WIFI_BAND_5GHZ`   : 5-GHz band

4. Configure the TCP window size in iPerf before building the application. See the command console library's [Readme.md](https://github.com/Infineon/command-console/blob/master/README.md) for instructions on how to configure the TCP window size.

5. Open a terminal program and select the KitProg3 COM port. Set the serial port parameters to 8N1 and 115200 baud.

6. Program the board using one of the following:

   <details><summary><b>Using Eclipse IDE for ModusToolbox&trade;</b></summary>

      1. Select the application project in the Project Explorer.

      2. In the **Quick Panel**, scroll down, and click **\<Application Name> Program (KitProg3_MiniProg4)**.
      </details>

   <details><summary><b>Using CLI</b></summary>

     From the terminal, execute the `make program` command to build and program the application using the default toolchain to the default target. You can specify a target and toolchain manually:
      ```
      make program TARGET=<BSP> TOOLCHAIN=<toolchain>
      ```

      Example:
      ```
      make program TARGET=CY8CPROTO-062-4343W TOOLCHAIN=GCC_ARM
      ```
</details>

   **Note:** 

   - For CYW943907AEVAL1F and CYW954907AEVAL1F kits, use the BSP `latest-v1.X` tag available.

   After programming, the application starts automatically. Observe the messages on the UART terminal, and wait for the device to make the required connections.

7. The application connects to the configured Wi-Fi access point (AP) and obtains the IP address. When the device is ready, the `>` prompt appears.

8. Run iPerf commands (client and server) against a remote peer device.

   - See [Running iPerf client and server against a remote peer device](https://github.com/Infineon/command-console#iperf-command).


9. Run Bluetooth® LE commands against a remote peer device.

   - A remote peer device can be the LE CoC application on a [CYW20719B2Q40EVB-01](%) kit.

   - See [Running  Bluetooth® LE commands against a remote peer device](https://github.com/Infineon/command-console#ble-commands).

**Note:** CYW943907AEVAL1F and CYW954907AEVAL1F kits do not support Bluetooth commands.

## Debugging

You can debug the example to step through the code. In the IDE, use the **\<Application Name> Debug (KitProg3_MiniProg4)** configuration in the **Quick Panel**. For more details, see the "Program and debug" section in the [Eclipse IDE for ModusToolbox&trade; user guide](https://www.infineon.com/MTBEclipseIDEUserGuide).

**Note:** **(Only while debugging)** On the CM4 CPU, some code in `main()` may execute before the debugger halts at the beginning of `main()`. This means that some code executes twice – once before the debugger stops execution, and again after the debugger resets the program counter to the beginning of `main()`. See [KBA231071](https://community.infineon.com/docs/DOC-21143) to learn about this and for the workaround.

## Design and implementation

The main function initializes wifi-connection-manager and connects to an AP whose details are specified. The command-console library is initialized which allows you to test the Wi-Fi,  Bluetooth®, and iPerf commands through command line.

### Resources and settings

**Table 1. Application resources**

| Resource  |  Alias/object     |    Purpose     |
| :------- | :------------    | :------------ |
| UART (HAL)|cy_retarget_io_uart_obj| UART HAL object used by Retarget-IO for Debug UART port  |

<br>

## Related resources

Resources  | Links
-----------|----------------------------------
Application notes  | [AN228571](https://www.infineon.com/AN228571) – Getting started with PSoC&trade; 6 MCU on ModusToolbox&trade; software <br />  [AN215656](https://www.infineon.com/AN215656) – PSoC&trade; 6 MCU: Dual-CPU system design <br /> [AN85951](https://www.infineon.com/AN85951) – PSoC&trade; 4 and PSoC&trade; 6 MCU CAPSENSE&trade; design guide
Code examples  | [Using ModusToolbox&trade; software](https://github.com/Infineon/Code-Examples-for-ModusToolbox-Software) on GitHub <br /> [Using PSoC&trade; Creator](https://www.infineon.com/cms/en/design-support/software/code-examples/psoc-3-4-5-code-examples-for-psoc-creator/)
Device documentation | [PSoC&trade; 6 MCU datasheets](https://www.infineon.com/cms/en/search.html#!view=downloads&term=psoc6&doc_group=Data%20Sheet) <br /> [PSoC&trade; 6 technical reference manuals](https://www.infineon.com/cms/en/search.html#!view=downloads&term=psoc6&doc_group=Additional%20Technical%20Information)
Development kits | Select your kits from the [Evaluation board finder](https://www.infineon.com/cms/en/design-support/finder-selection-tools/product-finder/evaluation-board) page
Libraries on GitHub  | [mtb-pdl-cat1](https://github.com/Infineon/mtb-pdl-cat1) – PSoC&trade; 6 peripheral driver library (PDL)  <br /> [mtb-hal-cat1](https://github.com/Infineon/mtb-hal-cat1) – Hardware abstraction layer (HAL) library <br /> [retarget-io](https://github.com/Infineon/retarget-io) – Utility library to retarget STDIO messages to a UART port 
Middleware on GitHub  | [capsense](https://github.com/Infineon/capsense) – CAPSENSE&trade; library and documents <br /> [psoc6-middleware](https://github.com/Infineon/modustoolbox-software#psoc-6-middleware-libraries) – Links to all PSoC&trade; 6 MCU middleware <br /> [Wi-Fi connection manager](https://github.com/Infineon/wifi-connection-manager) - Wi-Fi connection manager library and documents <br />[Command console library](https://github.com/Infineon/command-console) - command-console library and documents <br /> [btstack-integration](https://github.com/Infineon/btstack-integration) - btstack-integration library and documents
Tools  | [Eclipse IDE for ModusToolbox&trade; software](https://www.infineon.com/modustoolbox) – ModusToolbox&trade; software is a collection of easy-to-use software and tools enabling rapid development with Infineon MCUs, covering applications from embedded sense and control to wireless and cloud-connected systems using AIROC&trade; Wi-Fi and Bluetooth® connectivity devices. <br /> [PSoC&trade; Creator](https://www.infineon.com/cms/en/design-support/tools/sdk/psoc-software/psoc-creator/) – IDE for PSoC&trade; and FM0+ MCU development

## Other resources

Infineon provides a wealth of data at www.infineon.com to help you select the right device, and quickly and effectively integrate it into your design.

For PSoC&trade; 6 MCU devices, see [How to design with PSoC&trade; 6 MCU - KBA223067](https://community.infineon.com/docs/DOC-14644) in the Infineon Developer community.

## Document history

Document title: Wi-Fi Bluetooth® tester

| Version | Description of change |
| ------- | --------------------- |
| 1.0.0   | This is the first version of the application. |
| 1.1.0   | Updated FreeRtosConfig.h to get better TCP and UDP throughput numbers <br> Updated the app to use the latest command console library which supports wifi diagnostic commands |
| 1.2.0   | Updated the FreeRTOS configuration to FreeRTOS 10.3 <br> Updated the app to use bluetooth-freertos library version 3.x |
| 1.2.1   | Minor documentation updates. |
| 1.3.0   | Added support for CY8CEVAL-062S2-MUR-43439M2 kit. |
| 1.4.0   | Added support for CYW943907AEVAL1F and CYW954907AEVAL1F kits. |
| 2.0.0   | Updated to support ModusToolbox&trade; 3.0 software. <br> Application will not be backward compatible with older ModusToolbox&trade; software. |
| 2.0.1   | Changes to rename COMPONENT_43907 to COMPONENT_4390X. |
| 2.0.2   | Minor bug fixes and documentation updates |
| 2.1.0   | Added support for KIT_XMC72_EVK_MUR_43439M2 kit |
------

© Cypress Semiconductor Corporation, 2020-2023. This document is the property of Cypress Semiconductor Corporation, an Infineon Technologies company, and its affiliates ("Cypress").  This document, including any software or firmware included or referenced in this document ("Software"), is owned by Cypress under the intellectual property laws and treaties of the United States and other countries worldwide.  Cypress reserves all rights under such laws and treaties and does not, except as specifically stated in this paragraph, grant any license under its patents, copyrights, trademarks, or other intellectual property rights.  If the Software is not accompanied by a license agreement and you do not otherwise have a written agreement with Cypress governing the use of the Software, then Cypress hereby grants you a personal, non-exclusive, nontransferable license (without the right to sublicense) (1) under its copyright rights in the Software (a) for Software provided in source code form, to modify and reproduce the Software solely for use with Cypress hardware products, only internally within your organization, and (b) to distribute the Software in binary code form externally to end users (either directly or indirectly through resellers and distributors), solely for use on Cypress hardware product units, and (2) under those claims of Cypress’s patents that are infringed by the Software (as provided by Cypress, unmodified) to make, use, distribute, and import the Software solely for use with Cypress hardware products.  Any other use, reproduction, modification, translation, or compilation of the Software is prohibited.
<br />
TO THE EXTENT PERMITTED BY APPLICABLE LAW, CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH REGARD TO THIS DOCUMENT OR ANY SOFTWARE OR ACCOMPANYING HARDWARE, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  No computing device can be absolutely secure.  Therefore, despite security measures implemented in Cypress hardware or software products, Cypress shall have no liability arising out of any security breach, such as unauthorized access to or use of a Cypress product. CYPRESS DOES NOT REPRESENT, WARRANT, OR GUARANTEE THAT CYPRESS PRODUCTS, OR SYSTEMS CREATED USING CYPRESS PRODUCTS, WILL BE FREE FROM CORRUPTION, ATTACK, VIRUSES, INTERFERENCE, HACKING, DATA LOSS OR THEFT, OR OTHER SECURITY INTRUSION (collectively, "Security Breach").  Cypress disclaims any liability relating to any Security Breach, and you shall and hereby do release Cypress from any claim, damage, or other liability arising from any Security Breach.  In addition, the products described in these materials may contain design defects or errors known as errata which may cause the product to deviate from published specifications. To the extent permitted by applicable law, Cypress reserves the right to make changes to this document without further notice. Cypress does not assume any liability arising out of the application or use of any product or circuit described in this document. Any information provided in this document, including any sample design information or programming code, is provided only for reference purposes.  It is the responsibility of the user of this document to properly design, program, and test the functionality and safety of any application made of this information and any resulting product.  "High-Risk Device" means any device or system whose failure could cause personal injury, death, or property damage.  Examples of High-Risk Devices are weapons, nuclear installations, surgical implants, and other medical devices.  "Critical Component" means any component of a High-Risk Device whose failure to perform can be reasonably expected to cause, directly or indirectly, the failure of the High-Risk Device, or to affect its safety or effectiveness.  Cypress is not liable, in whole or in part, and you shall and hereby do release Cypress from any claim, damage, or other liability arising from any use of a Cypress product as a Critical Component in a High-Risk Device. You shall indemnify and hold Cypress, including its affiliates, and its directors, officers, employees, agents, distributors, and assigns harmless from and against all claims, costs, damages, and expenses, arising out of any claim, including claims for product liability, personal injury or death, or property damage arising from any use of a Cypress product as a Critical Component in a High-Risk Device. Cypress products are not intended or authorized for use as a Critical Component in any High-Risk Device except to the limited extent that (i) Cypress’s published data sheet for the product explicitly states Cypress has qualified the product for use in a specific High-Risk Device, or (ii) Cypress has given you advance written authorization to use the product as a Critical Component in the specific High-Risk Device and you have signed a separate indemnification agreement.
<br />
Cypress, the Cypress logo, and combinations thereof, WICED, ModusToolbox, PSoC, CapSense, EZ-USB, F-RAM, and Traveo are trademarks or registered trademarks of Cypress or a subsidiary of Cypress in the United States or in other countries. For a more complete list of Cypress trademarks, visit www.infineon.com. Other names and brands may be claimed as property of their respective owners.