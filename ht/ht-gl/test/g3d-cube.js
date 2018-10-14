let sdl = require('ht-sdl2');
let gl = require('../index.js');
let G3D = require('g3d');

class App {
  constructor(width, height) {
    this.width = width;
    this.height = height;
    this.deawScene = null;
  }

  init() {
    sdl.Init(sdl.INIT_VIDEO);

    sdl.GL_SetAttribute(sdl.GL_CONTEXT_PROFILE_MASK, sdl.GL_CONTEXT_PROFILE_ES);
    sdl.GL_SetAttribute(sdl.GL_CONTEXT_MAJOR_VERSION, 3);
    sdl.GL_SetAttribute(sdl.GL_CONTEXT_MINOR_VERSION, 0);
    sdl.GL_SetAttribute(sdl.GL_DOUBLEBUFFER, 1);

    this.win = sdl.CreateWindow(
      'sdl2 window',
      100,
      100,
      this.width,
      this.height,
      sdl.WINDOW_OPENGL
    );

    if (this.win === null) {
      throw 'could not create window';
    }

    this.context = sdl.GL_CreateContext(this.win);
    if (this.context === null) {
      throw 'could not create context';
    }

    sdl.GL_MakeCurrent(this.win, this.context);

    // create 3d engine
    this.engine = new G3D.Engine(this);

    // create a scene
    this.scene = new G3D.Scene(this.engine);

    // create camera
    const camera = new G3D.RotatePerspectiveCamera(this.scene);
    camera.alpha = 45;
    camera.beta = 30;
    camera.radius = 12;
    camera.fov = 60;

    // create 3 lights
    const light1 = new G3D.DirectionalLight(this.scene);
    light1.direction.x = -1;
    light1.direction.y = 0;
    light1.direction.z = 1;

    const light2 = new G3D.PointLight(this.scene);
    Object.assign(light2.color, {r: 255, g: 0, b: 0});
    Object.assign(light2.position, {x : 3, y : 0, z : 3});

    const light3 = new G3D.AmbientLight(this.scene);
    light3.color.r = 255;
    light3.color.g = 255;
    light3.color.b = 255;
    light3.intensity = 0.1;

    // create mesh
    this.mesh = G3D.MeshBuilder.createCube(this.scene, 6);

    Object.assign(this.mesh.materials.default.diffuseColor, {r: 200, g: 100, b: 100});
    Object.assign(this.mesh.materials.default.specularColor, {r: 200, g: 100, b: 100});
    this.mesh.materials.default.glossiness = 10;

    this.draw();
  }

  drawScene() {
    this.mesh.rotation.y +=1;
    this.scene.render();
  }

  draw() {
    let evt = sdl.PollEvent();
    while (evt !== null) {
      if (evt.type === sdl.QUIT) {
        this.destroy();
      } else if (evt.type === sdl.KEYDOWN) {
        if (evt.scancode === sdl.SCANCODE_ESCAPE) {
          this.destroy();
        }
      } else if (evt.type === sdl.KEYDOWN) {

      }
      evt = sdl.PollEvent();
    }

    if (this.finished) {
      return;
    }

    this.drawScene();
    sdl.GL_SwapWindow(this.win);
    setTimeout(this.draw.bind(this), 16.6);
  }

  getContext(ctx) {
      return gl;
  }

  destroy(time) {
    if (time) {
      this.destroyTimeoutID = setTimeout(this.destroy.bind(this), time);
      return;
    }
    clearTimeout(this.destroyTimeoutID);
    sdl.GL_DeleteContext(this.context);
    sdl.DestroyWindow(this.win);
    sdl.Quit();
    this.finished = true;
  }
};

module.exports = App;