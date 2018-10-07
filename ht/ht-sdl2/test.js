let sdl = require('./index.js');
sdl.Init(sdl.INIT_VIDEO);
console.log(sdl.WasInit(0));
console.log(sdl.GetError());
let win =  sdl.CreateWindow('sdl2 window',
  sdl.WINDOWS_CENTERED_DISPLAY,
  sdl.WINDOWS_CENTERED_DISPLAY,
  300, 500, 2);
console.log(sdl.GetError());
if (win === null) {
  throw('could not create window');
}

console.log('screen saver enabled: ' + sdl.IsScreenSaverEnabled());
let n = sdl.GetNumVideoDrivers();
for (let i = 0; i < n; i++) {
  console.log(`video driver ${i}: ${sdl.GetVideoDriver(i)}`);
}

n = sdl.GetNumVideoDisplays();
for (let i = 0; i < n; i++) {
  console.log(`video display ${i}: ${sdl.GetDisplayName(i)}`);
}

console.log(sdl.GetDisplayBounds(0));
console.log(sdl.GetDisplayBounds(1));
console.log(sdl.GetDisplayDPI(0));
console.log(sdl.GetDisplayDPI(1));
console.log(sdl.GetError());

n = sdl.GetNumDisplayModes(0);
for (let i = 0; i < n; i++) {
  console.log(i, sdl.GetDisplayMode(0, i));
}
console.log('current display mode: ', sdl.GetCurrentDisplayMode(0));
console.log('desktop display mode: ', sdl.GetDesktopDisplayMode(0));

let mode = sdl.GetDisplayMode(0, 0);
mode.h = 900;
mode.w = 1400;
console.log(sdl.GetClosestDisplayMode(0, mode));

console.log('window display index: ', sdl.GetWindowDisplayIndex(win));

mode = sdl.GetWindowDisplayMode(win);
console.log(mode);
sdl.SetWindowDisplayMode(win, mode);
console.log(sdl.GetWindowPixelFormat(win));

let id = sdl.GetWindowID(win);
console.log(id);
win = sdl.GetWindowFromID(id);
console.log(sdl.GetWindowTitle(win));
sdl.SetWindowTitle(win, 'haha');

console.log(sdl.GetWindowSize(win));
sdl.SetWindowSize(win, 500, 500);

console.log(sdl.GetWindowPosition(win));
sdl.SetWindowPosition(win, 100, 100);

sdl.ClearError();
let surface = sdl.GetWindowSurface(win);
n = sdl.UpdateWindowSurfaceRects(win, [
  {w: 10, h: 10, x:0, y:0},
  {w: 10, h: 10, x:0, y:1}
]);
console.log(n);
console.log(sdl.GetError());

function timeout(ms) {
  return new Promise((resolve) => {
    setTimeout(resolve, ms);
  });
}

timeout(1000)
//*
  .then(() => {
    sdl.HideWindow(win);
    return timeout(1000);
  })
  .then(() => {
    sdl.ShowWindow(win);
    return timeout(1000);
  })
  .then(() => {
    sdl.SetWindowFullscreen(win, sdl.WINDOW_FULLSCREEN);
    return timeout(2000);
  })
  .then(() => {
    sdl.SetWindowFullscreen(win, 0);
    return timeout(2000);
  })
  //*/
  .then(() => {
    sdl.DestroyWindow(win);
    sdl.Quit();
  });

console.log(sdl.GetVersion());
