#include <pybind11/pybind11.h>

void say_hello(const std::string& name) {
    printf("Hello, %s!\n", name.c_str());
}

PYBIND11_MODULE(example, m) {
    m.def("say_hello", &say_hello, "A function that greets somebody");
}