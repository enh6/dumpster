let sdl = require('ht-sdl2');
let gl = require('../index.js');
let Jimp = require('jimp');

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

      this.vs_source = `
        attribute vec2 a_position;
        attribute vec2 a_texcoord;

        uniform vec2 u_resolution;

        varying vec2 v_texcoord;

        void main() {
          // convert the rectangle from pixels to 0.0 to 1.0
          vec2 zeroToOne = a_position / u_resolution;

          // convert from 0->1 to 0->2
          vec2 zeroToTwo = zeroToOne * 2.0;

          // convert from 0->2 to -1->+1 (clipspace)
          vec2 clipSpace = zeroToTwo - 1.0;

          gl_Position = vec4(clipSpace * vec2(1, -1), 0, 1);

          // pass the texCoord to the fragment shader
          // The GPU will interpolate this value between points.
          v_texcoord = a_texcoord;
        }
      `;

      this.fs_source = `
        precision mediump float;

        // our texture
        uniform sampler2D u_image;
        uniform vec2 u_textureSize;
        uniform float u_kernel[9];
        uniform float u_kernelWeight;

        // the texCoords passed in from the vertex shader.
        varying vec2 v_texcoord;

        void main() {
          vec2 onePixel = vec2(1.0, 1.0) / u_textureSize;
          vec4 colorSum =
              texture2D(u_image, v_texcoord + onePixel * vec2(-1, -1)) * u_kernel[0] +
              texture2D(u_image, v_texcoord + onePixel * vec2( 0, -1)) * u_kernel[1] +
              texture2D(u_image, v_texcoord + onePixel * vec2( 1, -1)) * u_kernel[2] +
              texture2D(u_image, v_texcoord + onePixel * vec2(-1,  0)) * u_kernel[3] +
              texture2D(u_image, v_texcoord + onePixel * vec2( 0,  0)) * u_kernel[4] +
              texture2D(u_image, v_texcoord + onePixel * vec2( 1,  0)) * u_kernel[5] +
              texture2D(u_image, v_texcoord + onePixel * vec2(-1,  1)) * u_kernel[6] +
              texture2D(u_image, v_texcoord + onePixel * vec2( 0,  1)) * u_kernel[7] +
              texture2D(u_image, v_texcoord + onePixel * vec2( 1,  1)) * u_kernel[8] ;

          gl_FragColor = vec4((colorSum / u_kernelWeight).rgb, 1);
        }
      `;

      this.kernels = {
        normal: [
          0, 0, 0,
          0, 1, 0,
          0, 0, 0
        ],
        gaussianBlur: [
          0.045, 0.122, 0.045,
          0.122, 0.332, 0.122,
          0.045, 0.122, 0.045
        ],
        gaussianBlur2: [
          1, 2, 1,
          2, 4, 2,
          1, 2, 1
        ],
        gaussianBlur3: [
          0, 1, 0,
          1, 1, 1,
          0, 1, 0
        ],
        unsharpen: [
          -1, -1, -1,
          -1,  9, -1,
          -1, -1, -1
        ],
        sharpness: [
           0,-1, 0,
          -1, 5,-1,
           0,-1, 0
        ],
        sharpen: [
           -1, -1, -1,
           -1, 16, -1,
           -1, -1, -1
        ],
        edgeDetect: [
           -0.125, -0.125, -0.125,
           -0.125,  1,     -0.125,
           -0.125, -0.125, -0.125
        ],
        edgeDetect2: [
           -1, -1, -1,
           -1,  8, -1,
           -1, -1, -1
        ],
        edgeDetect3: [
           -5, 0, 0,
            0, 0, 0,
            0, 0, 5
        ],
        edgeDetect4: [
           -1, -1, -1,
            0,  0,  0,
            1,  1,  1
        ],
        edgeDetect5: [
           -1, -1, -1,
            2,  2,  2,
           -1, -1, -1
        ],
        edgeDetect6: [
           -5, -5, -5,
           -5, 39, -5,
           -5, -5, -5
        ],
        sobelHorizontal: [
            1,  2,  1,
            0,  0,  0,
           -1, -2, -1
        ],
        sobelVertical: [
            1,  0, -1,
            2,  0, -2,
            1,  0, -1
        ],
        previtHorizontal: [
            1,  1,  1,
            0,  0,  0,
           -1, -1, -1
        ],
        previtVertical: [
            1,  0, -1,
            1,  0, -1,
            1,  0, -1
        ],
        boxBlur: [
            0.111, 0.111, 0.111,
            0.111, 0.111, 0.111,
            0.111, 0.111, 0.111
        ],
        triangleBlur: [
            0.0625, 0.125, 0.0625,
            0.125,  0.25,  0.125,
            0.0625, 0.125, 0.0625
        ],
        emboss: [
           -2, -1,  0,
           -1,  1,  1,
            0,  1,  2
        ],
        computeKernelWeight: function(kernel) {
          var weight = kernel.reduce(function(prev, curr) {
              return prev + curr;
          });
          return weight <= 0 ? 1 : weight;
        }
      };

      this.program = this.createProgram(this.vs_source, this.fs_source);
      this.program_info = {
        program: this.program,
        attrib_locations: {
          vertex_position: gl.getAttribLocation(this.program, 'a_position'),
          texcoord_position: gl.getAttribLocation(this.program, 'a_texcoord')
        },
        uniform_locations: {
          resolution: gl.getUniformLocation(this.program, 'u_resolution'),
          texture_size: gl.getUniformLocation(this.program, 'u_textureSize'),
          kernel: gl.getUniformLocation(this.program, 'u_kernel[0]'),
          kernel_weight: gl.getUniformLocation(this.program, 'u_kernelWeight'),
        }
      };

      this.initBuffers();
      this.initTextures();

      gl.useProgram(this.program);

      gl.viewport(0, 0, this.width, this.height);
      gl.clearColor(0, 0, 0, 0);
    }

    initTextures() {
      Jimp.read('test/1.jpg')
      .then(image => {
        let data = new Uint8Array(image.bitmap.data);

        this.texture = gl.createTexture();
        gl.bindTexture(gl.TEXTURE_2D, this.texture);
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, image.bitmap.width, image.bitmap.height,
          0, gl.RGBA, gl.UNSIGNED_BYTE, data);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
        this.texture_width = image.bitmap.width;
        this.texture_height = image.bitmap.height;
        this.draw();
      })
      .catch(err => {
        console.log(err);
      });
    }

    initBuffers() {
      const positions = [
        0, 0,
        this.width, 0,
        0, this.height,
        0, this.width,
        this.width, 0,
        this.width, this.height
      ];
      const position_buffer = gl.createBuffer();
      gl.bindBuffer(gl.ARRAY_BUFFER, position_buffer);
      gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(positions), gl.STATIC_DRAW);
      gl.vertexAttribPointer(this.program_info.attrib_locations.vertex_position,
          2, gl.FLOAT, false, 0, 0);
      gl.enableVertexAttribArray(this.program_info.attrib_locations.vertex_position);

      const texcoords = [
        0.0, 0.0,
        1.0, 0.0,
        0.0, 1.0,
        0.0, 1.0,
        1.0, 0.0,
        1.0, 1.0
      ];
      const texcoord_buffer = gl.createBuffer();
      gl.bindBuffer(gl.ARRAY_BUFFER, texcoord_buffer);
      gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(texcoords), gl.STATIC_DRAW);
      gl.vertexAttribPointer(this.program_info.attrib_locations.texcoord_position,
          2, gl.FLOAT, false, 0, 0);
      gl.enableVertexAttribArray(this.program_info.attrib_locations.texcoord_position);

      this.buffers = {
        position: position_buffer,
        texcoord: texcoord_buffer,
      };
    }

    drawScene() {
      let kernel_name = 'edgeDetect2';
      gl.clear(gl.COLOR_BUFFER_BIT);
      gl.uniform2f(this.program_info.uniform_locations.resolution, this.width, this.height);
      gl.uniform2f(this.program_info.uniform_locations.texture_size, this.texture_width, this.texture_height);
      gl.uniform1fv(this.program_info.uniform_locations.kernel, new Float32Array(this.kernels[kernel_name]));
      gl.uniform1f(this.program_info.uniform_locations.kernel_weight, this.kernels.computeKernelWeight(this.kernels[kernel_name]));
      gl.drawArrays(gl.TRIANGLES, 0, 6);
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