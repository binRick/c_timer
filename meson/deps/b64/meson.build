b64_lib = library('b64', 
'../../../deps/b64/buffer.c', 
'../../../deps/b64/encode.c', 
'../../../deps/b64/decode.c', 
install: false, dependencies: [], 
  include_directories: [
    '../../../deps/b64',
  ]
)
b64_dep = declare_dependency(include_directories: ['../../../deps/b64'], link_with: b64_lib)
deps += b64_dep
