import 'package:flutter/material.dart';
import '../services/intra_api.dart';
import '../widgets/oauth_web_view.dart';
import 'search_view.dart';

// Login page
class LoginView extends StatefulWidget {
  const LoginView({super.key});

  @override
  State<LoginView> createState() => _LoginViewState();
}

class _LoginViewState extends State<LoginView> {
  final IntraApi _api = IntraApi();
  bool _isLoading = true;

  @override
  void initState() {
    super.initState();
    _checkLoginStatus();
  }

  void _checkLoginStatus() async {
    final isLoggedIn = await _api.isLoggedIn();
    if (isLoggedIn && mounted) {
      Navigator.pushReplacement(
        context,
        MaterialPageRoute(builder: (context) => const SearchView()),
      );
    } else {
      setState(() {
        _isLoading = false;
      });
    }
  }

  void _startLogin() {
    final authUrl = _api.getAuthorizationUrl();
    print('🔗 [LoginView] Generated auth URL: $authUrl');
    Navigator.push(
      context,
      MaterialPageRoute(
        builder: (context) => OAuthWebView(
          key: ValueKey(DateTime.now().millisecondsSinceEpoch), // Create unique key each time to ensure new instance
          authUrl: authUrl,
          redirectUri: IntraApi.redirectUri,
          onCodeReceived: _handleLoginSuccess,
        ),
      ),
    );
  }

  void _handleLoginSuccess(String code) async {
    // Close WebView
    if (mounted && Navigator.canPop(context)) {
      Navigator.pop(context);
    }

    setState(() {
      _isLoading = true;
    });

    final success = await _api.exchangeCodeForToken(code);

    if (success && mounted) {
      Navigator.pushReplacement(
        context,
        MaterialPageRoute(builder: (context) => const SearchView()),
      );
    } else {
      setState(() {
        _isLoading = false;
      });
      if (mounted) {
        ScaffoldMessenger.of(context).showSnackBar(
          const SnackBar(content: Text('Login failed')),
        );
      }
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('42 Swift Companion'),
      ),
      body: Center(
        child: _isLoading
            ? const CircularProgressIndicator(strokeWidth: 2)
            : Padding(
                padding: const EdgeInsets.all(32.0),
                child: Column(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: [
                    const Icon(Icons.school, size: 100, color: Colors.blue),
                    const SizedBox(height: 32),
                    const Text(
                      'Welcome to 42 Swift Companion',
                      style: TextStyle(fontSize: 24, fontWeight: FontWeight.bold),
                      textAlign: TextAlign.center,
                    ),
                    const SizedBox(height: 16),
                    const Text(
                      'Please login with your 42 account',
                      style: TextStyle(fontSize: 16),
                      textAlign: TextAlign.center,
                    ),
                    const SizedBox(height: 48),
                    ElevatedButton.icon(
                      onPressed: _startLogin,
                      icon: const Icon(Icons.login),
                      label: const Text('Login with 42'),
                      style: ElevatedButton.styleFrom(
                        padding: const EdgeInsets.symmetric(horizontal: 32, vertical: 16),
                      ),
                    ),
                  ],
                ),
              ),
      ),
    );
  }
}

