#include "napi.h"
#include <SDL2/SDL.h>
#include <memory>
#include <string>

using namespace Napi;

/* Basics */

Value Init(const CallbackInfo &info) {
  return Number::New(info.Env(), SDL_Init(info[0].As<Number>()));
}

void InitSubSystem(const CallbackInfo &info) {
  SDL_InitSubSystem(info[0].As<Number>());
}

void QuitSubSystem(const CallbackInfo &info) {
  SDL_QuitSubSystem(info[0].As<Number>());
}

Value WasInit(const CallbackInfo &info) {
  return Number::New(info.Env(), SDL_WasInit(info[0].As<Number>()));
}

void Quit(const CallbackInfo &info) { SDL_Quit(); }

Value GetError(const CallbackInfo &info) {
  return String::New(info.Env(), SDL_GetError());
}

void ClearError(const CallbackInfo &info) { SDL_ClearError(); }

Value GetVersion(const CallbackInfo &info) {
  Env env = info.Env();
  SDL_version compiled;
  SDL_version linked;
  SDL_VERSION(&compiled);
  SDL_GetVersion(&linked);
  Object cv = Object::New(env);
  cv["major"] = Number::New(env, compiled.major);
  cv["minor"] = Number::New(env, compiled.minor);
  cv["patch"] = Number::New(env, compiled.patch);
  Object lv = Object::New(env);
  lv["major"] = Number::New(env, linked.major);
  lv["minor"] = Number::New(env, linked.minor);
  lv["patch"] = Number::New(env, linked.patch);
  Object version = Object::New(env);
  version["compiled_version"] = cv;
  version["linked_version"] = lv;
  return version;
}

/* Display and window management */

Value GetNumVideoDrivers(const CallbackInfo &info) {
  return Number::New(info.Env(), SDL_GetNumVideoDrivers());
}

Value GetVideoDriver(const CallbackInfo &info) {
  return String::New(info.Env(), SDL_GetVideoDriver(info[0].As<Number>()));
}

Value VideoInit(const CallbackInfo &info) {
  Env env = info.Env();
  if (info.Length() == 0) {
    return Number::New(env, SDL_VideoInit(nullptr));
  } else {
    return Number::New(info.Env(),
                       SDL_VideoInit(info[0].As<String>().Utf8Value().c_str()));
  }
}

void VideoQuit(const CallbackInfo &info) { SDL_VideoQuit(); }

Value GetCurrentVideoDriver(const CallbackInfo &info) {
  return String::New(info.Env(), SDL_GetCurrentVideoDriver());
}

Value GetNumVideoDisplays(const CallbackInfo &info) {
  return Number::New(info.Env(), SDL_GetNumVideoDisplays());
}

Value GetDisplayName(const CallbackInfo &info) {
  return String::New(info.Env(), SDL_GetDisplayName(info[0].As<Number>()));
}

Value GetDisplayBounds(const CallbackInfo &info) {
  Env env = info.Env();
  SDL_Rect rect;
  if (SDL_GetDisplayBounds(info[0].As<Number>(), &rect) == 0) {
    Object rect_obj = Object::New(env);
    rect_obj["x"] = double(rect.x);
    rect_obj["y"] = double(rect.y);
    rect_obj["w"] = double(rect.w);
    rect_obj["h"] = double(rect.h);
    return rect_obj;
  } else {
    return env.Null();
  }
}

Value GetDisplayDPI(const CallbackInfo &info) {
  Env env = info.Env();
  float ddpi, hdpi, vdpi;
  if (SDL_GetDisplayDPI(info[0].As<Number>(), &ddpi, &hdpi, &vdpi) == 0) {
    Object ret_obj = Object::New(env);
    ret_obj["ddpi"] = ddpi;
    ret_obj["hdpi"] = hdpi;
    ret_obj["vdpi"] = vdpi;
    return ret_obj;
  } else {
    return env.Null();
  }
}

Value GetNumDisplayModes(const CallbackInfo &info) {
  return Number::New(info.Env(), SDL_GetNumDisplayModes(info[0].As<Number>()));
}

Value GetDisplayMode(const CallbackInfo &info) {
  Env env = info.Env();
  SDL_DisplayMode mode;
  if (SDL_GetDisplayMode(info[0].As<Number>(), info[1].As<Number>(), &mode) ==
      0) {
    Object mode_obj = Object::New(env);
    mode_obj["format"] = (double)mode.format;
    mode_obj["w"] = (double)mode.w;
    mode_obj["h"] = (double)mode.h;
    mode_obj["refresh_rate"] = (double)mode.refresh_rate;
    return mode_obj;
  } else {
    return env.Null();
  }
}

Value GetDesktopDisplayMode(const CallbackInfo &info) {
  Env env = info.Env();
  SDL_DisplayMode mode;
  if (SDL_GetDesktopDisplayMode(info[0].As<Number>(), &mode) == 0) {
    Object mode_obj = Object::New(env);
    mode_obj["format"] = (double)mode.format;
    mode_obj["w"] = (double)mode.w;
    mode_obj["h"] = (double)mode.h;
    mode_obj["refresh_rate"] = (double)mode.refresh_rate;
    return mode_obj;
  } else {
    return env.Null();
  }
}

Value GetCurrentDisplayMode(const CallbackInfo &info) {
  Env env = info.Env();
  SDL_DisplayMode mode;
  if (SDL_GetCurrentDisplayMode(info[0].As<Number>(), &mode) == 0) {
    Object mode_obj = Object::New(env);
    mode_obj["format"] = (double)mode.format;
    mode_obj["w"] = (double)mode.w;
    mode_obj["h"] = (double)mode.h;
    mode_obj["refresh_rate"] = (double)mode.refresh_rate;
    return mode_obj;
  } else {
    return env.Null();
  }
}

Value GetClosestDisplayMode(const CallbackInfo &info) {
  Env env = info.Env();
  SDL_DisplayMode mode, closest;
  const Object mode_obj = info[1].As<Object>();
  mode.format = mode_obj["format"].As<Number>();
  mode.w = mode_obj["w"].As<Number>();
  mode.h = mode_obj["h"].As<Number>();
  mode.refresh_rate = mode_obj["refresh_rate"].As<Number>();
  if (SDL_GetClosestDisplayMode(info[0].As<Number>(), &mode, &closest) !=
      nullptr) {
    Object closest_obj = Object::New(env);
    closest_obj["format"] = (double)closest.format;
    closest_obj["w"] = (double)closest.w;
    closest_obj["h"] = (double)closest.h;
    closest_obj["refresh_rate"] = (double)closest.refresh_rate;
    return closest_obj;
  } else {
    return env.Null();
  }
}

Value GetWindowDisplayIndex(const CallbackInfo &info) {
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  return Number::New(info.Env(), SDL_GetWindowDisplayIndex(window));
}

Value SetWindowDisplayMode(const CallbackInfo &info) {
  SDL_DisplayMode mode;
  const Object mode_obj = info[1].As<Object>();
  mode.format = mode_obj["format"].As<Number>();
  mode.w = mode_obj["w"].As<Number>();
  mode.h = mode_obj["h"].As<Number>();
  mode.refresh_rate = mode_obj["refresh_rate"].As<Number>();
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  return Number::New(info.Env(), SDL_SetWindowDisplayMode(window, &mode));
}

Value GetWindowDisplayMode(const CallbackInfo &info) {
  Env env = info.Env();
  SDL_DisplayMode mode;
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  if (SDL_GetWindowDisplayMode(window, &mode) == 0) {
    Object mode_obj = Object::New(env);
    mode_obj["format"] = (double)mode.format;
    mode_obj["w"] = (double)mode.w;
    mode_obj["h"] = (double)mode.h;
    mode_obj["refresh_rate"] = (double)mode.refresh_rate;
    return mode_obj;
  } else {
    return env.Null();
  }
}

Value GetWindowPixelFormat(const CallbackInfo &info) {
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  return Number::New(info.Env(), SDL_GetWindowPixelFormat(window));
}

Value CreateWindow(const CallbackInfo &info) {
  Env env = info.Env();
  SDL_Window *window;
  window = SDL_CreateWindow(info[0].As<String>().Utf8Value().c_str(),
                            info[1].As<Number>(), info[2].As<Number>(),
                            info[3].As<Number>(), info[4].As<Number>(),
                            info[5].As<Number>());
  if (window) {
    return External<SDL_Window>::New(env, window);
  } else {
    return env.Null();
  }
}

Value GetWindowID(const CallbackInfo &info) {
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  return Number::New(info.Env(), SDL_GetWindowID(window));
}

Value GetWindowFromID(const CallbackInfo &info) {
  Env env = info.Env();
  SDL_Window *window;
  window = SDL_GetWindowFromID(info[0].As<Number>());
  if (window) {
    return External<SDL_Window>::New(env, window);
  } else {
    return env.Null();
  }
}

Value GetWindowFlags(const CallbackInfo &info) {
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  return Number::New(info.Env(), SDL_GetWindowFlags(window));
}

void SetWindowTitle(const CallbackInfo &info) {
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  SDL_SetWindowTitle(window, info[1].As<String>().Utf8Value().c_str());
}

Value GetWindowTitle(const CallbackInfo &info) {
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  return String::New(info.Env(), SDL_GetWindowTitle(window));
}

void SetWindowPosition(const CallbackInfo &info) {
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  SDL_SetWindowPosition(window, info[1].As<Number>(), info[2].As<Number>());
}

Value GetWindowPosition(const CallbackInfo &info) {
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  int x, y;
  SDL_GetWindowPosition(window, &x, &y);
  Object obj = Object::New(info.Env());
  obj["x"] = (double)x;
  obj["y"] = (double)y;
  return obj;
}

void SetWindowSize(const CallbackInfo &info) {
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  SDL_SetWindowSize(window, info[1].As<Number>(), info[2].As<Number>());
}

Value GetWindowSize(const CallbackInfo &info) {
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  int w, h;
  SDL_GetWindowSize(window, &w, &h);
  Object obj = Object::New(info.Env());
  obj["w"] = (double)w;
  obj["h"] = (double)h;
  return obj;
}

void SetWindowMinimumSize(const CallbackInfo &info) {
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  SDL_SetWindowMinimumSize(window, info[1].As<Number>(), info[2].As<Number>());
}

Value GetWindowMinimumSize(const CallbackInfo &info) {
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  int w, h;
  SDL_GetWindowMinimumSize(window, &w, &h);
  Object obj = Object::New(info.Env());
  obj["w"] = (double)w;
  obj["h"] = (double)h;
  return obj;
}
void SetWindowMaximumSize(const CallbackInfo &info) {
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  SDL_SetWindowMaximumSize(window, info[1].As<Number>(), info[2].As<Number>());
}

Value GetWindowMaximumSize(const CallbackInfo &info) {
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  int w, h;
  SDL_GetWindowMaximumSize(window, &w, &h);
  Object obj = Object::New(info.Env());
  obj["w"] = (double)w;
  obj["h"] = (double)h;
  return obj;
}

void SetWindowBordered(const CallbackInfo &info) {
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  SDL_bool bordered = int(info[1].As<Number>()) == 0 ? SDL_FALSE : SDL_TRUE;
  SDL_SetWindowBordered(window, bordered);
}

void ShowWindow(const CallbackInfo &info) {
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  SDL_ShowWindow(window);
}

void HideWindow(const CallbackInfo &info) {
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  SDL_HideWindow(window);
}

void RaiseWindow(const CallbackInfo &info) {
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  SDL_RaiseWindow(window);
}

void MaximizeWindow(const CallbackInfo &info) {
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  SDL_MaximizeWindow(window);
}

void MinimizeWindow(const CallbackInfo &info) {
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  SDL_MinimizeWindow(window);
}

void RestoreWindow(const CallbackInfo &info) {
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  SDL_RestoreWindow(window);
}

Value SetWindowFullscreen(const CallbackInfo &info) {
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  return Number::New(info.Env(),
                     SDL_SetWindowFullscreen(window, info[1].As<Number>()));
}

Value GetWindowSurface(const CallbackInfo &info) {
  Env env = info.Env();
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  SDL_Surface *surface;
  surface = SDL_GetWindowSurface(window);
  if (surface) {
    return External<SDL_Surface>::New(env, surface);
  } else {
    return env.Null();
  }
}

Value UpdateWindowSurface(const CallbackInfo &info) {
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  return Number::New(info.Env(), SDL_UpdateWindowSurface(window));
}

Value UpdateWindowSurfaceRects(const CallbackInfo &info) {
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  const Object rects_obj = info[1].As<Object>();
  int n = rects_obj["length"].As<Number>();
  std::vector<SDL_Rect> rects(n);
  for (int i = 0; i < n; i++) {
    const Object rect_obj = rects_obj[i].As<Object>();
    rects[i].x = rect_obj["x"].As<Number>();
    rects[i].y = rect_obj["y"].As<Number>();
    rects[i].w = rect_obj["w"].As<Number>();
    rects[i].h = rect_obj["h"].As<Number>();
  }
  return Number::New(info.Env(),
                     SDL_UpdateWindowSurfaceRects(window, rects.data(), n));
}

void DestroyWindow(const CallbackInfo &info) {
  if (info[0].Type() == napi_null) {
    SDL_DestroyWindow(nullptr);
  } else {
    SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
    SDL_DestroyWindow(window);
  }
}

Value IsScreenSaverEnabled(const CallbackInfo &info) {
  return Boolean::New(info.Env(), SDL_IsScreenSaverEnabled());
}

void EnableScreenSaver(const CallbackInfo &info) { SDL_EnableScreenSaver(); }

void DisableScreenSaver(const CallbackInfo &info) { SDL_DisableScreenSaver(); }

Value GL_LoadLibrary(const CallbackInfo &info) {
  return Number::New(
      info.Env(), SDL_GL_LoadLibrary(info[0].As<String>().Utf8Value().c_str()));
}

void GL_UnloadLibrary(const CallbackInfo &info) { SDL_GL_UnloadLibrary(); }

Value GL_ExtensionSupported(const CallbackInfo &info) {
  SDL_bool supported =
      SDL_GL_ExtensionSupported(info[0].As<String>().Utf8Value().c_str());
  return Boolean::New(info.Env(), supported);
}

void GL_ResetAttributes(const CallbackInfo &info) { SDL_GL_ResetAttributes(); }

Value GL_SetAttribute(const CallbackInfo &info) {
  SDL_GLattr attr = static_cast<SDL_GLattr>((int)info[0].As<Number>());
  return Number::New(info.Env(),
                     SDL_GL_SetAttribute(attr, info[1].As<Number>()));
}

Value GL_GetAttribute(const CallbackInfo &info) {
  Env env = info.Env();
  SDL_GLattr attr = static_cast<SDL_GLattr>((int)info[0].As<Number>());
  int value;
  if (SDL_GL_GetAttribute(attr, &value) == 0) {
    return Number::New(env, value);
  } else {
    return env.Null();
  }
}

Value GL_CreateContext(const CallbackInfo &info) {
  Env env = info.Env();
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  SDL_GLContext context = SDL_GL_CreateContext(window);
  if (context == nullptr) {
    return env.Null();
  } else {
    return External<void>::New(env, context);
  }
}

Value GL_MakeCurrent(const CallbackInfo &info) {
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  SDL_GLContext context = info[1].As<External<void>>().Data();
  return Number::New(info.Env(), SDL_GL_MakeCurrent(window, context));
}

Value GL_GetCurrentWindow(const CallbackInfo &info) {
  Env env = info.Env();
  SDL_Window *window = SDL_GL_GetCurrentWindow();
  if (window == nullptr) {
    return env.Null();
  } else {
    return External<SDL_Window>::New(env, window);
  }
}

Value GL_GetCurrentContext(const CallbackInfo &info) {
  Env env = info.Env();
  SDL_GLContext context = SDL_GL_GetCurrentContext();
  if (context == nullptr) {
    return env.Null();
  } else {
    return External<void>::New(env, context);
  }
}

Value GL_GetDrawableSize(const CallbackInfo &info) {
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  int w, h;
  SDL_GL_GetDrawableSize(window, &w, &h);
  Object obj = Object::New(info.Env());
  obj["w"] = (double)w;
  obj["h"] = (double)h;
  return obj;
}

Value GL_SetSwapInterval(const CallbackInfo &info) {
  return Number::New(info.Env(), SDL_GL_SetSwapInterval(info[0].As<Number>()));
}

Value GL_GetSwapInterval(const CallbackInfo &info) {
  return Number::New(info.Env(), SDL_GL_GetSwapInterval());
}

void GL_SwapWindow(const CallbackInfo &info) {
  SDL_Window *window = info[0].As<External<SDL_Window>>().Data();
  SDL_GL_SwapWindow(window);
}

void GL_DeleteContext(const CallbackInfo &info) {
  SDL_GLContext context = info[0].As<External<void>>().Data();
  SDL_GL_DeleteContext(context);
}

/* Event handling */

Object eventToObject(Env env, SDL_Event event) {
  Object event_obj = Object::New(env);
  event_obj["type"] = (double)event.type;
  switch (event.type) {
  case SDL_WINDOWEVENT:
    event_obj["timestamp"] = (double)event.window.timestamp;
    event_obj["event"] = (double)event.window.event;
    event_obj["data1"] = (double)event.window.data1;
    event_obj["data2"] = (double)event.window.data2;
    break;
  case SDL_KEYDOWN:
  case SDL_KEYUP:
    event_obj["timestamp"] = (double)event.key.timestamp;
    event_obj["windowID"] = (double)event.key.windowID;
    event_obj["state"] = (double)event.key.state;
    event_obj["repeat"] = (double)event.key.repeat;
    event_obj["scancode"] = (double)event.key.keysym.scancode;
    // event_obj["keycode"] = (double) event.key.keysym.sym;
    event_obj["mod"] = (double)event.key.keysym.mod;
    break;
  // TODO
  default:
    break;
  }
  return event_obj;
}

SDL_Event objectToEvent(const Object event_obj) {
  SDL_Event event;
  event.type = event_obj["type"].As<Number>();
  switch (event.type) {
  case SDL_WINDOWEVENT:
    event.window.timestamp = event_obj["timestamp"].As<Number>();
    event.window.windowID = event_obj["windowID"].As<Number>();
    event.window.event = (uint32_t)event_obj["event"].As<Number>();
    event.window.data1 = event_obj["data1"].As<Number>();
    event.window.data2 = event_obj["data2"].As<Number>();
    break;
  case SDL_KEYDOWN:
  case SDL_KEYUP:
    event.key.timestamp = event_obj["timestamp"].As<Number>();
    event.key.windowID = event_obj["windowID"].As<Number>();
    event.key.state = (uint32_t)event_obj["state"].As<Number>();
    event.key.repeat = (uint32_t)event_obj["repeat"].As<Number>();
    event.key.keysym.scancode =
        static_cast<SDL_Scancode>((int)event_obj["scancode"].As<Number>());
    // event.key.keysym.sym = static_cast<SDL_Keycode>((int)
    // event_obj["keycode"].As<Number>());
    event.key.keysym.mod = (uint32_t)event_obj["mod"].As<Number>();
    break;
  // TODO
  default:
    break;
  }
  return event;
}

void PumpEvents(const CallbackInfo &info) { SDL_PumpEvents(); }

Value PeepEvents(const CallbackInfo &info) {
  Env env = info.Env();
  int n = info[1].As<Number>();
  auto events = std::unique_ptr<SDL_Event[]>(new SDL_Event[n]);
  SDL_eventaction action =
      static_cast<SDL_eventaction>((int)info[2].As<Number>());
  const Object events_obj = info[0].As<Object>();
  if (action == SDL_ADDEVENT) {
    for (int i = 0; i < n; i++) {
      events[i] = objectToEvent(events_obj[i].As<Object>());
    }
  }
  int ret = SDL_PeepEvents(events.get(), n, action, info[3].As<Number>(),
                           info[4].As<Number>());
  if (ret > 0 && (action == SDL_PEEKEVENT || action == SDL_GETEVENT)) {
    for (int i = 0; i < n; i++) {
      events_obj[i] = eventToObject(env, events[i]);
    }
  }
  return Number::New(env, ret);
}

Value HasEvent(const CallbackInfo &info) {
  return Boolean::New(info.Env(), SDL_HasEvent(info[0].As<Number>()));
}

Value HasEvents(const CallbackInfo &info) {
  return Boolean::New(
      info.Env(), SDL_HasEvents(info[0].As<Number>(), info[1].As<Number>()));
}

void FlushEvent(const CallbackInfo &info) {
  SDL_FlushEvent(info[0].As<Number>());
}

void FlushEvents(const CallbackInfo &info) {
  SDL_FlushEvents(info[0].As<Number>(), info[1].As<Number>());
}

Value PollEvent(const CallbackInfo &info) {
  Env env = info.Env();
  SDL_Event event;
  if (SDL_PollEvent(&event)) {
    return eventToObject(env, event);
  } else {
    return env.Null();
  }
}

Value WaitEvent(const CallbackInfo &info) {
  Env env = info.Env();
  SDL_Event event;
  if (SDL_WaitEvent(&event) == 1) {
    return eventToObject(env, event);
  } else {
    return env.Null();
  }
}

Value WaitEventTimeout(const CallbackInfo &info) {
  Env env = info.Env();
  SDL_Event event;
  if (SDL_WaitEventTimeout(&event, info[0].As<Number>()) == 1) {
    return eventToObject(env, event);
  } else {
    return env.Null();
  }
}

Value PushEvent(const CallbackInfo &info) {
  Env env = info.Env();
  SDL_Event event = objectToEvent(info[0].As<Object>());
  return Number::New(env, SDL_PushEvent(&event));
}

#define ADD_FUNCTION(obj, func) obj[#func] = Function::New(env, func, #func);

Object InitModule(Env env, Object exports) {
  ADD_FUNCTION(exports, Init);
  ADD_FUNCTION(exports, InitSubSystem);
  ADD_FUNCTION(exports, QuitSubSystem);
  ADD_FUNCTION(exports, WasInit);
  ADD_FUNCTION(exports, Quit);
  ADD_FUNCTION(exports, GetError);
  ADD_FUNCTION(exports, ClearError);
  ADD_FUNCTION(exports, GetVersion);

  ADD_FUNCTION(exports, GetNumVideoDrivers);
  ADD_FUNCTION(exports, GetVideoDriver);
  ADD_FUNCTION(exports, VideoInit);
  ADD_FUNCTION(exports, VideoQuit);
  ADD_FUNCTION(exports, GetCurrentVideoDriver);
  ADD_FUNCTION(exports, GetNumVideoDisplays);
  ADD_FUNCTION(exports, GetDisplayName);
  ADD_FUNCTION(exports, GetDisplayBounds);
  ADD_FUNCTION(exports, GetDisplayDPI);
  // ADD_FUNCTION(exports, GetDisplayUsableBounds);
  ADD_FUNCTION(exports, GetNumDisplayModes);
  ADD_FUNCTION(exports, GetDisplayMode);
  ADD_FUNCTION(exports, GetDesktopDisplayMode);
  ADD_FUNCTION(exports, GetCurrentDisplayMode);
  ADD_FUNCTION(exports, GetClosestDisplayMode);
  ADD_FUNCTION(exports, GetWindowDisplayIndex);
  ADD_FUNCTION(exports, SetWindowDisplayMode);
  ADD_FUNCTION(exports, GetWindowDisplayMode);
  ADD_FUNCTION(exports, GetWindowPixelFormat);
  ADD_FUNCTION(exports, CreateWindow);
  // ADD_FUNCTION(exports, CreateWindowFrom);
  ADD_FUNCTION(exports, GetWindowID);
  ADD_FUNCTION(exports, GetWindowFromID);
  ADD_FUNCTION(exports, GetWindowFlags);
  ADD_FUNCTION(exports, SetWindowTitle);
  ADD_FUNCTION(exports, GetWindowTitle);
  // ADD_FUNCTION(exports, SetWindowIcon);
  // ADD_FUNCTION(exports, SetWindowData);
  // ADD_FUNCTION(exports, GetWindowData);
  ADD_FUNCTION(exports, SetWindowPosition);
  ADD_FUNCTION(exports, GetWindowPosition);
  ADD_FUNCTION(exports, GetWindowSize);
  ADD_FUNCTION(exports, SetWindowSize);
  // ADD_FUNCTION(exports, GetWindowBorderSize);
  // ADD_FUNCTION(exports, SetWindowBorderSize);
  ADD_FUNCTION(exports, GetWindowMinimumSize);
  ADD_FUNCTION(exports, SetWindowMinimumSize);
  ADD_FUNCTION(exports, GetWindowMaximumSize);
  ADD_FUNCTION(exports, SetWindowMaximumSize);
  ADD_FUNCTION(exports, SetWindowBordered);
  // ADD_FUNCTION(exports, SetWindowResizable);
  ADD_FUNCTION(exports, ShowWindow);
  ADD_FUNCTION(exports, HideWindow);
  ADD_FUNCTION(exports, RaiseWindow);
  ADD_FUNCTION(exports, MaximizeWindow);
  ADD_FUNCTION(exports, MinimizeWindow);
  ADD_FUNCTION(exports, RestoreWindow);
  ADD_FUNCTION(exports, SetWindowFullscreen);
  ADD_FUNCTION(exports, GetWindowSurface);
  ADD_FUNCTION(exports, UpdateWindowSurface);
  ADD_FUNCTION(exports, UpdateWindowSurfaceRects);
  // ADD_FUNCTION(exports, SetWindowGrab);
  // ADD_FUNCTION(exports, GetWindowGrab);
  // ADD_FUNCTION(exports, GetGrabbedWindow);
  // ADD_FUNCTION(exports, SetWindowBrightness);
  // ADD_FUNCTION(exports, GetWindowBrightness);
  // ADD_FUNCTION(exports, SetWindowOpacity);
  // ADD_FUNCTION(exports, GetWindowOpacity);
  // ADD_FUNCTION(exports, SetWindowModalFor);
  // ADD_FUNCTION(exports, SetWindowInputFocus);
  // ADD_FUNCTION(exports, SetWindowGammaRamp);
  // ADD_FUNCTION(exports, GetWindowGammaRamp);
  // ADD_FUNCTION(exports, SetWindowHitTest);
  ADD_FUNCTION(exports, DestroyWindow);
  ADD_FUNCTION(exports, IsScreenSaverEnabled);
  ADD_FUNCTION(exports, EnableScreenSaver);
  ADD_FUNCTION(exports, DisableScreenSaver);

  ADD_FUNCTION(exports, GL_LoadLibrary);
  // ADD_FUNCTION(exports, GL_GetProcAddress);
  ADD_FUNCTION(exports, GL_UnloadLibrary);
  ADD_FUNCTION(exports, GL_ExtensionSupported);
  ADD_FUNCTION(exports, GL_ResetAttributes);
  ADD_FUNCTION(exports, GL_SetAttribute);
  ADD_FUNCTION(exports, GL_GetAttribute);
  ADD_FUNCTION(exports, GL_CreateContext);
  ADD_FUNCTION(exports, GL_MakeCurrent);
  ADD_FUNCTION(exports, GL_GetCurrentWindow);
  ADD_FUNCTION(exports, GL_GetCurrentContext);
  ADD_FUNCTION(exports, GL_GetDrawableSize);
  ADD_FUNCTION(exports, GL_SetSwapInterval);
  ADD_FUNCTION(exports, GL_GetSwapInterval);
  ADD_FUNCTION(exports, GL_SwapWindow);
  ADD_FUNCTION(exports, GL_DeleteContext);

  ADD_FUNCTION(exports, PumpEvents);
  ADD_FUNCTION(exports, PeepEvents);
  ADD_FUNCTION(exports, HasEvent);
  ADD_FUNCTION(exports, HasEvents);
  ADD_FUNCTION(exports, FlushEvent);
  ADD_FUNCTION(exports, FlushEvents);
  ADD_FUNCTION(exports, PollEvent);
  ADD_FUNCTION(exports, WaitEvent);
  ADD_FUNCTION(exports, WaitEventTimeout);
  ADD_FUNCTION(exports, PushEvent);
  // ADD_FUNCTION(exports, SetEventFilter);
  // ADD_FUNCTION(exports, GetEventFilter);
  // ADD_FUNCTION(exports, AddEventWatch);
  // ADD_FUNCTION(exports, DelEventWatch);
  // ADD_FUNCTION(exports, FilterEvents);
  // ADD_FUNCTION(exports, EventState);
  // ADD_FUNCTION(exports, RegisterEvents);

  // ADD_FUNCTION(exports, );

  return exports;
}

NODE_API_MODULE(sdl2, InitModule)
