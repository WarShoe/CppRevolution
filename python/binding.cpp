#include <pybind11/pybind11.h>
#include <fmt/format.h>
#include "qf.hpp"

using namespace pybind11::literals;
namespace py = pybind11;

PYBIND11_MODULE(numerics_py, m) {

    py::enum_<qf::Type>(m, "Type")
        .value("Call", qf::Type::Call)
        .value("Put" , qf::Type::Put )
        .export_values();

    m.def(
        "Black76",
        py::overload_cast<double,double,double,double,double>(qf::Black76)
    );
    m.def(
        "Black76",
        py::overload_cast<double,double,double,double,double,qf::Type>(qf::Black76)
    );
    m.def(
        "Bachelier",
        py::overload_cast<double,double,double,double,double>(qf::Bachelier),
        "This is my help!"
    );
    m.def(
        "Bachelier",
        py::overload_cast<double,double,double,double,double,qf::Type>(qf::Bachelier)
    );
    m.def(
        "Black76_ivol",
        qf::Black76_ivol,
        "Calculate implied volatility",
        py::arg("price"),
        py::arg("Call_or_Put"),
        py::arg("stock"),
        py::arg("strike"),
        py::arg("time"),
        py::arg("discount"),
        py::arg("vol_start") = 0.1,
        py::arg("vol_lo") = 0,
        py::arg("vol_hi") = 1,
        py::arg("price_tolerance") = 1e-9
    );
    m.def("Bachelier_ivol",qf::Bachelier_ivol);
    m.def(
        "Hi",
        [] (std::string name) {
            return fmt::format("Hello, {}!",name);
        },
        "Just says 'hi' to a person."
    );
    m.def(
        "Hi",
        [] (int x) {
            return fmt::format("Hello, {}!",x);
        }
    );
}
