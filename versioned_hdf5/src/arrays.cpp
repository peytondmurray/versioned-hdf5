#include <Python.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <hdf5.h>

namespace py = pybind11;

/**
 * @brief Read strings from an hdf5 vlen string array to a numpy vlen utf8 string array.
 *
 * This function makes use of the buffer protocol; see
 * https://docs.python.org/3/c-api/buffer.html and
 * https://pybind11.readthedocs.io/en/stable/advanced/pycpp/numpy.html
 * for more information.
 *
 * @param dataset h5py.Dataset instance to read into a numpy array
 * @return Tuple of three arrays:
 *      (delta_t(year2 - year1), year1, year2)
 */
PyObject *to_npy_str_array(
    PyObject *dataset

) {

    pybind11::object name = pybind11::getattr(dataset, "name")
    const char *filename = name.cast<const char *>();
    hid_t dataset_id = H5Dopen(
        file_id,
        filename,
        H5P_DEFAULT
    )

    H5Dopen(
        dataset.
    )

    H5Ddataset *dataset = dataset.ptr()
    printf("foo");

    // if (
    //     start1_bufinfo.ndim != 1 ||
    //     start2_bufinfo.ndim != 1 ||
    //     mean_t1_bufinfo.ndim != 1 ||
    //     mean_t2_bufinfo.ndim != 1
    // ) {
    //     throw std::runtime_error("All inputs must be 1-dimensional");
    // }

    // short *pStart1 = static_cast<short *>(start1_bufinfo.ptr);
    // short *pStart2 = static_cast<short *>(start2_bufinfo.ptr);
    // float *pMeanT1 = static_cast<float *>(mean_t1_bufinfo.ptr);
    // float *pMeanT2 = static_cast<float *>(mean_t2_bufinfo.ptr);
    //
    // py::ssize_t outLen = start1_bufinfo.shape[0]*start2_bufinfo.shape[0];
    //
    // // Let numpy allocate the new buffers
    // py::array_t<float> arrDt = py::array_t<float>(outLen);
    // py::array_t<short> arrStart1 = py::array_t<short>(outLen);
    // py::array_t<short> arrStart2 = py::array_t<short>(outLen);
    //
    // // Grab the buffer info via the buffer protocol
    // py::buffer_info buf_arrDt = arrDt.request();
    // py::buffer_info buf_arrStart1 = arrStart1.request();
    // py::buffer_info buf_arrStart2 = arrStart2.request();
    //
    // // Cast the pointers for each array to the appropriate type
    // float *pbuf_arrDt = static_cast<float *>(buf_arrDt.ptr);
    // short *pbuf_arrStart1 = static_cast<short *>(buf_arrStart1.ptr);
    // short *pbuf_arrStart2 = static_cast<short *>(buf_arrStart2.ptr);
    //
    // int k = 0;
    // for (int i=0; i<start1_bufinfo.shape[0]; i++) {
    //     for (int j=0; j<start2_bufinfo.shape[0]; j++) {
    //         pbuf_arrDt[k] = pMeanT2[j] - pMeanT1[i];
    //         pbuf_arrStart1[k] = pStart1[i];
    //         pbuf_arrStart2[k] = pStart2[j];
    //         k++;
    //     }
    // }

    int arrDt = 1;

    return py::make_tuple(arrDt);
}

PYBIND11_MODULE(_arrays, m) {
    m.doc() = "Bindings for fast compiled versioned-hdf5 functions.";
    m.def(
        "to_npy_str_array",
        &to_npy_str_array,
        "Read an hdf5 variable length string array to a numpy UTF-8 string array",
        py::return_value_policy::take_ownership
    );
}
