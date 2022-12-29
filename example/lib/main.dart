import 'dart:async';
import 'dart:io';

import 'package:flutter/material.dart';
import 'package:flutter_zip_archive/flutter_zip_archive.dart';
import 'package:image_picker/image_picker.dart';
import 'package:path_provider/path_provider.dart';
import 'package:share/share.dart';

void main() => runApp(const MyApp());

class MyApp extends StatefulWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  final TextEditingController _controller = TextEditingController(text: '1234');

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Plugin example app'),
        ),
        body: Center(
          child: Column(
            children: <Widget>[
              Row(
                children: <Widget>[
                  const Text('Password:'),
                  Expanded(
                      child: TextField(
                    controller: _controller,
                  ))
                ],
              ),
              MaterialButton(
                color: Theme.of(context).primaryColor,
                onPressed: () {
                  _zip();
                },
                child: const Text('ZIP FILE'),
              ),
              MaterialButton(
                color: Theme.of(context).primaryColor,
                onPressed: () {
                  _unzip();
                },
                child: const Text('UNZIP'),
              )
            ],
          ),
        ),
      ),
    );
  }

  Future _zip() async {
    final file = await ImagePicker().pickImage(source: ImageSource.gallery);
    final Directory cacheDir = await getTemporaryDirectory();
    if (file == null) {
      return;
    }
    final Directory testDir = Directory('${cacheDir.path}/test/');
    testDir.createSync();
    file.saveTo('${cacheDir.path}/test/${file.name}');
    final map = await FlutterZipArchive.zip(
        '${cacheDir.path}/test', '${cacheDir.path}/123.zip', _controller.text);
    debugPrint('_map:$map');
    Share.shareFiles([map['path']], text: 'ZIP FILE');
  }

  Future _unzip() async {
    final Directory cacheDir = await getTemporaryDirectory();
    final map = await FlutterZipArchive.unzip(
        '${cacheDir.path}/123.zip', cacheDir.path, _controller.text);
    debugPrint('_map:$map');
  }
}
