#include <boost/python.hpp>

using namespace boost::python;

void export_AmaInstance();

void export_instance_main() {
    export_AmaInstance();
}
