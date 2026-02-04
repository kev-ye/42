import 'package:flutter/material.dart';
import '../services/intra_api.dart';
import 'login_view.dart';
import 'user_detail_view.dart';

// Search view
class SearchView extends StatefulWidget {
  const SearchView({super.key});

  @override
  State<SearchView> createState() => _SearchViewState();
}

class _SearchViewState extends State<SearchView> {
  final TextEditingController _controller = TextEditingController();
  final IntraApi _api = IntraApi();
  bool _isLoading = false;
  bool _loadingUserData = true;
  String? _errorMessage;
  String? _currentUserLogin;

  @override
  void initState() {
    super.initState();
    _loadCurrentUser();
  }

  void _loadCurrentUser() async {
    final userData = await _api.getCurrentUser();
    if (mounted) {
      setState(() {
        _loadingUserData = false;
        _currentUserLogin = userData?['login'] as String?;
      });
    }
  }

  void _searchUser() async {
    // Prevent race condition: return early if already loading
    if (_isLoading) return;

    if (_controller.text.isEmpty) {
      if (mounted) {
        setState(() {
          _errorMessage = 'Please enter a login';
        });
      }
      return;
    }

    // Update state before making API call
    if (mounted) {
      setState(() {
        _isLoading = true;
        _errorMessage = null;
      });
    }

    final userData = await _api.searchUser(_controller.text.trim());

    // Update state before navigation to avoid setState after dispose
    if (!mounted) return;

    if (userData == null) {
      setState(() {
        _isLoading = false;
        _errorMessage = 'Failed to fetch data';
      });
    } else if (userData.containsKey('error')) {
      setState(() {
        _isLoading = false;
        _errorMessage = userData['error'] as String;
      });
    } else {
      // Update state before navigation
      setState(() {
        _isLoading = false;
      });
      Navigator.push(
        context,
        MaterialPageRoute(
          builder: (context) => UserDetailView(userData: userData),
        ),
      );
    }
  }

  void _logout() async {
    await _api.logout();
    if (mounted) {
      Navigator.pushReplacement(
        context,
        MaterialPageRoute(
          builder: (context) => const LoginView(),
        ),
      );
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Search User'),
        actions: [
          IconButton(
            icon: const Icon(Icons.logout),
            onPressed: _logout,
            tooltip: 'Logout',
          ),
        ],
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            // Show loading indicator to prevent UI flicker
            if (_loadingUserData)
              const CircularProgressIndicator(strokeWidth: 2)
            else if (_currentUserLogin != null) ...[
              Text(
                'Logged in as: $_currentUserLogin',
                style: const TextStyle(fontSize: 16, fontWeight: FontWeight.w500),
              ),
              const SizedBox(height: 24),
            ],
            const Text(
              'Search 42 User',
              style: TextStyle(fontSize: 24, fontWeight: FontWeight.bold),
            ),
            const SizedBox(height: 32),
            TextField(
              controller: _controller,
              decoration: InputDecoration(
                labelText: 'Login',
                border: const OutlineInputBorder(),
                errorText: _errorMessage,
              ),
              onSubmitted: (_) => _searchUser(),
            ),
            const SizedBox(height: 16),
            ElevatedButton(
              onPressed: _isLoading ? null : _searchUser,
              child: _isLoading
                  ? const SizedBox(
                      width: 20,
                      height: 20,
                      child: CircularProgressIndicator(strokeWidth: 2),
                    )
                  : const Text('Search'),
            ),
          ],
        ),
      ),
    );
  }

  @override
  void dispose() {
    _controller.dispose();
    super.dispose();
  }
}

