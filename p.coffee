import "#std.ffi!";
using namespace rew::ns;

ins = instantiate class
  ffi_type(ffi::i32, ffi::i32, ffi::i32) R3D_Init = -> ffi::void

lib = rew::ffi::open "./.artifacts/librayshim.so", ins

print lib