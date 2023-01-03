import 'dart:async';

import 'package:flutter/services.dart';

class FlutterZipArchive {
  static const MethodChannel _channel = MethodChannel('flutter_zip_archive');

  @Deprecated(
      'This method will be removed soon due to method channel not being implemented on the platforms')
  static Future<String> get platformVersion async {
    final String version = await _channel.invokeMethod('getPlatformVersion');
    return version;
  }

  static Future zip(String src, String dest, String password) async {
    return await _channel.invokeMethod('zip',
        <String, dynamic>{'src': src, 'dest': dest, 'password': password});
  }

  static Future unzip(String zip, String dest, String password) async {
    return await _channel.invokeMethod('unzip',
        <String, dynamic>{'zip': zip, 'dest': dest, 'password': password});
  }
}
