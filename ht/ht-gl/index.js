const gl_bindings = require('bindings')('ht-gl');

let GL = {};

GL.debug = false;

// Constants
GL.DEPTH_BUFFER_BIT               = 0x00000100;
GL.STENCIL_BUFFER_BIT             = 0x00000400;
GL.COLOR_BUFFER_BIT               = 0x00004000;
GL.FALSE                          = 0;
GL.TRUE                           = 1;
GL.POINTS                         = 0x0000;
GL.LINES                          = 0x0001;
GL.LINE_LOOP                      = 0x0002;
GL.LINE_STRIP                     = 0x0003;
GL.TRIANGLES                      = 0x0004;
GL.TRIANGLE_STRIP                 = 0x0005;
GL.TRIANGLE_FAN                   = 0x0006;
GL.ZERO                           = 0;
GL.ONE                            = 1;
GL.SRC_COLOR                      = 0x0300;
GL.ONE_MINUS_SRC_COLOR            = 0x0301;
GL.SRC_ALPHA                      = 0x0302;
GL.ONE_MINUS_SRC_ALPHA            = 0x0303;
GL.DST_ALPHA                      = 0x0304;
GL.ONE_MINUS_DST_ALPHA            = 0x0305;
GL.DST_COLOR                      = 0x0306;
GL.ONE_MINUS_DST_COLOR            = 0x0307;
GL.SRC_ALPHA_SATURATE             = 0x0308;
GL.FUNC_ADD                       = 0x8006;
GL.BLEND_EQUATION                 = 0x8009;
GL.BLEND_EQUATION_RGB             = 0x8009;
GL.BLEND_EQUATION_ALPHA           = 0x883D;
GL.FUNC_SUBTRACT                  = 0x800A;
GL.FUNC_REVERSE_SUBTRACT          = 0x800B;
GL.BLEND_DST_RGB                  = 0x80C8;
GL.BLEND_SRC_RGB                  = 0x80C9;
GL.BLEND_DST_ALPHA                = 0x80CA;
GL.BLEND_SRC_ALPHA                = 0x80CB;
GL.CONSTANT_COLOR                 = 0x8001;
GL.ONE_MINUS_CONSTANT_COLOR       = 0x8002;
GL.CONSTANT_ALPHA                 = 0x8003;
GL.ONE_MINUS_CONSTANT_ALPHA       = 0x8004;
GL.BLEND_COLOR                    = 0x8005;
GL.ARRAY_BUFFER                   = 0x8892;
GL.ELEMENT_ARRAY_BUFFER           = 0x8893;
GL.ARRAY_BUFFER_BINDING           = 0x8894;
GL.ELEMENT_ARRAY_BUFFER_BINDING   = 0x8895;
GL.STREAM_DRAW                    = 0x88E0;
GL.STATIC_DRAW                    = 0x88E4;
GL.DYNAMIC_DRAW                   = 0x88E8;
GL.BUFFER_SIZE                    = 0x8764;
GL.BUFFER_USAGE                   = 0x8765;
GL.CURRENT_VERTEX_ATTRIB          = 0x8626;
GL.FRONT                          = 0x0404;
GL.BACK                           = 0x0405;
GL.FRONT_AND_BACK                 = 0x0408;
GL.TEXTURE_2D                     = 0x0DE1;
GL.CULL_FACE                      = 0x0B44;
GL.BLEND                          = 0x0BE2;
GL.DITHER                         = 0x0BD0;
GL.STENCIL_TEST                   = 0x0B90;
GL.DEPTH_TEST                     = 0x0B71;
GL.SCISSOR_TEST                   = 0x0C11;
GL.POLYGON_OFFSET_FILL            = 0x8037;
GL.SAMPLE_ALPHA_TO_COVERAGE       = 0x809E;
GL.SAMPLE_COVERAGE                = 0x80A0;
GL.NO_ERROR                       = 0;
GL.INVALID_ENUM                   = 0x0500;
GL.INVALID_VALUE                  = 0x0501;
GL.INVALID_OPERATION              = 0x0502;
GL.OUT_OF_MEMORY                  = 0x0505;
GL.CW                             = 0x0900;
GL.CCW                            = 0x0901;
GL.LINE_WIDTH                     = 0x0B21;
GL.ALIASED_POINT_SIZE_RANGE       = 0x846D;
GL.ALIASED_LINE_WIDTH_RANGE       = 0x846E;
GL.CULL_FACE_MODE                 = 0x0B45;
GL.FRONT_FACE                     = 0x0B46;
GL.DEPTH_RANGE                    = 0x0B70;
GL.DEPTH_WRITEMASK                = 0x0B72;
GL.DEPTH_CLEAR_VALUE              = 0x0B73;
GL.DEPTH_FUNC                     = 0x0B74;
GL.STENCIL_CLEAR_VALUE            = 0x0B91;
GL.STENCIL_FUNC                   = 0x0B92;
GL.STENCIL_FAIL                   = 0x0B94;
GL.STENCIL_PASS_DEPTH_FAIL        = 0x0B95;
GL.STENCIL_PASS_DEPTH_PASS        = 0x0B96;
GL.STENCIL_REF                    = 0x0B97;
GL.STENCIL_VALUE_MASK             = 0x0B93;
GL.STENCIL_WRITEMASK              = 0x0B98;
GL.STENCIL_BACK_FUNC              = 0x8800;
GL.STENCIL_BACK_FAIL              = 0x8801;
GL.STENCIL_BACK_PASS_DEPTH_FAIL   = 0x8802;
GL.STENCIL_BACK_PASS_DEPTH_PASS   = 0x8803;
GL.STENCIL_BACK_REF               = 0x8CA3;
GL.STENCIL_BACK_VALUE_MASK        = 0x8CA4;
GL.STENCIL_BACK_WRITEMASK         = 0x8CA5;
GL.VIEWPORT                       = 0x0BA2;
GL.SCISSOR_BOX                    = 0x0C10;
GL.COLOR_CLEAR_VALUE              = 0x0C22;
GL.COLOR_WRITEMASK                = 0x0C23;
GL.UNPACK_ALIGNMENT               = 0x0CF5;
GL.PACK_ALIGNMENT                 = 0x0D05;
GL.MAX_TEXTURE_SIZE               = 0x0D33;
GL.MAX_VIEWPORT_DIMS              = 0x0D3A;
GL.SUBPIXEL_BITS                  = 0x0D50;
GL.RED_BITS                       = 0x0D52;
GL.GREEN_BITS                     = 0x0D53;
GL.BLUE_BITS                      = 0x0D54;
GL.ALPHA_BITS                     = 0x0D55;
GL.DEPTH_BITS                     = 0x0D56;
GL.STENCIL_BITS                   = 0x0D57;
GL.POLYGON_OFFSET_UNITS           = 0x2A00;
GL.POLYGON_OFFSET_FACTOR          = 0x8038;
GL.TEXTURE_BINDING_2D             = 0x8069;
GL.SAMPLE_BUFFERS                 = 0x80A8;
GL.SAMPLES                        = 0x80A9;
GL.SAMPLE_COVERAGE_VALUE          = 0x80AA;
GL.SAMPLE_COVERAGE_INVERT         = 0x80AB;
GL.NUM_COMPRESSED_TEXTURE_FORMATS = 0x86A2;
GL.COMPRESSED_TEXTURE_FORMATS     = 0x86A3;
GL.DONT_CARE                      = 0x1100;
GL.FASTEST                        = 0x1101;
GL.NICEST                         = 0x1102;
GL.GENERATE_MIPMAP_HINT           = 0x8192;
GL.BYTE                           = 0x1400;
GL.UNSIGNED_BYTE                  = 0x1401;
GL.SHORT                          = 0x1402;
GL.UNSIGNED_SHORT                 = 0x1403;
GL.INT                            = 0x1404;
GL.UNSIGNED_INT                   = 0x1405;
GL.FLOAT                          = 0x1406;
GL.FIXED                          = 0x140C;
GL.DEPTH_COMPONENT                = 0x1902;
GL.ALPHA                          = 0x1906;
GL.RGB                            = 0x1907;
GL.RGBA                           = 0x1908;
GL.LUMINANCE                      = 0x1909;
GL.LUMINANCE_ALPHA                = 0x190A;
GL.UNSIGNED_SHORT_4_4_4_4         = 0x8033;
GL.UNSIGNED_SHORT_5_5_5_1         = 0x8034;
GL.UNSIGNED_SHORT_5_6_5           = 0x8363;
GL.FRAGMENT_SHADER                = 0x8B30;
GL.VERTEX_SHADER                  = 0x8B31;
GL.MAX_VERTEX_ATTRIBS             = 0x8869;
GL.MAX_VERTEX_UNIFORM_VECTORS     = 0x8DFB;
GL.MAX_VARYING_VECTORS            = 0x8DFC;
GL.MAX_COMBINED_TEXTURE_IMAGE_UNITS = 0x8B4D;
GL.MAX_VERTEX_TEXTURE_IMAGE_UNITS = 0x8B4C;
GL.MAX_TEXTURE_IMAGE_UNITS        = 0x8872;
GL.MAX_FRAGMENT_UNIFORM_VECTORS   = 0x8DFD;
GL.SHADER_TYPE                    = 0x8B4F;
GL.DELETE_STATUS                  = 0x8B80;
GL.LINK_STATUS                    = 0x8B82;
GL.VALIDATE_STATUS                = 0x8B83;
GL.ATTACHED_SHADERS               = 0x8B85;
GL.ACTIVE_UNIFORMS                = 0x8B86;
GL.ACTIVE_UNIFORM_MAX_LENGTH      = 0x8B87;
GL.ACTIVE_ATTRIBUTES              = 0x8B89;
GL.ACTIVE_ATTRIBUTE_MAX_LENGTH    = 0x8B8A;
GL.SHADING_LANGUAGE_VERSION       = 0x8B8C;
GL.CURRENT_PROGRAM                = 0x8B8D;
GL.NEVER                          = 0x0200;
GL.LESS                           = 0x0201;
GL.EQUAL                          = 0x0202;
GL.LEQUAL                         = 0x0203;
GL.GREATER                        = 0x0204;
GL.NOTEQUAL                       = 0x0205;
GL.GEQUAL                         = 0x0206;
GL.ALWAYS                         = 0x0207;
GL.KEEP                           = 0x1E00;
GL.REPLACE                        = 0x1E01;
GL.INCR                           = 0x1E02;
GL.DECR                           = 0x1E03;
GL.INVERT                         = 0x150A;
GL.INCR_WRAP                      = 0x8507;
GL.DECR_WRAP                      = 0x8508;
GL.VENDOR                         = 0x1F00;
GL.RENDERER                       = 0x1F01;
GL.VERSION                        = 0x1F02;
GL.EXTENSIONS                     = 0x1F03;
GL.NEAREST                        = 0x2600;
GL.LINEAR                         = 0x2601;
GL.NEAREST_MIPMAP_NEAREST         = 0x2700;
GL.LINEAR_MIPMAP_NEAREST          = 0x2701;
GL.NEAREST_MIPMAP_LINEAR          = 0x2702;
GL.LINEAR_MIPMAP_LINEAR           = 0x2703;
GL.TEXTURE_MAG_FILTER             = 0x2800;
GL.TEXTURE_MIN_FILTER             = 0x2801;
GL.TEXTURE_WRAP_S                 = 0x2802;
GL.TEXTURE_WRAP_T                 = 0x2803;
GL.TEXTURE                        = 0x1702;
GL.TEXTURE_CUBE_MAP               = 0x8513;
GL.TEXTURE_BINDING_CUBE_MAP       = 0x8514;
GL.TEXTURE_CUBE_MAP_POSITIVE_X    = 0x8515;
GL.TEXTURE_CUBE_MAP_NEGATIVE_X    = 0x8516;
GL.TEXTURE_CUBE_MAP_POSITIVE_Y    = 0x8517;
GL.TEXTURE_CUBE_MAP_NEGATIVE_Y    = 0x8518;
GL.TEXTURE_CUBE_MAP_POSITIVE_Z    = 0x8519;
GL.TEXTURE_CUBE_MAP_NEGATIVE_Z    = 0x851A;
GL.MAX_CUBE_MAP_TEXTURE_SIZE      = 0x851C;
GL.TEXTURE0                       = 0x84C0;
GL.TEXTURE1                       = 0x84C1;
GL.TEXTURE2                       = 0x84C2;
GL.TEXTURE3                       = 0x84C3;
GL.TEXTURE4                       = 0x84C4;
GL.TEXTURE5                       = 0x84C5;
GL.TEXTURE6                       = 0x84C6;
GL.TEXTURE7                       = 0x84C7;
GL.TEXTURE8                       = 0x84C8;
GL.TEXTURE9                       = 0x84C9;
GL.TEXTURE10                      = 0x84CA;
GL.TEXTURE11                      = 0x84CB;
GL.TEXTURE12                      = 0x84CC;
GL.TEXTURE13                      = 0x84CD;
GL.TEXTURE14                      = 0x84CE;
GL.TEXTURE15                      = 0x84CF;
GL.TEXTURE16                      = 0x84D0;
GL.TEXTURE17                      = 0x84D1;
GL.TEXTURE18                      = 0x84D2;
GL.TEXTURE19                      = 0x84D3;
GL.TEXTURE20                      = 0x84D4;
GL.TEXTURE21                      = 0x84D5;
GL.TEXTURE22                      = 0x84D6;
GL.TEXTURE23                      = 0x84D7;
GL.TEXTURE24                      = 0x84D8;
GL.TEXTURE25                      = 0x84D9;
GL.TEXTURE26                      = 0x84DA;
GL.TEXTURE27                      = 0x84DB;
GL.TEXTURE28                      = 0x84DC;
GL.TEXTURE29                      = 0x84DD;
GL.TEXTURE30                      = 0x84DE;
GL.TEXTURE31                      = 0x84DF;
GL.ACTIVE_TEXTURE                 = 0x84E0;
GL.REPEAT                         = 0x2901;
GL.CLAMP_TO_EDGE                  = 0x812F;
GL.MIRRORED_REPEAT                = 0x8370;
GL.FLOAT_VEC2                     = 0x8B50;
GL.FLOAT_VEC3                     = 0x8B51;
GL.FLOAT_VEC4                     = 0x8B52;
GL.INT_VEC2                       = 0x8B53;
GL.INT_VEC3                       = 0x8B54;
GL.INT_VEC4                       = 0x8B55;
GL.BOOL                           = 0x8B56;
GL.BOOL_VEC2                      = 0x8B57;
GL.BOOL_VEC3                      = 0x8B58;
GL.BOOL_VEC4                      = 0x8B59;
GL.FLOAT_MAT2                     = 0x8B5A;
GL.FLOAT_MAT3                     = 0x8B5B;
GL.FLOAT_MAT4                     = 0x8B5C;
GL.SAMPLER_2D                     = 0x8B5E;
GL.SAMPLER_CUBE                   = 0x8B60;
GL.VERTEX_ATTRIB_ARRAY_ENABLED    = 0x8622;
GL.VERTEX_ATTRIB_ARRAY_SIZE       = 0x8623;
GL.VERTEX_ATTRIB_ARRAY_STRIDE     = 0x8624;
GL.VERTEX_ATTRIB_ARRAY_TYPE       = 0x8625;
GL.VERTEX_ATTRIB_ARRAY_NORMALIZED = 0x886A;
GL.VERTEX_ATTRIB_ARRAY_POINTER    = 0x8645;
GL.VERTEX_ATTRIB_ARRAY_BUFFER_BINDING = 0x889F;
GL.IMPLEMENTATION_COLOR_READ_TYPE = 0x8B9A;
GL.IMPLEMENTATION_COLOR_READ_FORMAT = 0x8B9B;
GL.COMPILE_STATUS                 = 0x8B81;
GL.INFO_LOG_LENGTH                = 0x8B84;
GL.SHADER_SOURCE_LENGTH           = 0x8B88;
GL.SHADER_COMPILER                = 0x8DFA;
GL.SHADER_BINARY_FORMATS          = 0x8DF8;
GL.NUM_SHADER_BINARY_FORMATS      = 0x8DF9;
GL.LOW_FLOAT                      = 0x8DF0;
GL.MEDIUM_FLOAT                   = 0x8DF1;
GL.HIGH_FLOAT                     = 0x8DF2;
GL.LOW_INT                        = 0x8DF3;
GL.MEDIUM_INT                     = 0x8DF4;
GL.HIGH_INT                       = 0x8DF5;
GL.FRAMEBUFFER                    = 0x8D40;
GL.RENDERBUFFER                   = 0x8D41;
GL.RGBA4                          = 0x8056;
GL.RGB5_A1                        = 0x8057;
GL.RGB565                         = 0x8D62;
GL.DEPTH_COMPONENT16              = 0x81A5;
GL.STENCIL_INDEX8                 = 0x8D48;
GL.RENDERBUFFER_WIDTH             = 0x8D42;
GL.RENDERBUFFER_HEIGHT            = 0x8D43;
GL.RENDERBUFFER_INTERNAL_FORMAT   = 0x8D44;
GL.RENDERBUFFER_RED_SIZE          = 0x8D50;
GL.RENDERBUFFER_GREEN_SIZE        = 0x8D51;
GL.RENDERBUFFER_BLUE_SIZE         = 0x8D52;
GL.RENDERBUFFER_ALPHA_SIZE        = 0x8D53;
GL.RENDERBUFFER_DEPTH_SIZE        = 0x8D54;
GL.RENDERBUFFER_STENCIL_SIZE      = 0x8D55;
GL.FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE = 0x8CD0;
GL.FRAMEBUFFER_ATTACHMENT_OBJECT_NAME = 0x8CD1;
GL.FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL = 0x8CD2;
GL.FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE = 0x8CD3;
GL.COLOR_ATTACHMENT0              = 0x8CE0;
GL.DEPTH_ATTACHMENT               = 0x8D00;
GL.STENCIL_ATTACHMENT             = 0x8D20;
GL.NONE                           = 0;
GL.FRAMEBUFFER_COMPLETE           = 0x8CD5;
GL.FRAMEBUFFER_INCOMPLETE_ATTACHMENT = 0x8CD6;
GL.FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT = 0x8CD7;
GL.FRAMEBUFFER_INCOMPLETE_DIMENSIONS = 0x8CD9;
GL.FRAMEBUFFER_UNSUPPORTED        = 0x8CDD;
GL.FRAMEBUFFER_BINDING            = 0x8CA6;
GL.RENDERBUFFER_BINDING           = 0x8CA7;
GL.MAX_RENDERBUFFER_SIZE          = 0x84E8;
GL.INVALID_FRAMEBUFFER_OPERATION  = 0x0506;

/* WebGL-specific enums */
GL.UNPACK_FLIP_Y_WEBGL            = 0x9240;
GL.UNPACK_PREMULTIPLY_ALPHA_WEBGL = 0x9241;
GL.CONTEXT_LOST_WEBGL             = 0x9242;
GL.UNPACK_COLORSPACE_CONVERSION_WEBGL = 0x9243;
GL.BROWSER_DEFAULT_WEBGL          = 0x9244;

GL.activeTexture = function() {
    if (GL.debug) {
        console.log("activeTexture");
        console.log(arguments);
    }
    return gl_bindings.activeTexture.apply(null, arguments);
};
GL.attachShader = function() {
    if (GL.debug) {
        console.log("attachShader");
        console.log(arguments);
    }
    return gl_bindings.attachShader.apply(null, arguments);
};
GL.bindAttribLocation = function() {
    if (GL.debug) {
        console.log("bindAttribLocation");
        console.log(arguments);
    }
    return gl_bindings.bindAttribLocation.apply(null, arguments);
};
GL.bindBuffer = function() {
    if (GL.debug) {
        console.log("bindBuffer");
        console.log(arguments);
    }
    return gl_bindings.bindBuffer.apply(null, arguments);
};
GL.bindFramebuffer = function() {
    if (GL.debug) {
        console.log("bindFramebuffer");
        console.log(arguments);
    }
    return gl_bindings.bindFramebuffer.apply(null, arguments);
};
GL.bindRenderbuffer = function() {
    if (GL.debug) {
        console.log("bindRenderbuffer");
        console.log(arguments);
    }
    return gl_bindings.bindRenderbuffer.apply(null, arguments);
};
GL.bindTexture = function() {
    if (GL.debug) {
        console.log("bindTexture");
        console.log(arguments);
    }
    return gl_bindings.bindTexture.apply(null, arguments);
};
GL.blendColor = function() {
    if (GL.debug) {
        console.log("blendColor");
        console.log(arguments);
    }
    return gl_bindings.blendColor.apply(null, arguments);
};
GL.blendEquation = function() {
    if (GL.debug) {
        console.log("blendEquation");
        console.log(arguments);
    }
    return gl_bindings.blendEquation.apply(null, arguments);
};
GL.blendEquationSeparate = function() {
    if (GL.debug) {
        console.log("blendEquationSeparate");
        console.log(arguments);
    }
    return gl_bindings.blendEquationSeparate.apply(null, arguments);
};
GL.blendFunc = function() {
    if (GL.debug) {
        console.log("blendFunc");
        console.log(arguments);
    }
    return gl_bindings.activeTexture.apply(null, arguments);
};
GL.blendFuncSeparate = function() {
    if (GL.debug) {
        console.log("blendFuncSeparate");
        console.log(arguments);
    }
    return gl_bindings.blendFunc.apply(null, arguments);
};
GL.bufferData = function() {
    if (GL.debug) {
        console.log("bufferData");
        console.log(arguments);
    }
    return gl_bindings.bufferData.apply(null, arguments);
};
GL.bufferSubData = function() {
    if (GL.debug) {
        console.log("bufferSubData");
        console.log(arguments);
    }
    return gl_bindings.bufferSubData.apply(null, arguments);
};
GL.checkFramebufferStatus = function() {
    if (GL.debug) {
        console.log("checkFramebufferStatus");
        console.log(arguments);
    }
    return gl_bindings.checkFramebufferStatus.apply(null, arguments);
};
GL.clear = function() {
    if (GL.debug) {
        console.log("clear");
        console.log(arguments);
    }
    return gl_bindings.clear.apply(null, arguments);
};
GL.clearColor = function() {
    if (GL.debug) {
        console.log("clearColor");
        console.log(arguments);
    }
    return gl_bindings.clearColor.apply(null, arguments);
};
GL.clearDepth = function() {
    if (GL.debug) {
        console.log("clearDepth");
        console.log(arguments);
    }
    return gl_bindings.clearDepth.apply(null, arguments);
};
GL.clearStencil = function() {
    if (GL.debug) {
        console.log("clearStencil");
        console.log(arguments);
    }
    return gl_bindings.clearStencil.apply(null, arguments);
};
GL.colorMask = function() {
    if (GL.debug) {
        console.log("colorMask");
        console.log(arguments);
    }
    return gl_bindings.colorMask.apply(null, arguments);
};
// GL.commit; // WebGL experimental API
GL.compileShader = function() {
    if (GL.debug) {
        console.log("compileShader");
        console.log(arguments);
    }
    return gl_bindings.compileShader.apply(null, arguments);
};
// GL.compressedTexImage2D;  // WebGL extension
// GL.compressedTexSubImage2D; // WebGL extension
GL.copyTexImage2D = function() {
    if (GL.debug) {
        console.log("copyTexImage2D");
        console.log(arguments);
    }
    return gl_bindings.copyTexImage2D.apply(null, arguments);
};
GL.copyTexSubImage2D = function() {
    if (GL.debug) {
        console.log("copyTexSubImage2D");
        console.log(arguments);
    }
    return gl_bindings.copyTexSubImage2D.apply(null, arguments);
};
GL.createBuffer = function() {
    if (GL.debug) {
        console.log("createBuffer");
        console.log(arguments);
    }
    return gl_bindings.createBuffer.apply(null, arguments);
};
GL.createFramebuffer = function() {
    if (GL.debug) {
        console.log("createFramebuffer");
        console.log(arguments);
    }
  return gl_bindings.createFramebuffer.apply(null, arguments);
};
GL.createProgram = function() {
    if (GL.debug) {
        console.log("createProgram");
        console.log(arguments);
    }
    return gl_bindings.createProgram.apply(null, arguments);
};
GL.createRenderbuffer = function() {
    if (GL.debug) {
        console.log("createRenderbuffer");
        console.log(arguments);
    }
    return gl_bindings.createRenderbuffer.apply(null, arguments);
};
GL.createShader = function() {
    if (GL.debug) {
        console.log("createShader");
        console.log(arguments);
    }
    return gl_bindings.createShader.apply(null, arguments);
};
GL.createTexture = function() {
    if (GL.debug) {
        console.log("createTexture");
        console.log(arguments);
    }
    return gl_bindings.createTexture.apply(null, arguments);
};
GL.cullFace = function() {
    if (GL.debug) {
        console.log("cullFace");
        console.log(arguments);
    }
    return gl_bindings.cullFace.apply(null, arguments);
};
GL.deleteBuffer = function() {
    if (GL.debug) {
        console.log("deleteBuffer");
        console.log(arguments);
    }
    return gl_bindings.deleteBuffer.apply(null, arguments);
};
GL.deleteFramebuffer = function() {
    if (GL.debug) {
        console.log("deleteFramebuffer");
        console.log(arguments);
    }
    return gl_bindings.deleteFramebuffer.apply(null, arguments);
};
GL.deleteProgram = function() {
    if (GL.debug) {
        console.log("deleteProgram");
        console.log(arguments);
    }
    return gl_bindings.deleteProgram.apply(null, arguments);
};
GL.deleteRenderbuffer = function() {
    if (GL.debug) {
        console.log("deleteRenderbuffer");
        console.log(arguments);
    }
    return gl_bindings.deleteRenderbuffer.apply(null, arguments);
};
GL.deleteShader = function() {
    if (GL.debug) {
        console.log("deleteShader");
        console.log(arguments);
    }
    return gl_bindings.deleteShader.apply(null, arguments);
};
GL.deleteTexture = function() {
    if (GL.debug) {
        console.log("deleteTexture");
        console.log(arguments);
    }
    return gl_bindings.deleteTexture.apply(null, arguments);
};
GL.depthFunc = function() {
    if (GL.debug) {
        console.log("depthFunc");
        console.log(arguments);
    }
    return gl_bindings.depthFunc.apply(null, arguments);
};
GL.depthMask = function() {
    if (GL.debug) {
        console.log("depthMask");
        console.log(arguments);
    }
    return gl_bindings.depthMask.apply(null, arguments);
};
GL.depthRange = function() {
    if (GL.debug) {
        console.log("depthRange");
        console.log(arguments);
    }
    return gl_bindings.depthRange.apply(null, arguments);
};
GL.detachShader = function() {
    if (GL.debug) {
        console.log("detachShader");
        console.log(arguments);
    }
    return gl_bindings.detachShader.apply(null, arguments);
};
GL.disable = function() {
    if (GL.debug) {
        console.log("disable");
        console.log(arguments);
    }
    return gl_bindings.disable.apply(null, arguments);
};
GL.disableVertexAttribArray = function() {
    if (GL.debug) {
        console.log("disableVertexAttribArray");
        console.log(arguments);
    }
    return gl_bindings.disableVertexAttribArray.apply(null, arguments);
};
GL.drawArrays = function() {
    if (GL.debug) {
        console.log("drawArrays");
        console.log(arguments);
    }
    return gl_bindings.drawArrays.apply(null, arguments);
};
GL.drawElements = function() {
    if (GL.debug) {
        console.log("drawElements");
        console.log(arguments);
    }
    return gl_bindings.drawElements.apply(null, arguments);
};
GL.enable = function() {
    if (GL.debug) {
        console.log("enable");
        console.log(arguments);
    }
    return gl_bindings.enable.apply(null, arguments);
};
GL.enableVertexAttribArray = function() {
    if (GL.debug) {
        console.log("enableVertexAttribArray");
        console.log(arguments);
    }
    return gl_bindings.enableVertexAttribArray.apply(null, arguments);
};
GL.finish = function() {
    if (GL.debug) {
        console.log("finish");
        console.log(arguments);
    }
    return gl_bindings.finish.apply(null, arguments);
};
GL.flush = function() {
    if (GL.debug) {
        console.log("flush");
        console.log(arguments);
    }
    return gl_bindings.flush.apply(null, arguments);
};
GL.framebufferRenderbuffer = function() {
    if (GL.debug) {
        console.log("framebufferRenderbuffer");
        console.log(arguments);
    }
    return gl_bindings.framebufferRenderbuffer.apply(null, arguments);
};
GL.framebufferTexture2D = function() {
    if (GL.debug) {
        console.log("framebufferTexture2D");
        console.log(arguments);
    }
    return gl_bindings.framebufferTexture2D.apply(null, arguments);
};
GL.frontFace = function() {
    if (GL.debug) {
        console.log("frontFace");
        console.log(arguments);
    }
    return gl_bindings.frontFace.apply(null, arguments);
};
GL.generateMipmap = function() {
    if (GL.debug) {
        console.log("generateMipmap");
        console.log(arguments);
    }
    return gl_bindings.generateMipmap.apply(null, arguments);
};
GL.getActiveAttrib = function() {
    if (GL.debug) {
        console.log("getActiveAttrib");
        console.log(arguments);
    }
    return gl_bindings.getActiveAttrib.apply(null, arguments);
};
GL.getActiveUniform = function() {
    if (GL.debug) {
        console.log("getActiveUniform");
        console.log(arguments);
    }
    return gl_bindings.getActiveUniform.apply(null, arguments);
};
// GL.getAttachedShaders;
GL.getAttribLocation = function() {
    if (GL.debug) {
        console.log("getAttribLocation");
        console.log(arguments);
    }
    return gl_bindings.getAttribLocation.apply(null, arguments);
};
// GL.getBufferParameteri; // glGetBufferParameteriv
// GL.getContextAttributes;
GL.getError = function() {
    if (GL.debug) {
        console.log("getError");
        console.log(arguments);
    }
    return gl_bindings.getError.apply(null, arguments);
};
GL.getExtension = function() {
    if (GL.debug) {
        console.log("getExtension");
        console.log(arguments);
    }
    return '';
}
// GL.getFramebufferAttachmentParameteri; // glGetFramebufferAttachmentParameteriv
// GL.getParameter;
// GL.getProgramInfoLog;
GL.getProgramParameter = function() {
    if (GL.debug) {
        console.log("getProgramParameter");
        console.log(arguments);
    }
    return gl_bindings.getProgramParameter.apply(null, arguments);
};
// GL.getRenderbufferParameter; // glGetRenderbufferParameteriv
GL.getShaderInfoLog = function() {
    if (GL.debug) {
        console.log("getShaderInfoLog");
        console.log(arguments);
    }
    return gl_bindings.getShaderInfoLog.apply(null, arguments);
};
GL.getShaderParameter = function() {
    if (GL.debug) {
        console.log("getShaderParameter");
        console.log(arguments);
    }
    return gl_bindings.getShaderParameter.apply(null, arguments);
};
// GL.getShaderPrecisionFormat;
// GL.getShaderSource;
// GL.getSupportedExtensions;
// GL.getTexParameter; // glGetTexParameterfv glGetTexParameteriv
// GL.getUniform; // glGetUniformfv glGetUniformiv
GL.getUniformLocation = function() {
    if (GL.debug) {
        console.log("getUniformLocation");
        console.log(arguments);
    }
    return gl_bindings.getUniformLocation.apply(null, arguments);
};
// GL.getVertexAttrib; // glGetVertexAttribfv glGetVertexAttribiv
// GL.getVertexAttribOffset; // glGetVertexAttribPointerv
// GL.hint;
// GL.isBuffer;
// GL.isContextLost;
// GL.isEnabled;
// GL.isFramebuffer;
// GL.isProgram;
// GL.isRenderbuffer;
// GL.isShader;
// GL.isTexture;
// GL.lineWidth;
GL.linkProgram = function() {
    if (GL.debug) {
        console.log("linkProgram");
        console.log(arguments);
    }
    return gl_bindings.linkProgram.apply(null, arguments);
};
GL.pixelStorei = function() {
    if (GL.debug) {
        console.log("pixelStorei");
        console.log(arguments);
    }
    arguments[1] = Number(arguments[1]);
    return gl_bindings.pixelStorei.apply(null, arguments);
};
// GL.polygonOffset;
// GL.readPixels;
// GL.releaseShaderCompiler; // ?
GL.renderbufferStorage = function() {
    if (GL.debug) {
        console.log("renderbufferStorage");
        console.log(arguments);
    }
    return gl_bindings.renderbufferStorage.apply(null, arguments);
};
// GL.sampleCoverage;
// GL.scissor;
// GL.shaderBinary; // ?
GL.shaderSource = function() {
    if (GL.debug) {
        console.log("shaderSource");
        console.log(arguments);
    }
    return gl_bindings.shaderSource.apply(null, arguments);
};
// GL.stencilFunc;
// GL.stencilFuncSeparate;
// GL.stencilMask;
// GL.stencilMaskSeparate;
// GL.stencilOp;
// GL.stencilOpSeparate;
GL.texImage2D = function() {
    if (GL.debug) {
        console.log("texImage2D");
        console.log(arguments);
    }
    return gl_bindings.texImage2D.apply(null, arguments);
};
// GL.texParameterf;
// GL.texParameterfv;
GL.texParameteri = function() {
    if (GL.debug) {
        console.log("texParameteri");
        console.log(arguments);
    }
    return gl_bindings.texParameteri.apply(null, arguments);
};
// GL.texParameteriv;
// GL.texSubImage2D;
GL.uniform1f = function() {
    if (GL.debug) {
        console.log("uniform1f");
        console.log(arguments);
    }
    return gl_bindings.uniform1f.apply(null, arguments);
};
GL.uniform1fv = function() {
    if (GL.debug) {
        console.log("uniform1fv");
        console.log(arguments);
    }
    arguments[1] = new Float32Array(arguments[1]);
    return gl_bindings.uniform1fv.apply(null, arguments);
};
GL.uniform1i = function() {
    if (GL.debug) {
        console.log("uniform1i");
        console.log(arguments);
    }
    return gl_bindings.uniform1i.apply(null, arguments);
};
GL.uniform1iv = function() {
    if (GL.debug) {
        console.log("uniform1iv");
        console.log(arguments);
    }
    arguments[1] = new Int32Array(arguments[1]);
    return gl_bindings.uniform1iv.apply(null, arguments);
};
GL.uniform2f = function() {
    if (GL.debug) {
        console.log("uniform2f");
        console.log(arguments);
    }
    return gl_bindings.uniform2f.apply(null, arguments);
};
GL.uniform2fv = function() {
    if (GL.debug) {
        console.log("uniform2fv");
        console.log(arguments);
    }
    arguments[1] = new Float32Array(arguments[1]);
    return gl_bindings.uniform2fv.apply(null, arguments);
};
GL.uniform2i = function() {
    if (GL.debug) {
        console.log("uniform2i");
        console.log(arguments);
    }
    return gl_bindings.uniform2i.apply(null, arguments);
};
GL.uniform2iv = function() {
    if (GL.debug) {
        console.log("uniform2iv");
        console.log(arguments);
    }
    arguments[1] = new Int32Array(arguments[1]);
    return gl_bindings.uniform2iv.apply(null, arguments);
};
GL.uniform3f = function() {
    if (GL.debug) {
        console.log("uniform3f");
        console.log(arguments);
    }
    return gl_bindings.uniform3f.apply(null, arguments);
};
GL.uniform3fv = function() {
    if (GL.debug) {
        console.log("uniform3fv");
        console.log(arguments);
    }
    arguments[1] = new Float32Array(arguments[1]);
    return gl_bindings.uniform3fv.apply(null, arguments);
};
GL.uniform3i = function() {
    if (GL.debug) {
        console.log("uniform3i");
        console.log(arguments);
    }
    return gl_bindings.uniform3i.apply(null, arguments);
};
GL.uniform3iv = function() {
    if (GL.debug) {
        console.log("uniform3iv");
        console.log(arguments);
    }
    arguments[1] = new Int32Array(arguments[1]);
    return gl_bindings.uniform3iv.apply(null, arguments);
};
GL.uniform4f = function() {
    if (GL.debug) {
        console.log("uniform4f");
        console.log(arguments);
    }
    return gl_bindings.uniform4f.apply(null, arguments);
};
GL.uniform4fv = function() {
    if (GL.debug) {
        console.log("uniform4fv");
        console.log(arguments);
    }
    arguments[1] = new Float32Array(arguments[1]);
    return gl_bindings.uniform4fv.apply(null, arguments);
};
GL.uniform4i = function() {
    if (GL.debug) {
        console.log("uniform4i");
        console.log(arguments);
    }
    return gl_bindings.uniform4i.apply(null, arguments);
};
GL.uniform4iv = function() {
    if (GL.debug) {
        console.log("uniform4iv");
        console.log(arguments);
    }
    arguments[1] = new Int32Array(arguments[1]);
    return gl_bindings.uniform4iv.apply(null, arguments);
};
GL.uniformMatrix2fv = function() {
    if (GL.debug) {
        console.log("uniformMatrix2fv");
        console.log(arguments);
    }
    return gl_bindings.uniformMatrix2fv.apply(null, arguments);
};
GL.uniformMatrix3fv = function() {
    if (GL.debug) {
        console.log("uniformMatrix3fv");
        console.log(arguments);
    }
    return gl_bindings.uniformMatrix3fv.apply(null, arguments);
};
GL.uniformMatrix4fv = function() {
    if (GL.debug) {
        console.log("uniformMatrix4fv");
        console.log(arguments);
    }
    return gl_bindings.uniformMatrix4fv.apply(null, arguments);
};
GL.useProgram = function() {
    if (GL.debug) {
        console.log("useProgram");
        console.log(arguments);
    }
    return gl_bindings.useProgram.apply(null, arguments);
};
// GL.validateProgram;
// GL.vertexAttrib1f;
// GL.vertexAttrib1fv;
// GL.vertexAttrib2f;
// GL.vertexAttrib2fv;
// GL.vertexAttrib3f;
// GL.vertexAttrib3fv;
// GL.vertexAttrib4f;
// GL.vertexAttrib4fv;
GL.vertexAttribPointer = function() {
    if (GL.debug) {
        console.log("vertexAttribPointer");
        console.log(arguments);
    }
    return gl_bindings.vertexAttribPointer.apply(null, arguments);
};
GL.viewport = function() {
    if (GL.debug) {
        console.log("viewport");
        console.log(arguments);
    }
    return gl_bindings.viewport.apply(null, arguments);
};

module.exports = GL;
