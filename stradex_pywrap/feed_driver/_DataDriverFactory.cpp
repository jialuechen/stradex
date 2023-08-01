#include <boost/python.hpp>
#include <stradex/data_driver/DataDriverFactory.h>

using namespace stradex;
using namespace boost::python;

void export_DataDriverFactory() {
    class_<DataDriverFactory>("DataDriverFactory", no_init)
      //.def("getBaseInfoDriver", &DataDriverFactory::getBaseInfoDriver)
      //.def("regBaseInfoDriver", &DataDriverFactory::regBaseInfoDriver)
      //.def("removeBaseInfoDriver", &DataDriverFactory::removeBaseInfoDriver)
      .def("regKDataDriver", &DataDriverFactory::regKDataDriver)
      .def("removeKDataDriver", &DataDriverFactory::removeKDataDriver)
      .def("getBlockDriver", &DataDriverFactory::getBlockDriver)
      .def("regBlockDriver", &DataDriverFactory::regBlockDriver)
      .def("removeBlockDriver", &DataDriverFactory::removeBlockDriver)
      //.staticmethod("getBaseInfoDriver")
      //.staticmethod("regBaseInfoDriver")
      //.staticmethod("removeBaseInfoDriver")
      .staticmethod("getBlockDriver")
      .staticmethod("regBlockDriver")
      .staticmethod("removeBlockDriver");
}
