project('wc', 'c',
  version : '0.1',
  default_options : ['warning_level=3', 'c_std=c11'])

glib = dependency('glib-2.0')

deps = [glib]

lib_obj = static_library(
  'lib',
  'src/lib.c',
  dependencies: deps,
  include_directories: include_directories('.')
)

executable(
  'wc-clone',
  'src/main.c',
  link_with: lib_obj,
  dependencies: deps
)

test(
  'unit',
  executable('unit', 'tests/unit.c', dependencies: deps, link_with: lib_obj),
  env: [
    'G_TEST_SRCDIR=@0@'.format(meson.current_source_dir()),
    'G_TEST_BUILDDIR=@0@'.format(meson.current_build_dir()),
  ],
  protocol: 'tap',
)

test(
  'integration',
  executable('integration', 'tests/integration.c', dependencies: deps, link_with: lib_obj),
  env: [
    'G_TEST_SRCDIR=@0@'.format(meson.current_source_dir()),
    'G_TEST_BUILDDIR=@0@'.format(meson.current_build_dir()),
  ],
  protocol: 'tap',
)
