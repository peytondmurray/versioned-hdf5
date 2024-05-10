project(
  'versioned-hdf5',
  'cpp',
  version: run_command(['python', '-m', 'setuptools_scm'], check: true).stdout().strip(),
)

pybind11_dep = dependency('pybind11', version: '>=2.10.4')
includes = include_directories(
  [
    'versioned_hdf5/src',
  ]
)
srcs = [
  'versioned_hdf5/src/arrays.cpp',
]


py = import('python').find_installation()
py.install_sources(
  [
    'versioned_hdf5/tests/__init__.py',
    'versioned_hdf5/tests/conftest.py',
    'versioned_hdf5/tests/test_api.py',
    'versioned_hdf5/tests/test_backend.py',
    'versioned_hdf5/tests/test_hashtable.py',
    'versioned_hdf5/tests/test_replay.py',
    'versioned_hdf5/tests/test_slicetools.py',
    'versioned_hdf5/tests/test_versions.py',
    'versioned_hdf5/tests/test_wrappers.py',
  ],
  subdir: 'versioned_hdf5/tests',
)
py.install_sources(
  [
    'versioned_hdf5/__init__.py',
    'versioned_hdf5/api.py',
    'versioned_hdf5/backend.py',
    'versioned_hdf5/hashtable.py',
    'versioned_hdf5/replay.py',
    'versioned_hdf5/slicetools.py',
    'versioned_hdf5/versions.py',
    'versioned_hdf5/wrappers.py',
  ],
  subdir: 'versioned_hdf5',
)

py.extension_module(
  '_arrays',
  srcs,
  install: true,
  subdir: 'versioned_hdf5',
  include_directories: includes,
  dependencies: [pybind11_dep]
)
