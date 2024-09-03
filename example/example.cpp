#include "ocean/ocean.h"

#include <iostream>

void on_download_installer(OceanAsyncTask task, OceanErrorCode_t err_code,
                           int progress, const wchar_t *__restrict fullpath) {
  std::wcout << "on_download_installer>>> task[" << task << "], err_code["
             << err_code << "] progress[" << progress << "] path[" << fullpath
             << "]" << std::endl;
  if (err_code == OCEAN_OK && progress == 100 && fullpath != nullptr) {
    OceanAsyncTask install_task = ocean_install(fullpath, "wxe5f52902cf4de896", "/page/cloud/index");
    std::wcout << "will install " << fullpath << std::endl;
  }
}

void on_install(OceanAsyncTask task, OceanErrorCode_t err_code,
                DWORD system_error) {
  std::cout << "on_install>>> task[" << task << "], err_code[" << err_code
            << "]" << std::endl;
}

void on_open_mini_program(OceanAsyncTask task, OceanErrorCode_t err_code,
                          DWORD system_error) {
  std::cout << "on_open_mini_program>>> task[" << task << "], err_code["
            << err_code << "]" << std::endl;
}

int main(int argc, char *argv[]) {
  OceanDelegate_t *delegate = new OceanDelegate_t();
  delegate->on_download_installer = on_download_installer;
  delegate->on_install_ocean = on_install;
  delegate->on_open_miniprogram = on_open_mini_program;
  ocean_init("official", delegate);
  // ocean_open_miniprogram_all_in_one("wxe5f52902cf4de896", "");
  bool installed = ocean_check_installation();
  std::cout << "Installed: " << (installed ? "true" : "false") << std::endl;
  if (installed) {
    OceanAsyncTask task = ocean_open_miniprogram("wxe5f52902cf4de896", "");
    std::cout << "Open MP task: " << task << std::endl;
  } else {
    OceanAsyncTask task = ocean_download_web_installer();
    std::cout << "Download task: " << task << std::endl;
    // std::getchar();
    // ocean_cancel_download_task(task);
  }
  std::cout << "Press any key to exit..." << std::endl;
  std::getchar();
  // Invoke uninit() such that the SDK get opportunity to delete cache files.
  ocean_uninit();
  return 0;
}