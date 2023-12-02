project(
  'versioned-hdf5',
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
    'versioned_hdf5/__init__.py',
    'versioned_hdf5/_api.py',
    'versioned_hdf5/backend.py',
    'versioned_hdf5/hashtable.py',
    'versioned_hdf5/replay.py',
    'versioned_hdf5/slicetools.py',
    'versioned_hdf5/versions.py',
    'versioned_hdf5/wrappers.py',
  ],
  subdir: 'versioned_hdf5',
  pure: false
)

py.extension_module(
  '_compiled',
  srcs,
  install: true,
  subdir: 'versioned_hdf5',
  # include_directories: includes,
  # dependencies: [np_dep, npymath_lib]
)
