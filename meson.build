project(
  'stringdtype',
  'c',
)

py_mod = import('python')
py = py_mod.find_installation()

cc = meson.get_compiler('c')

# includes = include_directories(
#   [
#     'stringdtype/src'
#   ]
# )

srcs = [
  'stringdtype/src/casts.c',
  'stringdtype/src/casts.h',
  'stringdtype/src/dtype.c',
  'stringdtype/src/main.c',
  'stringdtype/src/static_string.c',
  'stringdtype/src/static_string.h',
  'stringdtype/src/umath.c',
  'stringdtype/src/umath.h',
]

py.install_sources(
  [
    'stringdtype/__init__.py',
    'stringdtype/scalar.py',
  ],
  subdir: 'stringdtype',
  pure: false
)

py.extension_module(
  '_main',
  srcs,
  install: true,
  subdir: 'stringdtype',
  # include_directories: includes,
  # dependencies: [np_dep, npymath_lib]
)
