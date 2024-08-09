#include <pybind11/pybind11.h>
#include <hdf5.h>

namespace py = pybind11;

py::tuple spaceid_to_slice(hid_t id) {

    int rank;
    std::vector<hsize_t> start_array;
    std::vector<hsize_t> stride_array;
    std::vector<hsize_t> count_array;
    std::vector<hsize_t> block_array;
    htri_t ret;
    py::object slices = py::list();

    py::object Slice = py::module_::import("ndindex");

    switch (H5Sget_select_type(id)) {
        case H5S_SEL_ALL:
            return py::tuple();
        case H5S_SEL_NONE:
            return py::make_tuple(0, 0);
        case H5S_SEL_HYPERSLABS:

            rank = H5Sget_simple_extent_ndims(id);
            if (rank < 0) {
                throw py::value_error("Cannot determine rank of selection.");
            }

            ret = H5Sget_regular_hyperslab(
                id,
                start_array.data(),
                stride_array.data(),
                count_array.data(),
                block_array.data()
            );

            if (ret < 0) {
                throw py::value_error("Cannot determine hyperslab selection.");
            }

            for (int i=0; i<rank; i++) {
                hsize_t start = start_array[i];
                hsize_t stride = stride_array[i];
                hsize_t count = count_array[i];
                hsize_t block = block_array[i];


                if (block != 1 && count != 1) {
                    throw py::value_error("Nontrivial blocks are not yet supported.");
                }

                hsize_t end = start + (stride*(count - 1) + 1)*block;
                if (block != 1) {
                    stride = 1;
                }

                slices.attr("append")(Slice(start, end, stride));
            }

            return slices;
        default:
            throw py::value_error("Point selections are not yet supported");
    }
}


py::dict build_data_dict(py::object dcpl, py::str raw_data_name) {
    py::dict data_dict = py::dict();

    hid_t dcpl_id = py::cast<hid_t>(dcpl.attr("id"));
    size_t virtual_count = py::cast<size_t>(dcpl.attr("get_virtual_count")());

    char *dname;
    dname = py::cast<char *>(raw_data_name);
    size_t dnamelen = py::len(raw_data_name) + 1;

    char *vfilename = (char *)malloc(2);
    char *dset_buf = (char *)malloc(dnamelen);

    py::object spaceid_to_slice = (py::object) py::module_::import("slicetools").attr("spaceid_to_slice");

    for (size_t j=0; j<virtual_count; j++) {

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
