project('c_timer'
  , ['c']
  , version : '0.0.1'
  , default_options : ['warning_level=0'
    ,'c_std=gnu99']
)
add_project_arguments('-D_GNU_SOURCE', language : 'c')
#//***********************************************************/
deps = []
test_deps = []
srcs = []
c_timer_test_env = environment()
test_env = environment()
cc = meson.get_compiler('c')
#//***********************************************************/
find_deps_cmd = 'find meson/deps -type f -name meson.build|xargs dirname|sort -u'
find_enabled_bins_cmd = 'make enabled-bins'
csv = ['submodules/csv_parser/csv.c','submodules/csv_parser/split.c','submodules/csv_parser/fread_csv_line.c']
vterm = ['submodules/libvterm/src/vterm.c','submodules/libvterm/src/pen.c','submodules/libvterm/src/unicode.c',
'submodules/libvterm/src/parser.c', 'submodules/libvterm/src/screen.c', 'submodules/libvterm/src/state.c']
template = ['src/template/template.c','src/template/hashmap.c','src/template/vector.c','src/template/mpc.c','include/template/template.h','include/template/hashmap.h','include/template/vector.h','include/template/mpc.h']
#//***********************************************************/
sh = find_program('sh', required : true)
pwd_bin = find_program('pwd', required : true)
passh = find_program('passh', required : true)
#//***********************************************************/
find_deps = run_command(sh, '-c', find_deps_cmd, check: true).stdout().strip().split('\n')
enabled_bins = run_command(sh, '-c', find_enabled_bins_cmd, check: true).stdout().strip().split('\n')
pwd = run_command(pwd_bin, check: true).stdout().strip()
#//***********************************************************/
foreach m : find_deps
  subdir(m)
endforeach
#//***********************************************************/
host_system = host_machine.system()
#//***********************************************************/
cmake = import('cmake')
filesystem = import('fs')
pkg = import('pkgconfig')
#//***********************************************************/
opts = cmake.subproject_options()
opts.add_cmake_defines({'BUILD_SHARED_LIBS': false,'OLM_TESTS': false})
#//***********************************************************/
deps += dependency('threads', required : true)
deps += cc.find_library('m', required : true)
#//***********************************************************/
opts.set_override_option('werror', 'false')
opts.set_override_option('warning_level', '1')
#//***********************************************************/
incdir = include_directories(
  '.',
  './include', 
  './deps', 
  './src', 
)
install_headers([])
#//***********************************************************/
test_env.set('__MESON_TEST_MODE__', '1')
test_env.set('__SH', sh.full_path())
test_env.set('TEMPLATE_PATH', pwd + '/etc/tpl/color-names')
test_env.set('__BD', meson.current_build_dir())
test_env.set('__SD', meson.current_source_dir())
test_env.set('TEMPLATE_PATH', pwd + '/etc/tpl/color-names')
#//***********************************************************/
c_timer_test_env.set('__MESON_TEST_MODE__', '1')
#//***********************************************************/
bin_tests = []
bins = []
#//***********************************************************/
foreach b : enabled_bins
      bins += {
        'name': b,
        'executable': executable(b, ['bins/' + b + '.c', files(srcs)], 
          dependencies: [deps],
          include_directories: [incdir],
        )
      }
endforeach
foreach b : bins
  test(b['name'], b['executable'], args: ['--test'], env: test_env)
endforeach
