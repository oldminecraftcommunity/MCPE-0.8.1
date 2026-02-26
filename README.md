# MCPE 0.8.1

## An attempt to decompile the 0.8.1 libminecraftpe.so

## Building
Requires SDL1, opengl, zlib.
You must also have original 0.8.1 apk file to extract sounds(won't compile without them) and obtain assets(the compiled file will crash or not work properly without them).

should probably simplify it later

**Make sure to clone the repo with `--recursive` flag!**

*Or do `git submodule init` and `git submodule update` after!*

### Extracting sounds
* put armv8 version of libminecraftpe.so into the same folder as `get_sound_data.py`(currently located in `./minecraftpe/`)
* run `python get_sound_data.py` -> should generate `pcm_data.c`
* move `pcm_data.c` to `./minecraftpe/impl/`
### Building executable
```
mkdir build
cd build
cmake .. -DJSONCPP_WITH_TESTS=OFF -DJSONCPP_WITH_POST_BUILD_UNITTEST=OFF
make
```
the output should be `minecraftpe/build/minecraftpe08decomp`
### Running
* extract `assets` from real MCPE 0.8.1 apk into the folder you're running the executable from
* run compiled executable

## Some additional info:
* JSON library that was probably used by Mojang: https://chromium.googlesource.com/external/jsoncpp/+/6921bf1feef6f1fb83935ae3943f07753488311d/jsoncpp
* RakNet: https://github.com/facebookarchive/RakNet (possibly modifed by mojang in 0.1.x)
* CSHA1: https://www.dominik-reichl.de/projects/csha1/download/CSHA1-2.1-Source.zip
* GZIP stuff - zlib 1.2.3, based on https://zlib.net/zpipe.c
* https://github.com/nothings/stb/
* GLM - commit before https://github.com/g-truc/glm/commit/2b747cbbadfd3af39b443e88902f1c98bd231083 and -DGLM_FORCE_RADIANS <?>
