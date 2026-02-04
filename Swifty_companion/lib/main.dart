import 'package:flutter/material.dart';
import 'package:flutter_dotenv/flutter_dotenv.dart';
import 'screens/login_view.dart';

Future<void> main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await dotenv.load(fileName: ".env");
  runApp(const SwiftCompanionApp());
}

class SwiftCompanionApp extends StatelessWidget {
  const SwiftCompanionApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: '42 Swift Companion',
      theme: ThemeData(
        primarySwatch: Colors.blue,
        useMaterial3: true,
      ),
      home: const LoginView(),
    );
  }
}
