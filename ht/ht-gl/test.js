let sdl = require('../ht-sdl2');
let gl = require('./index.js');
let mat4 = require('gl-matrix').mat4;

sdl.Init(sdl.INIT_VIDEO);

sdl.GL_SetAttribute(sdl.GL_CONTEXT_PROFILE_MASK, sdl.GL_CONTEXT_PROFILE_ES);
sdl.GL_SetAttribute(sdl.GL_CONTEXT_MAJOR_VERSION, 3);
sdl.GL_SetAttribute(sdl.GL_CONTEXT_MINOR_VERSION, 0);
sdl.GL_SetAttribute(sdl.GL_DOUBLEBUFFER, 1);

const width = 500;
const height = 500;

let win = sdl.CreateWindow(
  'sdl2 window',
  100,
  100,
  width,
  height,
  sdl.WINDOW_OPENGL
);

if (win === null) {
  throw 'could not create window';
}

context = sdl.GL_CreateContext(win);
if (context === null) {
  throw 'could not create context';
}

sdl.GL_MakeCurrent(win, context);

console.log('vender: ', gl.getString(gl.VENDOR));
console.log('renderer: ', gl.getString(gl.RENDERER));
console.log('version: ', gl.getString(gl.VERSION));
console.log('glsl version: ', gl.getString(gl.SHADING_LANGUAGE_VERSION));
console.log('extensions: ', gl.getString(gl.EXTENSIONS));

const vs_source = `
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

const fs_source = `
  varying lowp vec4 vColor;
  void main() {
    gl_FragColor = vColor;
  }
`;

const program = initShaderProgram(gl, vs_source, fs_source);
const program_info = {
  program: program,
  attrib_locations: {
    vertex_position: gl.getAttribLocation(program, 'aPosition'),
    color_position: gl.getAttribLocation(program, 'aColor'),
  },
  uniform_locations: {
    projection_matrix: gl.getUniformLocation(program, 'uProjectionMatrix'),
    model_view_matrix: gl.getUniformLocation(program, 'uModelViewMatrix'),
  },
};
const buffers = initBuffers(gl);

gl.useProgram(program_info.program);

const fov = 45 * Math.PI / 180;
const aspect = width / height;
const z_near = 0.1;
const z_far = 100.0;
const projection_matrix = mat4.create();
mat4.perspective(projection_matrix, fov, aspect, z_near, z_far);

const model_view_matrix = mat4.create();
mat4.translate(model_view_matrix, model_view_matrix, [0.0, 0.0, -4.0]);

var rotation = 0.01;

gl.clearColor(0.0, 0.0, 0.0, 1.0);
gl.clearDepth(1.0);
gl.enable(gl.DEPTH_TEST);

draw();

function initBuffers(gl) {
  const positions = [
    1.0, 0.0, -0.707,
    -1.0, 0.0, -0.707,
    0.0, 1.0, 0.707,
    0.0, -1.0, 0.707,
  ];
  const position_buffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, position_buffer);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(positions), gl.STATIC_DRAW);
  gl.vertexAttribPointer(program_info.attrib_locations.vertex_position,
      3, gl.FLOAT, false, 0, 0);
  gl.enableVertexAttribArray(program_info.attrib_locations.vertex_position);

  const colors = [
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0,
  ];
  const color_buffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, color_buffer);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(colors), gl.STATIC_DRAW);
  gl.vertexAttribPointer(program_info.attrib_locations.color_position,
      4, gl.FLOAT, false, 0, 0);
  gl.enableVertexAttribArray(program_info.attrib_locations.color_position);

  const indices = [
    0, 1, 2, 3, 0, 1,
  ];
  const index_buffer = gl.createBuffer();
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, index_buffer);
  gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indices), gl.STATIC_DRAW);

  return {
    position: position_buffer,
    color: color_buffer,
  };
}

function drawScene(gl, program_info, buffers) {
  gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
  mat4.rotate(model_view_matrix, model_view_matrix, rotation, [0, 1, 0.707]);
  gl.uniformMatrix4fv(program_info.uniform_locations.projection_matrix, false, projection_matrix);
  gl.uniformMatrix4fv(program_info.uniform_locations.model_view_matrix, false, model_view_matrix);
  gl.drawElements(gl.TRIANGLE_STRIP, 12, gl.UNSIGNED_SHORT, 0);
}

function initShaderProgram(gl, vs_source, fs_source) {
  const vertex_shader = loadShader(gl, gl.VERTEX_SHADER, vs_source);
  const fragment_shader = loadShader(gl, gl.FRAGMENT_SHADER, fs_source);

  const program = gl.createProgram();
  gl.attachShader(program, vertex_shader);
  gl.attachShader(program, fragment_shader);
  gl.linkProgram(program);

  if (!gl.getProgramParameter(program, gl.LINK_STATUS)) {
    console.log('Unable to initialize the shader program: ' + gl.getProgramInfoLog(program));
    return null;
  }

  return program;
}

function loadShader(gl, type, source) {
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

function draw() {
  let evt = sdl.PollEvent();
  while (evt !== null) {
    if (evt.type === sdl.QUIT) {
      sdl.GL_DeleteContext(context);
      sdl.DestroyWindow(win);
      sdl.Quit();
      return;
    } else if (evt.type === sdl.KEYDOWN) {
    } else if (evt.type === sdl.KEYDOWN) {
    }
    evt = sdl.PollEvent();
  }

  drawScene(gl, program_info, buffers);
  sdl.GL_SwapWindow(win);
  setTimeout(draw, 16.6);
}

