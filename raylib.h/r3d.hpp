
/**
 * @brief Blend modes for rendering.
 *
 * Defines common blending modes used in 3D rendering to combine source and destination colors.
 * @note The blend mode is applied only if you are in forward rendering mode or auto-detect mode.
 */
typedef enum R3D_BlendMode {
    R3D_BLEND_OPAQUE,          ///< No blending, the source color fully replaces the destination color.
    R3D_BLEND_ALPHA,           ///< Alpha blending: source color is blended with the destination based on alpha value.
    R3D_BLEND_ADDITIVE,        ///< Additive blending: source color is added to the destination, making bright effects.
    R3D_BLEND_MULTIPLY         ///< Multiply blending: source color is multiplied with the destination, darkening the image.
} R3D_BlendMode;

/**
 * @brief Face culling modes for a mesh.
 *
 * Specifies which faces of a geometry are discarded during rendering based on their winding order.
 */
typedef enum R3D_CullMode {
    R3D_CULL_NONE,   ///< No culling; all faces are rendered.
    R3D_CULL_BACK,   ///< Cull back-facing polygons (faces with clockwise winding order).
    R3D_CULL_FRONT   ///< Cull front-facing polygons (faces with counter-clockwise winding order).
} R3D_CullMode;

/**
 * @brief Shadow casting modes for objects.
 *
 * Controls how an object interacts with the shadow mapping system.
 * These modes determine whether the object contributes to shadows,
 * and if so, whether it is also rendered in the main pass.
 */
typedef enum R3D_ShadowCastMode {
    R3D_SHADOW_CAST_ON,                 ///< The object casts shadows; the faces used are determined by the material's culling mode.
    R3D_SHADOW_CAST_ON_DOUBLE_SIDED,    ///< The object casts shadows with both front and back faces, ignoring face culling.
    R3D_SHADOW_CAST_ON_FRONT_SIDE,      ///< The object casts shadows with only front faces, culling back faces.
    R3D_SHADOW_CAST_ON_BACK_SIDE,       ///< The object casts shadows with only back faces, culling front faces.
    R3D_SHADOW_CAST_ONLY,               ///< The object only casts shadows; the faces used are determined by the material's culling mode.
    R3D_SHADOW_CAST_ONLY_DOUBLE_SIDED,  ///< The object only casts shadows with both front and back faces, ignoring face culling.
    R3D_SHADOW_CAST_ONLY_FRONT_SIDE,    ///< The object only casts shadows with only front faces, culling back faces.
    R3D_SHADOW_CAST_ONLY_BACK_SIDE,     ///< The object only casts shadows with only back faces, culling front faces.
    R3D_SHADOW_CAST_DISABLED            ///< The object does not cast shadows at all.
} R3D_ShadowCastMode;

/**
 * @brief Defines billboard modes for 3D objects.
 *
 * This enumeration defines how a 3D object aligns itself relative to the camera.
 * It provides options to disable billboarding or to enable specific modes of alignment.
 */
typedef enum R3D_BillboardMode {
    R3D_BILLBOARD_DISABLED,     ///< Billboarding is disabled; the object retains its original orientation.
    R3D_BILLBOARD_FRONT,        ///< Full billboarding; the object fully faces the camera, rotating on all axes.
    R3D_BILLBOARD_Y_AXIS        /**< Y-axis constrained billboarding; the object rotates only around the Y-axis,
                                     keeping its "up" orientation fixed. This is suitable for upright objects like characters or signs. */
} R3D_BillboardMode;

/**
 * @brief Types of lights supported by the rendering engine.
 *
 * Each light type has different behaviors and use cases.
 */
typedef enum R3D_LightType {
    R3D_LIGHT_DIR,                      ///< Directional light, affects the entire scene with parallel rays.
    R3D_LIGHT_SPOT,                     ///< Spot light, emits light in a cone shape.
    R3D_LIGHT_OMNI                      ///< Omni light, emits light in all directions from a single point.
} R3D_LightType;

/**
 * @brief Modes for updating shadow maps.
 *
 * Determines how often the shadow maps are refreshed.
 */
typedef enum R3D_ShadowUpdateMode {
    R3D_SHADOW_UPDATE_MANUAL,           ///< Shadow maps update only when explicitly requested.
    R3D_SHADOW_UPDATE_INTERVAL,         ///< Shadow maps update at defined time intervals.
    R3D_SHADOW_UPDATE_CONTINUOUS        ///< Shadow maps update every frame for real-time accuracy.
} R3D_ShadowUpdateMode;

/**
 * @brief Bloom effect modes.
 *
 * Specifies different post-processing bloom techniques that can be applied
 * to the rendered scene. Bloom effects enhance the appearance of bright areas
 * by simulating light bleeding, contributing to a more cinematic and realistic look.
 */
 typedef enum R3D_Bloom {
    R3D_BLOOM_DISABLED,     ///< Bloom effect is disabled. The scene is rendered without any glow enhancement.
    R3D_BLOOM_MIX,          ///< Blends the bloom effect with the original scene using linear interpolation (Lerp).
    R3D_BLOOM_ADDITIVE,     ///< Adds the bloom effect additively to the scene, intensifying bright regions.
    R3D_BLOOM_SCREEN        ///< Combines the scene and bloom using screen blending, which brightens highlights
} R3D_Bloom;

/**
 * @brief Fog effect modes.
 *
 * Determines how fog is applied to the scene, affecting depth perception and atmosphere.
 */
typedef enum R3D_Fog {
    R3D_FOG_DISABLED, ///< Fog effect is disabled.
    R3D_FOG_LINEAR,   ///< Fog density increases linearly with distance from the camera.
    R3D_FOG_EXP2,     ///< Exponential fog (exp2), where density increases exponentially with distance.
    R3D_FOG_EXP       ///< Exponential fog, similar to EXP2 but with a different rate of increase.
} R3D_Fog;

/**
 * @brief Tone mapping modes.
 *
 * Controls how high dynamic range (HDR) colors are mapped to low dynamic range (LDR) for display.
 */
typedef enum R3D_Tonemap {
    R3D_TONEMAP_LINEAR,   ///< Simple linear mapping of HDR values.
    R3D_TONEMAP_REINHARD, ///< Reinhard tone mapping, a balanced method for compressing HDR values.
    R3D_TONEMAP_FILMIC,   ///< Filmic tone mapping, mimicking the response of photographic film.
    R3D_TONEMAP_ACES,     ///< ACES tone mapping, a high-quality cinematic rendering technique.
    R3D_TONEMAP_AGX,      ///< AGX tone mapping, a modern technique designed to preserve both highlight and shadow details for HDR rendering.
    R3D_TONEMAP_COUNT     ///< Number of tone mapping modes (used internally)
} R3D_Tonemap;

/**
 * @brief Depth of field effect modes.
 *
 * Controls how depth of field is applied to the scene, affecting the focus and blur of objects.
 */
typedef enum R3D_Dof {
    R3D_DOF_DISABLED, ///< Depth of field effect is disabled.
    R3D_DOF_ENABLED,  ///< Depth of field effect is enabled.
} R3D_Dof;

/**
 * @brief Animation Update modes.
 *
 * Controls wether to allow external animation matrices
 */

typedef enum R3D_AnimMode {
    R3D_ANIM_INTERNAL,         ///< default animation solution
    R3D_ANIM_CUSTOM,           ///< user supplied matrices 
} R3D_AnimMode;