#include <boost/python.hpp>

using namespace boost::python;

void export_SpotAgent();

void export_global_main() {
    export_SpotAgent();
}
