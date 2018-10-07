#include "napi.h"

#include <GLES3/gl3.h>

using namespace Napi;

void activeTexture(const CallbackInfo &info) {
  glActiveTexture(info[0].As<Number>());
}

void attachShader(const CallbackInfo &info) {
  const Object program = info[0].As<Object>();
  const Object shader = info[1].As<Object>();
  glAttachShader(program["value"].As<Number>(), shader["value"].As<Number>());
}

void bindAttribLocation(const CallbackInfo &info) {
  glBindAttribLocation(info[0].As<Number>(), info[1].As<Number>(),
                       info[2].As<String>().Utf8Value().c_str());
}

void bindBuffer(const CallbackInfo &info) {
  const Object buffer = info[1].As<Object>();
  glBindBuffer(info[0].As<Number>(), buffer["value"].As<Number>());
}

void bindFramebuffer(const CallbackInfo &info) {
  const Object buffer = info[1].As<Object>();
  glBindFramebuffer(info[0].As<Number>(), buffer["value"].As<Number>());
}

void bindRenderbuffer(const CallbackInfo &info) {
  const Object buffer = info[1].As<Object>();
  glBindRenderbuffer(info[0].As<Number>(), buffer["value"].As<Number>());
}

void bindTexture(const CallbackInfo &info) {
  const Object texture = info[1].As<Object>();
  glBindTexture(info[0].As<Number>(), texture["value"].As<Number>());
}

void bufferData(const CallbackInfo &info) {
  ArrayBuffer buffer = info[1].As<TypedArray>().ArrayBuffer();
  glBufferData(info[0].As<Number>(), buffer.ByteLength(), buffer.Data(),
               info[2].As<Number>());
}

void clear(const CallbackInfo &info) { glClear(info[0].As<Number>()); }

void clearColor(const CallbackInfo &info) {
  glClearColor(info[0].As<Number>(), info[1].As<Number>(), info[2].As<Number>(),
               info[3].As<Number>());
}

void clearDepth(const CallbackInfo &info) {
  glClearDepthf(info[0].As<Number>());
}

void compileShader(const CallbackInfo &info) {
  const Object shader = info[0].As<Object>();
  glCompileShader(shader["value"].As<Number>());
}

Value createBuffer(const CallbackInfo &info) {
  Object buffer = Object::New(info.Env());
  GLuint buf;
  glGenBuffers(1, &buf);
  buffer["value"] = (double)buf;
  return buffer;
}

Value createProgram(const CallbackInfo &info) {
  Object program = Object::New(info.Env());
  program["value"] = (double)glCreateProgram();
  return program;
}

Value createShader(const CallbackInfo &info) {
  Object shader = Object::New(info.Env());
  shader["value"] = (double)glCreateShader(info[0].As<Number>());
  return shader;
}

Value createTexture(const CallbackInfo &info) {
  Object texture = Object::New(info.Env());
  GLuint tex;
  glGenTextures(1, &tex);
  texture["value"] = (double)tex;
  return texture;
}

void deleteTexture(const CallbackInfo &info) {
  const Object texture = info[0].As<Object>();
  GLuint tex = texture["value"].As<Number>();
  glDeleteTextures(1, &tex);
}

void depthFunc(const CallbackInfo &info) { glDepthFunc(info[0].As<Number>()); }

void disable(const CallbackInfo &info) { glDisable(info[0].As<Number>()); }

void disableVertexAttribArray(const CallbackInfo &info) {
  glDisableVertexAttribArray(info[0].As<Number>());
}

void drawArrays(const CallbackInfo &info) {
  glDrawArrays(info[0].As<Number>(), info[1].As<Number>(),
               info[2].As<Number>());
}

void drawElements(const CallbackInfo &info) {
  glDrawElements(info[0].As<Number>(), info[1].As<Number>(),
                 info[2].As<Number>(), (void *)(intptr_t)info[3].As<Number>());
}

void enable(const CallbackInfo &info) { glEnable(info[0].As<Number>()); }

void enableVertexAttribArray(const CallbackInfo &info) {
  glEnableVertexAttribArray(info[0].As<Number>());
}

void finish(const CallbackInfo &info) { glFinish(); }

void flush(const CallbackInfo &info) { glFlush(); }

void generateMipmap(const CallbackInfo &info) {
  glGenerateMipmap(info[0].As<Number>());
}

Value getAttribLocation(const CallbackInfo &info) {
  const Object program = info[0].As<Object>();
  int loc = glGetAttribLocation(program["value"].As<Number>(),
                                info[1].As<String>().Utf8Value().c_str());
  return Number::New(info.Env(), loc);
}

Value getError(const CallbackInfo &info) {
  return Number::New(info.Env(), glGetError());
}

Value getProgramParameter(const CallbackInfo &info) {
  const Object program = info[0].As<Object>();
  GLint param;
  glGetProgramiv(program["value"].As<Number>(), info[1].As<Number>(), &param);
  return Number::New(info.Env(), param);
}

Value getShaderParameter(const CallbackInfo &info) {
  const Object shader = info[0].As<Object>();
  GLint param;
  glGetShaderiv(shader["value"].As<Number>(), info[1].As<Number>(), &param);
  return Number::New(info.Env(), param);
}

Value getShaderInfoLog(const CallbackInfo &info) {
  const Object shader = info[0].As<Object>();
  GLint len;
  char info_log[1000];
  glGetShaderInfoLog(shader["value"].As<Number>(), 1000, &len, info_log);
  return String::New(info.Env(), info_log);
}

Value getString(const CallbackInfo &info) {
  const char *str =
      reinterpret_cast<const char *>(glGetString(info[0].As<Number>()));
  return String::New(info.Env(), str);
}

Value getUniformLocation(const CallbackInfo &info) {
  const Object program = info[0].As<Object>();
  GLint location = glGetUniformLocation(
      program["value"].As<Number>(), info[1].As<String>().Utf8Value().c_str());
  Object loc_obj = Object::New(info.Env());
  loc_obj["value"] = (double)location;
  return loc_obj;
}

void linkProgram(const CallbackInfo &info) {
  const Object program = info[0].As<Object>();
  glLinkProgram(program["value"].As<Number>());
}

void shaderSource(const CallbackInfo &info) {
  const Object shader = info[0].As<Object>();
  std::string str = info[1].As<String>().Utf8Value();
  const char *c_str = str.c_str();
  int length = strlen(c_str);
  glShaderSource(shader["value"].As<Number>(), 1, &c_str, &length);
}

void texImage2D(const CallbackInfo &info) {
  ArrayBuffer buffer = info[8].As<TypedArray>().ArrayBuffer();
  glTexImage2D(info[0].As<Number>(), info[1].As<Number>(), info[2].As<Number>(),
    info[3].As<Number>(), info[4].As<Number>(), info[5].As<Number>(), info[6].As<Number>(),
    info[7].As<Number>(), buffer.Data());
}

void texParameteri(const CallbackInfo &info) {
  glTexParameteri(info[0].As<Number>(), info[1].As<Number>(), info[2].As<Number>());
}

void uniformMatrix4fv(const CallbackInfo &info) {
  const Object location = info[0].As<Object>();
  const Object matrix = info[2].As<Object>();
  int size = matrix["length"].As<Number>();
  GLfloat value[16];
  for (int i = 0; i < size; i++) {
    value[i] = matrix[i].As<Number>();
  }
  glUniformMatrix4fv(location["value"].As<Number>(), size / 16,
                     info[1].As<Boolean>(), value);
}

void useProgram(const CallbackInfo &info) {
  const Object program = info[0].As<Object>();
  glUseProgram(program["value"].As<Number>());
}

void vertexAttribPointer(const CallbackInfo &info) {
  glVertexAttribPointer(info[0].As<Number>(), info[1].As<Number>(),
                        info[2].As<Number>(), info[3].As<Boolean>(),
                        info[4].As<Number>(),
                        (void *)(intptr_t)info[5].As<Number>());
}

void viewport(const CallbackInfo &info) {
  glViewport(info[0].As<Number>(), info[1].As<Number>(), info[2].As<Number>(),
             info[3].As<Number>());
}

#define ADD_FUNCTION(obj, func) obj[#func] = Function::New(env, func, #func);

Object InitModule(Env env, Object exports) {
  ADD_FUNCTION(exports, activeTexture);
  ADD_FUNCTION(exports, attachShader);
  ADD_FUNCTION(exports, bindAttribLocation);
  ADD_FUNCTION(exports, bindBuffer);
  ADD_FUNCTION(exports, bindFramebuffer);
  ADD_FUNCTION(exports, bindRenderbuffer);
  ADD_FUNCTION(exports, bindTexture);
  // ADD_FUNCTION(exports, blendColor);
  // ADD_FUNCTION(exports, blendEquation);
  // ADD_FUNCTION(exports, blendEquationSeparate);
  // ADD_FUNCTION(exports, blendFunc);
  // ADD_FUNCTION(exports, blendFuncSeparate);
  ADD_FUNCTION(exports, bufferData);
  // ADD_FUNCTION(exports, bufferSubData);
  // ADD_FUNCTION(exports, checkFramebufferStatus);
  ADD_FUNCTION(exports, clear);
  ADD_FUNCTION(exports, clearColor);
  ADD_FUNCTION(exports, clearDepth);
  // ADD_FUNCTION(exports, clearStencil);
  // ADD_FUNCTION(exports, colorMask);
  ADD_FUNCTION(exports, compileShader);
  // ADD_FUNCTION(exports, compressedTexImage2D);
  // ADD_FUNCTION(exports, compressedTexSubImage2D);
  // ADD_FUNCTION(exports, copyTexImage2D);
  // ADD_FUNCTION(exports, copyTexSubImage2D);
  ADD_FUNCTION(exports, createBuffer); // genBuffers
  ADD_FUNCTION(exports, createProgram);
  ADD_FUNCTION(exports, createShader);
  ADD_FUNCTION(exports, createTexture); //genTextures
  // ADD_FUNCTION(exports, cullFace);
  // ADD_FUNCTION(exports, deleteBuffers);
  // ADD_FUNCTION(exports, deleteFramebuffers);
  // ADD_FUNCTION(exports, deleteProgram);
  // ADD_FUNCTION(exports, deleteRenderbuffers);
  // ADD_FUNCTION(exports, deleteShader);
  ADD_FUNCTION(exports, deleteTexture); //deleteTextures
  ADD_FUNCTION(exports, depthFunc);
  // ADD_FUNCTION(exports, depthMask);
  // ADD_FUNCTION(exports, depthRangef);
  // ADD_FUNCTION(exports, detachShader);
  ADD_FUNCTION(exports, disable);
  ADD_FUNCTION(exports, disableVertexAttribArray);
  ADD_FUNCTION(exports, drawArrays);
  ADD_FUNCTION(exports, drawElements);
  ADD_FUNCTION(exports, enable);
  ADD_FUNCTION(exports, enableVertexAttribArray);
  ADD_FUNCTION(exports, finish);
  ADD_FUNCTION(exports, flush);
  // ADD_FUNCTION(exports, framebufferRenderbuffer);
  // ADD_FUNCTION(exports, framebufferTexture2D);
  // ADD_FUNCTION(exports, frontFace);
  ADD_FUNCTION(exports, generateMipmap);
  // ADD_FUNCTION(exports, genFramebuffers);
  // ADD_FUNCTION(exports, genRenderbuffers);
  // ADD_FUNCTION(exports, getActiveAttrib);
  // ADD_FUNCTION(exports, getActiveUniform);
  // ADD_FUNCTION(exports, getAttachedShaders);
  ADD_FUNCTION(exports, getAttribLocation);
  // ADD_FUNCTION(exports, getBooleanv);
  // ADD_FUNCTION(exports, getBufferParameteriv);
  ADD_FUNCTION(exports, getError);
  // ADD_FUNCTION(exports, getFloatv);
  // ADD_FUNCTION(exports, getFramebufferAttachmentParameteriv);
  // ADD_FUNCTION(exports, getIntegerv);
  ADD_FUNCTION(exports, getProgramParameter); // getProgramiv
  // ADD_FUNCTION(exports, getProgramInfoLog);
  // ADD_FUNCTION(exports, getRenderbufferParameteriv);
  ADD_FUNCTION(exports, getShaderParameter); // getShaderiv
  ADD_FUNCTION(exports, getShaderInfoLog);
  // ADD_FUNCTION(exports, getShaderPrecisionFormat);
  // ADD_FUNCTION(exports, getShaderSource);
  ADD_FUNCTION(exports, getString);
  // ADD_FUNCTION(exports, getTexParameterfv);
  // ADD_FUNCTION(exports, getTexParameteriv);
  // ADD_FUNCTION(exports, getUniformfv);
  // ADD_FUNCTION(exports, getUniformiv);
  ADD_FUNCTION(exports, getUniformLocation);
  // ADD_FUNCTION(exports, getVertexAttribfv);
  // ADD_FUNCTION(exports, getVertexAttribiv);
  // ADD_FUNCTION(exports, getVertexAttribPointerv);
  // ADD_FUNCTION(exports, hint);
  // ADD_FUNCTION(exports, isBuffer);
  // ADD_FUNCTION(exports, isEnabled);
  // ADD_FUNCTION(exports, isFramebuffer);
  // ADD_FUNCTION(exports, isProgram);
  // ADD_FUNCTION(exports, isRenderbuffer);
  // ADD_FUNCTION(exports, isShader);
  // ADD_FUNCTION(exports, isTexture);
  // ADD_FUNCTION(exports, lineWidth);
  ADD_FUNCTION(exports, linkProgram);
  // ADD_FUNCTION(exports, pixelStorei);
  // ADD_FUNCTION(exports, polygonOffset);
  // ADD_FUNCTION(exports, readPixels);
  // ADD_FUNCTION(exports, releaseShaderCompiler);
  // ADD_FUNCTION(exports, renderbufferStorage);
  // ADD_FUNCTION(exports, sampleCoverage);
  // ADD_FUNCTION(exports, scissor);
  // ADD_FUNCTION(exports, shaderBinary);
  ADD_FUNCTION(exports, shaderSource);
  // ADD_FUNCTION(exports, stencilFunc);
  // ADD_FUNCTION(exports, stencilFuncSeparate);
  // ADD_FUNCTION(exports, stencilMask);
  // ADD_FUNCTION(exports, stencilMaskSeparate);
  // ADD_FUNCTION(exports, stencilOp);
  // ADD_FUNCTION(exports, stencilOpSeparate);
  ADD_FUNCTION(exports, texImage2D);
  // ADD_FUNCTION(exports, texParameterf);
  // ADD_FUNCTION(exports, texParameterfv);
  ADD_FUNCTION(exports, texParameteri);
  // ADD_FUNCTION(exports, texParameteriv);
  // ADD_FUNCTION(exports, texSubImage2D);
  // ADD_FUNCTION(exports, uniform1f);
  // ADD_FUNCTION(exports, uniform1fv);
  // ADD_FUNCTION(exports, uniform1i);
  // ADD_FUNCTION(exports, uniform1iv);
  // ADD_FUNCTION(exports, uniform2f);
  // ADD_FUNCTION(exports, uniform2fv);
  // ADD_FUNCTION(exports, uniform2i);
  // ADD_FUNCTION(exports, uniform2iv);
  // ADD_FUNCTION(exports, uniform3f);
  // ADD_FUNCTION(exports, uniform3fv);
  // ADD_FUNCTION(exports, uniform3i);
  // ADD_FUNCTION(exports, uniform3iv);
  // ADD_FUNCTION(exports, uniform4f);
  // ADD_FUNCTION(exports, uniform4fv);
  // ADD_FUNCTION(exports, uniform4i);
  // ADD_FUNCTION(exports, uniform4iv);
  // ADD_FUNCTION(exports, uniformMatrix2fv);
  // ADD_FUNCTION(exports, uniformMatrix3fv);
  ADD_FUNCTION(exports, uniformMatrix4fv);
  ADD_FUNCTION(exports, useProgram);
  // ADD_FUNCTION(exports, validateProgram);
  // ADD_FUNCTION(exports, vertexAttrib1f);
  // ADD_FUNCTION(exports, vertexAttrib1fv);
  // ADD_FUNCTION(exports, vertexAttrib2f);
  // ADD_FUNCTION(exports, vertexAttrib2fv);
  // ADD_FUNCTION(exports, vertexAttrib3f);
  // ADD_FUNCTION(exports, vertexAttrib3fv);
  // ADD_FUNCTION(exports, vertexAttrib4f);
  // ADD_FUNCTION(exports, vertexAttrib4fv);
  ADD_FUNCTION(exports, vertexAttribPointer);
  ADD_FUNCTION(exports, viewport);

  return exports;
}

NODE_API_MODULE(sdl2, InitModule);
