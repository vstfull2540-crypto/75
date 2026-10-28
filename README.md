# LA-2A — อาร์ม หนองม่วง / มือเปิ่มสตูดิโอ

Windows JUCE/CMake project targeting VST3 and Standalone. UI artwork is loaded from `Assets/LA2A_Interface.png`.

## GitHub build
1. Upload all files to a GitHub repository.
2. Push to `main`/`master`, or use **Actions → Build LA-2A VST3 (Windows) → Run workflow**.
3. Download `LA2A-Windows-VST3` from the completed workflow's Artifacts.

## Local build
Install Visual Studio 2022 C++ build tools and CMake 3.22+:
```powershell
cmake -S . -B build -A x64 -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release --parallel
```

## PNG-only artwork
All interface artwork is PNG. C++ source and GitHub workflow are text files, as required to compile and build the plugin.

## NAM limitation
The plugin includes a built-in compressor and `.nam` file picker, but **does not run Neural Amp Modeler inference**. Selecting `LA-2A Classic - Medium.nam` only selects the file. Actual NAM support requires integration and testing of NeuralAmpModelerCore. The model is not bundled.


## Build-fix update
The editor constructor uses the JUCE `AudioProcessorEditor` reference constructor, and the processor now defines `createEditor()`. The workflow emits additional toolchain/build diagnostics if a future build fails. GitHub Actions still needs to run to verify the result in your repository.


## JUCE header generation fix
The CMake project explicitly calls `juce_generate_juce_header(ArmNongMuangLA2A)` so `JuceHeader.h` is generated for the plugin target before compilation. The build still must be run by GitHub Actions to confirm success on the runner.
