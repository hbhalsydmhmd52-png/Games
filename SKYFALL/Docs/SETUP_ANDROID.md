# Workstation setup — SKYFALL

## Prerequisites

- Install Unreal Engine 5.5 from the Epic Games Launcher or a source build matching the 5.5 release.
- Install the Android platform components supported by that exact Unreal release. Use Unreal's Android SDK setup instructions rather than mixing arbitrary SDK/NDK versions.
- Install a compatible JDK and Android SDK/NDK; verify paths in Unreal Editor > Platforms > Android > SDK Configuration.
- On Windows, install the Visual Studio C++ workload required by that Unreal release.

## Open and build

1. Download or clone the repository.
2. Open `SKYFALL/SKYFALL.uproject` with Unreal Engine 5.5.
3. Allow Unreal to generate project files when prompted.
4. Build the `SKYFALLEditor` target in Development Editor configuration using the IDE generated for your OS.
5. In Unreal Editor, create a test level and place a Blueprint child of `SkyfallCharacter` as the default pawn. Configure collision and input mappings.
6. For the vehicle prototype, create a Blueprint child of `SkyfallVehiclePawn`, assign a vehicle-shaped Static Mesh with simple collision, and enable physics on the mesh. Set a test pawn in the level and possess it to test driving inputs.
7. Configure Android SDK settings, enable USB debugging on a test device, package Development for Android, install, and capture logs before attempting Shipping.

## Example command (Windows, adjust engine path)

```powershell
& 'C:\Program Files\Epic Games\UE_5.5\Engine\Build\BatchFiles\Build.bat' SKYFALLEditor Win64 Development -Project="$PWD\SKYFALL.uproject" -WaitMutex
```

## Current verification boundary

This repository scaffold has not been compiled with Unreal, packaged, or run on a device in the current environment. The command above is an example for a Windows Unreal workstation, not evidence of a successful build. Linux/macOS paths and Android package commands depend on the installed engine and SDK configuration.
