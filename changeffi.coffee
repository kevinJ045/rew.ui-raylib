changeFfi = (obj) => {
  for key, value in obj
    args = value.parameters.map (i) => "ffi::#{i}"
    ret = "ffi::#{value.result}"
    rew::io::out.print "ffi_type(#{args}) #{key} = -> #{ret}"
}

changeFfi {
  "GuiButton": { parameters: ["buffer", "i32", "i32", "i32", "i32"], result: "bool" },
}