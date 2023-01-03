#include "flutter_zip_archive_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <memory>
#include <sstream>

namespace flutter_zip_archive {

// static
void FlutterZipArchivePlugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows *registrar) {
  auto channel =
      std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
          registrar->messenger(), "flutter_zip_archive",
          &flutter::StandardMethodCodec::GetInstance());

  auto plugin = std::make_unique<FlutterZipArchivePlugin>();

  channel->SetMethodCallHandler(
      [plugin_pointer = plugin.get()](const auto &call, auto result) {
        plugin_pointer->HandleMethodCall(call, std::move(result));
      });

  registrar->AddPlugin(std::move(plugin));
}

FlutterZipArchivePlugin::FlutterZipArchivePlugin() {}

FlutterZipArchivePlugin::~FlutterZipArchivePlugin() {}

void FlutterZipArchivePlugin::HandleMethodCall(
    const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  // if (method_call.method_name().compare("getPlatformVersion") == 0) {
    // std::ostringstream version_stream;
  //   version_stream << "Windows ";
  //   if (IsWindows10OrGreater()) {
  //     version_stream << "10+";
  //   } else if (IsWindows8OrGreater()) {
  //     version_stream << "8";
  //   } else if (IsWindows7OrGreater()) {
  //     version_stream << "7";
  //   }
    // result->Success(flutter::EncodableValue(version_stream.str()));
  // } else {
  //   result->NotImplemented();
  // }
  if (method_call.method_name().compare("zip") == 0) {
    const auto *args = 
      std::get_if<flutter::EncodableMap>(method_call.arguments());

    flutter_zip_archive::ZipParams params;
    params.sourcePath = std::get<std::string>(args->at(flutter::EncodableValue("src")));
    params.destinationPath = std::get<std::string>(args->at(flutter::EncodableValue("dest")));
    params.password = std::get<std::string>(args->at(flutter::EncodableValue("password")));
    FlutterZipArchivePlugin::Zip(params, std::move(result));
  } else if (method_call.method_name().compare("unzip") == 0) {
    const auto *args =
      std::get_if<flutter::EncodableMap>(method_call.arguments());

    flutter_zip_archive::UnzipParams params;
    params.zipPath = std::get<std::string>(args->at(flutter::EncodableValue("zip")));
    params.destinationPath = std::get<std::string>(args->at(flutter::EncodableValue("dest")));
    params.password = std::get<std::string>(args->at(flutter::EncodableValue("password")));
    FlutterZipArchivePlugin::Unzip(params, std::move(result));
  } else {  
    result->NotImplemented();
  }
}

// TODO: Add zip method
void FlutterZipArchivePlugin::Zip(
  ZipParams params, std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
    result->Error("-1", "Method is not ready to use. This needs to be continued.");
}

// TODO: Add unzip method
void FlutterZipArchivePlugin::Unzip(
  UnzipParams params, std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
    result->Error("-1", "Method is not ready to use. This needs to be continued.");
}

}  // namespace flutter_zip_archive
