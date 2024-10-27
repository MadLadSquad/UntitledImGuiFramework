/**
 * Loader 
 *
 * SPDX-License-Identifier: (WTFPL OR CC0-1.0) AND Apache-2.0
 *
 * Generator: C/C++
 * Specification: gl
 * Extensions: 74
 *
 * APIs:
 *  - gles1:common=1.0
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
 *    --api='gles1:common=1.0' --extensions='GL_AMD_compressed_3DC_texture,GL_AMD_compressed_ATC_texture,GL_APPLE_copy_texture_levels,GL_APPLE_framebuffer_multisample,GL_APPLE_sync,GL_APPLE_texture_2D_limited_npot,GL_APPLE_texture_format_BGRA8888,GL_APPLE_texture_max_level,GL_ARM_rgba8,GL_EXT_blend_minmax,GL_EXT_debug_marker,GL_EXT_discard_framebuffer,GL_EXT_map_buffer_range,GL_EXT_multi_draw_arrays,GL_EXT_multisampled_render_to_texture,GL_EXT_read_format_bgra,GL_EXT_robustness,GL_EXT_sRGB,GL_EXT_texture_compression_dxt1,GL_EXT_texture_filter_anisotropic,GL_EXT_texture_format_BGRA8888,GL_EXT_texture_lod_bias,GL_EXT_texture_storage,GL_IMG_multisampled_render_to_texture,GL_IMG_read_format,GL_IMG_texture_compression_pvrtc,GL_IMG_texture_env_enhanced_fixed_function,GL_IMG_user_clip_plane,GL_KHR_debug,GL_NV_fence,GL_OES_EGL_image,GL_OES_EGL_image_external,GL_OES_blend_equation_separate,GL_OES_blend_func_separate,GL_OES_blend_subtract,GL_OES_byte_coordinates,GL_OES_compressed_ETC1_RGB8_sub_texture,GL_OES_compressed_ETC1_RGB8_texture,GL_OES_compressed_paletted_texture,GL_OES_depth24,GL_OES_depth32,GL_OES_draw_texture,GL_OES_element_index_uint,GL_OES_extended_matrix_palette,GL_OES_fbo_render_mipmap,GL_OES_fixed_point,GL_OES_framebuffer_object,GL_OES_mapbuffer,GL_OES_matrix_get,GL_OES_matrix_palette,GL_OES_packed_depth_stencil,GL_OES_point_size_array,GL_OES_point_sprite,GL_OES_query_matrix,GL_OES_read_format,GL_OES_required_internalformat,GL_OES_rgb8_rgba8,GL_OES_single_precision,GL_OES_stencil1,GL_OES_stencil4,GL_OES_stencil8,GL_OES_stencil_wrap,GL_OES_surfaceless_context,GL_OES_texture_cube_map,GL_OES_texture_env_crossbar,GL_OES_texture_mirrored_repeat,GL_OES_texture_npot,GL_OES_vertex_array_object,GL_QCOM_driver_control,GL_QCOM_extended_get,GL_QCOM_extended_get2,GL_QCOM_perfmon_global_mode,GL_QCOM_tiled_rendering,GL_QCOM_writeonly_rendering' c
 *
 * Online:
 *    http://glad.sh/#api=gles1%3Acommon%3D1.0&generator=c&options=
 *
 */

#ifndef GLAD_GLES1_H_
#define GLAD_GLES1_H_

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifdef __gl_h_
  #error OpenGL ES 1 header already included (API: gles1), remove previous include!
#endif
#define __gl_h_ 1
#ifdef __gles1_gl_h_
  #error OpenGL ES 1 header already included (API: gles1), remove previous include!
#endif
#define __gles1_gl_h_ 1
#ifdef __clang__
#pragma clang diagnostic pop
#endif

#define GLAD_GLES1

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

#define GL_3DC_XY_AMD 0x87FA
#define GL_3DC_X_AMD 0x87F9
#define GL_ACTIVE_TEXTURE 0x84E0
#define GL_ADD 0x0104
#define GL_ADD_BLEND_IMG 0x8C09
#define GL_ADD_SIGNED 0x8574
#define GL_ALIASED_LINE_WIDTH_RANGE 0x846E
#define GL_ALIASED_POINT_SIZE_RANGE 0x846D
#define GL_ALL_COMPLETED_NV 0x84F2
#define GL_ALPHA 0x1906
#define GL_ALPHA16F_EXT 0x881C
#define GL_ALPHA32F_EXT 0x8816
#define GL_ALPHA8_EXT 0x803C
#define GL_ALPHA8_OES 0x803C
#define GL_ALPHA_BITS 0x0D55
#define GL_ALPHA_SCALE 0x0D1C
#define GL_ALPHA_TEST 0x0BC0
#define GL_ALPHA_TEST_FUNC 0x0BC1
#define GL_ALPHA_TEST_REF 0x0BC2
#define GL_ALREADY_SIGNALED_APPLE 0x911A
#define GL_ALWAYS 0x0207
#define GL_AMBIENT 0x1200
#define GL_AMBIENT_AND_DIFFUSE 0x1602
#define GL_AND 0x1501
#define GL_AND_INVERTED 0x1504
#define GL_AND_REVERSE 0x1502
#define GL_ARRAY_BUFFER 0x8892
#define GL_ARRAY_BUFFER_BINDING 0x8894
#define GL_ATC_RGBA_EXPLICIT_ALPHA_AMD 0x8C93
#define GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD 0x87EE
#define GL_ATC_RGB_AMD 0x8C92
#define GL_BACK 0x0405
#define GL_BGRA8_EXT 0x93A1
#define GL_BGRA_EXT 0x80E1
#define GL_BGRA_IMG 0x80E1
#define GL_BLEND 0x0BE2
#define GL_BLEND_DST 0x0BE0
#define GL_BLEND_DST_ALPHA_OES 0x80CA
#define GL_BLEND_DST_RGB_OES 0x80C8
#define GL_BLEND_EQUATION_ALPHA_OES 0x883D
#define GL_BLEND_EQUATION_OES 0x8009
#define GL_BLEND_EQUATION_RGB_OES 0x8009
#define GL_BLEND_SRC 0x0BE1
#define GL_BLEND_SRC_ALPHA_OES 0x80CB
#define GL_BLEND_SRC_RGB_OES 0x80C9
#define GL_BLUE_BITS 0x0D54
#define GL_BUFFER_ACCESS_OES 0x88BB
#define GL_BUFFER_MAPPED_OES 0x88BC
#define GL_BUFFER_MAP_POINTER_OES 0x88BD
#define GL_BUFFER_SIZE 0x8764
#define GL_BUFFER_USAGE 0x8765
#define GL_BYTE 0x1400
#define GL_CCW 0x0901
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_CLEAR 0x1500
#define GL_CLIENT_ACTIVE_TEXTURE 0x84E1
#define GL_CLIP_PLANE0 0x3000
#define GL_CLIP_PLANE0_IMG 0x3000
#define GL_CLIP_PLANE1 0x3001
#define GL_CLIP_PLANE1_IMG 0x3001
#define GL_CLIP_PLANE2 0x3002
#define GL_CLIP_PLANE2_IMG 0x3002
#define GL_CLIP_PLANE3 0x3003
#define GL_CLIP_PLANE3_IMG 0x3003
#define GL_CLIP_PLANE4 0x3004
#define GL_CLIP_PLANE4_IMG 0x3004
#define GL_CLIP_PLANE5 0x3005
#define GL_CLIP_PLANE5_IMG 0x3005
#define GL_COLOR_ARRAY 0x8076
#define GL_COLOR_ARRAY_BUFFER_BINDING 0x8898
#define GL_COLOR_ARRAY_POINTER 0x8090
#define GL_COLOR_ARRAY_SIZE 0x8081
#define GL_COLOR_ARRAY_STRIDE 0x8083
#define GL_COLOR_ARRAY_TYPE 0x8082
#define GL_COLOR_ATTACHMENT0_OES 0x8CE0
#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_COLOR_BUFFER_BIT0_QCOM 0x00000001
#define GL_COLOR_BUFFER_BIT1_QCOM 0x00000002
#define GL_COLOR_BUFFER_BIT2_QCOM 0x00000004
#define GL_COLOR_BUFFER_BIT3_QCOM 0x00000008
#define GL_COLOR_BUFFER_BIT4_QCOM 0x00000010
#define GL_COLOR_BUFFER_BIT5_QCOM 0x00000020
#define GL_COLOR_BUFFER_BIT6_QCOM 0x00000040
#define GL_COLOR_BUFFER_BIT7_QCOM 0x00000080
#define GL_COLOR_CLEAR_VALUE 0x0C22
#define GL_COLOR_EXT 0x1800
#define GL_COLOR_LOGIC_OP 0x0BF2
#define GL_COLOR_MATERIAL 0x0B57
#define GL_COLOR_WRITEMASK 0x0C23
#define GL_COMBINE 0x8570
#define GL_COMBINE_ALPHA 0x8572
#define GL_COMBINE_RGB 0x8571
#define GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG 0x8C03
#define GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG 0x8C02
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT 0x83F1
#define GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG 0x8C01
#define GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG 0x8C00
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT 0x83F0
#define GL_COMPRESSED_TEXTURE_FORMATS 0x86A3
#define GL_CONDITION_SATISFIED_APPLE 0x911C
#define GL_CONSTANT 0x8576
#define GL_CONSTANT_ATTENUATION 0x1207
#define GL_CONTEXT_ROBUST_ACCESS_EXT 0x90F3
#define GL_COORD_REPLACE_OES 0x8862
#define GL_COPY 0x1503
#define GL_COPY_INVERTED 0x150C
#define GL_CULL_FACE 0x0B44
#define GL_CULL_FACE_MODE 0x0B45
#define GL_CURRENT_COLOR 0x0B00
#define GL_CURRENT_NORMAL 0x0B02
#define GL_CURRENT_PALETTE_MATRIX_OES 0x8843
#define GL_CURRENT_TEXTURE_COORDS 0x0B03
#define GL_CW 0x0900
#define GL_DECAL 0x2101
#define GL_DECR 0x1E03
#define GL_DECR_WRAP_OES 0x8508
#define GL_DEPTH24_STENCIL8_OES 0x88F0
#define GL_DEPTH_ATTACHMENT_OES 0x8D00
#define GL_DEPTH_BITS 0x0D56
#define GL_DEPTH_BUFFER_BIT 0x00000100
#define GL_DEPTH_BUFFER_BIT0_QCOM 0x00000100
#define GL_DEPTH_BUFFER_BIT1_QCOM 0x00000200
#define GL_DEPTH_BUFFER_BIT2_QCOM 0x00000400
#define GL_DEPTH_BUFFER_BIT3_QCOM 0x00000800
#define GL_DEPTH_BUFFER_BIT4_QCOM 0x00001000
#define GL_DEPTH_BUFFER_BIT5_QCOM 0x00002000
#define GL_DEPTH_BUFFER_BIT6_QCOM 0x00004000
#define GL_DEPTH_BUFFER_BIT7_QCOM 0x00008000
#define GL_DEPTH_CLEAR_VALUE 0x0B73
#define GL_DEPTH_COMPONENT16_OES 0x81A5
#define GL_DEPTH_COMPONENT24_OES 0x81A6
#define GL_DEPTH_COMPONENT32_OES 0x81A7
#define GL_DEPTH_EXT 0x1801
#define GL_DEPTH_FUNC 0x0B74
#define GL_DEPTH_RANGE 0x0B70
#define GL_DEPTH_STENCIL_OES 0x84F9
#define GL_DEPTH_TEST 0x0B71
#define GL_DEPTH_WRITEMASK 0x0B72
#define GL_DIFFUSE 0x1201
#define GL_DITHER 0x0BD0
#define GL_DONT_CARE 0x1100
#define GL_DOT3_RGB 0x86AE
#define GL_DOT3_RGBA 0x86AF
#define GL_DOT3_RGBA_IMG 0x86AF
#define GL_DRAW_FRAMEBUFFER_APPLE 0x8CA9
#define GL_DRAW_FRAMEBUFFER_BINDING_APPLE 0x8CA6
#define GL_DST_ALPHA 0x0304
#define GL_DST_COLOR 0x0306
#define GL_DYNAMIC_DRAW 0x88E8
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_ELEMENT_ARRAY_BUFFER_BINDING 0x8895
#define GL_EMISSION 0x1600
#define GL_EQUAL 0x0202
#define GL_EQUIV 0x1509
#define GL_ETC1_RGB8_OES 0x8D64
#define GL_EXP 0x0800
#define GL_EXP2 0x0801
#define GL_EXTENSIONS 0x1F03
#define GL_FACTOR_ALPHA_MODULATE_IMG 0x8C07
#define GL_FALSE 0
#define GL_FASTEST 0x1101
#define GL_FENCE_CONDITION_NV 0x84F4
#define GL_FENCE_STATUS_NV 0x84F3
#define GL_FIXED 0x140C
#define GL_FIXED_OES 0x140C
#define GL_FLAT 0x1D00
#define GL_FLOAT 0x1406
#define GL_FOG 0x0B60
#define GL_FOG_COLOR 0x0B66
#define GL_FOG_DENSITY 0x0B62
#define GL_FOG_END 0x0B64
#define GL_FOG_HINT 0x0C54
#define GL_FOG_MODE 0x0B65
#define GL_FOG_START 0x0B63
#define GL_FRAGMENT_ALPHA_MODULATE_IMG 0x8C08
#define GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT 0x8210
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_OES 0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_OES 0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_OES 0x8CD3
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_OES 0x8CD2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT 0x8D6C
#define GL_FRAMEBUFFER_BINDING_OES 0x8CA6
#define GL_FRAMEBUFFER_COMPLETE_OES 0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_OES 0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_OES 0x8CD9
#define GL_FRAMEBUFFER_INCOMPLETE_FORMATS_OES 0x8CDA
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_OES 0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_APPLE 0x8D56
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT 0x8D56
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG 0x9134
#define GL_FRAMEBUFFER_OES 0x8D40
#define GL_FRAMEBUFFER_UNDEFINED_OES 0x8219
#define GL_FRAMEBUFFER_UNSUPPORTED_OES 0x8CDD
#define GL_FRONT 0x0404
#define GL_FRONT_AND_BACK 0x0408
#define GL_FRONT_FACE 0x0B46
#define GL_FUNC_ADD_OES 0x8006
#define GL_FUNC_REVERSE_SUBTRACT_OES 0x800B
#define GL_FUNC_SUBTRACT_OES 0x800A
#define GL_GENERATE_MIPMAP 0x8191
#define GL_GENERATE_MIPMAP_HINT 0x8192
#define GL_GEQUAL 0x0206
#define GL_GREATER 0x0204
#define GL_GREEN_BITS 0x0D53
#define GL_GUILTY_CONTEXT_RESET_EXT 0x8253
#define GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES 0x8B9B
#define GL_IMPLEMENTATION_COLOR_READ_TYPE_OES 0x8B9A
#define GL_INCR 0x1E02
#define GL_INCR_WRAP_OES 0x8507
#define GL_INNOCENT_CONTEXT_RESET_EXT 0x8254
#define GL_INTERPOLATE 0x8575
#define GL_INVALID_ENUM 0x0500
#define GL_INVALID_FRAMEBUFFER_OPERATION_OES 0x0506
#define GL_INVALID_OPERATION 0x0502
#define GL_INVALID_VALUE 0x0501
#define GL_INVERT 0x150A
#define GL_KEEP 0x1E00
#define GL_LEQUAL 0x0203
#define GL_LESS 0x0201
#define GL_LIGHT0 0x4000
#define GL_LIGHT1 0x4001
#define GL_LIGHT2 0x4002
#define GL_LIGHT3 0x4003
#define GL_LIGHT4 0x4004
#define GL_LIGHT5 0x4005
#define GL_LIGHT6 0x4006
#define GL_LIGHT7 0x4007
#define GL_LIGHTING 0x0B50
#define GL_LIGHT_MODEL_AMBIENT 0x0B53
#define GL_LIGHT_MODEL_TWO_SIDE 0x0B52
#define GL_LINEAR 0x2601
#define GL_LINEAR_ATTENUATION 0x1208
#define GL_LINEAR_MIPMAP_LINEAR 0x2703
#define GL_LINEAR_MIPMAP_NEAREST 0x2701
#define GL_LINES 0x0001
#define GL_LINE_LOOP 0x0002
#define GL_LINE_SMOOTH 0x0B20
#define GL_LINE_SMOOTH_HINT 0x0C52
#define GL_LINE_STRIP 0x0003
#define GL_LINE_WIDTH 0x0B21
#define GL_LINE_WIDTH_RANGE 0x0B22
#define GL_LOGIC_OP_MODE 0x0BF0
#define GL_LOSE_CONTEXT_ON_RESET_EXT 0x8252
#define GL_LUMINANCE 0x1909
#define GL_LUMINANCE16F_EXT 0x881E
#define GL_LUMINANCE32F_EXT 0x8818
#define GL_LUMINANCE4_ALPHA4_OES 0x8043
#define GL_LUMINANCE8_ALPHA8_EXT 0x8045
#define GL_LUMINANCE8_ALPHA8_OES 0x8045
#define GL_LUMINANCE8_EXT 0x8040
#define GL_LUMINANCE8_OES 0x8040
#define GL_LUMINANCE_ALPHA 0x190A
#define GL_LUMINANCE_ALPHA16F_EXT 0x881F
#define GL_LUMINANCE_ALPHA32F_EXT 0x8819
#define GL_MAP_FLUSH_EXPLICIT_BIT_EXT 0x0010
#define GL_MAP_INVALIDATE_BUFFER_BIT_EXT 0x0008
#define GL_MAP_INVALIDATE_RANGE_BIT_EXT 0x0004
#define GL_MAP_READ_BIT_EXT 0x0001
#define GL_MAP_UNSYNCHRONIZED_BIT_EXT 0x0020
#define GL_MAP_WRITE_BIT_EXT 0x0002
#define GL_MATRIX_INDEX_ARRAY_BUFFER_BINDING_OES 0x8B9E
#define GL_MATRIX_INDEX_ARRAY_OES 0x8844
#define GL_MATRIX_INDEX_ARRAY_POINTER_OES 0x8849
#define GL_MATRIX_INDEX_ARRAY_SIZE_OES 0x8846
#define GL_MATRIX_INDEX_ARRAY_STRIDE_OES 0x8848
#define GL_MATRIX_INDEX_ARRAY_TYPE_OES 0x8847
#define GL_MATRIX_MODE 0x0BA0
#define GL_MATRIX_PALETTE_OES 0x8840
#define GL_MAX_CLIP_PLANES 0x0D32
#define GL_MAX_CLIP_PLANES_IMG 0x0D32
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE_OES 0x851C
#define GL_MAX_EXT 0x8008
#define GL_MAX_LIGHTS 0x0D31
#define GL_MAX_MODELVIEW_STACK_DEPTH 0x0D36
#define GL_MAX_PALETTE_MATRICES_OES 0x8842
#define GL_MAX_PROJECTION_STACK_DEPTH 0x0D38
#define GL_MAX_RENDERBUFFER_SIZE_OES 0x84E8
#define GL_MAX_SAMPLES_APPLE 0x8D57
#define GL_MAX_SAMPLES_EXT 0x8D57
#define GL_MAX_SAMPLES_IMG 0x9135
#define GL_MAX_SERVER_WAIT_TIMEOUT_APPLE 0x9111
#define GL_MAX_TEXTURE_LOD_BIAS_EXT 0x84FD
#define GL_MAX_TEXTURE_MAX_ANISOTROPY 0x84FF
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#define GL_MAX_TEXTURE_SIZE 0x0D33
#define GL_MAX_TEXTURE_STACK_DEPTH 0x0D39
#define GL_MAX_TEXTURE_UNITS 0x84E2
#define GL_MAX_VERTEX_UNITS_OES 0x86A4
#define GL_MAX_VIEWPORT_DIMS 0x0D3A
#define GL_MIN_EXT 0x8007
#define GL_MIRRORED_REPEAT_OES 0x8370
#define GL_MODELVIEW 0x1700
#define GL_MODELVIEW_MATRIX 0x0BA6
#define GL_MODELVIEW_MATRIX_FLOAT_AS_INT_BITS_OES 0x898D
#define GL_MODELVIEW_STACK_DEPTH 0x0BA3
#define GL_MODULATE 0x2100
#define GL_MODULATE_COLOR_IMG 0x8C04
#define GL_MULTISAMPLE 0x809D
#define GL_MULTISAMPLE_BUFFER_BIT0_QCOM 0x01000000
#define GL_MULTISAMPLE_BUFFER_BIT1_QCOM 0x02000000
#define GL_MULTISAMPLE_BUFFER_BIT2_QCOM 0x04000000
#define GL_MULTISAMPLE_BUFFER_BIT3_QCOM 0x08000000
#define GL_MULTISAMPLE_BUFFER_BIT4_QCOM 0x10000000
#define GL_MULTISAMPLE_BUFFER_BIT5_QCOM 0x20000000
#define GL_MULTISAMPLE_BUFFER_BIT6_QCOM 0x40000000
#define GL_MULTISAMPLE_BUFFER_BIT7_QCOM 0x80000000
#define GL_NAND 0x150E
#define GL_NEAREST 0x2600
#define GL_NEAREST_MIPMAP_LINEAR 0x2702
#define GL_NEAREST_MIPMAP_NEAREST 0x2700
#define GL_NEVER 0x0200
#define GL_NICEST 0x1102
#define GL_NONE_OES 0
#define GL_NOOP 0x1505
#define GL_NOR 0x1508
#define GL_NORMALIZE 0x0BA1
#define GL_NORMAL_ARRAY 0x8075
#define GL_NORMAL_ARRAY_BUFFER_BINDING 0x8897
#define GL_NORMAL_ARRAY_POINTER 0x808F
#define GL_NORMAL_ARRAY_STRIDE 0x807F
#define GL_NORMAL_ARRAY_TYPE 0x807E
#define GL_NORMAL_MAP_OES 0x8511
#define GL_NOTEQUAL 0x0205
#define GL_NO_ERROR 0
#define GL_NO_RESET_NOTIFICATION_EXT 0x8261
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS 0x86A2
#define GL_OBJECT_TYPE_APPLE 0x9112
#define GL_ONE 1
#define GL_ONE_MINUS_DST_ALPHA 0x0305
#define GL_ONE_MINUS_DST_COLOR 0x0307
#define GL_ONE_MINUS_SRC_ALPHA 0x0303
#define GL_ONE_MINUS_SRC_COLOR 0x0301
#define GL_OPERAND0_ALPHA 0x8598
#define GL_OPERAND0_RGB 0x8590
#define GL_OPERAND1_ALPHA 0x8599
#define GL_OPERAND1_RGB 0x8591
#define GL_OPERAND2_ALPHA 0x859A
#define GL_OPERAND2_RGB 0x8592
#define GL_OR 0x1507
#define GL_OR_INVERTED 0x150D
#define GL_OR_REVERSE 0x150B
#define GL_OUT_OF_MEMORY 0x0505
#define GL_PACK_ALIGNMENT 0x0D05
#define GL_PALETTE4_R5_G6_B5_OES 0x8B92
#define GL_PALETTE4_RGB5_A1_OES 0x8B94
#define GL_PALETTE4_RGB8_OES 0x8B90
#define GL_PALETTE4_RGBA4_OES 0x8B93
#define GL_PALETTE4_RGBA8_OES 0x8B91
#define GL_PALETTE8_R5_G6_B5_OES 0x8B97
#define GL_PALETTE8_RGB5_A1_OES 0x8B99
#define GL_PALETTE8_RGB8_OES 0x8B95
#define GL_PALETTE8_RGBA4_OES 0x8B98
#define GL_PALETTE8_RGBA8_OES 0x8B96
#define GL_PERFMON_GLOBAL_MODE_QCOM 0x8FA0
#define GL_PERSPECTIVE_CORRECTION_HINT 0x0C50
#define GL_POINTS 0x0000
#define GL_POINT_DISTANCE_ATTENUATION 0x8129
#define GL_POINT_FADE_THRESHOLD_SIZE 0x8128
#define GL_POINT_SIZE 0x0B11
#define GL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES 0x8B9F
#define GL_POINT_SIZE_ARRAY_OES 0x8B9C
#define GL_POINT_SIZE_ARRAY_POINTER_OES 0x898C
#define GL_POINT_SIZE_ARRAY_STRIDE_OES 0x898B
#define GL_POINT_SIZE_ARRAY_TYPE_OES 0x898A
#define GL_POINT_SIZE_MAX 0x8127
#define GL_POINT_SIZE_MIN 0x8126
#define GL_POINT_SIZE_RANGE 0x0B12
#define GL_POINT_SMOOTH 0x0B10
#define GL_POINT_SMOOTH_HINT 0x0C51
#define GL_POINT_SPRITE_OES 0x8861
#define GL_POLYGON_OFFSET_FACTOR 0x8038
#define GL_POLYGON_OFFSET_FILL 0x8037
#define GL_POLYGON_OFFSET_UNITS 0x2A00
#define GL_POSITION 0x1203
#define GL_PREVIOUS 0x8578
#define GL_PRIMARY_COLOR 0x8577
#define GL_PROJECTION 0x1701
#define GL_PROJECTION_MATRIX 0x0BA7
#define GL_PROJECTION_MATRIX_FLOAT_AS_INT_BITS_OES 0x898E
#define GL_PROJECTION_STACK_DEPTH 0x0BA4
#define GL_QUADRATIC_ATTENUATION 0x1209
#define GL_R16F_EXT 0x822D
#define GL_R32F_EXT 0x822E
#define GL_R8_EXT 0x8229
#define GL_READ_FRAMEBUFFER_APPLE 0x8CA8
#define GL_READ_FRAMEBUFFER_BINDING_APPLE 0x8CAA
#define GL_RECIP_ADD_SIGNED_ALPHA_IMG 0x8C05
#define GL_RED_BITS 0x0D52
#define GL_REFLECTION_MAP_OES 0x8512
#define GL_RENDERBUFFER_ALPHA_SIZE_OES 0x8D53
#define GL_RENDERBUFFER_BINDING_OES 0x8CA7
#define GL_RENDERBUFFER_BLUE_SIZE_OES 0x8D52
#define GL_RENDERBUFFER_DEPTH_SIZE_OES 0x8D54
#define GL_RENDERBUFFER_GREEN_SIZE_OES 0x8D51
#define GL_RENDERBUFFER_HEIGHT_OES 0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT_OES 0x8D44
#define GL_RENDERBUFFER_OES 0x8D41
#define GL_RENDERBUFFER_RED_SIZE_OES 0x8D50
#define GL_RENDERBUFFER_SAMPLES_APPLE 0x8CAB
#define GL_RENDERBUFFER_SAMPLES_EXT 0x8CAB
#define GL_RENDERBUFFER_SAMPLES_IMG 0x9133
#define GL_RENDERBUFFER_STENCIL_SIZE_OES 0x8D55
#define GL_RENDERBUFFER_WIDTH_OES 0x8D42
#define GL_RENDERER 0x1F01
#define GL_REPEAT 0x2901
#define GL_REPLACE 0x1E01
#define GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES 0x8D68
#define GL_RESCALE_NORMAL 0x803A
#define GL_RESET_NOTIFICATION_STRATEGY_EXT 0x8256
#define GL_RG16F_EXT 0x822F
#define GL_RG32F_EXT 0x8230
#define GL_RG8_EXT 0x822B
#define GL_RGB 0x1907
#define GL_RGB10_A2_EXT 0x8059
#define GL_RGB10_EXT 0x8052
#define GL_RGB16F_EXT 0x881B
#define GL_RGB32F_EXT 0x8815
#define GL_RGB565_OES 0x8D62
#define GL_RGB5_A1_OES 0x8057
#define GL_RGB8_OES 0x8051
#define GL_RGBA 0x1908
#define GL_RGBA16F_EXT 0x881A
#define GL_RGBA32F_EXT 0x8814
#define GL_RGBA4_OES 0x8056
#define GL_RGBA8_OES 0x8058
#define GL_RGB_SCALE 0x8573
#define GL_SAMPLES 0x80A9
#define GL_SAMPLE_ALPHA_TO_COVERAGE 0x809E
#define GL_SAMPLE_ALPHA_TO_ONE 0x809F
#define GL_SAMPLE_BUFFERS 0x80A8
#define GL_SAMPLE_COVERAGE 0x80A0
#define GL_SAMPLE_COVERAGE_INVERT 0x80AB
#define GL_SAMPLE_COVERAGE_VALUE 0x80AA
#define GL_SCISSOR_BOX 0x0C10
#define GL_SCISSOR_TEST 0x0C11
#define GL_SET 0x150F
#define GL_SHADE_MODEL 0x0B54
#define GL_SHININESS 0x1601
#define GL_SHORT 0x1402
#define GL_SIGNALED_APPLE 0x9119
#define GL_SMOOTH 0x1D01
#define GL_SMOOTH_LINE_WIDTH_RANGE 0x0B22
#define GL_SMOOTH_POINT_SIZE_RANGE 0x0B12
#define GL_SOURCE0_ALPHA 0x8588
#define GL_SOURCE0_RGB 0x8580
#define GL_SOURCE1_ALPHA 0x8589
#define GL_SOURCE1_RGB 0x8581
#define GL_SOURCE2_ALPHA 0x858A
#define GL_SOURCE2_RGB 0x8582
#define GL_SPECULAR 0x1202
#define GL_SPOT_CUTOFF 0x1206
#define GL_SPOT_DIRECTION 0x1204
#define GL_SPOT_EXPONENT 0x1205
#define GL_SRC0_ALPHA 0x8588
#define GL_SRC0_RGB 0x8580
#define GL_SRC1_ALPHA 0x8589
#define GL_SRC1_RGB 0x8581
#define GL_SRC2_ALPHA 0x858A
#define GL_SRC2_RGB 0x8582
#define GL_SRC_ALPHA 0x0302
#define GL_SRC_ALPHA_SATURATE 0x0308
#define GL_SRC_COLOR 0x0300
#define GL_SRGB8_ALPHA8_EXT 0x8C43
#define GL_SRGB_ALPHA_EXT 0x8C42
#define GL_SRGB_EXT 0x8C40
#define GL_STACK_OVERFLOW 0x0503
#define GL_STACK_UNDERFLOW 0x0504
#define GL_STATE_RESTORE 0x8BDC
#define GL_STATIC_DRAW 0x88E4
#define GL_STENCIL_ATTACHMENT_OES 0x8D20
#define GL_STENCIL_BITS 0x0D57
#define GL_STENCIL_BUFFER_BIT 0x00000400
#define GL_STENCIL_BUFFER_BIT0_QCOM 0x00010000
#define GL_STENCIL_BUFFER_BIT1_QCOM 0x00020000
#define GL_STENCIL_BUFFER_BIT2_QCOM 0x00040000
#define GL_STENCIL_BUFFER_BIT3_QCOM 0x00080000
#define GL_STENCIL_BUFFER_BIT4_QCOM 0x00100000
#define GL_STENCIL_BUFFER_BIT5_QCOM 0x00200000
#define GL_STENCIL_BUFFER_BIT6_QCOM 0x00400000
#define GL_STENCIL_BUFFER_BIT7_QCOM 0x00800000
#define GL_STENCIL_CLEAR_VALUE 0x0B91
#define GL_STENCIL_EXT 0x1802
#define GL_STENCIL_FAIL 0x0B94
#define GL_STENCIL_FUNC 0x0B92
#define GL_STENCIL_INDEX1_OES 0x8D46
#define GL_STENCIL_INDEX4_OES 0x8D47
#define GL_STENCIL_INDEX8_OES 0x8D48
#define GL_STENCIL_PASS_DEPTH_FAIL 0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS 0x0B96
#define GL_STENCIL_REF 0x0B97
#define GL_STENCIL_TEST 0x0B90
#define GL_STENCIL_VALUE_MASK 0x0B93
#define GL_STENCIL_WRITEMASK 0x0B98
#define GL_SUBPIXEL_BITS 0x0D50
#define GL_SUBTRACT 0x84E7
#define GL_SYNC_CONDITION_APPLE 0x9113
#define GL_SYNC_FENCE_APPLE 0x9116
#define GL_SYNC_FLAGS_APPLE 0x9115
#define GL_SYNC_FLUSH_COMMANDS_BIT_APPLE 0x00000001
#define GL_SYNC_GPU_COMMANDS_COMPLETE_APPLE 0x9117
#define GL_SYNC_OBJECT_APPLE 0x8A53
#define GL_SYNC_STATUS_APPLE 0x9114
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
#define GL_TEXTURE_ALPHA_MODULATE_IMG 0x8C06
#define GL_TEXTURE_BINDING_2D 0x8069
#define GL_TEXTURE_BINDING_CUBE_MAP_OES 0x8514
#define GL_TEXTURE_BINDING_EXTERNAL_OES 0x8D67
#define GL_TEXTURE_COORD_ARRAY 0x8078
#define GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING 0x889A
#define GL_TEXTURE_COORD_ARRAY_POINTER 0x8092
#define GL_TEXTURE_COORD_ARRAY_SIZE 0x8088
#define GL_TEXTURE_COORD_ARRAY_STRIDE 0x808A
#define GL_TEXTURE_COORD_ARRAY_TYPE 0x8089
#define GL_TEXTURE_CROP_RECT_OES 0x8B9D
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X_OES 0x8516
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_OES 0x8518
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_OES 0x851A
#define GL_TEXTURE_CUBE_MAP_OES 0x8513
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X_OES 0x8515
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y_OES 0x8517
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z_OES 0x8519
#define GL_TEXTURE_DEPTH_QCOM 0x8BD4
#define GL_TEXTURE_ENV 0x2300
#define GL_TEXTURE_ENV_COLOR 0x2201
#define GL_TEXTURE_ENV_MODE 0x2200
#define GL_TEXTURE_EXTERNAL_OES 0x8D65
#define GL_TEXTURE_FILTER_CONTROL_EXT 0x8500
#define GL_TEXTURE_FORMAT_QCOM 0x8BD6
#define GL_TEXTURE_GEN_MODE_OES 0x2500
#define GL_TEXTURE_GEN_STR_OES 0x8D60
#define GL_TEXTURE_HEIGHT_QCOM 0x8BD3
#define GL_TEXTURE_IMAGE_VALID_QCOM 0x8BD8
#define GL_TEXTURE_IMMUTABLE_FORMAT_EXT 0x912F
#define GL_TEXTURE_INTERNAL_FORMAT_QCOM 0x8BD5
#define GL_TEXTURE_LOD_BIAS_EXT 0x8501
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_MATRIX 0x0BA8
#define GL_TEXTURE_MATRIX_FLOAT_AS_INT_BITS_OES 0x898F
#define GL_TEXTURE_MAX_ANISOTROPY 0x84FE
#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#define GL_TEXTURE_MAX_LEVEL_APPLE 0x813D
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_TEXTURE_NUM_LEVELS_QCOM 0x8BD9
#define GL_TEXTURE_OBJECT_VALID_QCOM 0x8BDB
#define GL_TEXTURE_SAMPLES_IMG 0x9136
#define GL_TEXTURE_STACK_DEPTH 0x0BA5
#define GL_TEXTURE_TARGET_QCOM 0x8BDA
#define GL_TEXTURE_TYPE_QCOM 0x8BD7
#define GL_TEXTURE_WIDTH_QCOM 0x8BD2
#define GL_TEXTURE_WRAP_S 0x2802
#define GL_TEXTURE_WRAP_T 0x2803
#define GL_TIMEOUT_EXPIRED_APPLE 0x911B
#define GL_TIMEOUT_IGNORED_APPLE 0xFFFFFFFFFFFFFFFF
#define GL_TRIANGLES 0x0004
#define GL_TRIANGLE_FAN 0x0006
#define GL_TRIANGLE_STRIP 0x0005
#define GL_TRUE 1
#define GL_UNKNOWN_CONTEXT_RESET_EXT 0x8255
#define GL_UNPACK_ALIGNMENT 0x0CF5
#define GL_UNSIGNALED_APPLE 0x9118
#define GL_UNSIGNED_BYTE 0x1401
#define GL_UNSIGNED_INT 0x1405
#define GL_UNSIGNED_INT_24_8_OES 0x84FA
#define GL_UNSIGNED_SHORT 0x1403
#define GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT 0x8366
#define GL_UNSIGNED_SHORT_4_4_4_4 0x8033
#define GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT 0x8365
#define GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG 0x8365
#define GL_UNSIGNED_SHORT_5_5_5_1 0x8034
#define GL_UNSIGNED_SHORT_5_6_5 0x8363
#define GL_VENDOR 0x1F00
#define GL_VERSION 0x1F02
#define GL_VERSION_ES_CL_1_0 1
#define GL_VERSION_ES_CL_1_1 1
#define GL_VERSION_ES_CM_1_1 1
#define GL_VERTEX_ARRAY 0x8074
#define GL_VERTEX_ARRAY_BINDING_OES 0x85B5
#define GL_VERTEX_ARRAY_BUFFER_BINDING 0x8896
#define GL_VERTEX_ARRAY_POINTER 0x808E
#define GL_VERTEX_ARRAY_SIZE 0x807A
#define GL_VERTEX_ARRAY_STRIDE 0x807C
#define GL_VERTEX_ARRAY_TYPE 0x807B
#define GL_VIEWPORT 0x0BA2
#define GL_WAIT_FAILED_APPLE 0x911D
#define GL_WEIGHT_ARRAY_BUFFER_BINDING_OES 0x889E
#define GL_WEIGHT_ARRAY_OES 0x86AD
#define GL_WEIGHT_ARRAY_POINTER_OES 0x86AC
#define GL_WEIGHT_ARRAY_SIZE_OES 0x86AB
#define GL_WEIGHT_ARRAY_STRIDE_OES 0x86AA
#define GL_WEIGHT_ARRAY_TYPE_OES 0x86A9
#define GL_WRITEONLY_RENDERING_QCOM 0x8823
#define GL_WRITE_ONLY_OES 0x88B9
#define GL_XOR 0x1506
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


#define GL_VERSION_ES_CM_1_0 1
GLAD_API_CALL int GLAD_GL_VERSION_ES_CM_1_0;
#define GL_AMD_compressed_3DC_texture 1
GLAD_API_CALL int GLAD_GL_AMD_compressed_3DC_texture;
#define GL_AMD_compressed_ATC_texture 1
GLAD_API_CALL int GLAD_GL_AMD_compressed_ATC_texture;
#define GL_APPLE_copy_texture_levels 1
GLAD_API_CALL int GLAD_GL_APPLE_copy_texture_levels;
#define GL_APPLE_framebuffer_multisample 1
GLAD_API_CALL int GLAD_GL_APPLE_framebuffer_multisample;
#define GL_APPLE_sync 1
GLAD_API_CALL int GLAD_GL_APPLE_sync;
#define GL_APPLE_texture_2D_limited_npot 1
GLAD_API_CALL int GLAD_GL_APPLE_texture_2D_limited_npot;
#define GL_APPLE_texture_format_BGRA8888 1
GLAD_API_CALL int GLAD_GL_APPLE_texture_format_BGRA8888;
#define GL_APPLE_texture_max_level 1
GLAD_API_CALL int GLAD_GL_APPLE_texture_max_level;
#define GL_ARM_rgba8 1
GLAD_API_CALL int GLAD_GL_ARM_rgba8;
#define GL_EXT_blend_minmax 1
GLAD_API_CALL int GLAD_GL_EXT_blend_minmax;
#define GL_EXT_debug_marker 1
GLAD_API_CALL int GLAD_GL_EXT_debug_marker;
#define GL_EXT_discard_framebuffer 1
GLAD_API_CALL int GLAD_GL_EXT_discard_framebuffer;
#define GL_EXT_map_buffer_range 1
GLAD_API_CALL int GLAD_GL_EXT_map_buffer_range;
#define GL_EXT_multi_draw_arrays 1
GLAD_API_CALL int GLAD_GL_EXT_multi_draw_arrays;
#define GL_EXT_multisampled_render_to_texture 1
GLAD_API_CALL int GLAD_GL_EXT_multisampled_render_to_texture;
#define GL_EXT_read_format_bgra 1
GLAD_API_CALL int GLAD_GL_EXT_read_format_bgra;
#define GL_EXT_robustness 1
GLAD_API_CALL int GLAD_GL_EXT_robustness;
#define GL_EXT_sRGB 1
GLAD_API_CALL int GLAD_GL_EXT_sRGB;
#define GL_EXT_texture_compression_dxt1 1
GLAD_API_CALL int GLAD_GL_EXT_texture_compression_dxt1;
#define GL_EXT_texture_filter_anisotropic 1
GLAD_API_CALL int GLAD_GL_EXT_texture_filter_anisotropic;
#define GL_EXT_texture_format_BGRA8888 1
GLAD_API_CALL int GLAD_GL_EXT_texture_format_BGRA8888;
#define GL_EXT_texture_lod_bias 1
GLAD_API_CALL int GLAD_GL_EXT_texture_lod_bias;
#define GL_EXT_texture_storage 1
GLAD_API_CALL int GLAD_GL_EXT_texture_storage;
#define GL_IMG_multisampled_render_to_texture 1
GLAD_API_CALL int GLAD_GL_IMG_multisampled_render_to_texture;
#define GL_IMG_read_format 1
GLAD_API_CALL int GLAD_GL_IMG_read_format;
#define GL_IMG_texture_compression_pvrtc 1
GLAD_API_CALL int GLAD_GL_IMG_texture_compression_pvrtc;
#define GL_IMG_texture_env_enhanced_fixed_function 1
GLAD_API_CALL int GLAD_GL_IMG_texture_env_enhanced_fixed_function;
#define GL_IMG_user_clip_plane 1
GLAD_API_CALL int GLAD_GL_IMG_user_clip_plane;
#define GL_KHR_debug 1
GLAD_API_CALL int GLAD_GL_KHR_debug;
#define GL_NV_fence 1
GLAD_API_CALL int GLAD_GL_NV_fence;
#define GL_OES_EGL_image 1
GLAD_API_CALL int GLAD_GL_OES_EGL_image;
#define GL_OES_EGL_image_external 1
GLAD_API_CALL int GLAD_GL_OES_EGL_image_external;
#define GL_OES_blend_equation_separate 1
GLAD_API_CALL int GLAD_GL_OES_blend_equation_separate;
#define GL_OES_blend_func_separate 1
GLAD_API_CALL int GLAD_GL_OES_blend_func_separate;
#define GL_OES_blend_subtract 1
GLAD_API_CALL int GLAD_GL_OES_blend_subtract;
#define GL_OES_byte_coordinates 1
GLAD_API_CALL int GLAD_GL_OES_byte_coordinates;
#define GL_OES_compressed_ETC1_RGB8_sub_texture 1
GLAD_API_CALL int GLAD_GL_OES_compressed_ETC1_RGB8_sub_texture;
#define GL_OES_compressed_ETC1_RGB8_texture 1
GLAD_API_CALL int GLAD_GL_OES_compressed_ETC1_RGB8_texture;
#define GL_OES_compressed_paletted_texture 1
GLAD_API_CALL int GLAD_GL_OES_compressed_paletted_texture;
#define GL_OES_depth24 1
GLAD_API_CALL int GLAD_GL_OES_depth24;
#define GL_OES_depth32 1
GLAD_API_CALL int GLAD_GL_OES_depth32;
#define GL_OES_draw_texture 1
GLAD_API_CALL int GLAD_GL_OES_draw_texture;
#define GL_OES_element_index_uint 1
GLAD_API_CALL int GLAD_GL_OES_element_index_uint;
#define GL_OES_extended_matrix_palette 1
GLAD_API_CALL int GLAD_GL_OES_extended_matrix_palette;
#define GL_OES_fbo_render_mipmap 1
GLAD_API_CALL int GLAD_GL_OES_fbo_render_mipmap;
#define GL_OES_fixed_point 1
GLAD_API_CALL int GLAD_GL_OES_fixed_point;
#define GL_OES_framebuffer_object 1
GLAD_API_CALL int GLAD_GL_OES_framebuffer_object;
#define GL_OES_mapbuffer 1
GLAD_API_CALL int GLAD_GL_OES_mapbuffer;
#define GL_OES_matrix_get 1
GLAD_API_CALL int GLAD_GL_OES_matrix_get;
#define GL_OES_matrix_palette 1
GLAD_API_CALL int GLAD_GL_OES_matrix_palette;
#define GL_OES_packed_depth_stencil 1
GLAD_API_CALL int GLAD_GL_OES_packed_depth_stencil;
#define GL_OES_point_size_array 1
GLAD_API_CALL int GLAD_GL_OES_point_size_array;
#define GL_OES_point_sprite 1
GLAD_API_CALL int GLAD_GL_OES_point_sprite;
#define GL_OES_query_matrix 1
GLAD_API_CALL int GLAD_GL_OES_query_matrix;
#define GL_OES_read_format 1
GLAD_API_CALL int GLAD_GL_OES_read_format;
#define GL_OES_required_internalformat 1
GLAD_API_CALL int GLAD_GL_OES_required_internalformat;
#define GL_OES_rgb8_rgba8 1
GLAD_API_CALL int GLAD_GL_OES_rgb8_rgba8;
#define GL_OES_single_precision 1
GLAD_API_CALL int GLAD_GL_OES_single_precision;
#define GL_OES_stencil1 1
GLAD_API_CALL int GLAD_GL_OES_stencil1;
#define GL_OES_stencil4 1
GLAD_API_CALL int GLAD_GL_OES_stencil4;
#define GL_OES_stencil8 1
GLAD_API_CALL int GLAD_GL_OES_stencil8;
#define GL_OES_stencil_wrap 1
GLAD_API_CALL int GLAD_GL_OES_stencil_wrap;
#define GL_OES_surfaceless_context 1
GLAD_API_CALL int GLAD_GL_OES_surfaceless_context;
#define GL_OES_texture_cube_map 1
GLAD_API_CALL int GLAD_GL_OES_texture_cube_map;
#define GL_OES_texture_env_crossbar 1
GLAD_API_CALL int GLAD_GL_OES_texture_env_crossbar;
#define GL_OES_texture_mirrored_repeat 1
GLAD_API_CALL int GLAD_GL_OES_texture_mirrored_repeat;
#define GL_OES_texture_npot 1
GLAD_API_CALL int GLAD_GL_OES_texture_npot;
#define GL_OES_vertex_array_object 1
GLAD_API_CALL int GLAD_GL_OES_vertex_array_object;
#define GL_QCOM_driver_control 1
GLAD_API_CALL int GLAD_GL_QCOM_driver_control;
#define GL_QCOM_extended_get 1
GLAD_API_CALL int GLAD_GL_QCOM_extended_get;
#define GL_QCOM_extended_get2 1
GLAD_API_CALL int GLAD_GL_QCOM_extended_get2;
#define GL_QCOM_perfmon_global_mode 1
GLAD_API_CALL int GLAD_GL_QCOM_perfmon_global_mode;
#define GL_QCOM_tiled_rendering 1
GLAD_API_CALL int GLAD_GL_QCOM_tiled_rendering;
#define GL_QCOM_writeonly_rendering 1
GLAD_API_CALL int GLAD_GL_QCOM_writeonly_rendering;


typedef void (GLAD_API_PTR *PFNGLACTIVETEXTUREPROC)(GLenum texture);
typedef void (GLAD_API_PTR *PFNGLALPHAFUNCPROC)(GLenum func, GLfloat ref);
typedef void (GLAD_API_PTR *PFNGLALPHAFUNCXPROC)(GLenum func, GLfixed ref);
typedef void (GLAD_API_PTR *PFNGLALPHAFUNCXOESPROC)(GLenum func, GLfixed ref);
typedef void (GLAD_API_PTR *PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
typedef void (GLAD_API_PTR *PFNGLBINDFRAMEBUFFEROESPROC)(GLenum target, GLuint framebuffer);
typedef void (GLAD_API_PTR *PFNGLBINDRENDERBUFFEROESPROC)(GLenum target, GLuint renderbuffer);
typedef void (GLAD_API_PTR *PFNGLBINDTEXTUREPROC)(GLenum target, GLuint texture);
typedef void (GLAD_API_PTR *PFNGLBINDVERTEXARRAYOESPROC)(GLuint array);
typedef void (GLAD_API_PTR *PFNGLBLENDEQUATIONOESPROC)(GLenum mode);
typedef void (GLAD_API_PTR *PFNGLBLENDEQUATIONSEPARATEOESPROC)(GLenum modeRGB, GLenum modeAlpha);
typedef void (GLAD_API_PTR *PFNGLBLENDFUNCPROC)(GLenum sfactor, GLenum dfactor);
typedef void (GLAD_API_PTR *PFNGLBLENDFUNCSEPARATEOESPROC)(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
typedef void (GLAD_API_PTR *PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const void * data, GLenum usage);
typedef void (GLAD_API_PTR *PFNGLBUFFERSUBDATAPROC)(GLenum target, GLintptr offset, GLsizeiptr size, const void * data);
typedef GLenum (GLAD_API_PTR *PFNGLCHECKFRAMEBUFFERSTATUSOESPROC)(GLenum target);
typedef void (GLAD_API_PTR *PFNGLCLEARPROC)(GLbitfield mask);
typedef void (GLAD_API_PTR *PFNGLCLEARCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (GLAD_API_PTR *PFNGLCLEARCOLORXPROC)(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
typedef void (GLAD_API_PTR *PFNGLCLEARCOLORXOESPROC)(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
typedef void (GLAD_API_PTR *PFNGLCLEARDEPTHFPROC)(GLfloat d);
typedef void (GLAD_API_PTR *PFNGLCLEARDEPTHFOESPROC)(GLclampf depth);
typedef void (GLAD_API_PTR *PFNGLCLEARDEPTHXPROC)(GLfixed depth);
typedef void (GLAD_API_PTR *PFNGLCLEARDEPTHXOESPROC)(GLfixed depth);
typedef void (GLAD_API_PTR *PFNGLCLEARSTENCILPROC)(GLint s);
typedef void (GLAD_API_PTR *PFNGLCLIENTACTIVETEXTUREPROC)(GLenum texture);
typedef GLenum (GLAD_API_PTR *PFNGLCLIENTWAITSYNCAPPLEPROC)(GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (GLAD_API_PTR *PFNGLCLIPPLANEFPROC)(GLenum p, const GLfloat * eqn);
typedef void (GLAD_API_PTR *PFNGLCLIPPLANEFIMGPROC)(GLenum p, const GLfloat * eqn);
typedef void (GLAD_API_PTR *PFNGLCLIPPLANEFOESPROC)(GLenum plane, const GLfloat * equation);
typedef void (GLAD_API_PTR *PFNGLCLIPPLANEXPROC)(GLenum plane, const GLfixed * equation);
typedef void (GLAD_API_PTR *PFNGLCLIPPLANEXIMGPROC)(GLenum p, const GLfixed * eqn);
typedef void (GLAD_API_PTR *PFNGLCLIPPLANEXOESPROC)(GLenum plane, const GLfixed * equation);
typedef void (GLAD_API_PTR *PFNGLCOLOR4FPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (GLAD_API_PTR *PFNGLCOLOR4UBPROC)(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
typedef void (GLAD_API_PTR *PFNGLCOLOR4XPROC)(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
typedef void (GLAD_API_PTR *PFNGLCOLOR4XOESPROC)(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
typedef void (GLAD_API_PTR *PFNGLCOLORMASKPROC)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
typedef void (GLAD_API_PTR *PFNGLCOLORPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const void * pointer);
typedef void (GLAD_API_PTR *PFNGLCOMPRESSEDTEXIMAGE2DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data);
typedef void (GLAD_API_PTR *PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data);
typedef void (GLAD_API_PTR *PFNGLCOPYTEXIMAGE2DPROC)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
typedef void (GLAD_API_PTR *PFNGLCOPYTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (GLAD_API_PTR *PFNGLCOPYTEXTURELEVELSAPPLEPROC)(GLuint destinationTexture, GLuint sourceTexture, GLint sourceBaseLevel, GLsizei sourceLevelCount);
typedef void (GLAD_API_PTR *PFNGLCULLFACEPROC)(GLenum mode);
typedef void (GLAD_API_PTR *PFNGLCURRENTPALETTEMATRIXOESPROC)(GLuint matrixpaletteindex);
typedef void (GLAD_API_PTR *PFNGLDELETEBUFFERSPROC)(GLsizei n, const GLuint * buffers);
typedef void (GLAD_API_PTR *PFNGLDELETEFENCESNVPROC)(GLsizei n, const GLuint * fences);
typedef void (GLAD_API_PTR *PFNGLDELETEFRAMEBUFFERSOESPROC)(GLsizei n, const GLuint * framebuffers);
typedef void (GLAD_API_PTR *PFNGLDELETERENDERBUFFERSOESPROC)(GLsizei n, const GLuint * renderbuffers);
typedef void (GLAD_API_PTR *PFNGLDELETESYNCAPPLEPROC)(GLsync sync);
typedef void (GLAD_API_PTR *PFNGLDELETETEXTURESPROC)(GLsizei n, const GLuint * textures);
typedef void (GLAD_API_PTR *PFNGLDELETEVERTEXARRAYSOESPROC)(GLsizei n, const GLuint * arrays);
typedef void (GLAD_API_PTR *PFNGLDEPTHFUNCPROC)(GLenum func);
typedef void (GLAD_API_PTR *PFNGLDEPTHMASKPROC)(GLboolean flag);
typedef void (GLAD_API_PTR *PFNGLDEPTHRANGEFPROC)(GLfloat n, GLfloat f);
typedef void (GLAD_API_PTR *PFNGLDEPTHRANGEFOESPROC)(GLclampf n, GLclampf f);
typedef void (GLAD_API_PTR *PFNGLDEPTHRANGEXPROC)(GLfixed n, GLfixed f);
typedef void (GLAD_API_PTR *PFNGLDEPTHRANGEXOESPROC)(GLfixed n, GLfixed f);
typedef void (GLAD_API_PTR *PFNGLDISABLEPROC)(GLenum cap);
typedef void (GLAD_API_PTR *PFNGLDISABLECLIENTSTATEPROC)(GLenum array);
typedef void (GLAD_API_PTR *PFNGLDISABLEDRIVERCONTROLQCOMPROC)(GLuint driverControl);
typedef void (GLAD_API_PTR *PFNGLDISCARDFRAMEBUFFEREXTPROC)(GLenum target, GLsizei numAttachments, const GLenum * attachments);
typedef void (GLAD_API_PTR *PFNGLDRAWARRAYSPROC)(GLenum mode, GLint first, GLsizei count);
typedef void (GLAD_API_PTR *PFNGLDRAWELEMENTSPROC)(GLenum mode, GLsizei count, GLenum type, const void * indices);
typedef void (GLAD_API_PTR *PFNGLDRAWTEXFOESPROC)(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height);
typedef void (GLAD_API_PTR *PFNGLDRAWTEXFVOESPROC)(const GLfloat * coords);
typedef void (GLAD_API_PTR *PFNGLDRAWTEXIOESPROC)(GLint x, GLint y, GLint z, GLint width, GLint height);
typedef void (GLAD_API_PTR *PFNGLDRAWTEXIVOESPROC)(const GLint * coords);
typedef void (GLAD_API_PTR *PFNGLDRAWTEXSOESPROC)(GLshort x, GLshort y, GLshort z, GLshort width, GLshort height);
typedef void (GLAD_API_PTR *PFNGLDRAWTEXSVOESPROC)(const GLshort * coords);
typedef void (GLAD_API_PTR *PFNGLDRAWTEXXOESPROC)(GLfixed x, GLfixed y, GLfixed z, GLfixed width, GLfixed height);
typedef void (GLAD_API_PTR *PFNGLDRAWTEXXVOESPROC)(const GLfixed * coords);
typedef void (GLAD_API_PTR *PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC)(GLenum target, GLeglImageOES image);
typedef void (GLAD_API_PTR *PFNGLEGLIMAGETARGETTEXTURE2DOESPROC)(GLenum target, GLeglImageOES image);
typedef void (GLAD_API_PTR *PFNGLENABLEPROC)(GLenum cap);
typedef void (GLAD_API_PTR *PFNGLENABLECLIENTSTATEPROC)(GLenum array);
typedef void (GLAD_API_PTR *PFNGLENABLEDRIVERCONTROLQCOMPROC)(GLuint driverControl);
typedef void (GLAD_API_PTR *PFNGLENDTILINGQCOMPROC)(GLbitfield preserveMask);
typedef void (GLAD_API_PTR *PFNGLEXTGETBUFFERPOINTERVQCOMPROC)(GLenum target, void ** params);
typedef void (GLAD_API_PTR *PFNGLEXTGETBUFFERSQCOMPROC)(GLuint * buffers, GLint maxBuffers, GLint * numBuffers);
typedef void (GLAD_API_PTR *PFNGLEXTGETFRAMEBUFFERSQCOMPROC)(GLuint * framebuffers, GLint maxFramebuffers, GLint * numFramebuffers);
typedef void (GLAD_API_PTR *PFNGLEXTGETPROGRAMBINARYSOURCEQCOMPROC)(GLuint program, GLenum shadertype, GLchar * source, GLint * length);
typedef void (GLAD_API_PTR *PFNGLEXTGETPROGRAMSQCOMPROC)(GLuint * programs, GLint maxPrograms, GLint * numPrograms);
typedef void (GLAD_API_PTR *PFNGLEXTGETRENDERBUFFERSQCOMPROC)(GLuint * renderbuffers, GLint maxRenderbuffers, GLint * numRenderbuffers);
typedef void (GLAD_API_PTR *PFNGLEXTGETSHADERSQCOMPROC)(GLuint * shaders, GLint maxShaders, GLint * numShaders);
typedef void (GLAD_API_PTR *PFNGLEXTGETTEXLEVELPARAMETERIVQCOMPROC)(GLuint texture, GLenum face, GLint level, GLenum pname, GLint * params);
typedef void (GLAD_API_PTR *PFNGLEXTGETTEXSUBIMAGEQCOMPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, void * texels);
typedef void (GLAD_API_PTR *PFNGLEXTGETTEXTURESQCOMPROC)(GLuint * textures, GLint maxTextures, GLint * numTextures);
typedef GLboolean (GLAD_API_PTR *PFNGLEXTISPROGRAMBINARYQCOMPROC)(GLuint program);
typedef void (GLAD_API_PTR *PFNGLEXTTEXOBJECTSTATEOVERRIDEIQCOMPROC)(GLenum target, GLenum pname, GLint param);
typedef GLsync (GLAD_API_PTR *PFNGLFENCESYNCAPPLEPROC)(GLenum condition, GLbitfield flags);
typedef void (GLAD_API_PTR *PFNGLFINISHPROC)(void);
typedef void (GLAD_API_PTR *PFNGLFINISHFENCENVPROC)(GLuint fence);
typedef void (GLAD_API_PTR *PFNGLFLUSHPROC)(void);
typedef void (GLAD_API_PTR *PFNGLFLUSHMAPPEDBUFFERRANGEEXTPROC)(GLenum target, GLintptr offset, GLsizeiptr length);
typedef void (GLAD_API_PTR *PFNGLFOGFPROC)(GLenum pname, GLfloat param);
typedef void (GLAD_API_PTR *PFNGLFOGFVPROC)(GLenum pname, const GLfloat * params);
typedef void (GLAD_API_PTR *PFNGLFOGXPROC)(GLenum pname, GLfixed param);
typedef void (GLAD_API_PTR *PFNGLFOGXOESPROC)(GLenum pname, GLfixed param);
typedef void (GLAD_API_PTR *PFNGLFOGXVPROC)(GLenum pname, const GLfixed * param);
typedef void (GLAD_API_PTR *PFNGLFOGXVOESPROC)(GLenum pname, const GLfixed * param);
typedef void (GLAD_API_PTR *PFNGLFRAMEBUFFERRENDERBUFFEROESPROC)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (GLAD_API_PTR *PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
typedef void (GLAD_API_PTR *PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
typedef void (GLAD_API_PTR *PFNGLFRAMEBUFFERTEXTURE2DOESPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (GLAD_API_PTR *PFNGLFRONTFACEPROC)(GLenum mode);
typedef void (GLAD_API_PTR *PFNGLFRUSTUMFPROC)(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
typedef void (GLAD_API_PTR *PFNGLFRUSTUMFOESPROC)(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
typedef void (GLAD_API_PTR *PFNGLFRUSTUMXPROC)(GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
typedef void (GLAD_API_PTR *PFNGLFRUSTUMXOESPROC)(GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
typedef void (GLAD_API_PTR *PFNGLGENBUFFERSPROC)(GLsizei n, GLuint * buffers);
typedef void (GLAD_API_PTR *PFNGLGENFENCESNVPROC)(GLsizei n, GLuint * fences);
typedef void (GLAD_API_PTR *PFNGLGENFRAMEBUFFERSOESPROC)(GLsizei n, GLuint * framebuffers);
typedef void (GLAD_API_PTR *PFNGLGENRENDERBUFFERSOESPROC)(GLsizei n, GLuint * renderbuffers);
typedef void (GLAD_API_PTR *PFNGLGENTEXTURESPROC)(GLsizei n, GLuint * textures);
typedef void (GLAD_API_PTR *PFNGLGENVERTEXARRAYSOESPROC)(GLsizei n, GLuint * arrays);
typedef void (GLAD_API_PTR *PFNGLGENERATEMIPMAPOESPROC)(GLenum target);
typedef void (GLAD_API_PTR *PFNGLGETBOOLEANVPROC)(GLenum pname, GLboolean * data);
typedef void (GLAD_API_PTR *PFNGLGETBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, GLint * params);
typedef void (GLAD_API_PTR *PFNGLGETBUFFERPOINTERVOESPROC)(GLenum target, GLenum pname, void ** params);
typedef void (GLAD_API_PTR *PFNGLGETCLIPPLANEFPROC)(GLenum plane, GLfloat * equation);
typedef void (GLAD_API_PTR *PFNGLGETCLIPPLANEFOESPROC)(GLenum plane, GLfloat * equation);
typedef void (GLAD_API_PTR *PFNGLGETCLIPPLANEXPROC)(GLenum plane, GLfixed * equation);
typedef void (GLAD_API_PTR *PFNGLGETCLIPPLANEXOESPROC)(GLenum plane, GLfixed * equation);
typedef void (GLAD_API_PTR *PFNGLGETDRIVERCONTROLSTRINGQCOMPROC)(GLuint driverControl, GLsizei bufSize, GLsizei * length, GLchar * driverControlString);
typedef void (GLAD_API_PTR *PFNGLGETDRIVERCONTROLSQCOMPROC)(GLint * num, GLsizei size, GLuint * driverControls);
typedef GLenum (GLAD_API_PTR *PFNGLGETERRORPROC)(void);
typedef void (GLAD_API_PTR *PFNGLGETFENCEIVNVPROC)(GLuint fence, GLenum pname, GLint * params);
typedef void (GLAD_API_PTR *PFNGLGETFIXEDVPROC)(GLenum pname, GLfixed * params);
typedef void (GLAD_API_PTR *PFNGLGETFIXEDVOESPROC)(GLenum pname, GLfixed * params);
typedef void (GLAD_API_PTR *PFNGLGETFLOATVPROC)(GLenum pname, GLfloat * data);
typedef void (GLAD_API_PTR *PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVOESPROC)(GLenum target, GLenum attachment, GLenum pname, GLint * params);
typedef GLenum (GLAD_API_PTR *PFNGLGETGRAPHICSRESETSTATUSEXTPROC)(void);
typedef void (GLAD_API_PTR *PFNGLGETINTEGER64VAPPLEPROC)(GLenum pname, GLint64 * params);
typedef void (GLAD_API_PTR *PFNGLGETINTEGERVPROC)(GLenum pname, GLint * data);
typedef void (GLAD_API_PTR *PFNGLGETLIGHTFVPROC)(GLenum light, GLenum pname, GLfloat * params);
typedef void (GLAD_API_PTR *PFNGLGETLIGHTXVPROC)(GLenum light, GLenum pname, GLfixed * params);
typedef void (GLAD_API_PTR *PFNGLGETLIGHTXVOESPROC)(GLenum light, GLenum pname, GLfixed * params);
typedef void (GLAD_API_PTR *PFNGLGETMATERIALFVPROC)(GLenum face, GLenum pname, GLfloat * params);
typedef void (GLAD_API_PTR *PFNGLGETMATERIALXVPROC)(GLenum face, GLenum pname, GLfixed * params);
typedef void (GLAD_API_PTR *PFNGLGETMATERIALXVOESPROC)(GLenum face, GLenum pname, GLfixed * params);
typedef void (GLAD_API_PTR *PFNGLGETPOINTERVPROC)(GLenum pname, void ** params);
typedef void (GLAD_API_PTR *PFNGLGETRENDERBUFFERPARAMETERIVOESPROC)(GLenum target, GLenum pname, GLint * params);
typedef const GLubyte * (GLAD_API_PTR *PFNGLGETSTRINGPROC)(GLenum name);
typedef void (GLAD_API_PTR *PFNGLGETSYNCIVAPPLEPROC)(GLsync sync, GLenum pname, GLsizei count, GLsizei * length, GLint * values);
typedef void (GLAD_API_PTR *PFNGLGETTEXENVFVPROC)(GLenum target, GLenum pname, GLfloat * params);
typedef void (GLAD_API_PTR *PFNGLGETTEXENVIVPROC)(GLenum target, GLenum pname, GLint * params);
typedef void (GLAD_API_PTR *PFNGLGETTEXENVXVPROC)(GLenum target, GLenum pname, GLfixed * params);
typedef void (GLAD_API_PTR *PFNGLGETTEXENVXVOESPROC)(GLenum target, GLenum pname, GLfixed * params);
typedef void (GLAD_API_PTR *PFNGLGETTEXGENFVOESPROC)(GLenum coord, GLenum pname, GLfloat * params);
typedef void (GLAD_API_PTR *PFNGLGETTEXGENIVOESPROC)(GLenum coord, GLenum pname, GLint * params);
typedef void (GLAD_API_PTR *PFNGLGETTEXGENXVOESPROC)(GLenum coord, GLenum pname, GLfixed * params);
typedef void (GLAD_API_PTR *PFNGLGETTEXPARAMETERFVPROC)(GLenum target, GLenum pname, GLfloat * params);
typedef void (GLAD_API_PTR *PFNGLGETTEXPARAMETERIVPROC)(GLenum target, GLenum pname, GLint * params);
typedef void (GLAD_API_PTR *PFNGLGETTEXPARAMETERXVPROC)(GLenum target, GLenum pname, GLfixed * params);
typedef void (GLAD_API_PTR *PFNGLGETTEXPARAMETERXVOESPROC)(GLenum target, GLenum pname, GLfixed * params);
typedef void (GLAD_API_PTR *PFNGLGETNUNIFORMFVEXTPROC)(GLuint program, GLint location, GLsizei bufSize, GLfloat * params);
typedef void (GLAD_API_PTR *PFNGLGETNUNIFORMIVEXTPROC)(GLuint program, GLint location, GLsizei bufSize, GLint * params);
typedef void (GLAD_API_PTR *PFNGLHINTPROC)(GLenum target, GLenum mode);
typedef void (GLAD_API_PTR *PFNGLINSERTEVENTMARKEREXTPROC)(GLsizei length, const GLchar * marker);
typedef GLboolean (GLAD_API_PTR *PFNGLISBUFFERPROC)(GLuint buffer);
typedef GLboolean (GLAD_API_PTR *PFNGLISENABLEDPROC)(GLenum cap);
typedef GLboolean (GLAD_API_PTR *PFNGLISFENCENVPROC)(GLuint fence);
typedef GLboolean (GLAD_API_PTR *PFNGLISFRAMEBUFFEROESPROC)(GLuint framebuffer);
typedef GLboolean (GLAD_API_PTR *PFNGLISRENDERBUFFEROESPROC)(GLuint renderbuffer);
typedef GLboolean (GLAD_API_PTR *PFNGLISSYNCAPPLEPROC)(GLsync sync);
typedef GLboolean (GLAD_API_PTR *PFNGLISTEXTUREPROC)(GLuint texture);
typedef GLboolean (GLAD_API_PTR *PFNGLISVERTEXARRAYOESPROC)(GLuint array);
typedef void (GLAD_API_PTR *PFNGLLIGHTMODELFPROC)(GLenum pname, GLfloat param);
typedef void (GLAD_API_PTR *PFNGLLIGHTMODELFVPROC)(GLenum pname, const GLfloat * params);
typedef void (GLAD_API_PTR *PFNGLLIGHTMODELXPROC)(GLenum pname, GLfixed param);
typedef void (GLAD_API_PTR *PFNGLLIGHTMODELXOESPROC)(GLenum pname, GLfixed param);
typedef void (GLAD_API_PTR *PFNGLLIGHTMODELXVPROC)(GLenum pname, const GLfixed * param);
typedef void (GLAD_API_PTR *PFNGLLIGHTMODELXVOESPROC)(GLenum pname, const GLfixed * param);
typedef void (GLAD_API_PTR *PFNGLLIGHTFPROC)(GLenum light, GLenum pname, GLfloat param);
typedef void (GLAD_API_PTR *PFNGLLIGHTFVPROC)(GLenum light, GLenum pname, const GLfloat * params);
typedef void (GLAD_API_PTR *PFNGLLIGHTXPROC)(GLenum light, GLenum pname, GLfixed param);
typedef void (GLAD_API_PTR *PFNGLLIGHTXOESPROC)(GLenum light, GLenum pname, GLfixed param);
typedef void (GLAD_API_PTR *PFNGLLIGHTXVPROC)(GLenum light, GLenum pname, const GLfixed * params);
typedef void (GLAD_API_PTR *PFNGLLIGHTXVOESPROC)(GLenum light, GLenum pname, const GLfixed * params);
typedef void (GLAD_API_PTR *PFNGLLINEWIDTHPROC)(GLfloat width);
typedef void (GLAD_API_PTR *PFNGLLINEWIDTHXPROC)(GLfixed width);
typedef void (GLAD_API_PTR *PFNGLLINEWIDTHXOESPROC)(GLfixed width);
typedef void (GLAD_API_PTR *PFNGLLOADIDENTITYPROC)(void);
typedef void (GLAD_API_PTR *PFNGLLOADMATRIXFPROC)(const GLfloat * m);
typedef void (GLAD_API_PTR *PFNGLLOADMATRIXXPROC)(const GLfixed * m);
typedef void (GLAD_API_PTR *PFNGLLOADMATRIXXOESPROC)(const GLfixed * m);
typedef void (GLAD_API_PTR *PFNGLLOADPALETTEFROMMODELVIEWMATRIXOESPROC)(void);
typedef void (GLAD_API_PTR *PFNGLLOGICOPPROC)(GLenum opcode);
typedef void * (GLAD_API_PTR *PFNGLMAPBUFFEROESPROC)(GLenum target, GLenum access);
typedef void * (GLAD_API_PTR *PFNGLMAPBUFFERRANGEEXTPROC)(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef void (GLAD_API_PTR *PFNGLMATERIALFPROC)(GLenum face, GLenum pname, GLfloat param);
typedef void (GLAD_API_PTR *PFNGLMATERIALFVPROC)(GLenum face, GLenum pname, const GLfloat * params);
typedef void (GLAD_API_PTR *PFNGLMATERIALXPROC)(GLenum face, GLenum pname, GLfixed param);
typedef void (GLAD_API_PTR *PFNGLMATERIALXOESPROC)(GLenum face, GLenum pname, GLfixed param);
typedef void (GLAD_API_PTR *PFNGLMATERIALXVPROC)(GLenum face, GLenum pname, const GLfixed * param);
typedef void (GLAD_API_PTR *PFNGLMATERIALXVOESPROC)(GLenum face, GLenum pname, const GLfixed * param);
typedef void (GLAD_API_PTR *PFNGLMATRIXINDEXPOINTEROESPROC)(GLint size, GLenum type, GLsizei stride, const void * pointer);
typedef void (GLAD_API_PTR *PFNGLMATRIXMODEPROC)(GLenum mode);
typedef void (GLAD_API_PTR *PFNGLMULTMATRIXFPROC)(const GLfloat * m);
typedef void (GLAD_API_PTR *PFNGLMULTMATRIXXPROC)(const GLfixed * m);
typedef void (GLAD_API_PTR *PFNGLMULTMATRIXXOESPROC)(const GLfixed * m);
typedef void (GLAD_API_PTR *PFNGLMULTIDRAWARRAYSEXTPROC)(GLenum mode, const GLint * first, const GLsizei * count, GLsizei primcount);
typedef void (GLAD_API_PTR *PFNGLMULTIDRAWELEMENTSEXTPROC)(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei primcount);
typedef void (GLAD_API_PTR *PFNGLMULTITEXCOORD4FPROC)(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
typedef void (GLAD_API_PTR *PFNGLMULTITEXCOORD4XPROC)(GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
typedef void (GLAD_API_PTR *PFNGLMULTITEXCOORD4XOESPROC)(GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
typedef void (GLAD_API_PTR *PFNGLNORMAL3FPROC)(GLfloat nx, GLfloat ny, GLfloat nz);
typedef void (GLAD_API_PTR *PFNGLNORMAL3XPROC)(GLfixed nx, GLfixed ny, GLfixed nz);
typedef void (GLAD_API_PTR *PFNGLNORMAL3XOESPROC)(GLfixed nx, GLfixed ny, GLfixed nz);
typedef void (GLAD_API_PTR *PFNGLNORMALPOINTERPROC)(GLenum type, GLsizei stride, const void * pointer);
typedef void (GLAD_API_PTR *PFNGLORTHOFPROC)(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
typedef void (GLAD_API_PTR *PFNGLORTHOFOESPROC)(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
typedef void (GLAD_API_PTR *PFNGLORTHOXPROC)(GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
typedef void (GLAD_API_PTR *PFNGLORTHOXOESPROC)(GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
typedef void (GLAD_API_PTR *PFNGLPIXELSTOREIPROC)(GLenum pname, GLint param);
typedef void (GLAD_API_PTR *PFNGLPOINTPARAMETERFPROC)(GLenum pname, GLfloat param);
typedef void (GLAD_API_PTR *PFNGLPOINTPARAMETERFVPROC)(GLenum pname, const GLfloat * params);
typedef void (GLAD_API_PTR *PFNGLPOINTPARAMETERXPROC)(GLenum pname, GLfixed param);
typedef void (GLAD_API_PTR *PFNGLPOINTPARAMETERXOESPROC)(GLenum pname, GLfixed param);
typedef void (GLAD_API_PTR *PFNGLPOINTPARAMETERXVPROC)(GLenum pname, const GLfixed * params);
typedef void (GLAD_API_PTR *PFNGLPOINTPARAMETERXVOESPROC)(GLenum pname, const GLfixed * params);
typedef void (GLAD_API_PTR *PFNGLPOINTSIZEPROC)(GLfloat size);
typedef void (GLAD_API_PTR *PFNGLPOINTSIZEPOINTEROESPROC)(GLenum type, GLsizei stride, const void * pointer);
typedef void (GLAD_API_PTR *PFNGLPOINTSIZEXPROC)(GLfixed size);
typedef void (GLAD_API_PTR *PFNGLPOINTSIZEXOESPROC)(GLfixed size);
typedef void (GLAD_API_PTR *PFNGLPOLYGONOFFSETPROC)(GLfloat factor, GLfloat units);
typedef void (GLAD_API_PTR *PFNGLPOLYGONOFFSETXPROC)(GLfixed factor, GLfixed units);
typedef void (GLAD_API_PTR *PFNGLPOLYGONOFFSETXOESPROC)(GLfixed factor, GLfixed units);
typedef void (GLAD_API_PTR *PFNGLPOPGROUPMARKEREXTPROC)(void);
typedef void (GLAD_API_PTR *PFNGLPOPMATRIXPROC)(void);
typedef void (GLAD_API_PTR *PFNGLPUSHGROUPMARKEREXTPROC)(GLsizei length, const GLchar * marker);
typedef void (GLAD_API_PTR *PFNGLPUSHMATRIXPROC)(void);
typedef GLbitfield (GLAD_API_PTR *PFNGLQUERYMATRIXXOESPROC)(GLfixed * mantissa, GLint * exponent);
typedef void (GLAD_API_PTR *PFNGLREADPIXELSPROC)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels);
typedef void (GLAD_API_PTR *PFNGLREADNPIXELSEXTPROC)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void * data);
typedef void (GLAD_API_PTR *PFNGLRENDERBUFFERSTORAGEMULTISAMPLEAPPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (GLAD_API_PTR *PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (GLAD_API_PTR *PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (GLAD_API_PTR *PFNGLRENDERBUFFERSTORAGEOESPROC)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (GLAD_API_PTR *PFNGLRESOLVEMULTISAMPLEFRAMEBUFFERAPPLEPROC)(void);
typedef void (GLAD_API_PTR *PFNGLROTATEFPROC)(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLAD_API_PTR *PFNGLROTATEXPROC)(GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
typedef void (GLAD_API_PTR *PFNGLROTATEXOESPROC)(GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
typedef void (GLAD_API_PTR *PFNGLSAMPLECOVERAGEPROC)(GLfloat value, GLboolean invert);
typedef void (GLAD_API_PTR *PFNGLSAMPLECOVERAGEXPROC)(GLclampx value, GLboolean invert);
typedef void (GLAD_API_PTR *PFNGLSAMPLECOVERAGEXOESPROC)(GLclampx value, GLboolean invert);
typedef void (GLAD_API_PTR *PFNGLSCALEFPROC)(GLfloat x, GLfloat y, GLfloat z);
typedef void (GLAD_API_PTR *PFNGLSCALEXPROC)(GLfixed x, GLfixed y, GLfixed z);
typedef void (GLAD_API_PTR *PFNGLSCALEXOESPROC)(GLfixed x, GLfixed y, GLfixed z);
typedef void (GLAD_API_PTR *PFNGLSCISSORPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (GLAD_API_PTR *PFNGLSETFENCENVPROC)(GLuint fence, GLenum condition);
typedef void (GLAD_API_PTR *PFNGLSHADEMODELPROC)(GLenum mode);
typedef void (GLAD_API_PTR *PFNGLSTARTTILINGQCOMPROC)(GLuint x, GLuint y, GLuint width, GLuint height, GLbitfield preserveMask);
typedef void (GLAD_API_PTR *PFNGLSTENCILFUNCPROC)(GLenum func, GLint ref, GLuint mask);
typedef void (GLAD_API_PTR *PFNGLSTENCILMASKPROC)(GLuint mask);
typedef void (GLAD_API_PTR *PFNGLSTENCILOPPROC)(GLenum fail, GLenum zfail, GLenum zpass);
typedef GLboolean (GLAD_API_PTR *PFNGLTESTFENCENVPROC)(GLuint fence);
typedef void (GLAD_API_PTR *PFNGLTEXCOORDPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const void * pointer);
typedef void (GLAD_API_PTR *PFNGLTEXENVFPROC)(GLenum target, GLenum pname, GLfloat param);
typedef void (GLAD_API_PTR *PFNGLTEXENVFVPROC)(GLenum target, GLenum pname, const GLfloat * params);
typedef void (GLAD_API_PTR *PFNGLTEXENVIPROC)(GLenum target, GLenum pname, GLint param);
typedef void (GLAD_API_PTR *PFNGLTEXENVIVPROC)(GLenum target, GLenum pname, const GLint * params);
typedef void (GLAD_API_PTR *PFNGLTEXENVXPROC)(GLenum target, GLenum pname, GLfixed param);
typedef void (GLAD_API_PTR *PFNGLTEXENVXOESPROC)(GLenum target, GLenum pname, GLfixed param);
typedef void (GLAD_API_PTR *PFNGLTEXENVXVPROC)(GLenum target, GLenum pname, const GLfixed * params);
typedef void (GLAD_API_PTR *PFNGLTEXENVXVOESPROC)(GLenum target, GLenum pname, const GLfixed * params);
typedef void (GLAD_API_PTR *PFNGLTEXGENFOESPROC)(GLenum coord, GLenum pname, GLfloat param);
typedef void (GLAD_API_PTR *PFNGLTEXGENFVOESPROC)(GLenum coord, GLenum pname, const GLfloat * params);
typedef void (GLAD_API_PTR *PFNGLTEXGENIOESPROC)(GLenum coord, GLenum pname, GLint param);
typedef void (GLAD_API_PTR *PFNGLTEXGENIVOESPROC)(GLenum coord, GLenum pname, const GLint * params);
typedef void (GLAD_API_PTR *PFNGLTEXGENXOESPROC)(GLenum coord, GLenum pname, GLfixed param);
typedef void (GLAD_API_PTR *PFNGLTEXGENXVOESPROC)(GLenum coord, GLenum pname, const GLfixed * params);
typedef void (GLAD_API_PTR *PFNGLTEXIMAGE2DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels);
typedef void (GLAD_API_PTR *PFNGLTEXPARAMETERFPROC)(GLenum target, GLenum pname, GLfloat param);
typedef void (GLAD_API_PTR *PFNGLTEXPARAMETERFVPROC)(GLenum target, GLenum pname, const GLfloat * params);
typedef void (GLAD_API_PTR *PFNGLTEXPARAMETERIPROC)(GLenum target, GLenum pname, GLint param);
typedef void (GLAD_API_PTR *PFNGLTEXPARAMETERIVPROC)(GLenum target, GLenum pname, const GLint * params);
typedef void (GLAD_API_PTR *PFNGLTEXPARAMETERXPROC)(GLenum target, GLenum pname, GLfixed param);
typedef void (GLAD_API_PTR *PFNGLTEXPARAMETERXOESPROC)(GLenum target, GLenum pname, GLfixed param);
typedef void (GLAD_API_PTR *PFNGLTEXPARAMETERXVPROC)(GLenum target, GLenum pname, const GLfixed * params);
typedef void (GLAD_API_PTR *PFNGLTEXPARAMETERXVOESPROC)(GLenum target, GLenum pname, const GLfixed * params);
typedef void (GLAD_API_PTR *PFNGLTEXSTORAGE1DEXTPROC)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
typedef void (GLAD_API_PTR *PFNGLTEXSTORAGE2DEXTPROC)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (GLAD_API_PTR *PFNGLTEXSTORAGE3DEXTPROC)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
typedef void (GLAD_API_PTR *PFNGLTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels);
typedef void (GLAD_API_PTR *PFNGLTEXTURESTORAGE1DEXTPROC)(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
typedef void (GLAD_API_PTR *PFNGLTEXTURESTORAGE2DEXTPROC)(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (GLAD_API_PTR *PFNGLTEXTURESTORAGE3DEXTPROC)(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
typedef void (GLAD_API_PTR *PFNGLTRANSLATEFPROC)(GLfloat x, GLfloat y, GLfloat z);
typedef void (GLAD_API_PTR *PFNGLTRANSLATEXPROC)(GLfixed x, GLfixed y, GLfixed z);
typedef void (GLAD_API_PTR *PFNGLTRANSLATEXOESPROC)(GLfixed x, GLfixed y, GLfixed z);
typedef GLboolean (GLAD_API_PTR *PFNGLUNMAPBUFFEROESPROC)(GLenum target);
typedef void (GLAD_API_PTR *PFNGLVERTEXPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const void * pointer);
typedef void (GLAD_API_PTR *PFNGLVIEWPORTPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (GLAD_API_PTR *PFNGLWAITSYNCAPPLEPROC)(GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (GLAD_API_PTR *PFNGLWEIGHTPOINTEROESPROC)(GLint size, GLenum type, GLsizei stride, const void * pointer);

GLAD_API_CALL PFNGLACTIVETEXTUREPROC glad_glActiveTexture;
#define glActiveTexture glad_glActiveTexture
GLAD_API_CALL PFNGLALPHAFUNCPROC glad_glAlphaFunc;
#define glAlphaFunc glad_glAlphaFunc
GLAD_API_CALL PFNGLALPHAFUNCXPROC glad_glAlphaFuncx;
#define glAlphaFuncx glad_glAlphaFuncx
GLAD_API_CALL PFNGLALPHAFUNCXOESPROC glad_glAlphaFuncxOES;
#define glAlphaFuncxOES glad_glAlphaFuncxOES
GLAD_API_CALL PFNGLBINDBUFFERPROC glad_glBindBuffer;
#define glBindBuffer glad_glBindBuffer
GLAD_API_CALL PFNGLBINDFRAMEBUFFEROESPROC glad_glBindFramebufferOES;
#define glBindFramebufferOES glad_glBindFramebufferOES
GLAD_API_CALL PFNGLBINDRENDERBUFFEROESPROC glad_glBindRenderbufferOES;
#define glBindRenderbufferOES glad_glBindRenderbufferOES
GLAD_API_CALL PFNGLBINDTEXTUREPROC glad_glBindTexture;
#define glBindTexture glad_glBindTexture
GLAD_API_CALL PFNGLBINDVERTEXARRAYOESPROC glad_glBindVertexArrayOES;
#define glBindVertexArrayOES glad_glBindVertexArrayOES
GLAD_API_CALL PFNGLBLENDEQUATIONOESPROC glad_glBlendEquationOES;
#define glBlendEquationOES glad_glBlendEquationOES
GLAD_API_CALL PFNGLBLENDEQUATIONSEPARATEOESPROC glad_glBlendEquationSeparateOES;
#define glBlendEquationSeparateOES glad_glBlendEquationSeparateOES
GLAD_API_CALL PFNGLBLENDFUNCPROC glad_glBlendFunc;
#define glBlendFunc glad_glBlendFunc
GLAD_API_CALL PFNGLBLENDFUNCSEPARATEOESPROC glad_glBlendFuncSeparateOES;
#define glBlendFuncSeparateOES glad_glBlendFuncSeparateOES
GLAD_API_CALL PFNGLBUFFERDATAPROC glad_glBufferData;
#define glBufferData glad_glBufferData
GLAD_API_CALL PFNGLBUFFERSUBDATAPROC glad_glBufferSubData;
#define glBufferSubData glad_glBufferSubData
GLAD_API_CALL PFNGLCHECKFRAMEBUFFERSTATUSOESPROC glad_glCheckFramebufferStatusOES;
#define glCheckFramebufferStatusOES glad_glCheckFramebufferStatusOES
GLAD_API_CALL PFNGLCLEARPROC glad_glClear;
#define glClear glad_glClear
GLAD_API_CALL PFNGLCLEARCOLORPROC glad_glClearColor;
#define glClearColor glad_glClearColor
GLAD_API_CALL PFNGLCLEARCOLORXPROC glad_glClearColorx;
#define glClearColorx glad_glClearColorx
GLAD_API_CALL PFNGLCLEARCOLORXOESPROC glad_glClearColorxOES;
#define glClearColorxOES glad_glClearColorxOES
GLAD_API_CALL PFNGLCLEARDEPTHFPROC glad_glClearDepthf;
#define glClearDepthf glad_glClearDepthf
GLAD_API_CALL PFNGLCLEARDEPTHFOESPROC glad_glClearDepthfOES;
#define glClearDepthfOES glad_glClearDepthfOES
GLAD_API_CALL PFNGLCLEARDEPTHXPROC glad_glClearDepthx;
#define glClearDepthx glad_glClearDepthx
GLAD_API_CALL PFNGLCLEARDEPTHXOESPROC glad_glClearDepthxOES;
#define glClearDepthxOES glad_glClearDepthxOES
GLAD_API_CALL PFNGLCLEARSTENCILPROC glad_glClearStencil;
#define glClearStencil glad_glClearStencil
GLAD_API_CALL PFNGLCLIENTACTIVETEXTUREPROC glad_glClientActiveTexture;
#define glClientActiveTexture glad_glClientActiveTexture
GLAD_API_CALL PFNGLCLIENTWAITSYNCAPPLEPROC glad_glClientWaitSyncAPPLE;
#define glClientWaitSyncAPPLE glad_glClientWaitSyncAPPLE
GLAD_API_CALL PFNGLCLIPPLANEFPROC glad_glClipPlanef;
#define glClipPlanef glad_glClipPlanef
GLAD_API_CALL PFNGLCLIPPLANEFIMGPROC glad_glClipPlanefIMG;
#define glClipPlanefIMG glad_glClipPlanefIMG
GLAD_API_CALL PFNGLCLIPPLANEFOESPROC glad_glClipPlanefOES;
#define glClipPlanefOES glad_glClipPlanefOES
GLAD_API_CALL PFNGLCLIPPLANEXPROC glad_glClipPlanex;
#define glClipPlanex glad_glClipPlanex
GLAD_API_CALL PFNGLCLIPPLANEXIMGPROC glad_glClipPlanexIMG;
#define glClipPlanexIMG glad_glClipPlanexIMG
GLAD_API_CALL PFNGLCLIPPLANEXOESPROC glad_glClipPlanexOES;
#define glClipPlanexOES glad_glClipPlanexOES
GLAD_API_CALL PFNGLCOLOR4FPROC glad_glColor4f;
#define glColor4f glad_glColor4f
GLAD_API_CALL PFNGLCOLOR4UBPROC glad_glColor4ub;
#define glColor4ub glad_glColor4ub
GLAD_API_CALL PFNGLCOLOR4XPROC glad_glColor4x;
#define glColor4x glad_glColor4x
GLAD_API_CALL PFNGLCOLOR4XOESPROC glad_glColor4xOES;
#define glColor4xOES glad_glColor4xOES
GLAD_API_CALL PFNGLCOLORMASKPROC glad_glColorMask;
#define glColorMask glad_glColorMask
GLAD_API_CALL PFNGLCOLORPOINTERPROC glad_glColorPointer;
#define glColorPointer glad_glColorPointer
GLAD_API_CALL PFNGLCOMPRESSEDTEXIMAGE2DPROC glad_glCompressedTexImage2D;
#define glCompressedTexImage2D glad_glCompressedTexImage2D
GLAD_API_CALL PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glad_glCompressedTexSubImage2D;
#define glCompressedTexSubImage2D glad_glCompressedTexSubImage2D
GLAD_API_CALL PFNGLCOPYTEXIMAGE2DPROC glad_glCopyTexImage2D;
#define glCopyTexImage2D glad_glCopyTexImage2D
GLAD_API_CALL PFNGLCOPYTEXSUBIMAGE2DPROC glad_glCopyTexSubImage2D;
#define glCopyTexSubImage2D glad_glCopyTexSubImage2D
GLAD_API_CALL PFNGLCOPYTEXTURELEVELSAPPLEPROC glad_glCopyTextureLevelsAPPLE;
#define glCopyTextureLevelsAPPLE glad_glCopyTextureLevelsAPPLE
GLAD_API_CALL PFNGLCULLFACEPROC glad_glCullFace;
#define glCullFace glad_glCullFace
GLAD_API_CALL PFNGLCURRENTPALETTEMATRIXOESPROC glad_glCurrentPaletteMatrixOES;
#define glCurrentPaletteMatrixOES glad_glCurrentPaletteMatrixOES
GLAD_API_CALL PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers;
#define glDeleteBuffers glad_glDeleteBuffers
GLAD_API_CALL PFNGLDELETEFENCESNVPROC glad_glDeleteFencesNV;
#define glDeleteFencesNV glad_glDeleteFencesNV
GLAD_API_CALL PFNGLDELETEFRAMEBUFFERSOESPROC glad_glDeleteFramebuffersOES;
#define glDeleteFramebuffersOES glad_glDeleteFramebuffersOES
GLAD_API_CALL PFNGLDELETERENDERBUFFERSOESPROC glad_glDeleteRenderbuffersOES;
#define glDeleteRenderbuffersOES glad_glDeleteRenderbuffersOES
GLAD_API_CALL PFNGLDELETESYNCAPPLEPROC glad_glDeleteSyncAPPLE;
#define glDeleteSyncAPPLE glad_glDeleteSyncAPPLE
GLAD_API_CALL PFNGLDELETETEXTURESPROC glad_glDeleteTextures;
#define glDeleteTextures glad_glDeleteTextures
GLAD_API_CALL PFNGLDELETEVERTEXARRAYSOESPROC glad_glDeleteVertexArraysOES;
#define glDeleteVertexArraysOES glad_glDeleteVertexArraysOES
GLAD_API_CALL PFNGLDEPTHFUNCPROC glad_glDepthFunc;
#define glDepthFunc glad_glDepthFunc
GLAD_API_CALL PFNGLDEPTHMASKPROC glad_glDepthMask;
#define glDepthMask glad_glDepthMask
GLAD_API_CALL PFNGLDEPTHRANGEFPROC glad_glDepthRangef;
#define glDepthRangef glad_glDepthRangef
GLAD_API_CALL PFNGLDEPTHRANGEFOESPROC glad_glDepthRangefOES;
#define glDepthRangefOES glad_glDepthRangefOES
GLAD_API_CALL PFNGLDEPTHRANGEXPROC glad_glDepthRangex;
#define glDepthRangex glad_glDepthRangex
GLAD_API_CALL PFNGLDEPTHRANGEXOESPROC glad_glDepthRangexOES;
#define glDepthRangexOES glad_glDepthRangexOES
GLAD_API_CALL PFNGLDISABLEPROC glad_glDisable;
#define glDisable glad_glDisable
GLAD_API_CALL PFNGLDISABLECLIENTSTATEPROC glad_glDisableClientState;
#define glDisableClientState glad_glDisableClientState
GLAD_API_CALL PFNGLDISABLEDRIVERCONTROLQCOMPROC glad_glDisableDriverControlQCOM;
#define glDisableDriverControlQCOM glad_glDisableDriverControlQCOM
GLAD_API_CALL PFNGLDISCARDFRAMEBUFFEREXTPROC glad_glDiscardFramebufferEXT;
#define glDiscardFramebufferEXT glad_glDiscardFramebufferEXT
GLAD_API_CALL PFNGLDRAWARRAYSPROC glad_glDrawArrays;
#define glDrawArrays glad_glDrawArrays
GLAD_API_CALL PFNGLDRAWELEMENTSPROC glad_glDrawElements;
#define glDrawElements glad_glDrawElements
GLAD_API_CALL PFNGLDRAWTEXFOESPROC glad_glDrawTexfOES;
#define glDrawTexfOES glad_glDrawTexfOES
GLAD_API_CALL PFNGLDRAWTEXFVOESPROC glad_glDrawTexfvOES;
#define glDrawTexfvOES glad_glDrawTexfvOES
GLAD_API_CALL PFNGLDRAWTEXIOESPROC glad_glDrawTexiOES;
#define glDrawTexiOES glad_glDrawTexiOES
GLAD_API_CALL PFNGLDRAWTEXIVOESPROC glad_glDrawTexivOES;
#define glDrawTexivOES glad_glDrawTexivOES
GLAD_API_CALL PFNGLDRAWTEXSOESPROC glad_glDrawTexsOES;
#define glDrawTexsOES glad_glDrawTexsOES
GLAD_API_CALL PFNGLDRAWTEXSVOESPROC glad_glDrawTexsvOES;
#define glDrawTexsvOES glad_glDrawTexsvOES
GLAD_API_CALL PFNGLDRAWTEXXOESPROC glad_glDrawTexxOES;
#define glDrawTexxOES glad_glDrawTexxOES
GLAD_API_CALL PFNGLDRAWTEXXVOESPROC glad_glDrawTexxvOES;
#define glDrawTexxvOES glad_glDrawTexxvOES
GLAD_API_CALL PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC glad_glEGLImageTargetRenderbufferStorageOES;
#define glEGLImageTargetRenderbufferStorageOES glad_glEGLImageTargetRenderbufferStorageOES
GLAD_API_CALL PFNGLEGLIMAGETARGETTEXTURE2DOESPROC glad_glEGLImageTargetTexture2DOES;
#define glEGLImageTargetTexture2DOES glad_glEGLImageTargetTexture2DOES
GLAD_API_CALL PFNGLENABLEPROC glad_glEnable;
#define glEnable glad_glEnable
GLAD_API_CALL PFNGLENABLECLIENTSTATEPROC glad_glEnableClientState;
#define glEnableClientState glad_glEnableClientState
GLAD_API_CALL PFNGLENABLEDRIVERCONTROLQCOMPROC glad_glEnableDriverControlQCOM;
#define glEnableDriverControlQCOM glad_glEnableDriverControlQCOM
GLAD_API_CALL PFNGLENDTILINGQCOMPROC glad_glEndTilingQCOM;
#define glEndTilingQCOM glad_glEndTilingQCOM
GLAD_API_CALL PFNGLEXTGETBUFFERPOINTERVQCOMPROC glad_glExtGetBufferPointervQCOM;
#define glExtGetBufferPointervQCOM glad_glExtGetBufferPointervQCOM
GLAD_API_CALL PFNGLEXTGETBUFFERSQCOMPROC glad_glExtGetBuffersQCOM;
#define glExtGetBuffersQCOM glad_glExtGetBuffersQCOM
GLAD_API_CALL PFNGLEXTGETFRAMEBUFFERSQCOMPROC glad_glExtGetFramebuffersQCOM;
#define glExtGetFramebuffersQCOM glad_glExtGetFramebuffersQCOM
GLAD_API_CALL PFNGLEXTGETPROGRAMBINARYSOURCEQCOMPROC glad_glExtGetProgramBinarySourceQCOM;
#define glExtGetProgramBinarySourceQCOM glad_glExtGetProgramBinarySourceQCOM
GLAD_API_CALL PFNGLEXTGETPROGRAMSQCOMPROC glad_glExtGetProgramsQCOM;
#define glExtGetProgramsQCOM glad_glExtGetProgramsQCOM
GLAD_API_CALL PFNGLEXTGETRENDERBUFFERSQCOMPROC glad_glExtGetRenderbuffersQCOM;
#define glExtGetRenderbuffersQCOM glad_glExtGetRenderbuffersQCOM
GLAD_API_CALL PFNGLEXTGETSHADERSQCOMPROC glad_glExtGetShadersQCOM;
#define glExtGetShadersQCOM glad_glExtGetShadersQCOM
GLAD_API_CALL PFNGLEXTGETTEXLEVELPARAMETERIVQCOMPROC glad_glExtGetTexLevelParameterivQCOM;
#define glExtGetTexLevelParameterivQCOM glad_glExtGetTexLevelParameterivQCOM
GLAD_API_CALL PFNGLEXTGETTEXSUBIMAGEQCOMPROC glad_glExtGetTexSubImageQCOM;
#define glExtGetTexSubImageQCOM glad_glExtGetTexSubImageQCOM
GLAD_API_CALL PFNGLEXTGETTEXTURESQCOMPROC glad_glExtGetTexturesQCOM;
#define glExtGetTexturesQCOM glad_glExtGetTexturesQCOM
GLAD_API_CALL PFNGLEXTISPROGRAMBINARYQCOMPROC glad_glExtIsProgramBinaryQCOM;
#define glExtIsProgramBinaryQCOM glad_glExtIsProgramBinaryQCOM
GLAD_API_CALL PFNGLEXTTEXOBJECTSTATEOVERRIDEIQCOMPROC glad_glExtTexObjectStateOverrideiQCOM;
#define glExtTexObjectStateOverrideiQCOM glad_glExtTexObjectStateOverrideiQCOM
GLAD_API_CALL PFNGLFENCESYNCAPPLEPROC glad_glFenceSyncAPPLE;
#define glFenceSyncAPPLE glad_glFenceSyncAPPLE
GLAD_API_CALL PFNGLFINISHPROC glad_glFinish;
#define glFinish glad_glFinish
GLAD_API_CALL PFNGLFINISHFENCENVPROC glad_glFinishFenceNV;
#define glFinishFenceNV glad_glFinishFenceNV
GLAD_API_CALL PFNGLFLUSHPROC glad_glFlush;
#define glFlush glad_glFlush
GLAD_API_CALL PFNGLFLUSHMAPPEDBUFFERRANGEEXTPROC glad_glFlushMappedBufferRangeEXT;
#define glFlushMappedBufferRangeEXT glad_glFlushMappedBufferRangeEXT
GLAD_API_CALL PFNGLFOGFPROC glad_glFogf;
#define glFogf glad_glFogf
GLAD_API_CALL PFNGLFOGFVPROC glad_glFogfv;
#define glFogfv glad_glFogfv
GLAD_API_CALL PFNGLFOGXPROC glad_glFogx;
#define glFogx glad_glFogx
GLAD_API_CALL PFNGLFOGXOESPROC glad_glFogxOES;
#define glFogxOES glad_glFogxOES
GLAD_API_CALL PFNGLFOGXVPROC glad_glFogxv;
#define glFogxv glad_glFogxv
GLAD_API_CALL PFNGLFOGXVOESPROC glad_glFogxvOES;
#define glFogxvOES glad_glFogxvOES
GLAD_API_CALL PFNGLFRAMEBUFFERRENDERBUFFEROESPROC glad_glFramebufferRenderbufferOES;
#define glFramebufferRenderbufferOES glad_glFramebufferRenderbufferOES
GLAD_API_CALL PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC glad_glFramebufferTexture2DMultisampleEXT;
#define glFramebufferTexture2DMultisampleEXT glad_glFramebufferTexture2DMultisampleEXT
GLAD_API_CALL PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC glad_glFramebufferTexture2DMultisampleIMG;
#define glFramebufferTexture2DMultisampleIMG glad_glFramebufferTexture2DMultisampleIMG
GLAD_API_CALL PFNGLFRAMEBUFFERTEXTURE2DOESPROC glad_glFramebufferTexture2DOES;
#define glFramebufferTexture2DOES glad_glFramebufferTexture2DOES
GLAD_API_CALL PFNGLFRONTFACEPROC glad_glFrontFace;
#define glFrontFace glad_glFrontFace
GLAD_API_CALL PFNGLFRUSTUMFPROC glad_glFrustumf;
#define glFrustumf glad_glFrustumf
GLAD_API_CALL PFNGLFRUSTUMFOESPROC glad_glFrustumfOES;
#define glFrustumfOES glad_glFrustumfOES
GLAD_API_CALL PFNGLFRUSTUMXPROC glad_glFrustumx;
#define glFrustumx glad_glFrustumx
GLAD_API_CALL PFNGLFRUSTUMXOESPROC glad_glFrustumxOES;
#define glFrustumxOES glad_glFrustumxOES
GLAD_API_CALL PFNGLGENBUFFERSPROC glad_glGenBuffers;
#define glGenBuffers glad_glGenBuffers
GLAD_API_CALL PFNGLGENFENCESNVPROC glad_glGenFencesNV;
#define glGenFencesNV glad_glGenFencesNV
GLAD_API_CALL PFNGLGENFRAMEBUFFERSOESPROC glad_glGenFramebuffersOES;
#define glGenFramebuffersOES glad_glGenFramebuffersOES
GLAD_API_CALL PFNGLGENRENDERBUFFERSOESPROC glad_glGenRenderbuffersOES;
#define glGenRenderbuffersOES glad_glGenRenderbuffersOES
GLAD_API_CALL PFNGLGENTEXTURESPROC glad_glGenTextures;
#define glGenTextures glad_glGenTextures
GLAD_API_CALL PFNGLGENVERTEXARRAYSOESPROC glad_glGenVertexArraysOES;
#define glGenVertexArraysOES glad_glGenVertexArraysOES
GLAD_API_CALL PFNGLGENERATEMIPMAPOESPROC glad_glGenerateMipmapOES;
#define glGenerateMipmapOES glad_glGenerateMipmapOES
GLAD_API_CALL PFNGLGETBOOLEANVPROC glad_glGetBooleanv;
#define glGetBooleanv glad_glGetBooleanv
GLAD_API_CALL PFNGLGETBUFFERPARAMETERIVPROC glad_glGetBufferParameteriv;
#define glGetBufferParameteriv glad_glGetBufferParameteriv
GLAD_API_CALL PFNGLGETBUFFERPOINTERVOESPROC glad_glGetBufferPointervOES;
#define glGetBufferPointervOES glad_glGetBufferPointervOES
GLAD_API_CALL PFNGLGETCLIPPLANEFPROC glad_glGetClipPlanef;
#define glGetClipPlanef glad_glGetClipPlanef
GLAD_API_CALL PFNGLGETCLIPPLANEFOESPROC glad_glGetClipPlanefOES;
#define glGetClipPlanefOES glad_glGetClipPlanefOES
GLAD_API_CALL PFNGLGETCLIPPLANEXPROC glad_glGetClipPlanex;
#define glGetClipPlanex glad_glGetClipPlanex
GLAD_API_CALL PFNGLGETCLIPPLANEXOESPROC glad_glGetClipPlanexOES;
#define glGetClipPlanexOES glad_glGetClipPlanexOES
GLAD_API_CALL PFNGLGETDRIVERCONTROLSTRINGQCOMPROC glad_glGetDriverControlStringQCOM;
#define glGetDriverControlStringQCOM glad_glGetDriverControlStringQCOM
GLAD_API_CALL PFNGLGETDRIVERCONTROLSQCOMPROC glad_glGetDriverControlsQCOM;
#define glGetDriverControlsQCOM glad_glGetDriverControlsQCOM
GLAD_API_CALL PFNGLGETERRORPROC glad_glGetError;
#define glGetError glad_glGetError
GLAD_API_CALL PFNGLGETFENCEIVNVPROC glad_glGetFenceivNV;
#define glGetFenceivNV glad_glGetFenceivNV
GLAD_API_CALL PFNGLGETFIXEDVPROC glad_glGetFixedv;
#define glGetFixedv glad_glGetFixedv
GLAD_API_CALL PFNGLGETFIXEDVOESPROC glad_glGetFixedvOES;
#define glGetFixedvOES glad_glGetFixedvOES
GLAD_API_CALL PFNGLGETFLOATVPROC glad_glGetFloatv;
#define glGetFloatv glad_glGetFloatv
GLAD_API_CALL PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVOESPROC glad_glGetFramebufferAttachmentParameterivOES;
#define glGetFramebufferAttachmentParameterivOES glad_glGetFramebufferAttachmentParameterivOES
GLAD_API_CALL PFNGLGETGRAPHICSRESETSTATUSEXTPROC glad_glGetGraphicsResetStatusEXT;
#define glGetGraphicsResetStatusEXT glad_glGetGraphicsResetStatusEXT
GLAD_API_CALL PFNGLGETINTEGER64VAPPLEPROC glad_glGetInteger64vAPPLE;
#define glGetInteger64vAPPLE glad_glGetInteger64vAPPLE
GLAD_API_CALL PFNGLGETINTEGERVPROC glad_glGetIntegerv;
#define glGetIntegerv glad_glGetIntegerv
GLAD_API_CALL PFNGLGETLIGHTFVPROC glad_glGetLightfv;
#define glGetLightfv glad_glGetLightfv
GLAD_API_CALL PFNGLGETLIGHTXVPROC glad_glGetLightxv;
#define glGetLightxv glad_glGetLightxv
GLAD_API_CALL PFNGLGETLIGHTXVOESPROC glad_glGetLightxvOES;
#define glGetLightxvOES glad_glGetLightxvOES
GLAD_API_CALL PFNGLGETMATERIALFVPROC glad_glGetMaterialfv;
#define glGetMaterialfv glad_glGetMaterialfv
GLAD_API_CALL PFNGLGETMATERIALXVPROC glad_glGetMaterialxv;
#define glGetMaterialxv glad_glGetMaterialxv
GLAD_API_CALL PFNGLGETMATERIALXVOESPROC glad_glGetMaterialxvOES;
#define glGetMaterialxvOES glad_glGetMaterialxvOES
GLAD_API_CALL PFNGLGETPOINTERVPROC glad_glGetPointerv;
#define glGetPointerv glad_glGetPointerv
GLAD_API_CALL PFNGLGETRENDERBUFFERPARAMETERIVOESPROC glad_glGetRenderbufferParameterivOES;
#define glGetRenderbufferParameterivOES glad_glGetRenderbufferParameterivOES
GLAD_API_CALL PFNGLGETSTRINGPROC glad_glGetString;
#define glGetString glad_glGetString
GLAD_API_CALL PFNGLGETSYNCIVAPPLEPROC glad_glGetSyncivAPPLE;
#define glGetSyncivAPPLE glad_glGetSyncivAPPLE
GLAD_API_CALL PFNGLGETTEXENVFVPROC glad_glGetTexEnvfv;
#define glGetTexEnvfv glad_glGetTexEnvfv
GLAD_API_CALL PFNGLGETTEXENVIVPROC glad_glGetTexEnviv;
#define glGetTexEnviv glad_glGetTexEnviv
GLAD_API_CALL PFNGLGETTEXENVXVPROC glad_glGetTexEnvxv;
#define glGetTexEnvxv glad_glGetTexEnvxv
GLAD_API_CALL PFNGLGETTEXENVXVOESPROC glad_glGetTexEnvxvOES;
#define glGetTexEnvxvOES glad_glGetTexEnvxvOES
GLAD_API_CALL PFNGLGETTEXGENFVOESPROC glad_glGetTexGenfvOES;
#define glGetTexGenfvOES glad_glGetTexGenfvOES
GLAD_API_CALL PFNGLGETTEXGENIVOESPROC glad_glGetTexGenivOES;
#define glGetTexGenivOES glad_glGetTexGenivOES
GLAD_API_CALL PFNGLGETTEXGENXVOESPROC glad_glGetTexGenxvOES;
#define glGetTexGenxvOES glad_glGetTexGenxvOES
GLAD_API_CALL PFNGLGETTEXPARAMETERFVPROC glad_glGetTexParameterfv;
#define glGetTexParameterfv glad_glGetTexParameterfv
GLAD_API_CALL PFNGLGETTEXPARAMETERIVPROC glad_glGetTexParameteriv;
#define glGetTexParameteriv glad_glGetTexParameteriv
GLAD_API_CALL PFNGLGETTEXPARAMETERXVPROC glad_glGetTexParameterxv;
#define glGetTexParameterxv glad_glGetTexParameterxv
GLAD_API_CALL PFNGLGETTEXPARAMETERXVOESPROC glad_glGetTexParameterxvOES;
#define glGetTexParameterxvOES glad_glGetTexParameterxvOES
GLAD_API_CALL PFNGLGETNUNIFORMFVEXTPROC glad_glGetnUniformfvEXT;
#define glGetnUniformfvEXT glad_glGetnUniformfvEXT
GLAD_API_CALL PFNGLGETNUNIFORMIVEXTPROC glad_glGetnUniformivEXT;
#define glGetnUniformivEXT glad_glGetnUniformivEXT
GLAD_API_CALL PFNGLHINTPROC glad_glHint;
#define glHint glad_glHint
GLAD_API_CALL PFNGLINSERTEVENTMARKEREXTPROC glad_glInsertEventMarkerEXT;
#define glInsertEventMarkerEXT glad_glInsertEventMarkerEXT
GLAD_API_CALL PFNGLISBUFFERPROC glad_glIsBuffer;
#define glIsBuffer glad_glIsBuffer
GLAD_API_CALL PFNGLISENABLEDPROC glad_glIsEnabled;
#define glIsEnabled glad_glIsEnabled
GLAD_API_CALL PFNGLISFENCENVPROC glad_glIsFenceNV;
#define glIsFenceNV glad_glIsFenceNV
GLAD_API_CALL PFNGLISFRAMEBUFFEROESPROC glad_glIsFramebufferOES;
#define glIsFramebufferOES glad_glIsFramebufferOES
GLAD_API_CALL PFNGLISRENDERBUFFEROESPROC glad_glIsRenderbufferOES;
#define glIsRenderbufferOES glad_glIsRenderbufferOES
GLAD_API_CALL PFNGLISSYNCAPPLEPROC glad_glIsSyncAPPLE;
#define glIsSyncAPPLE glad_glIsSyncAPPLE
GLAD_API_CALL PFNGLISTEXTUREPROC glad_glIsTexture;
#define glIsTexture glad_glIsTexture
GLAD_API_CALL PFNGLISVERTEXARRAYOESPROC glad_glIsVertexArrayOES;
#define glIsVertexArrayOES glad_glIsVertexArrayOES
GLAD_API_CALL PFNGLLIGHTMODELFPROC glad_glLightModelf;
#define glLightModelf glad_glLightModelf
GLAD_API_CALL PFNGLLIGHTMODELFVPROC glad_glLightModelfv;
#define glLightModelfv glad_glLightModelfv
GLAD_API_CALL PFNGLLIGHTMODELXPROC glad_glLightModelx;
#define glLightModelx glad_glLightModelx
GLAD_API_CALL PFNGLLIGHTMODELXOESPROC glad_glLightModelxOES;
#define glLightModelxOES glad_glLightModelxOES
GLAD_API_CALL PFNGLLIGHTMODELXVPROC glad_glLightModelxv;
#define glLightModelxv glad_glLightModelxv
GLAD_API_CALL PFNGLLIGHTMODELXVOESPROC glad_glLightModelxvOES;
#define glLightModelxvOES glad_glLightModelxvOES
GLAD_API_CALL PFNGLLIGHTFPROC glad_glLightf;
#define glLightf glad_glLightf
GLAD_API_CALL PFNGLLIGHTFVPROC glad_glLightfv;
#define glLightfv glad_glLightfv
GLAD_API_CALL PFNGLLIGHTXPROC glad_glLightx;
#define glLightx glad_glLightx
GLAD_API_CALL PFNGLLIGHTXOESPROC glad_glLightxOES;
#define glLightxOES glad_glLightxOES
GLAD_API_CALL PFNGLLIGHTXVPROC glad_glLightxv;
#define glLightxv glad_glLightxv
GLAD_API_CALL PFNGLLIGHTXVOESPROC glad_glLightxvOES;
#define glLightxvOES glad_glLightxvOES
GLAD_API_CALL PFNGLLINEWIDTHPROC glad_glLineWidth;
#define glLineWidth glad_glLineWidth
GLAD_API_CALL PFNGLLINEWIDTHXPROC glad_glLineWidthx;
#define glLineWidthx glad_glLineWidthx
GLAD_API_CALL PFNGLLINEWIDTHXOESPROC glad_glLineWidthxOES;
#define glLineWidthxOES glad_glLineWidthxOES
GLAD_API_CALL PFNGLLOADIDENTITYPROC glad_glLoadIdentity;
#define glLoadIdentity glad_glLoadIdentity
GLAD_API_CALL PFNGLLOADMATRIXFPROC glad_glLoadMatrixf;
#define glLoadMatrixf glad_glLoadMatrixf
GLAD_API_CALL PFNGLLOADMATRIXXPROC glad_glLoadMatrixx;
#define glLoadMatrixx glad_glLoadMatrixx
GLAD_API_CALL PFNGLLOADMATRIXXOESPROC glad_glLoadMatrixxOES;
#define glLoadMatrixxOES glad_glLoadMatrixxOES
GLAD_API_CALL PFNGLLOADPALETTEFROMMODELVIEWMATRIXOESPROC glad_glLoadPaletteFromModelViewMatrixOES;
#define glLoadPaletteFromModelViewMatrixOES glad_glLoadPaletteFromModelViewMatrixOES
GLAD_API_CALL PFNGLLOGICOPPROC glad_glLogicOp;
#define glLogicOp glad_glLogicOp
GLAD_API_CALL PFNGLMAPBUFFEROESPROC glad_glMapBufferOES;
#define glMapBufferOES glad_glMapBufferOES
GLAD_API_CALL PFNGLMAPBUFFERRANGEEXTPROC glad_glMapBufferRangeEXT;
#define glMapBufferRangeEXT glad_glMapBufferRangeEXT
GLAD_API_CALL PFNGLMATERIALFPROC glad_glMaterialf;
#define glMaterialf glad_glMaterialf
GLAD_API_CALL PFNGLMATERIALFVPROC glad_glMaterialfv;
#define glMaterialfv glad_glMaterialfv
GLAD_API_CALL PFNGLMATERIALXPROC glad_glMaterialx;
#define glMaterialx glad_glMaterialx
GLAD_API_CALL PFNGLMATERIALXOESPROC glad_glMaterialxOES;
#define glMaterialxOES glad_glMaterialxOES
GLAD_API_CALL PFNGLMATERIALXVPROC glad_glMaterialxv;
#define glMaterialxv glad_glMaterialxv
GLAD_API_CALL PFNGLMATERIALXVOESPROC glad_glMaterialxvOES;
#define glMaterialxvOES glad_glMaterialxvOES
GLAD_API_CALL PFNGLMATRIXINDEXPOINTEROESPROC glad_glMatrixIndexPointerOES;
#define glMatrixIndexPointerOES glad_glMatrixIndexPointerOES
GLAD_API_CALL PFNGLMATRIXMODEPROC glad_glMatrixMode;
#define glMatrixMode glad_glMatrixMode
GLAD_API_CALL PFNGLMULTMATRIXFPROC glad_glMultMatrixf;
#define glMultMatrixf glad_glMultMatrixf
GLAD_API_CALL PFNGLMULTMATRIXXPROC glad_glMultMatrixx;
#define glMultMatrixx glad_glMultMatrixx
GLAD_API_CALL PFNGLMULTMATRIXXOESPROC glad_glMultMatrixxOES;
#define glMultMatrixxOES glad_glMultMatrixxOES
GLAD_API_CALL PFNGLMULTIDRAWARRAYSEXTPROC glad_glMultiDrawArraysEXT;
#define glMultiDrawArraysEXT glad_glMultiDrawArraysEXT
GLAD_API_CALL PFNGLMULTIDRAWELEMENTSEXTPROC glad_glMultiDrawElementsEXT;
#define glMultiDrawElementsEXT glad_glMultiDrawElementsEXT
GLAD_API_CALL PFNGLMULTITEXCOORD4FPROC glad_glMultiTexCoord4f;
#define glMultiTexCoord4f glad_glMultiTexCoord4f
GLAD_API_CALL PFNGLMULTITEXCOORD4XPROC glad_glMultiTexCoord4x;
#define glMultiTexCoord4x glad_glMultiTexCoord4x
GLAD_API_CALL PFNGLMULTITEXCOORD4XOESPROC glad_glMultiTexCoord4xOES;
#define glMultiTexCoord4xOES glad_glMultiTexCoord4xOES
GLAD_API_CALL PFNGLNORMAL3FPROC glad_glNormal3f;
#define glNormal3f glad_glNormal3f
GLAD_API_CALL PFNGLNORMAL3XPROC glad_glNormal3x;
#define glNormal3x glad_glNormal3x
GLAD_API_CALL PFNGLNORMAL3XOESPROC glad_glNormal3xOES;
#define glNormal3xOES glad_glNormal3xOES
GLAD_API_CALL PFNGLNORMALPOINTERPROC glad_glNormalPointer;
#define glNormalPointer glad_glNormalPointer
GLAD_API_CALL PFNGLORTHOFPROC glad_glOrthof;
#define glOrthof glad_glOrthof
GLAD_API_CALL PFNGLORTHOFOESPROC glad_glOrthofOES;
#define glOrthofOES glad_glOrthofOES
GLAD_API_CALL PFNGLORTHOXPROC glad_glOrthox;
#define glOrthox glad_glOrthox
GLAD_API_CALL PFNGLORTHOXOESPROC glad_glOrthoxOES;
#define glOrthoxOES glad_glOrthoxOES
GLAD_API_CALL PFNGLPIXELSTOREIPROC glad_glPixelStorei;
#define glPixelStorei glad_glPixelStorei
GLAD_API_CALL PFNGLPOINTPARAMETERFPROC glad_glPointParameterf;
#define glPointParameterf glad_glPointParameterf
GLAD_API_CALL PFNGLPOINTPARAMETERFVPROC glad_glPointParameterfv;
#define glPointParameterfv glad_glPointParameterfv
GLAD_API_CALL PFNGLPOINTPARAMETERXPROC glad_glPointParameterx;
#define glPointParameterx glad_glPointParameterx
GLAD_API_CALL PFNGLPOINTPARAMETERXOESPROC glad_glPointParameterxOES;
#define glPointParameterxOES glad_glPointParameterxOES
GLAD_API_CALL PFNGLPOINTPARAMETERXVPROC glad_glPointParameterxv;
#define glPointParameterxv glad_glPointParameterxv
GLAD_API_CALL PFNGLPOINTPARAMETERXVOESPROC glad_glPointParameterxvOES;
#define glPointParameterxvOES glad_glPointParameterxvOES
GLAD_API_CALL PFNGLPOINTSIZEPROC glad_glPointSize;
#define glPointSize glad_glPointSize
GLAD_API_CALL PFNGLPOINTSIZEPOINTEROESPROC glad_glPointSizePointerOES;
#define glPointSizePointerOES glad_glPointSizePointerOES
GLAD_API_CALL PFNGLPOINTSIZEXPROC glad_glPointSizex;
#define glPointSizex glad_glPointSizex
GLAD_API_CALL PFNGLPOINTSIZEXOESPROC glad_glPointSizexOES;
#define glPointSizexOES glad_glPointSizexOES
GLAD_API_CALL PFNGLPOLYGONOFFSETPROC glad_glPolygonOffset;
#define glPolygonOffset glad_glPolygonOffset
GLAD_API_CALL PFNGLPOLYGONOFFSETXPROC glad_glPolygonOffsetx;
#define glPolygonOffsetx glad_glPolygonOffsetx
GLAD_API_CALL PFNGLPOLYGONOFFSETXOESPROC glad_glPolygonOffsetxOES;
#define glPolygonOffsetxOES glad_glPolygonOffsetxOES
GLAD_API_CALL PFNGLPOPGROUPMARKEREXTPROC glad_glPopGroupMarkerEXT;
#define glPopGroupMarkerEXT glad_glPopGroupMarkerEXT
GLAD_API_CALL PFNGLPOPMATRIXPROC glad_glPopMatrix;
#define glPopMatrix glad_glPopMatrix
GLAD_API_CALL PFNGLPUSHGROUPMARKEREXTPROC glad_glPushGroupMarkerEXT;
#define glPushGroupMarkerEXT glad_glPushGroupMarkerEXT
GLAD_API_CALL PFNGLPUSHMATRIXPROC glad_glPushMatrix;
#define glPushMatrix glad_glPushMatrix
GLAD_API_CALL PFNGLQUERYMATRIXXOESPROC glad_glQueryMatrixxOES;
#define glQueryMatrixxOES glad_glQueryMatrixxOES
GLAD_API_CALL PFNGLREADPIXELSPROC glad_glReadPixels;
#define glReadPixels glad_glReadPixels
GLAD_API_CALL PFNGLREADNPIXELSEXTPROC glad_glReadnPixelsEXT;
#define glReadnPixelsEXT glad_glReadnPixelsEXT
GLAD_API_CALL PFNGLRENDERBUFFERSTORAGEMULTISAMPLEAPPLEPROC glad_glRenderbufferStorageMultisampleAPPLE;
#define glRenderbufferStorageMultisampleAPPLE glad_glRenderbufferStorageMultisampleAPPLE
GLAD_API_CALL PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC glad_glRenderbufferStorageMultisampleEXT;
#define glRenderbufferStorageMultisampleEXT glad_glRenderbufferStorageMultisampleEXT
GLAD_API_CALL PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC glad_glRenderbufferStorageMultisampleIMG;
#define glRenderbufferStorageMultisampleIMG glad_glRenderbufferStorageMultisampleIMG
GLAD_API_CALL PFNGLRENDERBUFFERSTORAGEOESPROC glad_glRenderbufferStorageOES;
#define glRenderbufferStorageOES glad_glRenderbufferStorageOES
GLAD_API_CALL PFNGLRESOLVEMULTISAMPLEFRAMEBUFFERAPPLEPROC glad_glResolveMultisampleFramebufferAPPLE;
#define glResolveMultisampleFramebufferAPPLE glad_glResolveMultisampleFramebufferAPPLE
GLAD_API_CALL PFNGLROTATEFPROC glad_glRotatef;
#define glRotatef glad_glRotatef
GLAD_API_CALL PFNGLROTATEXPROC glad_glRotatex;
#define glRotatex glad_glRotatex
GLAD_API_CALL PFNGLROTATEXOESPROC glad_glRotatexOES;
#define glRotatexOES glad_glRotatexOES
GLAD_API_CALL PFNGLSAMPLECOVERAGEPROC glad_glSampleCoverage;
#define glSampleCoverage glad_glSampleCoverage
GLAD_API_CALL PFNGLSAMPLECOVERAGEXPROC glad_glSampleCoveragex;
#define glSampleCoveragex glad_glSampleCoveragex
GLAD_API_CALL PFNGLSAMPLECOVERAGEXOESPROC glad_glSampleCoveragexOES;
#define glSampleCoveragexOES glad_glSampleCoveragexOES
GLAD_API_CALL PFNGLSCALEFPROC glad_glScalef;
#define glScalef glad_glScalef
GLAD_API_CALL PFNGLSCALEXPROC glad_glScalex;
#define glScalex glad_glScalex
GLAD_API_CALL PFNGLSCALEXOESPROC glad_glScalexOES;
#define glScalexOES glad_glScalexOES
GLAD_API_CALL PFNGLSCISSORPROC glad_glScissor;
#define glScissor glad_glScissor
GLAD_API_CALL PFNGLSETFENCENVPROC glad_glSetFenceNV;
#define glSetFenceNV glad_glSetFenceNV
GLAD_API_CALL PFNGLSHADEMODELPROC glad_glShadeModel;
#define glShadeModel glad_glShadeModel
GLAD_API_CALL PFNGLSTARTTILINGQCOMPROC glad_glStartTilingQCOM;
#define glStartTilingQCOM glad_glStartTilingQCOM
GLAD_API_CALL PFNGLSTENCILFUNCPROC glad_glStencilFunc;
#define glStencilFunc glad_glStencilFunc
GLAD_API_CALL PFNGLSTENCILMASKPROC glad_glStencilMask;
#define glStencilMask glad_glStencilMask
GLAD_API_CALL PFNGLSTENCILOPPROC glad_glStencilOp;
#define glStencilOp glad_glStencilOp
GLAD_API_CALL PFNGLTESTFENCENVPROC glad_glTestFenceNV;
#define glTestFenceNV glad_glTestFenceNV
GLAD_API_CALL PFNGLTEXCOORDPOINTERPROC glad_glTexCoordPointer;
#define glTexCoordPointer glad_glTexCoordPointer
GLAD_API_CALL PFNGLTEXENVFPROC glad_glTexEnvf;
#define glTexEnvf glad_glTexEnvf
GLAD_API_CALL PFNGLTEXENVFVPROC glad_glTexEnvfv;
#define glTexEnvfv glad_glTexEnvfv
GLAD_API_CALL PFNGLTEXENVIPROC glad_glTexEnvi;
#define glTexEnvi glad_glTexEnvi
GLAD_API_CALL PFNGLTEXENVIVPROC glad_glTexEnviv;
#define glTexEnviv glad_glTexEnviv
GLAD_API_CALL PFNGLTEXENVXPROC glad_glTexEnvx;
#define glTexEnvx glad_glTexEnvx
GLAD_API_CALL PFNGLTEXENVXOESPROC glad_glTexEnvxOES;
#define glTexEnvxOES glad_glTexEnvxOES
GLAD_API_CALL PFNGLTEXENVXVPROC glad_glTexEnvxv;
#define glTexEnvxv glad_glTexEnvxv
GLAD_API_CALL PFNGLTEXENVXVOESPROC glad_glTexEnvxvOES;
#define glTexEnvxvOES glad_glTexEnvxvOES
GLAD_API_CALL PFNGLTEXGENFOESPROC glad_glTexGenfOES;
#define glTexGenfOES glad_glTexGenfOES
GLAD_API_CALL PFNGLTEXGENFVOESPROC glad_glTexGenfvOES;
#define glTexGenfvOES glad_glTexGenfvOES
GLAD_API_CALL PFNGLTEXGENIOESPROC glad_glTexGeniOES;
#define glTexGeniOES glad_glTexGeniOES
GLAD_API_CALL PFNGLTEXGENIVOESPROC glad_glTexGenivOES;
#define glTexGenivOES glad_glTexGenivOES
GLAD_API_CALL PFNGLTEXGENXOESPROC glad_glTexGenxOES;
#define glTexGenxOES glad_glTexGenxOES
GLAD_API_CALL PFNGLTEXGENXVOESPROC glad_glTexGenxvOES;
#define glTexGenxvOES glad_glTexGenxvOES
GLAD_API_CALL PFNGLTEXIMAGE2DPROC glad_glTexImage2D;
#define glTexImage2D glad_glTexImage2D
GLAD_API_CALL PFNGLTEXPARAMETERFPROC glad_glTexParameterf;
#define glTexParameterf glad_glTexParameterf
GLAD_API_CALL PFNGLTEXPARAMETERFVPROC glad_glTexParameterfv;
#define glTexParameterfv glad_glTexParameterfv
GLAD_API_CALL PFNGLTEXPARAMETERIPROC glad_glTexParameteri;
#define glTexParameteri glad_glTexParameteri
GLAD_API_CALL PFNGLTEXPARAMETERIVPROC glad_glTexParameteriv;
#define glTexParameteriv glad_glTexParameteriv
GLAD_API_CALL PFNGLTEXPARAMETERXPROC glad_glTexParameterx;
#define glTexParameterx glad_glTexParameterx
GLAD_API_CALL PFNGLTEXPARAMETERXOESPROC glad_glTexParameterxOES;
#define glTexParameterxOES glad_glTexParameterxOES
GLAD_API_CALL PFNGLTEXPARAMETERXVPROC glad_glTexParameterxv;
#define glTexParameterxv glad_glTexParameterxv
GLAD_API_CALL PFNGLTEXPARAMETERXVOESPROC glad_glTexParameterxvOES;
#define glTexParameterxvOES glad_glTexParameterxvOES
GLAD_API_CALL PFNGLTEXSTORAGE1DEXTPROC glad_glTexStorage1DEXT;
#define glTexStorage1DEXT glad_glTexStorage1DEXT
GLAD_API_CALL PFNGLTEXSTORAGE2DEXTPROC glad_glTexStorage2DEXT;
#define glTexStorage2DEXT glad_glTexStorage2DEXT
GLAD_API_CALL PFNGLTEXSTORAGE3DEXTPROC glad_glTexStorage3DEXT;
#define glTexStorage3DEXT glad_glTexStorage3DEXT
GLAD_API_CALL PFNGLTEXSUBIMAGE2DPROC glad_glTexSubImage2D;
#define glTexSubImage2D glad_glTexSubImage2D
GLAD_API_CALL PFNGLTEXTURESTORAGE1DEXTPROC glad_glTextureStorage1DEXT;
#define glTextureStorage1DEXT glad_glTextureStorage1DEXT
GLAD_API_CALL PFNGLTEXTURESTORAGE2DEXTPROC glad_glTextureStorage2DEXT;
#define glTextureStorage2DEXT glad_glTextureStorage2DEXT
GLAD_API_CALL PFNGLTEXTURESTORAGE3DEXTPROC glad_glTextureStorage3DEXT;
#define glTextureStorage3DEXT glad_glTextureStorage3DEXT
GLAD_API_CALL PFNGLTRANSLATEFPROC glad_glTranslatef;
#define glTranslatef glad_glTranslatef
GLAD_API_CALL PFNGLTRANSLATEXPROC glad_glTranslatex;
#define glTranslatex glad_glTranslatex
GLAD_API_CALL PFNGLTRANSLATEXOESPROC glad_glTranslatexOES;
#define glTranslatexOES glad_glTranslatexOES
GLAD_API_CALL PFNGLUNMAPBUFFEROESPROC glad_glUnmapBufferOES;
#define glUnmapBufferOES glad_glUnmapBufferOES
GLAD_API_CALL PFNGLVERTEXPOINTERPROC glad_glVertexPointer;
#define glVertexPointer glad_glVertexPointer
GLAD_API_CALL PFNGLVIEWPORTPROC glad_glViewport;
#define glViewport glad_glViewport
GLAD_API_CALL PFNGLWAITSYNCAPPLEPROC glad_glWaitSyncAPPLE;
#define glWaitSyncAPPLE glad_glWaitSyncAPPLE
GLAD_API_CALL PFNGLWEIGHTPOINTEROESPROC glad_glWeightPointerOES;
#define glWeightPointerOES glad_glWeightPointerOES





GLAD_API_CALL int gladLoadGLES1UserPtr( GLADuserptrloadfunc load, void *userptr);
GLAD_API_CALL int gladLoadGLES1( GLADloadfunc load);



#ifdef __cplusplus
}
#endif
#endif
