let sdl = require('ht-sdl2');
let gl = require('../index.js');
let mat4 = require('gl-matrix').mat4;

class App {
    constructor(width, height) {
      this.width = width;
      this.height = height;
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

      console.log('vender: ', gl.getString(gl.VENDOR));
      console.log('renderer: ', gl.getString(gl.RENDERER));
      console.log('version: ', gl.getString(gl.VERSION));
      console.log('glsl version: ', gl.getString(gl.SHADING_LANGUAGE_VERSION));
      //console.log('extensions: ', gl.getString(gl.EXTENSIONS));

      this.vs_source = `
        attribute vec4 aColor;
        attribute vec4 aPosition;

        uniform mat4 uModelViewMatrix;
        uniform mat4 uProjectionMatrix;

        varying lowp vec4 vColor;

        void main() {
          gl_Position = uProjectionMatrix * uModelViewMatrix * aPosition;
          vColor = aColor;
        }
      `;

      this.fs_source = `
        varying lowp vec4 vColor;
        void main() {
          gl_FragColor = vColor;
        }
      `;

      this.program = this.createProgram(this.vs_source, this.fs_source);
      this.program_info = {
        program: this.program,
        attrib_locations: {
          vertex_position: gl.getAttribLocation(this.program, 'aPosition'),
          color_position: gl.getAttribLocation(this.program, 'aColor')
        },
        uniform_locations: {
          projection_matrix: gl.getUniformLocation(this.program, 'uProjectionMatrix'),
          model_view_matrix: gl.getUniformLocation(this.program, 'uModelViewMatrix')
        }
      };

      this.initBuffers();

      gl.useProgram(this.program);

      const fov = 45 * Math.PI / 180;
      const aspect = this.width / this.height;
      const z_near = 0.1;
      const z_far = 100.0;

      this.projection_matrix = mat4.create();
      mat4.perspective(this.projection_matrix, fov, aspect, z_near, z_far);

      this.model_view_matrix = mat4.create();
      mat4.translate(this.model_view_matrix, this.model_view_matrix, [0.0, 0.0, -4.0]);

      this.rotation = 0.01;

      gl.clearColor(0.0, 0.0, 0.0, 1.0);
      gl.clearDepth(1.0);
      gl.enable(gl.DEPTH_TEST);

      this.draw();
    }

    initBuffers() {
      const positions = [
        1.0, 0.0, -0.707,
        -1.0, 0.0, -0.707,
        0.0, 1.0, 0.707,
        0.0, -1.0, 0.707,
      ];
      const position_buffer = gl.createBuffer();
      gl.bindBuffer(gl.ARRAY_BUFFER, position_buffer);
      gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(positions), gl.STATIC_DRAW);
      gl.vertexAttribPointer(this.program_info.attrib_locations.vertex_position,
          3, gl.FLOAT, false, 0, 0);
      gl.enableVertexAttribArray(this.program_info.attrib_locations.vertex_position);

      const colors = [
        1.0, 0.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0,
        0.0, 0.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0,
      ];
      const color_buffer = gl.createBuffer();
      gl.bindBuffer(gl.ARRAY_BUFFER, color_buffer);
      gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(colors), gl.STATIC_DRAW);
      gl.vertexAttribPointer(this.program_info.attrib_locations.color_position,
          4, gl.FLOAT, false, 0, 0);
      gl.enableVertexAttribArray(this.program_info.attrib_locations.color_position);

      const indices = [
        0, 1, 2, 3, 0, 1,
      ];
      const index_buffer = gl.createBuffer();
      gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, index_buffer);
      gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indices), gl.STATIC_DRAW);

      this.buffers = {
        position: position_buffer,
        color: color_buffer,
      };
    }

    drawScene() {
      gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
      mat4.rotate(this.model_view_matrix, this.model_view_matrix, this.rotation, [0, 1, 0.707]);
      gl.uniformMatrix4fv(this.program_info.uniform_locations.projection_matrix, false, this.projection_matrix);
      gl.uniformMatrix4fv(this.program_info.uniform_locations.model_view_matrix, false, this.model_view_matrix);
      gl.drawElements(gl.TRIANGLE_STRIP, 12, gl.UNSIGNED_SHORT, 0);
    }

    createProgram(vs_source, fs_source) {
      const vertex_shader = this.loadShader(gl.VERTEX_SHADER, vs_source);
      const fragment_shader = this.loadShader(gl.FRAGMENT_SHADER, fs_source);

      let program = gl.createProgram();
      gl.attachShader(program, vertex_shader);
      gl.attachShader(program, fragment_shader);
      gl.linkProgram(program);

      if (!gl.getProgramParameter(program, gl.LINK_STATUS)) {
        console.log('Unable to initialize the shader program: ' + gl.getProgramInfoLog(program));
        return null;
      }
      return program;
    }

    loadShader(type, source) {
      const shader = gl.createShader(type);

      gl.shaderSource(shader, source);
      gl.compileShader(shader);

      if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
        console.log('An error occurred compiling the shaders: ' + gl.getShaderInfoLog(shader));
        gl.deleteShader(shader);
        return null;
      }

      return shader;
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
  }

  module.exports = App;