#include <cstdlib>
#include <iostream>

#include <dlfcn.h>
#include <ucp_client_server.h>

int main(int argc, char** argv) {
  // Python effectively does this upon importing a C extension
  void* handle = dlopen("./libclient_server.so", RTLD_NOW | RTLD_LOCAL);
  if (!handle) {
    std::cerr << "Failed to open clientserver.so: " << dlerror() << std::endl;
    return EXIT_FAILURE;
  }

  decltype(&RunMain) run_main = nullptr;
  run_main = reinterpret_cast<decltype(run_main)>(dlsym(handle, "RunMain"));

  if (auto error = dlerror()) {
    std::cerr << "Failed to get RunMain: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return run_main(argc, argv);
}
