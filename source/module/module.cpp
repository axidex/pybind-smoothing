#include <pybind11/pybind11.h>

#include"smoothing.h"

PYBIND11_MODULE(smoothingmodule, module)
{
	module.doc() = "smoothingmodule";

	pybind11::class_<Smoothing>(module, "Smoothing")
		.def(pybind11::init<>())
		.def(pybind11::init<int, int>(), "constructor 2", pybind11::arg("sigmaColor"), pybind11::arg("sigmaSpace"))
		.def("set_sigmaColor", &Smoothing::set_sigmaColor, pybind11::arg("sigmaColor"))
		.def("set_sigmaSpace", &Smoothing::set_sigmaSpace, pybind11::arg("sigmaSpace"))
		.def("init_image", &Smoothing::init_image, pybind11::arg("name"))
		.def("init_cascade", &Smoothing::init_cascade, pybind11::arg("cascadeName"))
		.def("detectAndDraw", &Smoothing::detectAndDraw)
		.def("show", &Smoothing::show)
		.def("save", &Smoothing::save, pybind11::arg("path"));
}
