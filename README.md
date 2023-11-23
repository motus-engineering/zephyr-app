## Firmware Development Environment Setup

The firmware development environment is based on a devcontainer model.

Follow the instructions below to get your development environment up and running.

## Required Software Installation and Configuration
The Following installation and setup instructions are for Windows 11 Pro:

1. Install [Windows Terminal](https://learn.microsoft.com/en-us/windows/wsl/setup/environment#set-up-windows-terminal)
2. Install [WSL](https://learn.microsoft.com/en-us/windows/wsl/setup/environment)
3. Install WSL Linux image Ubuntu-22.04:
    * Open Windows Terminal from step 1
    * Run `wsl --install Ubuntu-22.04`
    * Folow prompts including setting up initial Linux user account. It should place you directly into a bash shell when done.
4. In Linux terminal, install github cli tool and setup git:
    * `sudo apt update`
    * `sudo apt install gh`
    * `git config --global user.name "Your Name"` ,   replace "Your Name" with your preferred username 
    * `git config --global user.email "youremail@domain.com"` , replace "youremail@&#65279;domain.com" with the email you prefer 
    * `gh auth login`, which will prompt:
        * Answer "​&#65279;GitHub.com" to "What account do you want to log into?"
        * Answer "HTTPS" to "What is your preferred protocol for Git operations?"
        * Answer "Yes" to "Authenticate Git with your GitHub credentials?"
        * Answer "Login with a web browser" to "How would you like to authenticate GitHub CLI?"
        * If successful, "Logged in as $<$your username$>$ " will be printed.
        * If it fails to open a web browser, try the following:
            - `sudo apt install xdg-utils`
            - `export BROWSER=wslview` 
            -  `sudo ln -s $(which wslview) /usr/local/bin/xdg-open`
            -  `explorer.exe Preview.html`
            -  `sudo update-alternatives --config x-www-browser`
    * References: [Git Installation](https://learn.microsoft.com/en-us/windows/wsl/tutorials/wsl-git), [Git Config](https://learn.microsoft.com/en-us/windows/wsl/tutorials/wsl-git#git-config-file-setup),[Git Credentail Manager (GCM)](https://learn.microsoft.com/en-us/windows/wsl/tutorials/wsl-git#git-credential-manager-setup)
5. Install [USBIPD-WIN](https://learn.microsoft.com/en-us/windows/wsl/connect-usb) in both the WSL Linux environment as well as Windows.
6. Install the [STM32CubeCLT](https://www.st.com/en/development-tools/stm32cubeclt.html) in your WSL environment: 
    * Select the "STM32CubeCLT Debian Linux Installer" package to download
    * In Windows Explorer, copy the downloaded file to the following WSL Linux folder `\\wsl.localhost\Ubuntu-22.04\home\<username>\share`
    * Unzip the file
    * Run the extracted file, e.g. `sudo ./st-stm32cubeclt_1.12.1_16088_20230420_1057_amd64.deb_bundle.sh`
    * Leave the zip file in the folder as it will be used by the devcontainer as well
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
* navigate to your desired project location
* `git clone https://github.com/motus-engineering/zephyr-app.git`
* `cd zephyr-app`
* If not already running, start Docker Desktop. It should always be running in the background when using a devcontainer
* `code . ` to start VSCode in this directory
* Click the `Reopen in Container` button on the notification that appears or use the `Dev Containers: Reopen in Container` command from the Command Palette `(F1, Ctrl+Shift+P)`
* VSCode will restart and build the devcontainer. Once complete, your development environment is setup and ready to use.

## Configuring and Building the Firmware
The following steps are to compile the zephyr-app firmware application within the docker container specified in the devcontainer.json file.

In a VSCode container bash terminal, run the following from the root of the repo:
* `west update`
* `west build -d build -b nucleo_l476rg app`

## Debugging
In order to debug using a USB debugger the previously installed USBIPD package will be used. This package creates a bridge from the Windows host to the WSL environment.
* Connect the debugger to the target hardware
* Ensure the device has power
* "Attach" the debugger to WSL by following these [instructions](https://learn.microsoft.com/en-us/windows/wsl/connect-usb#attach-a-usb-device)
    * When attaching the debugger for the first time, the terminal must have admin privileges. You can Ctrl-click PowerShell in the new terminal menu option to do this
* Run `west st-cli` to install the required tools for debugging over ST Link. This uses the STM32CubeCLT zip file that was previously used when setting up your WSL. This only needs to be done once for a new container.
* Start your debug session in [VSCode](https://code.visualstudio.com/docs/editor/debugging)
    * When debugging for the first time, select "Debug with STLink" within the drop-down menu at the top of the Run and Debug sidebar.

## Compile and run unit tests locally (posix build)
In a VSCode container bash terminal, run the following:
* `cd /workdir`
* `./run_tests.sh`

## Code formatting
### Automatic code formatting tool
In VSCode, the automatic code formatting tool can be applied at any time to the in-focus C source code file by pressing `Shift + Alt + F`.

### `.c` and `.h` file templates
Templates are implemented as VS Code snippets. To populate a template in a .c or .h file:
* Press `Ctrl+Space`
* Type:
    * `fileh` for the .h file template, or
    * `filec` for the .c file template, or
    * `testc` for the .c unit test file template
* Press enter

## Continuous Integration (CI) Pipeline
The same image used in the devcontainer is also used for building the firmware as part of the CI Pipeline in Github Actions. The workflow file is located in `.github/ci.yml.`

The workflow will do the following:
* download and start the container
* TODO: check that the code follows the formatting guidlines
* build the firmware application
* run the unit tests
* add a code coverage report to the PR if the run was triggered by a PR

The CI build may fail at any one of the above steps. The CI Pipeline must be passing in order to merge a PR.

### Release Checklist
Before merging to master
* Ensure the VERSION file in the root directory has been updated
* Update `release_notes.txt` with the summaries of the features and bug fixes added since the last release. This information will get included in the release description on Github.
* From the Continuous Integration Pipeline [Github Action](https://github.com/motus-engineering/zephyr-app/actions/workflows/ci.yml), use the `Run Workflow` dropdown to select the build type and run the release workflow. A tagged [release](https://github.com/motus-engineering/zephyr-app/releases) will be created in Github with the associated firmware application files. A release build will follow the `major.minor.patch` format (e.g. 1.2.3). Other options will follow the `major.minor.patch-git_hash+build_type` format (e.g. 1.2.3-abcd1234+debug).
