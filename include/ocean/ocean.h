// Copyright 2024 Tencent Inc. All rights reserved.
// Ocean is stand for WeChat Mini Program app(Windows).

#pragma once
#ifndef OCEAN_H_
#define OCEAN_H_

#include <wtypes.h>
#define DLLEXPORT __declspec(dllexport)

#ifdef __cplusplus
extern "C" {
#endif

/**** Error Code *****/
    typedef enum OceanErrorCode {
        OCEAN_OK = 0,
        OCEAN_UNDEFINED = 100,
        OCEAN_UNHANDLED_SYSTEM_ERROR = 101,
        OCEAN_PERMISSION_DENIED = 102,
        OCEAN_NO_SUCH_FILE_OR_DIRECTORY = 103,
        OCEAN_USER_ABORT = 104,
        OCEAN_NOT_INSTALLED = 105,
        OCEAN_FAILED_TO_LAUNCH = 106,
        OCEAN_MINIPROGRAM_ALREADY_LAUNCHED = 107,
        OCEAN_NO_INTERNET_CONNECTION = 108,
        OCEAN_URI_UNREACHED = 109,
        OCEAN_NO_MEMORY = 110,
        OCEAN_FAILED_TO_INSTALL = 111,
        OCEAN_CANCELED = 112,
        OCEAN_FILE_NOT_FOUND = 113,
        OCEAN_UNSUPPORTED_PROCESSOR_ARCH = 114,
        OCEAN_UNSUPPORTED_WINDOWS_VERSION = 115,
} OceanErrorCode_t;

/**
 * @brief A handle to an async task. Positive value for a valid task, and 0 for
 * an invalid task.
 *
 */
typedef unsigned int OceanAsyncTask;

/**
 * @brief Callback for downloading ocean app's installer.
 *
 * @param err_code error code.
 * @param progress download progress in [0, 100]. 100 for download complete. No
 * meaning if err_code is not OCEAN_OK.
 * @param fullpath File path to the downloaded installer if (err_code ==
 * OCEAN_OK && progress == 100); NULL otherwise.
 */
typedef void (*OceanOnDownloadInstallerFun)(OceanAsyncTask task,
                                            OceanErrorCode_t err_code,
                                            int progress,
                                            const wchar_t *__restrict fullpath);

/**
 * @brief Callback for the installing ocean app.
 *
 * @param err_code error code.
 * @param system_error. Windows system error returned by GetLastError(). Only
 * available if err_code == OCEAN_UNHANDLED_SYSTEM_ERROR.
 */
typedef void (*OceanOnInstallFun)(OceanAsyncTask task,
                                  OceanErrorCode_t err_code,
                                  DWORD system_error);

/**
 * @brief Callback for opening a mini program.
 *
 * @param err_code error code.
 * @param system_error. Windows system error returned by GetLastError(). Only
 * available if err_code == OCEAN_UNHANDLED_SYSTEM_ERROR.
 */
typedef void (*OceanOnOpenMiniProgramFun)(OceanAsyncTask task,
                                          OceanErrorCode_t err_code,
                                          DWORD system_error);

typedef struct DLLEXPORT OceanDelegate {
  OceanOnDownloadInstallerFun on_download_installer;
  OceanOnInstallFun on_install_ocean;
  OceanOnOpenMiniProgramFun on_open_miniprogram;
} OceanDelegate_t;

/**
 * @brief Initialize the SDK. You should pair the init/uninit invocation if you
 * want to invoke this function multiple times.
 *
 * @param channel_id Your Channal ID, or NULL if you don't have one.
 * @param delegate A pointer to your OceanDelegate object. The pointed object
 * should remain alive after ocean_uninit is invoked. You should take care of
 * the memory management of this object.
 */
DLLEXPORT void ocean_init(const char *__restrict channel_id, OceanDelegate_t *delegate);

/**
 * @brief Uninitialize the SDK. Does nothing if not invoke ocean_init() yet.
 * Note: It's necessary to invoke this method, such that the SDK could remove all local files properly. 
 */
DLLEXPORT void ocean_uninit();

/**
 * @brief Check if ocean app is installed on the system.
 *
 * @return true if installed.
 */
DLLEXPORT bool ocean_check_installation();

/**
 * @brief Download the full installer of Ocean App.
 */
DLLEXPORT OceanAsyncTask ocean_download_installer();

/**
 * @brief Download the web installer of Ocean App. This installer is much
 * smaller. If you don't provide a user interface to indicate to download
 * process, it's better to use this one so the user won't wait too long.
 */
DLLEXPORT OceanAsyncTask ocean_download_web_installer();

/**
 * @brief Cancel a download task.
 */
DLLEXPORT void ocean_cancel_download_task(OceanAsyncTask task_id);

/**
 * @brief Install Ocean app.
 *
 * @param fullpath Path to the installer.
 * @param appid AppID of a mini-program you'd like to show in the installing process.
 * @param path In-app path and query to launch. NULL for the default page. For a
 * mini-game it's OK to set query only, eg "?foo=bar".
 */
DLLEXPORT OceanAsyncTask ocean_install(const wchar_t *__restrict fullpath, const char* __restrict appid, const char* __restrict path);

/**
 * @brief Launcher a mini-program.
 *
 * @param appid AppID of the mini-program.
 * @param path In-app path and query to launch. NULL for the default page. For a
 * mini-game it's OK to set query only, eg "?foo=bar".
 */
DLLEXPORT OceanAsyncTask ocean_open_miniprogram(const char *__restrict appid,
                                      const char *__restrict path);

/**
 * @brief Download、Install and Launcher a mini-program in one single funciton.
 *
 * @param appid AppID of the mini-program.
 * @param path In-app path and query to launch. NULL for the default page. For a
 * mini-game it's OK to set query only, eg "?foo=bar".
 */
DLLEXPORT OceanAsyncTask ocean_open_miniprogram_all_in_one(const char *__restrict appid,
                                                 const char *__restrict path);

#ifdef __cplusplus
}
#endif

#endif // OCEAN_H_