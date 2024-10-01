import h5py
import numpy as np

from versioned_hdf5 import VersionedHDF5File

d = "./testdata.h5"

with h5py.File(d, mode="w") as f:
    with VersionedHDF5File(f).stage_version("r0") as sv:
        sv.create_dataset("values", data=np.arange(100), chunks=(10,), maxshape=(None,))

with h5py.File(d, mode="r+") as f:
    with VersionedHDF5File(f).stage_version("r1") as sv:
        values = sv["values"][:]
        values.resize((110,))  # <-- Exception raised here
