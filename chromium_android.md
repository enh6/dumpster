## Build Chromium Android

[official doc](https://github.com/chromium/chromium/blob/master/docs/android_build_instructions.md)

ninja targets:
- `chrome_public_apk` Android 4.4+
- `chrome_modern_public_apk` Android L 5.0+
- `monochrome_public_apk` Android N 7.0+ (contains system webview)

## Working with Release Branches

[official doc](https://www.chromium.org/developers/how-tos/get-the-code/working-with-release-branches)

`gclient sync --with_branch_heads --with_tags`

## Links

https://github.com/PeterWangIntel/crosswalk-website/wiki/Crosswalk-Lite-15-Disabled-Feature-List.md

https://github.com/bromite/bromite

## 

## Remove locale

base chromium mod size: 68.2 MiB

remove locale: 61.8 MiB

diff: -6.4 MiB

## args.gn

```
# official build
#is_official_build=true
is_debug=false
#is_component_build=true
is_component_build=false

# build for android armeabi-v7a stable channel
target_os="android"
android_channel="stable"
target_cpu="arm"

# build arm64-v8a
#target_cpu="arm64"
#build_apk_secondary_abi=false

# no symbols
blink_symbol_level=0
symbol_level=0

# enable H264 codec
ffmpeg_branding="Chrome"
proprietary_codecs=true

# disable some components
#enable_basic_printing=false
enable_feed_in_chrome=false
enable_gvr_services=false
enable_mdns=false
enable_media_remoting=false
enable_nacl=false 
enable_nacl_nonsfi=false
enable_remoting=false
enable_reporting=false
enable_resource_whitelist_generation=false
#enable_supervised_users=false
enable_vr=false
#enable_vulkan=false

# disable field trial tests
fieldtrial_testing_like_official_build=true

# jumbo build
#use_jumbo_build=true
```
