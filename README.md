## Firmware Development Environment Setup

The firmware development environment is based on a devcontainer model.

Follow the instructions below to get your development environment up and running.

Note: The installation and setup instructions are a for Windows 11 Pro host machine.

## Required Software Installation

1. Install [Windows Terminal](https://learn.microsoft.com/en-us/windows/wsl/setup/environment#set-up-windows-terminal)
1. Install [WSL](https://learn.microsoft.com/en-us/windows/wsl/setup/environment)
1. Install WSL Linux image Ubuntu:
    * Open PowerShell from Windows Terminal from step 1
    * Run `wsl --install Ubuntu`
    * Folow prompts including setting up initial Linux user account. It should place you directly into a bash shell when done.
    * Note: you may need to run `wsl --set-default Unbuntu` if this install is not your default.
1. Install [Docker Desktop](https://learn.microsoft.com/en-us/windows/wsl/tutorials/wsl-containers)
    * Confirm that WSL2 is enabled as part of the installation process.
1. Install VSCode and extensions:
    * [VSCode Installation](https://code.visualstudio.com/download)
    * [VSCode - WSL extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-wsl)
    * [VSCode - Dev Containers extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)
    * [VSCode - Docker extension](https://marketplace.visualstudio.com/items?itemName=ms-azuretools.vscode-docker)

## Repository
The code repository should be cloned into your WSL file system to ensure best possible performance ([see note](https://learn.microsoft.com/en-us/windows/wsl/filesystems#file-storage-and-performance-across-file-systems))
* Open a terimal to your WSL Ubuntu Distribution using the Windows Teminal program
* Navigate to your desired project location
* Install github cli tool and setup git. This will allow you to use these credentials in your containers as well.
    * `sudo apt update`
    * `sudo apt install gh`
    * `git config --global user.name "Your Name"` ,   replace "Your Name" with your preferred username 
    * `git config --global user.email "youremail@domain.com"` , replace "youremail@domain.com" with the email you prefer 
    * `gh auth login`, follow the prompts to login:
    * References: [Git Installation](https://learn.microsoft.com/en-us/windows/wsl/tutorials/wsl-git), [Git Config](https://learn.microsoft.com/en-us/windows/wsl/tutorials/wsl-git#git-config-file-setup),[Git Credentail Manager (GCM)](https://learn.microsoft.com/en-us/windows/wsl/tutorials/wsl-git#git-credential-manager-setup)
* `git clone https://github.com/motus-engineering/zephyr-app.git`
* `cd zephyr-app`
* `code . ` to start VSCode in this directory
* If not already running, start Docker Desktop. It should always be running in the background when using a devcontainer
* Click the `Reopen in Container` button on the notification that appears or use the `Dev Containers: Reopen in Container` command from the Command Palette `(F1, Ctrl+Shift+P)`
* VSCode will restart and build the devcontainer. Once complete, your development environment is setup and ready to use.

## Configuring and Building the Firmware
The following steps are to compile the `zephyr-app` firmware application within the docker container specified in the devcontainer.json file.

In a VSCode container bash terminal, run the following from the root of the repo:
* `west update`
* `west build -d build -b nucleo_l476rg app`

Note: west remembers the most recent application directory and board (-b) selection. For incremental builds on the same application/board, use `west build` 

## Debugging
In order to debug using a USB debugger the USBIPD package will be used. This package creates a bridge from the Windows host to the WSL environment.

1. Install [USBIPD-WIN](https://learn.microsoft.com/en-us/windows/wsl/connect-usb) in both the Windows and WSL Linux environment
1. Install ST Link tools in WSL instance. This will ensure the proper udev rules are applied for ST USB debuggers.
    * `sudo apt install stlink-tools`
1. Install the required tools in the devcontainer for debugging over ST Link:
    * This part is done manually as ST does not provide tools without accepting their user agreement
    * Download the [STM32CubeCLT](https://www.st.com/en/development-tools/stm32cubeclt.html)
        * Select the "STM32CubeCLT Debian Linux Installer" package to download
    * Place the downloaded file in the following WSL Linux folder (this location is shared with the devcontainer, see devcontainer.json):
        * `\\wsl.localhost\Ubuntu\home\<username>\share`
        * Note: the `owner:group` should the `<username>` for share. If it is `root`, run `sudo chown -R <username>:<username> ~/share` to change it and its subfiles.
    * Run `west st-clt /mnt/share/<SMT32CubeCLT filename>` in the devcontainer
        * This only needs to be done once for a new devcontainer
1. Once the CLT is installed:
    * Connect the debugger to the target hardware
    * Ensure the device has power
    * "Attach" the debugger to WSL by following these [instructions](https://learn.microsoft.com/en-us/windows/wsl/connect-usb#attach-a-usb-device)
        * When attaching the debugger for the first time, the terminal must have admin privileges. You can Ctrl-click or right-click the PowerShell option in the new terminal menu option to do this
    * Start your debug session in [VSCode](https://code.visualstudio.com/docs/editor/debugging)
        * When debugging for the first time, select "Debug with STLink" within the drop-down menu at the top of the Run and Debug sidebar.

## Compile and run unit tests locally (posix build)
In a VSCode container bash terminal, run the following:
* `west unit`

This runs a script that calls the Zephyr test tool, `twister`, to run all app unit tests including code coverage results.

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
* code formatting guidlines check
* build the firmware application
* run the unit tests
* add a code coverage report to the PR if the run was triggered by a PR

The CI build may fail at any one of the above steps. The CI Pipeline must be passing in order to merge a PR.

## Releasing
* Releases are expected to be done off `master`
* Before merging to `master`, Ensure the `VERSION` file in the root directory has been updated
* Update `release_notes.txt` in the root directory with the summaries of the features and bug fixes added since the last release. This information will get included in the release description on Github.
* Merge to `master`
* From the Continuous Integration Pipeline [Github Action](https://github.com/motus-engineering/zephyr-app/actions/workflows/ci.yml), use the `Run Workflow` dropdown to select the build type and run the release workflow. A tagged [release](https://github.com/motus-engineering/zephyr-app/releases) will be created in Github with the associated firmware application files. A release build will follow the `major.minor.patch` format (e.g. 1.2.3). Other options will follow the `major.minor.patch-git_hash+build_type` format (e.g. 1.2.3-abcd1234+debug).
