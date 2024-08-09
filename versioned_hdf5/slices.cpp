#include <pybind11/pybind11.h>
#include <hdf5.h>

namespace py = pybind11;

py::dict build_data_dict(py::object dcpl, py::str raw_data_name) {
    auto data_dict = py::dict();

    hid_t dcpl_id = py::cast<hid_t>(dcpl.attr("id"));
    size_t virtual_count = py::cast<size_t>(dcpl.attr("get_virtual_count")());
    char* dname = py::cast<char *>(raw_data_name);
    size_t dnamelen = py::len(raw_data_name) + 1;

    char *vfilename = (char *)malloc(2);
    char *dset_buf = (char *)malloc(dnamelen);

    for (int j=0; j<virtual_count; j++) {

        // Check that the virtual file is '.'
        if (H5Pget_virtual_filename(dcpl_id, j, vfilename, 2) < 0) {
            free(vfilename);
            free(dset_buf);
            throw py::value_error("Could not get virtual filename.");
        }
        if (strncmp(vfilename, ".", 2) != 0) {
            free(vfilename);
            free(dset_buf);
            throw py::value_error("Virtual dataset filename mismatch, expected '.'.");
        }

        if (H5Pget_virtual_dsetname(dcpl_id, j, dset_buf, dnamelen) < 0) {
            free(vfilename);
            free(dset_buf);
            throw py::value_error("Could not get virtual dsetname.");
        }
        if (strncmp(dset_buf, dname, dnamelen) != 0) {
            free(vfilename);
            free(dset_buf);
            throw py::value_error("Virtual dataset name mismatch.");
        }

        hid_t vspace_id = H5Pget_virtual_vspace(dcpl_id, j);
        if (vspace_id == -1) {
            throw py::value_error("Could not get vspace_id");
        }

        hid_t srcspace_id = H5Pget_virtual_srcspace(dcpl_id, j);
        if (srcspace_id == -1) {
            throw py::value_error("Could not get srcspace_id");
        }

        py::tuple vspace_slice_tuple = spaceid_to_slice(vspace_id);
        py::tuple srcspace_slice_tuple = spaceid_to_slice(srcspace_id);

        data_dict[vspace_slice_tuple] = srcspace_slice_tuple.attr("args")[0];
    }

    free(vfilename);
    free(dset_buf);
    return data_dict;
}


PYBIND11_MODULE(slices, m) {
    m.doc() = "C++ slice tools.";
    m.def(
        "build_data_dict",
        &build_data_dict,
        "Build the data_dict of a versioned virtual dataset.",
        py::return_value_policy::take_ownership
    );
}
