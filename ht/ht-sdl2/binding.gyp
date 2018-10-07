{
  "targets": [
    {
      "target_name": "ht-sdl2",
      "sources": [ "sdl2.cpp" ],
      "libraries": [ "-lSDL2" ],
      "defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS" ],
      "include_dirs": ["<!@(node -p \"require('node-addon-api').include\")"],
      "dependencies": ["<!(node -p \"require('node-addon-api').gyp\")"]
    }
  ]
}

