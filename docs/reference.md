# API Documentation

## VersionedHDF5File

::: versioned_hdf5.api.VersionedHDF5File

## Version Replaying

The functions in this module allow replaying versions in a file
in-place, in order to globally modify metadata across all versions that
otherwise cannot be changed across versions, such as the dtype of a
dataset. This also allows editing data in old versions, and deleting
datasets or versions.

<!-- ::: {.automodule members=""} -->
<!-- versioned_hdf5.replay -->
<!-- ::: -->
