#include "./shim/r3d/details/r3d_billboard.c"
#include "./shim/r3d/details/r3d_drawcall.c"
#include "./shim/r3d/details/r3d_frustum.c"
#include "./shim/r3d/details/r3d_light.c"
#include "./shim/r3d/details/r3d_primitives.c"
#include "./shim/r3d/r3d_core.c"
#include "./shim/r3d/r3d_culling.c"
#include "./shim/r3d/r3d_curves.c"
#include "./shim/r3d/r3d_environment.c"
#include "./shim/r3d/r3d_lighting.c"
#include "./shim/r3d/r3d_model.c"
#include "./shim/r3d/r3d_particles.c"
#include "./shim/r3d/r3d_skybox.c"
#include "./shim/r3d/r3d_sprite.c"
#include "./shim/r3d/r3d_state.c"
#include "./shim/r3d/r3d_utils.c"

int main(void)
{
    InitWindow(800, 600, "R3D Example");
    R3D_Init(800, 600, 0);

    // Create scene objects
    R3D_Mesh mesh = R3D_GenMeshCube(1, 1, 1, true);
    R3D_Model model = R3D_LoadModelFromMesh(&mesh);
    R3D_Material material = R3D_GetDefaultMaterial();
    
    // Setup lighting
    R3D_Light light = R3D_CreateLight(R3D_LIGHT_DIR);
    R3D_SetLightDirection(light, (Vector3){ -1, -1, -1 });
    R3D_SetLightActive(light, true);
    
    // Camera setup
    Camera3D camera = {
        .position = { -3, 3, 3 },
        .target = { 0, 0, 0 },
        .up = { 0, 1, 0 },
        .fovy = 60.0f,
        .projection = CAMERA_PERSPECTIVE
    };

    // Main loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        R3D_Begin(camera);
        R3D_DrawModelEx(&model, (Vector3){x: 0, y: 0, z: 0}, (Vector3){x: 0, y: 0, z: 0}, 0.0f, (Vector3){x: 0, y: 0, z: 0});
        R3D_End();
        EndDrawing();
    }

    R3D_UnloadMesh(&mesh);
    R3D_Close();
    CloseWindow();
    return 0;
}
