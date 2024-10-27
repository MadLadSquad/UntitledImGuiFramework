/**
 * Loader 
 *
 * SPDX-License-Identifier: (WTFPL OR CC0-1.0) AND Apache-2.0
 *
 * Generator: C/C++
 * Specification: gl
 * Extensions: 7
 *
 * APIs:
 *  - glsc2=2.0
 *
 * Options:
 *  - ALIAS = False
 *  - DEBUG = False
 *  - HEADER_ONLY = False
 *  - LOADER = False
 *  - MX = False
 *  - ON_DEMAND = False
 *
 * Commandline:
 *    --api='glsc2=2.0' --extensions='GL_EXT_texture_compression_s3tc,GL_IMG_pvric_end_to_end_signature,GL_IMG_tile_region_protection,GL_OES_depth24,GL_OES_depth32,GL_OES_rgb8_rgba8,GL_OES_standard_derivatives' c
 *
 * Online:
 *    http://glad.sh/#api=glsc2%3D2.0&extensions=GL_EXT_texture_compression_s3tc%2CGL_IMG_pvric_end_to_end_signature%2CGL_IMG_tile_region_protection%2CGL_OES_depth24%2CGL_OES_depth32%2CGL_OES_rgb8_rgba8%2CGL_OES_standard_derivatives&generator=c&options=
 *
 */

#ifndef GLAD_GLSC2_H_
#define GLAD_GLSC2_H_

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifdef __clang__
#pragma clang diagnostic pop
#endif

#define GLAD_GLSC2

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GLAD_PLATFORM_H_
#define GLAD_PLATFORM_H_

#ifndef GLAD_PLATFORM_WIN32
  #if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(__MINGW32__)
    #define GLAD_PLATFORM_WIN32 1
  #else
    #define GLAD_PLATFORM_WIN32 0
  #endif
#endif

#ifndef GLAD_PLATFORM_APPLE
  #ifdef __APPLE__
    #define GLAD_PLATFORM_APPLE 1
  #else
    #define GLAD_PLATFORM_APPLE 0
  #endif
#endif

#ifndef GLAD_PLATFORM_EMSCRIPTEN
  #ifdef __EMSCRIPTEN__
    #define GLAD_PLATFORM_EMSCRIPTEN 1
  #else
    #define GLAD_PLATFORM_EMSCRIPTEN 0
  #endif
#endif

#ifndef GLAD_PLATFORM_UWP
  #if defined(_MSC_VER) && !defined(GLAD_INTERNAL_HAVE_WINAPIFAMILY)
    #ifdef __has_include
      #if __has_include(<winapifamily.h>)
        #define GLAD_INTERNAL_HAVE_WINAPIFAMILY 1
      #endif
    #elif _MSC_VER >= 1700 && !_USING_V110_SDK71_
      #define GLAD_INTERNAL_HAVE_WINAPIFAMILY 1
    #endif
  #endif

  #ifdef GLAD_INTERNAL_HAVE_WINAPIFAMILY
    #include <winapifamily.h>
    #if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) && WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
      #define GLAD_PLATFORM_UWP 1
    #endif
  #endif

  #ifndef GLAD_PLATFORM_UWP
    #define GLAD_PLATFORM_UWP 0
  #endif
#endif

#ifdef __GNUC__
  #define GLAD_GNUC_EXTENSION __extension__
#else
  #define GLAD_GNUC_EXTENSION
#endif

#define GLAD_UNUSED(x) (void)(x)

#ifndef GLAD_API_CALL
  #if defined(GLAD_API_CALL_EXPORT)
    #if GLAD_PLATFORM_WIN32 || defined(__CYGWIN__)
      #if defined(GLAD_API_CALL_EXPORT_BUILD)
        #if defined(__GNUC__)
          #define GLAD_API_CALL __attribute__ ((dllexport)) extern
        #else
          #define GLAD_API_CALL __declspec(dllexport) extern
        #endif
      #else
        #if defined(__GNUC__)
          #define GLAD_API_CALL __attribute__ ((dllimport)) extern
        #else
          #define GLAD_API_CALL __declspec(dllimport) extern
        #endif
      #endif
    #elif defined(__GNUC__) && defined(GLAD_API_CALL_EXPORT_BUILD)
      #define GLAD_API_CALL __attribute__ ((visibility ("default"))) extern
    #else
      #define GLAD_API_CALL extern
    #endif
  #else
    #define GLAD_API_CALL extern
  #endif
#endif

#ifdef APIENTRY
  #define GLAD_API_PTR APIENTRY
#elif GLAD_PLATFORM_WIN32
  #define GLAD_API_PTR __stdcall
#else
  #define GLAD_API_PTR
#endif

#ifndef GLAPI
#define GLAPI GLAD_API_CALL
#endif

#ifndef GLAPIENTRY
#define GLAPIENTRY GLAD_API_PTR
#endif

#define GLAD_MAKE_VERSION(major, minor) (major * 10000 + minor)
#define GLAD_VERSION_MAJOR(version) (version / 10000)
#define GLAD_VERSION_MINOR(version) (version % 10000)

#define GLAD_GENERATOR_VERSION "2.0.8"

typedef void (*GLADapiproc)(void);

typedef GLADapiproc (*GLADloadfunc)(const char *name);
typedef GLADapiproc (*GLADuserptrloadfunc)(void *userptr, const char *name);

typedef void (*GLADprecallback)(const char *name, GLADapiproc apiproc, int len_args, ...);
typedef void (*GLADpostcallback)(void *ret, const char *name, GLADapiproc apiproc, int len_args, ...);

#endif /* GLAD_PLATFORM_H_ */

#define GL_ACTIVE_TEXTURE 0x84E0
#define GL_ALIASED_LINE_WIDTH_RANGE 0x846E
#define GL_ALIASED_POINT_SIZE_RANGE 0x846D
#define GL_ALPHA_BITS 0x0D55
#define GL_ALWAYS 0x0207
#define GL_ARRAY_BUFFER 0x8892
#define GL_ARRAY_BUFFER_BINDING 0x8894
#define GL_BACK 0x0405
#define GL_BLEND 0x0BE2
#define GL_BLEND_COLOR 0x8005
#define GL_BLEND_DST_ALPHA 0x80CA
#define GL_BLEND_DST_RGB 0x80C8
#define GL_BLEND_EQUATION 0x8009
#define GL_BLEND_EQUATION_ALPHA 0x883D
#define GL_BLEND_EQUATION_RGB 0x8009
#define GL_BLEND_SRC_ALPHA 0x80CB
#define GL_BLEND_SRC_RGB 0x80C9
#define GL_BLUE_BITS 0x0D54
#define GL_BUFFER_SIZE 0x8764
#define GL_BUFFER_USAGE 0x8765
#define GL_BYTE 0x1400
#define GL_CCW 0x0901
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_COLOR_ATTACHMENT0 0x8CE0
#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_COLOR_CLEAR_VALUE 0x0C22
#define GL_COLOR_WRITEMASK 0x0C23
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT 0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT 0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT 0x83F3
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT 0x83F0
#define GL_COMPRESSED_TEXTURE_FORMATS 0x86A3
#define GL_CONSTANT_ALPHA 0x8003
#define GL_CONSTANT_COLOR 0x8001
#define GL_CONTEXT_LOST 0x0507
#define GL_CONTEXT_ROBUST_ACCESS 0x90F3
#define GL_CULL_FACE 0x0B44
#define GL_CULL_FACE_MODE 0x0B45
#define GL_CURRENT_PROGRAM 0x8B8D
#define GL_CURRENT_VERTEX_ATTRIB 0x8626
#define GL_CW 0x0900
#define GL_DECR 0x1E03
#define GL_DECR_WRAP 0x8508
#define GL_DEPTH_ATTACHMENT 0x8D00
#define GL_DEPTH_BITS 0x0D56
#define GL_DEPTH_BUFFER_BIT 0x00000100
#define GL_DEPTH_CLEAR_VALUE 0x0B73
#define GL_DEPTH_COMPONENT16 0x81A5
#define GL_DEPTH_COMPONENT24_OES 0x81A6
#define GL_DEPTH_COMPONENT32_OES 0x81A7
#define GL_DEPTH_FUNC 0x0B74
#define GL_DEPTH_RANGE 0x0B70
#define GL_DEPTH_TEST 0x0B71
#define GL_DEPTH_WRITEMASK 0x0B72
#define GL_DITHER 0x0BD0
#define GL_DONT_CARE 0x1100
#define GL_DST_ALPHA 0x0304
#define GL_DST_COLOR 0x0306
#define GL_DYNAMIC_DRAW 0x88E8
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_ELEMENT_ARRAY_BUFFER_BINDING 0x8895
#define GL_EQUAL 0x0202
#define GL_EXTENSIONS 0x1F03
#define GL_FALSE 0
#define GL_FASTEST 0x1101
#define GL_FLOAT 0x1406
#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT_OES 0x8B8B
#define GL_FRAMEBUFFER 0x8D40
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL 0x8CD2
#define GL_FRAMEBUFFER_BINDING 0x8CA6
#define GL_FRAMEBUFFER_COMPLETE 0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS 0x8CD9
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8CD7
#define GL_FRAMEBUFFER_UNDEFINED 0x8219
#define GL_FRAMEBUFFER_UNSUPPORTED 0x8CDD
#define GL_FRONT 0x0404
#define GL_FRONT_AND_BACK 0x0408
#define GL_FRONT_FACE 0x0B46
#define GL_FUNC_ADD 0x8006
#define GL_FUNC_REVERSE_SUBTRACT 0x800B
#define GL_FUNC_SUBTRACT 0x800A
#define GL_GENERATE_MIPMAP_HINT 0x8192
#define GL_GEQUAL 0x0206
#define GL_GREATER 0x0204
#define GL_GREEN_BITS 0x0D53
#define GL_GUILTY_CONTEXT_RESET 0x8253
#define GL_HIGH_FLOAT 0x8DF2
#define GL_HIGH_INT 0x8DF5
#define GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8B9B
#define GL_IMPLEMENTATION_COLOR_READ_TYPE 0x8B9A
#define GL_INCR 0x1E02
#define GL_INCR_WRAP 0x8507
#define GL_INNOCENT_CONTEXT_RESET 0x8254
#define GL_INT 0x1404
#define GL_INVALID_ENUM 0x0500
#define GL_INVALID_FRAMEBUFFER_OPERATION 0x0506
#define GL_INVALID_OPERATION 0x0502
#define GL_INVALID_VALUE 0x0501
#define GL_INVERT 0x150A
#define GL_KEEP 0x1E00
#define GL_LEQUAL 0x0203
#define GL_LESS 0x0201
#define GL_LINEAR 0x2601
#define GL_LINEAR_MIPMAP_LINEAR 0x2703
#define GL_LINEAR_MIPMAP_NEAREST 0x2701
#define GL_LINES 0x0001
#define GL_LINE_LOOP 0x0002
#define GL_LINE_STRIP 0x0003
#define GL_LINE_WIDTH 0x0B21
#define GL_LINK_STATUS 0x8B82
#define GL_LOSE_CONTEXT_ON_RESET 0x8252
#define GL_LOW_FLOAT 0x8DF0
#define GL_LOW_INT 0x8DF3
#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#define GL_MAX_FRAGMENT_UNIFORM_VECTORS 0x8DFD
#define GL_MAX_RENDERBUFFER_SIZE 0x84E8
#define GL_MAX_TEXTURE_IMAGE_UNITS 0x8872
#define GL_MAX_TEXTURE_SIZE 0x0D33
#define GL_MAX_VARYING_VECTORS 0x8DFC
#define GL_MAX_VERTEX_ATTRIBS 0x8869
#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS 0x8B4C
#define GL_MAX_VERTEX_UNIFORM_VECTORS 0x8DFB
#define GL_MAX_VIEWPORT_DIMS 0x0D3A
#define GL_MEDIUM_FLOAT 0x8DF1
#define GL_MEDIUM_INT 0x8DF4
#define GL_MIRRORED_REPEAT 0x8370
#define GL_NEAREST 0x2600
#define GL_NEAREST_MIPMAP_LINEAR 0x2702
#define GL_NEAREST_MIPMAP_NEAREST 0x2700
#define GL_NEVER 0x0200
#define GL_NICEST 0x1102
#define GL_NONE 0
#define GL_NOTEQUAL 0x0205
#define GL_NO_ERROR 0
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS 0x86A2
#define GL_NUM_PROGRAM_BINARY_FORMATS 0x87FE
#define GL_ONE 1
#define GL_ONE_MINUS_CONSTANT_ALPHA 0x8004
#define GL_ONE_MINUS_CONSTANT_COLOR 0x8002
#define GL_ONE_MINUS_DST_ALPHA 0x0305
#define GL_ONE_MINUS_DST_COLOR 0x0307
#define GL_ONE_MINUS_SRC_ALPHA 0x0303
#define GL_ONE_MINUS_SRC_COLOR 0x0301
#define GL_OUT_OF_MEMORY 0x0505
#define GL_PACK_ALIGNMENT 0x0D05
#define GL_POINTS 0x0000
#define GL_POLYGON_OFFSET_FACTOR 0x8038
#define GL_POLYGON_OFFSET_FILL 0x8037
#define GL_POLYGON_OFFSET_UNITS 0x2A00
#define GL_PROGRAM_BINARY_FORMATS 0x87FF
#define GL_PVRIC_SIGNATURE_MISMATCH_IMG 0x8EA3
#define GL_R8 0x8229
#define GL_RED 0x1903
#define GL_RED_BITS 0x0D52
#define GL_RENDERBUFFER 0x8D41
#define GL_RENDERBUFFER_ALPHA_SIZE 0x8D53
#define GL_RENDERBUFFER_BINDING 0x8CA7
#define GL_RENDERBUFFER_BLUE_SIZE 0x8D52
#define GL_RENDERBUFFER_DEPTH_SIZE 0x8D54
#define GL_RENDERBUFFER_GREEN_SIZE 0x8D51
#define GL_RENDERBUFFER_HEIGHT 0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT 0x8D44
#define GL_RENDERBUFFER_RED_SIZE 0x8D50
#define GL_RENDERBUFFER_STENCIL_SIZE 0x8D55
#define GL_RENDERBUFFER_WIDTH 0x8D42
#define GL_RENDERER 0x1F01
#define GL_REPEAT 0x2901
#define GL_REPLACE 0x1E01
#define GL_RESET_NOTIFICATION_STRATEGY 0x8256
#define GL_RG 0x8227
#define GL_RG8 0x822B
#define GL_RGB 0x1907
#define GL_RGB565 0x8D62
#define GL_RGB5_A1 0x8057
#define GL_RGB8 0x8051
#define GL_RGB8_OES 0x8051
#define GL_RGBA 0x1908
#define GL_RGBA4 0x8056
#define GL_RGBA8 0x8058
#define GL_RGBA8_OES 0x8058
#define GL_SAMPLER_2D 0x8B5E
#define GL_SAMPLES 0x80A9
#define GL_SAMPLE_ALPHA_TO_COVERAGE 0x809E
#define GL_SAMPLE_BUFFERS 0x80A8
#define GL_SAMPLE_COVERAGE 0x80A0
#define GL_SAMPLE_COVERAGE_INVERT 0x80AB
#define GL_SAMPLE_COVERAGE_VALUE 0x80AA
#define GL_SCISSOR_BOX 0x0C10
#define GL_SCISSOR_TEST 0x0C11
#define GL_SHADING_LANGUAGE_VERSION 0x8B8C
#define GL_SHORT 0x1402
#define GL_SRC_ALPHA 0x0302
#define GL_SRC_ALPHA_SATURATE 0x0308
#define GL_SRC_COLOR 0x0300
#define GL_STATIC_DRAW 0x88E4
#define GL_STENCIL_ATTACHMENT 0x8D20
#define GL_STENCIL_BACK_FAIL 0x8801
#define GL_STENCIL_BACK_FUNC 0x8800
#define GL_STENCIL_BACK_PASS_DEPTH_FAIL 0x8802
#define GL_STENCIL_BACK_PASS_DEPTH_PASS 0x8803
#define GL_STENCIL_BACK_REF 0x8CA3
#define GL_STENCIL_BACK_VALUE_MASK 0x8CA4
#define GL_STENCIL_BACK_WRITEMASK 0x8CA5
#define GL_STENCIL_BITS 0x0D57
#define GL_STENCIL_BUFFER_BIT 0x00000400
#define GL_STENCIL_CLEAR_VALUE 0x0B91
#define GL_STENCIL_FAIL 0x0B94
#define GL_STENCIL_FUNC 0x0B92
#define GL_STENCIL_INDEX8 0x8D48
#define GL_STENCIL_PASS_DEPTH_FAIL 0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS 0x0B96
#define GL_STENCIL_REF 0x0B97
#define GL_STENCIL_TEST 0x0B90
#define GL_STENCIL_VALUE_MASK 0x0B93
#define GL_STENCIL_WRITEMASK 0x0B98
#define GL_STREAM_DRAW 0x88E0
#define GL_SUBPIXEL_BITS 0x0D50
#define GL_TEXTURE 0x1702
#define GL_TEXTURE0 0x84C0
#define GL_TEXTURE1 0x84C1
#define GL_TEXTURE10 0x84CA
#define GL_TEXTURE11 0x84CB
#define GL_TEXTURE12 0x84CC
#define GL_TEXTURE13 0x84CD
#define GL_TEXTURE14 0x84CE
#define GL_TEXTURE15 0x84CF
#define GL_TEXTURE16 0x84D0
#define GL_TEXTURE17 0x84D1
#define GL_TEXTURE18 0x84D2
#define GL_TEXTURE19 0x84D3
#define GL_TEXTURE2 0x84C2
#define GL_TEXTURE20 0x84D4
#define GL_TEXTURE21 0x84D5
#define GL_TEXTURE22 0x84D6
#define GL_TEXTURE23 0x84D7
#define GL_TEXTURE24 0x84D8
#define GL_TEXTURE25 0x84D9
#define GL_TEXTURE26 0x84DA
#define GL_TEXTURE27 0x84DB
#define GL_TEXTURE28 0x84DC
#define GL_TEXTURE29 0x84DD
#define GL_TEXTURE3 0x84C3
#define GL_TEXTURE30 0x84DE
#define GL_TEXTURE31 0x84DF
#define GL_TEXTURE4 0x84C4
#define GL_TEXTURE5 0x84C5
#define GL_TEXTURE6 0x84C6
#define GL_TEXTURE7 0x84C7
#define GL_TEXTURE8 0x84C8
#define GL_TEXTURE9 0x84C9
#define GL_TEXTURE_2D 0x0DE1
#define GL_TEXTURE_BINDING_2D 0x8069
#define GL_TEXTURE_IMMUTABLE_FORMAT 0x912F
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_TEXTURE_WRAP_S 0x2802
#define GL_TEXTURE_WRAP_T 0x2803
#define GL_TRIANGLES 0x0004
#define GL_TRIANGLE_FAN 0x0006
#define GL_TRIANGLE_STRIP 0x0005
#define GL_TRP_ERROR_CONTEXT_RESET_IMG 0x8EA1
#define GL_TRP_IMG 0x8EA0
#define GL_TRP_UNSUPPORTED_CONTEXT_IMG 0x8EA2
#define GL_TRUE 1
#define GL_UNKNOWN_CONTEXT_RESET 0x8255
#define GL_UNPACK_ALIGNMENT 0x0CF5
#define GL_UNSIGNED_BYTE 0x1401
#define GL_UNSIGNED_INT 0x1405
#define GL_UNSIGNED_SHORT 0x1403
#define GL_UNSIGNED_SHORT_4_4_4_4 0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1 0x8034
#define GL_UNSIGNED_SHORT_5_6_5 0x8363
#define GL_VENDOR 0x1F00
#define GL_VERSION 0x1F02
#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING 0x889F
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED 0x8622
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED 0x886A
#define GL_VERTEX_ATTRIB_ARRAY_POINTER 0x8645
#define GL_VERTEX_ATTRIB_ARRAY_SIZE 0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE 0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE 0x8625
#define GL_VIEWPORT 0x0BA2
#define GL_ZERO 0


#include <KHR/khrplatform.h>
typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef void GLvoid;
typedef khronos_int8_t GLbyte;
typedef khronos_uint8_t GLubyte;
typedef khronos_int16_t GLshort;
typedef khronos_uint16_t GLushort;
typedef int GLint;
typedef unsigned int GLuint;
typedef khronos_int32_t GLclampx;
typedef int GLsizei;
typedef khronos_float_t GLfloat;
typedef khronos_float_t GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void *GLeglClientBufferEXT;
typedef void *GLeglImageOES;
typedef char GLchar;
typedef char GLcharARB;
#ifdef __APPLE__
typedef void *GLhandleARB;
#else
typedef unsigned int GLhandleARB;
#endif
typedef khronos_uint16_t GLhalf;
typedef khronos_uint16_t GLhalfARB;
typedef khronos_int32_t GLfixed;
#if defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__) && (__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ > 1060)
typedef khronos_intptr_t GLintptr;
#else
typedef khronos_intptr_t GLintptr;
#endif
#if defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__) && (__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ > 1060)
typedef khronos_intptr_t GLintptrARB;
#else
typedef khronos_intptr_t GLintptrARB;
#endif
#if defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__) && (__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ > 1060)
typedef khronos_ssize_t GLsizeiptr;
#else
typedef khronos_ssize_t GLsizeiptr;
#endif
#if defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__) && (__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ > 1060)
typedef khronos_ssize_t GLsizeiptrARB;
#else
typedef khronos_ssize_t GLsizeiptrARB;
#endif
typedef khronos_int64_t GLint64;
typedef khronos_int64_t GLint64EXT;
typedef khronos_uint64_t GLuint64;
typedef khronos_uint64_t GLuint64EXT;
typedef struct __GLsync *GLsync;
struct _cl_context;
struct _cl_event;
typedef void (GLAD_API_PTR *GLDEBUGPROC)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef void (GLAD_API_PTR *GLDEBUGPROCARB)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef void (GLAD_API_PTR *GLDEBUGPROCKHR)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef void (GLAD_API_PTR *GLDEBUGPROCAMD)(GLuint id,GLenum category,GLenum severity,GLsizei length,const GLchar *message,void *userParam);
typedef unsigned short GLhalfNV;
typedef GLintptr GLvdpauSurfaceNV;
typedef void (GLAD_API_PTR *GLVULKANPROCNV)(void);


#define GL_SC_VERSION_2_0 1
GLAD_API_CALL int GLAD_GL_SC_VERSION_2_0;
#define GL_EXT_texture_compression_s3tc 1
GLAD_API_CALL int GLAD_GL_EXT_texture_compression_s3tc;
#define GL_IMG_pvric_end_to_end_signature 1
GLAD_API_CALL int GLAD_GL_IMG_pvric_end_to_end_signature;
#define GL_IMG_tile_region_protection 1
GLAD_API_CALL int GLAD_GL_IMG_tile_region_protection;
#define GL_OES_depth24 1
GLAD_API_CALL int GLAD_GL_OES_depth24;
#define GL_OES_depth32 1
GLAD_API_CALL int GLAD_GL_OES_depth32;
#define GL_OES_rgb8_rgba8 1
GLAD_API_CALL int GLAD_GL_OES_rgb8_rgba8;
#define GL_OES_standard_derivatives 1
GLAD_API_CALL int GLAD_GL_OES_standard_derivatives;


typedef void (GLAD_API_PTR *PFNGLACTIVETEXTUREPROC)(GLenum texture);
typedef void (GLAD_API_PTR *PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
typedef void (GLAD_API_PTR *PFNGLBINDFRAMEBUFFERPROC)(GLenum target, GLuint framebuffer);
typedef void (GLAD_API_PTR *PFNGLBINDRENDERBUFFERPROC)(GLenum target, GLuint renderbuffer);
typedef void (GLAD_API_PTR *PFNGLBINDTEXTUREPROC)(GLenum target, GLuint texture);
typedef void (GLAD_API_PTR *PFNGLBLENDCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (GLAD_API_PTR *PFNGLBLENDEQUATIONPROC)(GLenum mode);
typedef void (GLAD_API_PTR *PFNGLBLENDEQUATIONSEPARATEPROC)(GLenum modeRGB, GLenum modeAlpha);
typedef void (GLAD_API_PTR *PFNGLBLENDFUNCPROC)(GLenum sfactor, GLenum dfactor);
typedef void (GLAD_API_PTR *PFNGLBLENDFUNCSEPARATEPROC)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
typedef void (GLAD_API_PTR *PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const void * data, GLenum usage);
typedef void (GLAD_API_PTR *PFNGLBUFFERSUBDATAPROC)(GLenum target, GLintptr offset, GLsizeiptr size, const void * data);
typedef GLenum (GLAD_API_PTR *PFNGLCHECKFRAMEBUFFERSTATUSPROC)(GLenum target);
typedef void (GLAD_API_PTR *PFNGLCLEARPROC)(GLbitfield mask);
typedef void (GLAD_API_PTR *PFNGLCLEARCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (GLAD_API_PTR *PFNGLCLEARDEPTHFPROC)(GLfloat d);
typedef void (GLAD_API_PTR *PFNGLCLEARSTENCILPROC)(GLint s);
typedef void (GLAD_API_PTR *PFNGLCOLORMASKPROC)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
typedef void (GLAD_API_PTR *PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data);
typedef GLuint (GLAD_API_PTR *PFNGLCREATEPROGRAMPROC)(void);
typedef void (GLAD_API_PTR *PFNGLCULLFACEPROC)(GLenum mode);
typedef void (GLAD_API_PTR *PFNGLDEPTHFUNCPROC)(GLenum func);
typedef void (GLAD_API_PTR *PFNGLDEPTHMASKPROC)(GLboolean flag);
typedef void (GLAD_API_PTR *PFNGLDEPTHRANGEFPROC)(GLfloat n, GLfloat f);
typedef void (GLAD_API_PTR *PFNGLDISABLEPROC)(GLenum cap);
typedef void (GLAD_API_PTR *PFNGLDISABLEVERTEXATTRIBARRAYPROC)(GLuint index);
typedef void (GLAD_API_PTR *PFNGLDRAWARRAYSPROC)(GLenum mode, GLint first, GLsizei count);
typedef void (GLAD_API_PTR *PFNGLDRAWRANGEELEMENTSPROC)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices);
typedef void (GLAD_API_PTR *PFNGLENABLEPROC)(GLenum cap);
typedef void (GLAD_API_PTR *PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
typedef void (GLAD_API_PTR *PFNGLFINISHPROC)(void);
typedef void (GLAD_API_PTR *PFNGLFLUSHPROC)(void);
typedef void (GLAD_API_PTR *PFNGLFRAMEBUFFERRENDERBUFFERPROC)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (GLAD_API_PTR *PFNGLFRAMEBUFFERTEXTURE2DPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (GLAD_API_PTR *PFNGLFRONTFACEPROC)(GLenum mode);
typedef void (GLAD_API_PTR *PFNGLGENBUFFERSPROC)(GLsizei n, GLuint * buffers);
typedef void (GLAD_API_PTR *PFNGLGENFRAMEBUFFERSPROC)(GLsizei n, GLuint * framebuffers);
typedef void (GLAD_API_PTR *PFNGLGENRENDERBUFFERSPROC)(GLsizei n, GLuint * renderbuffers);
typedef void (GLAD_API_PTR *PFNGLGENTEXTURESPROC)(GLsizei n, GLuint * textures);
typedef void (GLAD_API_PTR *PFNGLGENERATEMIPMAPPROC)(GLenum target);
typedef GLint (GLAD_API_PTR *PFNGLGETATTRIBLOCATIONPROC)(GLuint program, const GLchar * name);
typedef void (GLAD_API_PTR *PFNGLGETBOOLEANVPROC)(GLenum pname, GLboolean * data);
typedef void (GLAD_API_PTR *PFNGLGETBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, GLint * params);
typedef GLenum (GLAD_API_PTR *PFNGLGETERRORPROC)(void);
typedef void (GLAD_API_PTR *PFNGLGETFLOATVPROC)(GLenum pname, GLfloat * data);
typedef void (GLAD_API_PTR *PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)(GLenum target, GLenum attachment, GLenum pname, GLint * params);
typedef GLenum (GLAD_API_PTR *PFNGLGETGRAPHICSRESETSTATUSPROC)(void);
typedef void (GLAD_API_PTR *PFNGLGETINTEGERVPROC)(GLenum pname, GLint * data);
typedef void (GLAD_API_PTR *PFNGLGETPROGRAMIVPROC)(GLuint program, GLenum pname, GLint * params);
typedef void (GLAD_API_PTR *PFNGLGETRENDERBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, GLint * params);
typedef const GLubyte * (GLAD_API_PTR *PFNGLGETSTRINGPROC)(GLenum name);
typedef void (GLAD_API_PTR *PFNGLGETTEXPARAMETERFVPROC)(GLenum target, GLenum pname, GLfloat * params);
typedef void (GLAD_API_PTR *PFNGLGETTEXPARAMETERIVPROC)(GLenum target, GLenum pname, GLint * params);
typedef GLint (GLAD_API_PTR *PFNGLGETUNIFORMLOCATIONPROC)(GLuint program, const GLchar * name);
typedef void (GLAD_API_PTR *PFNGLGETVERTEXATTRIBPOINTERVPROC)(GLuint index, GLenum pname, void ** pointer);
typedef void (GLAD_API_PTR *PFNGLGETVERTEXATTRIBFVPROC)(GLuint index, GLenum pname, GLfloat * params);
typedef void (GLAD_API_PTR *PFNGLGETVERTEXATTRIBIVPROC)(GLuint index, GLenum pname, GLint * params);
typedef void (GLAD_API_PTR *PFNGLGETNUNIFORMFVPROC)(GLuint program, GLint location, GLsizei bufSize, GLfloat * params);
typedef void (GLAD_API_PTR *PFNGLGETNUNIFORMIVPROC)(GLuint program, GLint location, GLsizei bufSize, GLint * params);
typedef void (GLAD_API_PTR *PFNGLHINTPROC)(GLenum target, GLenum mode);
typedef GLboolean (GLAD_API_PTR *PFNGLISENABLEDPROC)(GLenum cap);
typedef void (GLAD_API_PTR *PFNGLLINEWIDTHPROC)(GLfloat width);
typedef void (GLAD_API_PTR *PFNGLPIXELSTOREIPROC)(GLenum pname, GLint param);
typedef void (GLAD_API_PTR *PFNGLPOLYGONOFFSETPROC)(GLfloat factor, GLfloat units);
typedef void (GLAD_API_PTR *PFNGLPROGRAMBINARYPROC)(GLuint program, GLenum binaryFormat, const void * binary, GLsizei length);
typedef void (GLAD_API_PTR *PFNGLREADNPIXELSPROC)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void * data);
typedef void (GLAD_API_PTR *PFNGLRENDERBUFFERSTORAGEPROC)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (GLAD_API_PTR *PFNGLSAMPLECOVERAGEPROC)(GLfloat value, GLboolean invert);
typedef void (GLAD_API_PTR *PFNGLSCISSORPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (GLAD_API_PTR *PFNGLSTENCILFUNCPROC)(GLenum func, GLint ref, GLuint mask);
typedef void (GLAD_API_PTR *PFNGLSTENCILFUNCSEPARATEPROC)(GLenum face, GLenum func, GLint ref, GLuint mask);
typedef void (GLAD_API_PTR *PFNGLSTENCILMASKPROC)(GLuint mask);
typedef void (GLAD_API_PTR *PFNGLSTENCILMASKSEPARATEPROC)(GLenum face, GLuint mask);
typedef void (GLAD_API_PTR *PFNGLSTENCILOPPROC)(GLenum fail, GLenum zfail, GLenum zpass);
typedef void (GLAD_API_PTR *PFNGLSTENCILOPSEPARATEPROC)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
typedef void (GLAD_API_PTR *PFNGLTEXPARAMETERFPROC)(GLenum target, GLenum pname, GLfloat param);
typedef void (GLAD_API_PTR *PFNGLTEXPARAMETERFVPROC)(GLenum target, GLenum pname, const GLfloat * params);
typedef void (GLAD_API_PTR *PFNGLTEXPARAMETERIPROC)(GLenum target, GLenum pname, GLint param);
typedef void (GLAD_API_PTR *PFNGLTEXPARAMETERIVPROC)(GLenum target, GLenum pname, const GLint * params);
typedef void (GLAD_API_PTR *PFNGLTEXSTORAGE2DPROC)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (GLAD_API_PTR *PFNGLTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels);
typedef void (GLAD_API_PTR *PFNGLUNIFORM1FPROC)(GLint location, GLfloat v0);
typedef void (GLAD_API_PTR *PFNGLUNIFORM1FVPROC)(GLint location, GLsizei count, const GLfloat * value);
typedef void (GLAD_API_PTR *PFNGLUNIFORM1IPROC)(GLint location, GLint v0);
typedef void (GLAD_API_PTR *PFNGLUNIFORM1IVPROC)(GLint location, GLsizei count, const GLint * value);
typedef void (GLAD_API_PTR *PFNGLUNIFORM2FPROC)(GLint location, GLfloat v0, GLfloat v1);
typedef void (GLAD_API_PTR *PFNGLUNIFORM2FVPROC)(GLint location, GLsizei count, const GLfloat * value);
typedef void (GLAD_API_PTR *PFNGLUNIFORM2IPROC)(GLint location, GLint v0, GLint v1);
typedef void (GLAD_API_PTR *PFNGLUNIFORM2IVPROC)(GLint location, GLsizei count, const GLint * value);
typedef void (GLAD_API_PTR *PFNGLUNIFORM3FPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (GLAD_API_PTR *PFNGLUNIFORM3FVPROC)(GLint location, GLsizei count, const GLfloat * value);
typedef void (GLAD_API_PTR *PFNGLUNIFORM3IPROC)(GLint location, GLint v0, GLint v1, GLint v2);
typedef void (GLAD_API_PTR *PFNGLUNIFORM3IVPROC)(GLint location, GLsizei count, const GLint * value);
typedef void (GLAD_API_PTR *PFNGLUNIFORM4FPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (GLAD_API_PTR *PFNGLUNIFORM4FVPROC)(GLint location, GLsizei count, const GLfloat * value);
typedef void (GLAD_API_PTR *PFNGLUNIFORM4IPROC)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (GLAD_API_PTR *PFNGLUNIFORM4IVPROC)(GLint location, GLsizei count, const GLint * value);
typedef void (GLAD_API_PTR *PFNGLUNIFORMMATRIX2FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (GLAD_API_PTR *PFNGLUNIFORMMATRIX3FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (GLAD_API_PTR *PFNGLUNIFORMMATRIX4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (GLAD_API_PTR *PFNGLUSEPROGRAMPROC)(GLuint program);
typedef void (GLAD_API_PTR *PFNGLVERTEXATTRIB1FPROC)(GLuint index, GLfloat x);
typedef void (GLAD_API_PTR *PFNGLVERTEXATTRIB1FVPROC)(GLuint index, const GLfloat * v);
typedef void (GLAD_API_PTR *PFNGLVERTEXATTRIB2FPROC)(GLuint index, GLfloat x, GLfloat y);
typedef void (GLAD_API_PTR *PFNGLVERTEXATTRIB2FVPROC)(GLuint index, const GLfloat * v);
typedef void (GLAD_API_PTR *PFNGLVERTEXATTRIB3FPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLAD_API_PTR *PFNGLVERTEXATTRIB3FVPROC)(GLuint index, const GLfloat * v);
typedef void (GLAD_API_PTR *PFNGLVERTEXATTRIB4FPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (GLAD_API_PTR *PFNGLVERTEXATTRIB4FVPROC)(GLuint index, const GLfloat * v);
typedef void (GLAD_API_PTR *PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);
typedef void (GLAD_API_PTR *PFNGLVIEWPORTPROC)(GLint x, GLint y, GLsizei width, GLsizei height);

GLAD_API_CALL PFNGLACTIVETEXTUREPROC glad_glActiveTexture;
#define glActiveTexture glad_glActiveTexture
GLAD_API_CALL PFNGLBINDBUFFERPROC glad_glBindBuffer;
#define glBindBuffer glad_glBindBuffer
GLAD_API_CALL PFNGLBINDFRAMEBUFFERPROC glad_glBindFramebuffer;
#define glBindFramebuffer glad_glBindFramebuffer
GLAD_API_CALL PFNGLBINDRENDERBUFFERPROC glad_glBindRenderbuffer;
#define glBindRenderbuffer glad_glBindRenderbuffer
GLAD_API_CALL PFNGLBINDTEXTUREPROC glad_glBindTexture;
#define glBindTexture glad_glBindTexture
GLAD_API_CALL PFNGLBLENDCOLORPROC glad_glBlendColor;
#define glBlendColor glad_glBlendColor
GLAD_API_CALL PFNGLBLENDEQUATIONPROC glad_glBlendEquation;
#define glBlendEquation glad_glBlendEquation
GLAD_API_CALL PFNGLBLENDEQUATIONSEPARATEPROC glad_glBlendEquationSeparate;
#define glBlendEquationSeparate glad_glBlendEquationSeparate
GLAD_API_CALL PFNGLBLENDFUNCPROC glad_glBlendFunc;
#define glBlendFunc glad_glBlendFunc
GLAD_API_CALL PFNGLBLENDFUNCSEPARATEPROC glad_glBlendFuncSeparate;
#define glBlendFuncSeparate glad_glBlendFuncSeparate
GLAD_API_CALL PFNGLBUFFERDATAPROC glad_glBufferData;
#define glBufferData glad_glBufferData
GLAD_API_CALL PFNGLBUFFERSUBDATAPROC glad_glBufferSubData;
#define glBufferSubData glad_glBufferSubData
GLAD_API_CALL PFNGLCHECKFRAMEBUFFERSTATUSPROC glad_glCheckFramebufferStatus;
#define glCheckFramebufferStatus glad_glCheckFramebufferStatus
GLAD_API_CALL PFNGLCLEARPROC glad_glClear;
#define glClear glad_glClear
GLAD_API_CALL PFNGLCLEARCOLORPROC glad_glClearColor;
#define glClearColor glad_glClearColor
GLAD_API_CALL PFNGLCLEARDEPTHFPROC glad_glClearDepthf;
#define glClearDepthf glad_glClearDepthf
GLAD_API_CALL PFNGLCLEARSTENCILPROC glad_glClearStencil;
#define glClearStencil glad_glClearStencil
GLAD_API_CALL PFNGLCOLORMASKPROC glad_glColorMask;
#define glColorMask glad_glColorMask
GLAD_API_CALL PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glad_glCompressedTexSubImage2D;
#define glCompressedTexSubImage2D glad_glCompressedTexSubImage2D
GLAD_API_CALL PFNGLCREATEPROGRAMPROC glad_glCreateProgram;
#define glCreateProgram glad_glCreateProgram
GLAD_API_CALL PFNGLCULLFACEPROC glad_glCullFace;
#define glCullFace glad_glCullFace
GLAD_API_CALL PFNGLDEPTHFUNCPROC glad_glDepthFunc;
#define glDepthFunc glad_glDepthFunc
GLAD_API_CALL PFNGLDEPTHMASKPROC glad_glDepthMask;
#define glDepthMask glad_glDepthMask
GLAD_API_CALL PFNGLDEPTHRANGEFPROC glad_glDepthRangef;
#define glDepthRangef glad_glDepthRangef
GLAD_API_CALL PFNGLDISABLEPROC glad_glDisable;
#define glDisable glad_glDisable
GLAD_API_CALL PFNGLDISABLEVERTEXATTRIBARRAYPROC glad_glDisableVertexAttribArray;
#define glDisableVertexAttribArray glad_glDisableVertexAttribArray
GLAD_API_CALL PFNGLDRAWARRAYSPROC glad_glDrawArrays;
#define glDrawArrays glad_glDrawArrays
GLAD_API_CALL PFNGLDRAWRANGEELEMENTSPROC glad_glDrawRangeElements;
#define glDrawRangeElements glad_glDrawRangeElements
GLAD_API_CALL PFNGLENABLEPROC glad_glEnable;
#define glEnable glad_glEnable
GLAD_API_CALL PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray;
#define glEnableVertexAttribArray glad_glEnableVertexAttribArray
GLAD_API_CALL PFNGLFINISHPROC glad_glFinish;
#define glFinish glad_glFinish
GLAD_API_CALL PFNGLFLUSHPROC glad_glFlush;
#define glFlush glad_glFlush
GLAD_API_CALL PFNGLFRAMEBUFFERRENDERBUFFERPROC glad_glFramebufferRenderbuffer;
#define glFramebufferRenderbuffer glad_glFramebufferRenderbuffer
GLAD_API_CALL PFNGLFRAMEBUFFERTEXTURE2DPROC glad_glFramebufferTexture2D;
#define glFramebufferTexture2D glad_glFramebufferTexture2D
GLAD_API_CALL PFNGLFRONTFACEPROC glad_glFrontFace;
#define glFrontFace glad_glFrontFace
GLAD_API_CALL PFNGLGENBUFFERSPROC glad_glGenBuffers;
#define glGenBuffers glad_glGenBuffers
GLAD_API_CALL PFNGLGENFRAMEBUFFERSPROC glad_glGenFramebuffers;
#define glGenFramebuffers glad_glGenFramebuffers
GLAD_API_CALL PFNGLGENRENDERBUFFERSPROC glad_glGenRenderbuffers;
#define glGenRenderbuffers glad_glGenRenderbuffers
GLAD_API_CALL PFNGLGENTEXTURESPROC glad_glGenTextures;
#define glGenTextures glad_glGenTextures
GLAD_API_CALL PFNGLGENERATEMIPMAPPROC glad_glGenerateMipmap;
#define glGenerateMipmap glad_glGenerateMipmap
GLAD_API_CALL PFNGLGETATTRIBLOCATIONPROC glad_glGetAttribLocation;
#define glGetAttribLocation glad_glGetAttribLocation
GLAD_API_CALL PFNGLGETBOOLEANVPROC glad_glGetBooleanv;
#define glGetBooleanv glad_glGetBooleanv
GLAD_API_CALL PFNGLGETBUFFERPARAMETERIVPROC glad_glGetBufferParameteriv;
#define glGetBufferParameteriv glad_glGetBufferParameteriv
GLAD_API_CALL PFNGLGETERRORPROC glad_glGetError;
#define glGetError glad_glGetError
GLAD_API_CALL PFNGLGETFLOATVPROC glad_glGetFloatv;
#define glGetFloatv glad_glGetFloatv
GLAD_API_CALL PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glad_glGetFramebufferAttachmentParameteriv;
#define glGetFramebufferAttachmentParameteriv glad_glGetFramebufferAttachmentParameteriv
GLAD_API_CALL PFNGLGETGRAPHICSRESETSTATUSPROC glad_glGetGraphicsResetStatus;
#define glGetGraphicsResetStatus glad_glGetGraphicsResetStatus
GLAD_API_CALL PFNGLGETINTEGERVPROC glad_glGetIntegerv;
#define glGetIntegerv glad_glGetIntegerv
GLAD_API_CALL PFNGLGETPROGRAMIVPROC glad_glGetProgramiv;
#define glGetProgramiv glad_glGetProgramiv
GLAD_API_CALL PFNGLGETRENDERBUFFERPARAMETERIVPROC glad_glGetRenderbufferParameteriv;
#define glGetRenderbufferParameteriv glad_glGetRenderbufferParameteriv
GLAD_API_CALL PFNGLGETSTRINGPROC glad_glGetString;
#define glGetString glad_glGetString
GLAD_API_CALL PFNGLGETTEXPARAMETERFVPROC glad_glGetTexParameterfv;
#define glGetTexParameterfv glad_glGetTexParameterfv
GLAD_API_CALL PFNGLGETTEXPARAMETERIVPROC glad_glGetTexParameteriv;
#define glGetTexParameteriv glad_glGetTexParameteriv
GLAD_API_CALL PFNGLGETUNIFORMLOCATIONPROC glad_glGetUniformLocation;
#define glGetUniformLocation glad_glGetUniformLocation
GLAD_API_CALL PFNGLGETVERTEXATTRIBPOINTERVPROC glad_glGetVertexAttribPointerv;
#define glGetVertexAttribPointerv glad_glGetVertexAttribPointerv
GLAD_API_CALL PFNGLGETVERTEXATTRIBFVPROC glad_glGetVertexAttribfv;
#define glGetVertexAttribfv glad_glGetVertexAttribfv
GLAD_API_CALL PFNGLGETVERTEXATTRIBIVPROC glad_glGetVertexAttribiv;
#define glGetVertexAttribiv glad_glGetVertexAttribiv
GLAD_API_CALL PFNGLGETNUNIFORMFVPROC glad_glGetnUniformfv;
#define glGetnUniformfv glad_glGetnUniformfv
GLAD_API_CALL PFNGLGETNUNIFORMIVPROC glad_glGetnUniformiv;
#define glGetnUniformiv glad_glGetnUniformiv
GLAD_API_CALL PFNGLHINTPROC glad_glHint;
#define glHint glad_glHint
GLAD_API_CALL PFNGLISENABLEDPROC glad_glIsEnabled;
#define glIsEnabled glad_glIsEnabled
GLAD_API_CALL PFNGLLINEWIDTHPROC glad_glLineWidth;
#define glLineWidth glad_glLineWidth
GLAD_API_CALL PFNGLPIXELSTOREIPROC glad_glPixelStorei;
#define glPixelStorei glad_glPixelStorei
GLAD_API_CALL PFNGLPOLYGONOFFSETPROC glad_glPolygonOffset;
#define glPolygonOffset glad_glPolygonOffset
GLAD_API_CALL PFNGLPROGRAMBINARYPROC glad_glProgramBinary;
#define glProgramBinary glad_glProgramBinary
GLAD_API_CALL PFNGLREADNPIXELSPROC glad_glReadnPixels;
#define glReadnPixels glad_glReadnPixels
GLAD_API_CALL PFNGLRENDERBUFFERSTORAGEPROC glad_glRenderbufferStorage;
#define glRenderbufferStorage glad_glRenderbufferStorage
GLAD_API_CALL PFNGLSAMPLECOVERAGEPROC glad_glSampleCoverage;
#define glSampleCoverage glad_glSampleCoverage
GLAD_API_CALL PFNGLSCISSORPROC glad_glScissor;
#define glScissor glad_glScissor
GLAD_API_CALL PFNGLSTENCILFUNCPROC glad_glStencilFunc;
#define glStencilFunc glad_glStencilFunc
GLAD_API_CALL PFNGLSTENCILFUNCSEPARATEPROC glad_glStencilFuncSeparate;
#define glStencilFuncSeparate glad_glStencilFuncSeparate
GLAD_API_CALL PFNGLSTENCILMASKPROC glad_glStencilMask;
#define glStencilMask glad_glStencilMask
GLAD_API_CALL PFNGLSTENCILMASKSEPARATEPROC glad_glStencilMaskSeparate;
#define glStencilMaskSeparate glad_glStencilMaskSeparate
GLAD_API_CALL PFNGLSTENCILOPPROC glad_glStencilOp;
#define glStencilOp glad_glStencilOp
GLAD_API_CALL PFNGLSTENCILOPSEPARATEPROC glad_glStencilOpSeparate;
#define glStencilOpSeparate glad_glStencilOpSeparate
GLAD_API_CALL PFNGLTEXPARAMETERFPROC glad_glTexParameterf;
#define glTexParameterf glad_glTexParameterf
GLAD_API_CALL PFNGLTEXPARAMETERFVPROC glad_glTexParameterfv;
#define glTexParameterfv glad_glTexParameterfv
GLAD_API_CALL PFNGLTEXPARAMETERIPROC glad_glTexParameteri;
#define glTexParameteri glad_glTexParameteri
GLAD_API_CALL PFNGLTEXPARAMETERIVPROC glad_glTexParameteriv;
#define glTexParameteriv glad_glTexParameteriv
GLAD_API_CALL PFNGLTEXSTORAGE2DPROC glad_glTexStorage2D;
#define glTexStorage2D glad_glTexStorage2D
GLAD_API_CALL PFNGLTEXSUBIMAGE2DPROC glad_glTexSubImage2D;
#define glTexSubImage2D glad_glTexSubImage2D
GLAD_API_CALL PFNGLUNIFORM1FPROC glad_glUniform1f;
#define glUniform1f glad_glUniform1f
GLAD_API_CALL PFNGLUNIFORM1FVPROC glad_glUniform1fv;
#define glUniform1fv glad_glUniform1fv
GLAD_API_CALL PFNGLUNIFORM1IPROC glad_glUniform1i;
#define glUniform1i glad_glUniform1i
GLAD_API_CALL PFNGLUNIFORM1IVPROC glad_glUniform1iv;
#define glUniform1iv glad_glUniform1iv
GLAD_API_CALL PFNGLUNIFORM2FPROC glad_glUniform2f;
#define glUniform2f glad_glUniform2f
GLAD_API_CALL PFNGLUNIFORM2FVPROC glad_glUniform2fv;
#define glUniform2fv glad_glUniform2fv
GLAD_API_CALL PFNGLUNIFORM2IPROC glad_glUniform2i;
#define glUniform2i glad_glUniform2i
GLAD_API_CALL PFNGLUNIFORM2IVPROC glad_glUniform2iv;
#define glUniform2iv glad_glUniform2iv
GLAD_API_CALL PFNGLUNIFORM3FPROC glad_glUniform3f;
#define glUniform3f glad_glUniform3f
GLAD_API_CALL PFNGLUNIFORM3FVPROC glad_glUniform3fv;
#define glUniform3fv glad_glUniform3fv
GLAD_API_CALL PFNGLUNIFORM3IPROC glad_glUniform3i;
#define glUniform3i glad_glUniform3i
GLAD_API_CALL PFNGLUNIFORM3IVPROC glad_glUniform3iv;
#define glUniform3iv glad_glUniform3iv
GLAD_API_CALL PFNGLUNIFORM4FPROC glad_glUniform4f;
#define glUniform4f glad_glUniform4f
GLAD_API_CALL PFNGLUNIFORM4FVPROC glad_glUniform4fv;
#define glUniform4fv glad_glUniform4fv
GLAD_API_CALL PFNGLUNIFORM4IPROC glad_glUniform4i;
#define glUniform4i glad_glUniform4i
GLAD_API_CALL PFNGLUNIFORM4IVPROC glad_glUniform4iv;
#define glUniform4iv glad_glUniform4iv
GLAD_API_CALL PFNGLUNIFORMMATRIX2FVPROC glad_glUniformMatrix2fv;
#define glUniformMatrix2fv glad_glUniformMatrix2fv
GLAD_API_CALL PFNGLUNIFORMMATRIX3FVPROC glad_glUniformMatrix3fv;
#define glUniformMatrix3fv glad_glUniformMatrix3fv
GLAD_API_CALL PFNGLUNIFORMMATRIX4FVPROC glad_glUniformMatrix4fv;
#define glUniformMatrix4fv glad_glUniformMatrix4fv
GLAD_API_CALL PFNGLUSEPROGRAMPROC glad_glUseProgram;
#define glUseProgram glad_glUseProgram
GLAD_API_CALL PFNGLVERTEXATTRIB1FPROC glad_glVertexAttrib1f;
#define glVertexAttrib1f glad_glVertexAttrib1f
GLAD_API_CALL PFNGLVERTEXATTRIB1FVPROC glad_glVertexAttrib1fv;
#define glVertexAttrib1fv glad_glVertexAttrib1fv
GLAD_API_CALL PFNGLVERTEXATTRIB2FPROC glad_glVertexAttrib2f;
#define glVertexAttrib2f glad_glVertexAttrib2f
GLAD_API_CALL PFNGLVERTEXATTRIB2FVPROC glad_glVertexAttrib2fv;
#define glVertexAttrib2fv glad_glVertexAttrib2fv
GLAD_API_CALL PFNGLVERTEXATTRIB3FPROC glad_glVertexAttrib3f;
#define glVertexAttrib3f glad_glVertexAttrib3f
GLAD_API_CALL PFNGLVERTEXATTRIB3FVPROC glad_glVertexAttrib3fv;
#define glVertexAttrib3fv glad_glVertexAttrib3fv
GLAD_API_CALL PFNGLVERTEXATTRIB4FPROC glad_glVertexAttrib4f;
#define glVertexAttrib4f glad_glVertexAttrib4f
GLAD_API_CALL PFNGLVERTEXATTRIB4FVPROC glad_glVertexAttrib4fv;
#define glVertexAttrib4fv glad_glVertexAttrib4fv
GLAD_API_CALL PFNGLVERTEXATTRIBPOINTERPROC glad_glVertexAttribPointer;
#define glVertexAttribPointer glad_glVertexAttribPointer
GLAD_API_CALL PFNGLVIEWPORTPROC glad_glViewport;
#define glViewport glad_glViewport





GLAD_API_CALL int gladLoadGLSC2UserPtr( GLADuserptrloadfunc load, void *userptr);
GLAD_API_CALL int gladLoadGLSC2( GLADloadfunc load);



#ifdef __cplusplus
}
#endif
#endif
