# SKYFALL: NEXT REALITY

Original Unreal Engine 5 C++ open-world prototype targeting Android.

## Status

This repository folder contains source/configuration scaffolding. It is **not yet a compiled Unreal project or APK**. Build and device verification require a compatible Unreal Engine installation and Android toolchain.

## Open in Unreal

1. Install a compatible Unreal Engine 5 release with Android platform support.
2. Ensure Android SDK/NDK and Java versions match that engine release.
3. Generate project files for `SKYFALL.uproject` using the Unreal Editor or platform-specific project-file generator.
4. Build the `SKYFALLEditor` target in Development Editor configuration.
5. Open the project, create a test map, and set `ASkyfallCharacter` as the default pawn through a GameMode Blueprint or project settings.

## Current implementation scope

- C++ game module and target definitions.
- Character movement with built-in CharacterMovementComponent.
- A simple physics-driven vehicle prototype with throttle/brake/steering input hooks.
- A first-mission objective component and basic save-game schema are planned for subsequent commits.

## Important

No art assets, map packages, animations, or Android APK are included yet. Do not interpret the source scaffold as a playable, packaged game.
