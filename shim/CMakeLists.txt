cmake_minimum_required(VERSION 3.8)
project(rayshim VERSION 0.1 LANGUAGES C CXX)

set(RAYSHIM_ROOT ${CMAKE_CURRENT_SOURCE_DIR})


set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_CURRENT_SOURCE_DIR}/cmake")


include(CheckLibraryExists)
include(EmbedShaders)
include(EmbedAssets)


find_package(PkgConfig REQUIRED)
pkg_check_modules(ASSIMP REQUIRED assimp)

include_directories(${ASSIMP_INCLUDE_DIRS})
link_directories(${ASSIMP_LIBRARY_DIRS})
add_definitions(${ASSIMP_CFLAGS_OTHER})

find_package(raylib QUIET)
get_target_property(RAYLIB_INCLUDE_DIR raylib INTERFACE_INCLUDE_DIRECTORIES)
set(R3D_RAYLIB_INC_PATH "${RAYLIB_INCLUDE_DIR}" CACHE STRING "Path to raylib includes" FORCE)



# Your sources
add_library(rayshim SHARED
    "${RAYSHIM_ROOT}/main.c"
    "${RAYSHIM_ROOT}/texture_gen.c"
    "${RAYSHIM_ROOT}/r3d/details/r3d_primitives.c"
    "${RAYSHIM_ROOT}/r3d/details/r3d_billboard.c"
    "${RAYSHIM_ROOT}/r3d/details/r3d_drawcall.c"
    "${RAYSHIM_ROOT}/r3d/details/r3d_frustum.c"
    "${RAYSHIM_ROOT}/r3d/details/r3d_light.c"
    "${RAYSHIM_ROOT}/r3d/r3d_environment.c"
    "${RAYSHIM_ROOT}/r3d/r3d_particles.c"
    "${RAYSHIM_ROOT}/r3d/r3d_lighting.c"
    "${RAYSHIM_ROOT}/r3d/r3d_culling.c"
    "${RAYSHIM_ROOT}/r3d/r3d_skybox.c"
    "${RAYSHIM_ROOT}/r3d/r3d_curves.c"
    "${RAYSHIM_ROOT}/r3d/r3d_sprite.c"
    "${RAYSHIM_ROOT}/r3d/r3d_model.c"
    "${RAYSHIM_ROOT}/r3d/r3d_utils.c"
    "${RAYSHIM_ROOT}/r3d/r3d_state.c"
    "${RAYSHIM_ROOT}/r3d/r3d_core.c"
    # "${RAYSHIM_ROOT}/include/glad/glad.c"
)


# EmbedShaders(${PROJECT_NAME}
#     "${RAYSHIM_ROOT}/shaders/common/screen.vert"
#     "${RAYSHIM_ROOT}/shaders/common/cubemap.vert"
#     "${RAYSHIM_ROOT}/shaders/generate/gaussian_blur_dual_pass.frag"
#     "${RAYSHIM_ROOT}/shaders/generate/downsampling.frag"
#     "${RAYSHIM_ROOT}/shaders/generate/upsampling.frag"
#     "${RAYSHIM_ROOT}/shaders/generate/cubemap_from_equirectangular.frag"
#     "${RAYSHIM_ROOT}/shaders/generate/irradiance_convolution.frag"
#     "${RAYSHIM_ROOT}/shaders/generate/prefilter.frag"
#     "${RAYSHIM_ROOT}/shaders/raster/geometry.vert"
#     "${RAYSHIM_ROOT}/shaders/raster/geometry_instanced.vert"
#     "${RAYSHIM_ROOT}/shaders/raster/geometry.frag"
#     "${RAYSHIM_ROOT}/shaders/raster/forward.vert"
#     "${RAYSHIM_ROOT}/shaders/raster/forward_instanced.vert"
#     "${RAYSHIM_ROOT}/shaders/raster/forward.frag"
#     "${RAYSHIM_ROOT}/shaders/raster/skybox.vert"
#     "${RAYSHIM_ROOT}/shaders/raster/skybox.frag"
#     "${RAYSHIM_ROOT}/shaders/raster/depth_volume.vert"
#     "${RAYSHIM_ROOT}/shaders/raster/depth_volume.frag"
#     "${RAYSHIM_ROOT}/shaders/raster/depth.vert"
#     "${RAYSHIM_ROOT}/shaders/raster/depth_instanced.vert"
#     "${RAYSHIM_ROOT}/shaders/raster/depth.frag"
#     "${RAYSHIM_ROOT}/shaders/raster/depth_cube.vert"
#     "${RAYSHIM_ROOT}/shaders/raster/depth_cube_instanced.vert"
#     "${RAYSHIM_ROOT}/shaders/raster/depth_cube.frag"
#     "${RAYSHIM_ROOT}/shaders/screen/ssao.frag"
#     "${RAYSHIM_ROOT}/shaders/screen/ambient.frag"
#     "${RAYSHIM_ROOT}/shaders/screen/lighting.frag"
#     "${RAYSHIM_ROOT}/shaders/screen/scene.frag"
#     "${RAYSHIM_ROOT}/shaders/screen/bloom.frag"
#     "${RAYSHIM_ROOT}/shaders/screen/ssr.frag"
#     "${RAYSHIM_ROOT}/shaders/screen/fog.frag"
#     "${RAYSHIM_ROOT}/shaders/screen/dof.frag"
#     "${RAYSHIM_ROOT}/shaders/screen/output.frag"
#     "${RAYSHIM_ROOT}/shaders/screen/fxaa.frag"
# )
# 
# EmbedAssets(${PROJECT_NAME}
#     "${RAYSHIM_ROOT}/assets/brdf_lut_512_rg16_float.raw"
#     "${RAYSHIM_ROOT}/assets/blue_noise_64_r8_unorm.raw"
# )


find_package(OpenGL REQUIRED)


# Link your target
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_glx_LIBRARY})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        raylib
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${ASSIMP_LIBRARIES})

check_library_exists(m cos "" HAVE_LIB_M)

if(HAVE_LIB_M)
    target_link_libraries(${PROJECT_NAME} PUBLIC m)
endif()

# Include r3d headers only
target_include_directories(rayshim PRIVATE
    "${RAYSHIM_ROOT}/external/glad"
    "${RAYSHIM_ROOT}/include"
)


# C standard
set_property(TARGET rayshim PROPERTY C_STANDARD 11)
set_property(TARGET rayshim PROPERTY C_STANDARD_REQUIRED ON)
set_property(TARGET rayshim PROPERTY C_EXTENSIONS OFF)
