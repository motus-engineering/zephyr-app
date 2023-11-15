# Design Log for Tersa Earth : Field Trial Fuel Cell - MFC Cascade PCB Firmware

The Issues in this repository are intended to serve as the Design Log / Notebook for the project.
- Open Github issues capture the scope of design intent.
- Comments on Github Issues maintain a record of the design conversation that occurs as the Issue moves from Intent through Investigation, Implementation and Validation before being Released as Content.
- Completed Github issues capture the scope of design content.

_NOTE: Logistics (Time management) conversations should *NOT* be in Github comments, but should be in the Mavenlink Activity feed of the Task linked to the Issue.

The Issues will also serve to bridge between the Motus [Design Specification](https://docs.google.com/document/d/18Qxqf7OG2-gpJk1O_4ziVJWdTjbd8Apsrcyv1l5y_c8) and Mavenlink project.
- Github Issues will be organized into Github Projects which correspond to Design Spec Sections and Milestones which correspond to Mavenlink Milestones
- Github Issues may be linked to Design Spec Sections or Sub-sections as needed.
- Github Issues may be linked to other documentation as needed.

DEVELOPMENT is the process of turning design INTENT into design CONTENT.

## Design Intent 
Open Design Issues in GitHub capture the design scope and/or provide a link to the appropriate section in the [Design Specification](https://docs.google.com/document/d/18Qxqf7OG2-gpJk1O_4ziVJWdTjbd8Apsrcyv1l5y_c8).
- Identified Bugs and Feature requests
- Technical Investigations
- Architecture Design and Definition

## Content 
The results of work on the Design Issues that have been marked Released in GitHub.
- Defined Functionality
- Completed Architecture Definition 
- Completed Code, CAD, Calculations, Documentation, Test Results
- Work Product (builds, post processed controlled revision files)

## Firmware Development Environment Setup

The firmware development environment is based on a devcontainer model.

Follow the instructions below to get your development environment up and running.

## Required Software Installation and Configuration
Windows 11 is required. Follow the installation and setup instructions at following links:

1. Install [Windows Terminal](https://learn.microsoft.com/en-us/windows/wsl/setup/environment#set-up-windows-terminal)
2. Install [WSL](https://learn.microsoft.com/en-us/windows/wsl/setup/environment)
3. Install WSL Linux image Ubuntu-22.04:


* Open Windows Terminal
* Run `wsl --install Ubuntu-22.04`
* Folow prompts including setting up initial Linux user account. It should place you directly into a bash shell when done.
4. In Linux terminal, install github:
* `sudo apt update`
* `sudo apt install gh`
* `git config --global user.name "Your Name"` ,   replace "Your Name" with your preferred username 
* `git config --global user.email "youremail@domain.com"` , replace "youremail@&#65279;domain.com" with the email you prefer 
* gh auth login, which will prompt:
    * Answer "​&#65279;GitHub.com" to "What account do you want to log into?"
    * Answer "HTTPS" to "What is your preferred protocol for Git operations?"
    * Answer "Yes" to "Authenticate Git with your GitHub credentials?"
    * Answer "Login with a web browser" to "How would you like to authenticate GitHub CLI?"
    * If successful, "Logged in as $<$your username$>$ " will be printed.
    * If it fails to open a web browser, try the following:
        1- `sudo apt install xdg-utils`
        2- `export BROWSER=wslview` 
        3-  `sudo ln -s $(which wslview) /usr/local/bin/xdg-open`
        4-  `explorer.exe Preview.html`
        5-  `sudo update-alternatives --config x-www-browser`
* References: [Git Installation](https://learn.microsoft.com/en-us/windows/wsl/tutorials/wsl-git), [Git Config](https://learn.microsoft.com/en-us/windows/wsl/tutorials/wsl-git#git-config-file-setup),[Git Credentail Manager (GCM)](https://learn.microsoft.com/en-us/windows/wsl/tutorials/wsl-git#git-credential-manager-setup)
5. Install [USBIPD-WIN](https://learn.microsoft.com/en-us/windows/wsl/connect-usb) in both the WSL Linux environment as well as Windows.
6. Install the [STM32CubeCLT](https://www.st.com/en/development-tools/stm32cubeclt.html) in your WSL environment: 
* Select the "STM32CubeCLT Debian Linux Installer" package to download
* Unzip the downloaded zip file.
* In Windows Explorer, copy the extracted file 'st-stm32cubeclt_1.12.1_16088_20230420_1057_amd64.deb_bundle.sh' to your local WSL Linux shared drive `\\wsl.localhost\Ubuntu-22.04\home\<username>\` .
* In the WSL Linux terminal, change to home directory (`cd ~`)
* Run the extracted file as `sudo ./st-stm32cubeclt_1.12.1_16088_20230420_1057_amd64.deb_bundle.sh`
7. Install [Docker Desktop](https://learn.microsoft.com/en-us/windows/wsl/tutorials/wsl-containers)
* Confirm that WSL2 is enabled as part of the installation process.
8. Install VSCode and extensions:
* [VSCode Installation](https://code.visualstudio.com/download)
* [VSCode - WSL extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-wsl)
* [VSCode - Dev Containers extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)
* [VSCode - Docker extension](https://marketplace.visualstudio.com/items?itemName=ms-azuretools.vscode-docker)
## Repository
The code repository should be cloned into your WSL file system to ensure best possible performance ([see note](https://learn.microsoft.com/en-us/windows/wsl/filesystems#file-storage-and-performance-across-file-systems))
* open your WSL Linux terminal using the Windows Teminal program
* `mkdir repos`  in your home directory
* `cd repos`
*  `git clone https://github.com/mdg-00271/mfc-cascade-pcb-fw.git`
* `cd mfc-cascade-pcb-fw`
* If not already open, open the Docker Desktop GUI in Windows and leave it running.
* `code . ` to start VSCode in this directory
* Click the `Reopen in Container` button on the notification that appears or use the `Dev Containers: Reopen in Container` command from the Command Palette `(F1, Ctrl+Shift+P)`
* VSCode will restart and build the devcontainer. Once complete, your development environment is setup and ready to use.
## Configuring and Building the Firmware
This section needs to be updated as the application is developed.

The following steps are to compile the mfc cascade pcba firmware application within the docker container specified in the devcontainer.json file.

In a VSCode container bash terminal, run the following:
* `cd /workdir`
* `west update`
* `west build -p always -b cascade_pcba mfc-cascade-pcb-fw`
## Debugging
In order to debug using a USB debugger the previously installed USBIPD package will be used. This package creates a bridge from the Windows host to the WSL environment.
* Connect the debugger to the target hardware
* Ensure the device has power
* "Attach" the debugger to WSL by following these [instructions](https://learn.microsoft.com/en-us/windows/wsl/connect-usb#attach-a-usb-device)
    * When attaching the debugger for the first time, open (but do not use) a Linux terminal with Windows admin privileges by Ctrl-clicking the Ubuntu new terminal menu option and authenticating with the Windows' admin prompt
* Start your debug session in [VSCode](https://code.visualstudio.com/docs/editor/debugging)
    * When debugging for the first time, select "Debug with STLink" within the drop-down menu at the top of the Run and Debug sidebar.
## Compile and run unit tests locally (posix build)
In a VSCode container bash terminal, run the following:
* `cd /workdir/mfc-cascade-pcb-fw`
* `./run_tests.sh`
## Code formatting
###Automatic code formatting tool
In VSCode, the automatic code formatting tool can be applied at any time to the in-focus C source code file by pressing `Shift + Alt + F`.
### `.c and .h file templates`
Templates are implemented as VS Code snippets. To populate a template in a .c or .h file:
* Press `Ctrl+Space`
* Type:
    * `fileh` for the .h file template, or
    * `filec` for the .c file template, or
    * `testc` for the .c unit test file template
* Press enter
## Continuous Integration (CI) Pipeline
*The following to be implemented*

The devcontainer is also used for building the firmware as part of the CI Pipeline in Github Actions. The workflow file is located in `.github/ci.yml.`

The workflow will do the following:
* build the container
* check that the code follows the formatting guidlines
* build the firmware application
* run the unit tests
* output a code coverage report
* add the code coverage report details to the PR if the run was triggered by a PR

The CI build may fail at any one of the above steps. The CI Pipeline must be passing in order to merge code to `develop` or `main`.

## Firmware Release Process
Follows the process described in the Motus [SOP - Git Firmware Management](https://docs.google.com/document/d/1T6_ogBWhr2-Q9jRyn47n8mObT7cwgjO1i3QbFDEQ63c) document.

### Release Checklist
Before merging to master
* Ensure the VERSION file in the root directory has been updated
* Update `release_notes.txt` with the summaries of the features and bug fixes added since the last release. This information will get included in the release description on Github.
* From the Continuous Integration Pipeline [Github Action](https://github.com/mdg-00271/mfc-cascade-pcb-fw/actions/workflows/ci.yml), use the `Run Workflow` dropdown to select the build type and run the release workflow. A tagged [release](https://github.com/mdg-00271/mfc-cascade-pcb-fw/releases) will be created in Github with the associated firmware application files. A release build will follow the `major.minor.patch` format (e.g. 1.2.3). Other options will follow the `major.minor.patch-git_hash+build_type` format (e.g. 1.2.3-abcd1234+debug).
