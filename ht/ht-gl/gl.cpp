#include "napi.h"

#include <GLES3/gl3.h>

using namespace Napi;

void activeTexture(const CallbackInfo &info) {
  glActiveTexture(info[0].As<Number>());
}

void attachShader(const CallbackInfo &info) {
  glAttachShader(info[0].As<Number>(), info[1].As<Number>());
}

void bindAttribLocation(const CallbackInfo &info) {
  glBindAttribLocation(info[0].As<Number>(), info[1].As<Number>(),
                       info[2].As<String>().Utf8Value().c_str());
}

void bindBuffer(const CallbackInfo &info) {
  glBindBuffer(info[0].As<Number>(), info[1].As<Number>());
}

void bindFramebuffer(const CallbackInfo &info) {
  glBindFramebuffer(info[0].As<Number>(), info[1].As<Number>());
}

void bindRenderbuffer(const CallbackInfo &info) {
  glBindRenderbuffer(info[0].As<Number>(), info[1].As<Number>());
}

void bindTexture(const CallbackInfo &info) {
  glBindTexture(info[0].As<Number>(), info[1].As<Number>());
}

void blendColor(const CallbackInfo &info) {
  glBlendColor(info[0].As<Number>(), info[1].As<Number>(), info[2].As<Number>(),
               info[3].As<Number>());
}

void blendEquation(const CallbackInfo &info) {
  glBlendEquation(info[0].As<Number>());
}

void blendEquationSeparate(const CallbackInfo &info) {
  glBlendEquationSeparate(info[0].As<Number>(), info[1].As<Number>());
}

void blendFunc(const CallbackInfo &info) {
  glBlendFunc(info[0].As<Number>(), info[1].As<Number>());
}

void blendFuncSeparate(const CallbackInfo &info) {
  glBlendFuncSeparate(info[0].As<Number>(), info[1].As<Number>(),
                      info[2].As<Number>(), info[3].As<Number>());
}

void bufferData(const CallbackInfo &info) {
  ArrayBuffer buffer = info[1].As<TypedArray>().ArrayBuffer();
  glBufferData(info[0].As<Number>(), buffer.ByteLength(), buffer.Data(),
               info[2].As<Number>());
}

void bufferSubData(const CallbackInfo &info) {
  ArrayBuffer buffer = info[2].As<TypedArray>().ArrayBuffer();
  glBufferSubData(info[0].As<Number>(), info[1].As<Number>(),
                  buffer.ByteLength(), buffer.Data());
}

Value checkFramebufferStatus(const CallbackInfo &info) {
  GLenum status = glCheckFramebufferStatus(info[0].As<Number>());
  return Number::New(info.Env(), status);
}

void clear(const CallbackInfo &info) { glClear(info[0].As<Number>()); }

void clearColor(const CallbackInfo &info) {
  glClearColor(info[0].As<Number>(), info[1].As<Number>(), info[2].As<Number>(),
               info[3].As<Number>());
}

void clearDepth(const CallbackInfo &info) {
  glClearDepthf(info[0].As<Number>());
}

void clearStencil(const CallbackInfo &info) {
  glClearStencil(info[0].As<Number>());
}

void colorMask(const CallbackInfo &info) {
  glColorMask(info[0].As<Boolean>(), info[1].As<Boolean>(),
              info[2].As<Boolean>(), info[3].As<Boolean>());
}

void compileShader(const CallbackInfo &info) {
  glCompileShader(info[0].As<Number>());
}

void copyTexImage2D(const CallbackInfo &info) {
  glCopyTexImage2D(info[0].As<Number>(), info[1].As<Number>(),
                   info[2].As<Number>(), info[3].As<Number>(),
                   info[4].As<Number>(), info[5].As<Number>(),
                   info[6].As<Number>(), info[7].As<Number>());
}

void copyTexSubImage2D(const CallbackInfo &info) {
  glCopyTexSubImage2D(info[0].As<Number>(), info[1].As<Number>(),
                      info[2].As<Number>(), info[3].As<Number>(),
                      info[4].As<Number>(), info[5].As<Number>(),
                      info[6].As<Number>(), info[7].As<Number>());
}

Value createBuffer(const CallbackInfo &info) {
  GLuint buffer;
  glGenBuffers(1, &buffer);
  return Number::New(info.Env(), buffer);
}

Value createFramebuffer(const CallbackInfo &info) {
  GLuint buffer;
  glGenFramebuffers(1, &buffer);
  return Number::New(info.Env(), buffer);
}

Value createProgram(const CallbackInfo &info) {
  return Number::New(info.Env(), glCreateProgram());
}

Value createRenderbuffer(const CallbackInfo &info) {
  GLuint buffer;
  glGenRenderbuffers(1, &buffer);
  return Number::New(info.Env(), buffer);
}

Value createShader(const CallbackInfo &info) {
  return Number::New(info.Env(), glCreateShader(info[0].As<Number>()));
}

Value createTexture(const CallbackInfo &info) {
  GLuint texture;
  glGenTextures(1, &texture);
  return Number::New(info.Env(), texture);
}

void cullFace(const CallbackInfo &info) { glCullFace(info[0].As<Number>()); }

void deleteBuffer(const CallbackInfo &info) {
  GLuint buffer = info[0].As<Number>();
  glDeleteBuffers(1, &buffer);
}

void deleteFramebuffer(const CallbackInfo &info) {
  GLuint buffer = info[0].As<Number>();
  glDeleteFramebuffers(1, &buffer);
}

void deleteProgram(const CallbackInfo &info) {
  glDeleteProgram(info[0].As<Number>());
}

void deleteRenderbuffer(const CallbackInfo &info) {
  GLuint buffer = info[0].As<Number>();
  glDeleteRenderbuffers(1, &buffer);
}

void deleteShader(const CallbackInfo &info) {
  glDeleteShader(info[0].As<Number>());
}

void deleteTexture(const CallbackInfo &info) {
  GLuint buffer = info[0].As<Number>();
  glDeleteTextures(1, &buffer);
}

void depthFunc(const CallbackInfo &info) { glDepthFunc(info[0].As<Number>()); }

void depthMask(const CallbackInfo &info) { glDepthMask(info[0].As<Boolean>()); }

void depthRange(const CallbackInfo &info) {
  glDepthRangef(info[0].As<Number>(), info[1].As<Number>());
}

void detachShader(const CallbackInfo &info) {
  glDetachShader(info[0].As<Number>(), info[2].As<Number>());
}

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

void framebufferRenderbuffer(const CallbackInfo &info) {
  glFramebufferRenderbuffer(info[0].As<Number>(), info[1].As<Number>(),
                            info[2].As<Number>(), info[3].As<Number>());
}

void framebufferTexture2D(const CallbackInfo &info) {
  glFramebufferTexture2D(info[0].As<Number>(), info[1].As<Number>(),
                         info[2].As<Number>(), info[3].As<Number>(),
                         info[4].As<Number>());
}

void frontFace(const CallbackInfo &info) { glFrontFace(info[0].As<Number>()); }

void generateMipmap(const CallbackInfo &info) {
  glGenerateMipmap(info[0].As<Number>());
}

Value getAttribLocation(const CallbackInfo &info) {
  GLint loc = glGetAttribLocation(info[0].As<Number>(),
                                  info[1].As<String>().Utf8Value().c_str());
  return Number::New(info.Env(), loc);
}

Value getError(const CallbackInfo &info) {
  return Number::New(info.Env(), glGetError());
}

Value getProgramParameter(const CallbackInfo &info) {
  GLint param;
  glGetProgramiv(info[0].As<Number>(), info[1].As<Number>(), &param);
  return Number::New(info.Env(), param);
}

Value getShaderParameter(const CallbackInfo &info) {
  GLint param;
  glGetShaderiv(info[0].As<Number>(), info[1].As<Number>(), &param);
  return Number::New(info.Env(), param);
}

Value getShaderInfoLog(const CallbackInfo &info) {
  GLint len;
  char info_log[1000];
  glGetShaderInfoLog(info[0].As<Number>(), 1000, &len, info_log);
  return String::New(info.Env(), info_log);
}

Value getString(const CallbackInfo &info) {
  const char *str =
      reinterpret_cast<const char *>(glGetString(info[0].As<Number>()));
  return String::New(info.Env(), str);
}

Value getUniformLocation(const CallbackInfo &info) {
  GLint location = glGetUniformLocation(
      info[0].As<Number>(), info[1].As<String>().Utf8Value().c_str());
  return Number::New(info.Env(), location);
}

void linkProgram(const CallbackInfo &info) {
  glLinkProgram(info[0].As<Number>());
}

void shaderSource(const CallbackInfo &info) {
  std::string str = info[1].As<String>().Utf8Value();
  const char *c_str = str.c_str();
  int length = strlen(c_str);
  glShaderSource(info[0].As<Number>(), 1, &c_str, &length);
}

void texImage2D(const CallbackInfo &info) {
  ArrayBuffer buffer = info[8].As<TypedArray>().ArrayBuffer();
  glTexImage2D(info[0].As<Number>(), info[1].As<Number>(), info[2].As<Number>(),
               info[3].As<Number>(), info[4].As<Number>(), info[5].As<Number>(),
               info[6].As<Number>(), info[7].As<Number>(), buffer.Data());
}

void texParameteri(const CallbackInfo &info) {
  glTexParameteri(info[0].As<Number>(), info[1].As<Number>(),
                  info[2].As<Number>());
}

void uniform1f(const CallbackInfo &info) {
  glUniform1f(info[0].As<Number>(), info[1].As<Number>());
}

void uniform1fv(const CallbackInfo &info) {
  const Float32Array value = info[1].As<Float32Array>();
  glUniform1fv(info[0].As<Number>(), value.ElementLength(), value.Data());
}

void uniform1i(const CallbackInfo &info) {
  glUniform1i(info[0].As<Number>(), info[1].As<Number>());
}

void uniform1iv(const CallbackInfo &info) {
  const Int32Array value = info[1].As<Int32Array>();
  glUniform1iv(info[0].As<Number>(), value.ElementLength(), value.Data());
}

void uniform2f(const CallbackInfo &info) {
  glUniform2f(info[0].As<Number>(), info[1].As<Number>(), info[2].As<Number>());
}

void uniform2fv(const CallbackInfo &info) {
  const Float32Array value = info[1].As<Float32Array>();
  glUniform2fv(info[0].As<Number>(), value.ElementLength() / 2, value.Data());
}

void uniform2i(const CallbackInfo &info) {
  glUniform2i(info[0].As<Number>(), info[1].As<Number>(), info[2].As<Number>());
}

void uniform2iv(const CallbackInfo &info) {
  const Int32Array value = info[1].As<Int32Array>();
  glUniform2iv(info[0].As<Number>(), value.ElementLength() / 2, value.Data());
}

void uniform3f(const CallbackInfo &info) {
  glUniform3f(info[0].As<Number>(), info[1].As<Number>(), info[2].As<Number>(),
              info[3].As<Number>());
}

void uniform3fv(const CallbackInfo &info) {
  const Float32Array value = info[1].As<Float32Array>();
  glUniform3fv(info[0].As<Number>(), value.ElementLength() / 3, value.Data());
}

void uniform3i(const CallbackInfo &info) {
  glUniform3i(info[0].As<Number>(), info[1].As<Number>(), info[2].As<Number>(),
              info[3].As<Number>());
}

void uniform3iv(const CallbackInfo &info) {
  const Int32Array value = info[1].As<Int32Array>();
  glUniform3iv(info[0].As<Number>(), value.ElementLength() / 3, value.Data());
}

void uniform4f(const CallbackInfo &info) {
  glUniform4f(info[0].As<Number>(), info[1].As<Number>(), info[2].As<Number>(),
              info[3].As<Number>(), info[4].As<Number>());
}

void uniform4fv(const CallbackInfo &info) {
  const Float32Array value = info[1].As<Float32Array>();
  glUniform4fv(info[0].As<Number>(), value.ElementLength() / 4, value.Data());
}

void uniform4i(const CallbackInfo &info) {
  glUniform4i(info[0].As<Number>(), info[1].As<Number>(), info[2].As<Number>(),
              info[3].As<Number>(), info[4].As<Number>());
}

void uniform4iv(const CallbackInfo &info) {
  const Int32Array value = info[1].As<Int32Array>();
  glUniform4iv(info[0].As<Number>(), value.ElementLength() / 4, value.Data());
}

void uniformMatrix2fv(const CallbackInfo &info) {
  const Float32Array array = info[2].As<Float32Array>();
  glUniformMatrix2fv(info[0].As<Number>(), array.ElementLength() / 4,
                     info[1].As<Boolean>(), array.Data());
}

void uniformMatrix3fv(const CallbackInfo &info) {
  const Float32Array array = info[2].As<Float32Array>();
  glUniformMatrix3fv(info[0].As<Number>(), array.ElementLength() / 9,
                     info[1].As<Boolean>(), array.Data());
}

void uniformMatrix4fv(const CallbackInfo &info) {
  const Float32Array array = info[2].As<Float32Array>();
  glUniformMatrix4fv(info[0].As<Number>(), array.ElementLength() / 16,
                     info[1].As<Boolean>(), array.Data());
}

void useProgram(const CallbackInfo &info) {
  glUseProgram(info[0].As<Number>());
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
  // WebGLRenderingContext APIs. see
  // https://developer.mozilla.org/en-US/docs/Web/API/WebGLRenderingContext
  ADD_FUNCTION(exports, activeTexture);
  ADD_FUNCTION(exports, attachShader);
  ADD_FUNCTION(exports, bindAttribLocation);
  ADD_FUNCTION(exports, bindBuffer);
  ADD_FUNCTION(exports, bindFramebuffer);
  ADD_FUNCTION(exports, bindRenderbuffer);
  ADD_FUNCTION(exports, bindTexture);
  ADD_FUNCTION(exports, blendColor);
  ADD_FUNCTION(exports, blendEquation);
  ADD_FUNCTION(exports, blendEquationSeparate);
  ADD_FUNCTION(exports, blendFunc);
  ADD_FUNCTION(exports, blendFuncSeparate);
  ADD_FUNCTION(exports, bufferData);
  ADD_FUNCTION(exports, bufferSubData);
  ADD_FUNCTION(exports, checkFramebufferStatus);
  ADD_FUNCTION(exports, clear);
  ADD_FUNCTION(exports, clearColor);
  ADD_FUNCTION(exports, clearDepth);
  ADD_FUNCTION(exports, clearStencil);
  ADD_FUNCTION(exports, colorMask);
  // ADD_FUNCTION(exports, commit); // WebGL experimental API
  ADD_FUNCTION(exports, compileShader);
  // ADD_FUNCTION(exports, compressedTexImage2D);  // WebGL extension
  // ADD_FUNCTION(exports, compressedTexSubImage2D); // WebGL extension
  ADD_FUNCTION(exports, copyTexImage2D);
  ADD_FUNCTION(exports, copyTexSubImage2D);
  ADD_FUNCTION(exports, createBuffer);      // glGenBuffers
  ADD_FUNCTION(exports, createFramebuffer); // glGenFramebuffers
  ADD_FUNCTION(exports, createProgram);
  ADD_FUNCTION(exports, createRenderbuffer); // glGenRenderbuffers
  ADD_FUNCTION(exports, createShader);
  ADD_FUNCTION(exports, createTexture); // glGenTextures
  ADD_FUNCTION(exports, cullFace);
  ADD_FUNCTION(exports, deleteBuffer);      // glDeleteBuffers
  ADD_FUNCTION(exports, deleteFramebuffer); // glDeleteFramebuffers
  ADD_FUNCTION(exports, deleteProgram);
  ADD_FUNCTION(exports, deleteRenderbuffer); // glDeleteRenderbuffers
  ADD_FUNCTION(exports, deleteShader);
  ADD_FUNCTION(exports, deleteTexture); // glDeleteTextures
  ADD_FUNCTION(exports, depthFunc);
  ADD_FUNCTION(exports, depthMask);
  ADD_FUNCTION(exports, depthRange); // glDepthRangef
  ADD_FUNCTION(exports, detachShader);
  ADD_FUNCTION(exports, disable);
  ADD_FUNCTION(exports, disableVertexAttribArray);
  ADD_FUNCTION(exports, drawArrays);
  ADD_FUNCTION(exports, drawElements);
  ADD_FUNCTION(exports, enable);
  ADD_FUNCTION(exports, enableVertexAttribArray);
  ADD_FUNCTION(exports, finish);
  ADD_FUNCTION(exports, flush);
  ADD_FUNCTION(exports, framebufferRenderbuffer);
  ADD_FUNCTION(exports, framebufferTexture2D);
  ADD_FUNCTION(exports, frontFace);
  ADD_FUNCTION(exports, generateMipmap);
  // ADD_FUNCTION(exports, getActiveAttrib);
  // ADD_FUNCTION(exports, getActiveUniform);
  // ADD_FUNCTION(exports, getAttachedShaders);
  ADD_FUNCTION(exports, getAttribLocation);
  // ADD_FUNCTION(exports, getBooleanv); // ?
  // ADD_FUNCTION(exports, getBufferParameteri); // glGetBufferParameteriv
  // ADD_FUNCTION(exports, getContextAttributes);
  ADD_FUNCTION(exports, getError);
  // ADD_FUNCTION(exports, getExtension);
  // ADD_FUNCTION(exports, getFloatv); // ?
  // ADD_FUNCTION(exports, getFramebufferAttachmentParameteri); // glGetFramebufferAttachmentParameteriv
  // ADD_FUNCTION(exports, getIntegerv); // ?
  // ADD_FUNCTION(exports, getParameter);
  // ADD_FUNCTION(exports, getProgramInfoLog);
  ADD_FUNCTION(exports, getProgramParameter); // glGetProgramiv
  // ADD_FUNCTION(exports, getRenderbufferParameter); // glGetRenderbufferParameteriv
  ADD_FUNCTION(exports, getShaderInfoLog);
  ADD_FUNCTION(exports, getShaderParameter); // glGetShaderiv
  // ADD_FUNCTION(exports, getShaderPrecisionFormat);
  // ADD_FUNCTION(exports, getShaderSource);
  // ADD_FUNCTION(exports, getSupportedExtensions);
  ADD_FUNCTION(exports, getString); // ?
  // ADD_FUNCTION(exports, getTexParameter); // glGetTexParameterfv glGetTexParameteriv
  // ADD_FUNCTION(exports, getUniform); // glGetUniformfv glGetUniformiv
  ADD_FUNCTION(exports, getUniformLocation);
  // ADD_FUNCTION(exports, getVertexAttrib); // glGetVertexAttribfv glGetVertexAttribiv
  // ADD_FUNCTION(exports, getVertexAttribOffset); // glGetVertexAttribPointerv
  // ADD_FUNCTION(exports, hint);
  // ADD_FUNCTION(exports, isBuffer);
  // ADD_FUNCTION(exports, isContextLost);
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
  // ADD_FUNCTION(exports, releaseShaderCompiler); // ?
  // ADD_FUNCTION(exports, renderbufferStorage);
  // ADD_FUNCTION(exports, sampleCoverage);
  // ADD_FUNCTION(exports, scissor);
  // ADD_FUNCTION(exports, shaderBinary); // ?
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
  ADD_FUNCTION(exports, uniform1f);
  ADD_FUNCTION(exports, uniform1fv); // uniform**v support TypedArray, do not support Array
  ADD_FUNCTION(exports, uniform1i);
  ADD_FUNCTION(exports, uniform1iv);
  ADD_FUNCTION(exports, uniform2f);
  ADD_FUNCTION(exports, uniform2fv);
  ADD_FUNCTION(exports, uniform2i);
  ADD_FUNCTION(exports, uniform2iv);
  ADD_FUNCTION(exports, uniform3f);
  ADD_FUNCTION(exports, uniform3fv);
  ADD_FUNCTION(exports, uniform3i);
  ADD_FUNCTION(exports, uniform3iv);
  ADD_FUNCTION(exports, uniform4f);
  ADD_FUNCTION(exports, uniform4fv);
  ADD_FUNCTION(exports, uniform4i);
  ADD_FUNCTION(exports, uniform4iv);
  ADD_FUNCTION(exports, uniformMatrix2fv);
  ADD_FUNCTION(exports, uniformMatrix3fv);
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
