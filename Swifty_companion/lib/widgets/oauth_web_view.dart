import 'package:flutter/material.dart';
import 'package:webview_flutter/webview_flutter.dart';
import 'package:webview_flutter_android/webview_flutter_android.dart';
import 'package:webview_flutter_wkwebview/webview_flutter_wkwebview.dart';
import 'package:flutter/services.dart';

// OAuth WebView page
class OAuthWebView extends StatefulWidget {
  final String authUrl;
  final String redirectUri;
  final Function(String code) onCodeReceived;

  const OAuthWebView({
    super.key,
    required this.authUrl,
    required this.redirectUri,
    required this.onCodeReceived,
  });

  @override
  State<OAuthWebView> createState() => _OAuthWebViewState();
}

class _OAuthWebViewState extends State<OAuthWebView> {
  WebViewController? _controller;  // Nullable type because initialization is async
  bool _isLoading = true;
  bool _codeReceived = false;

  @override
  void initState() {
    super.initState();
    _initializeWebView();
  }

  // Clear cookies using platform channel (Android and iOS)
  Future<void> _clearCookies() async {
    try {
      const platform = MethodChannel('com.example.swiftcompanion/cookies');
      await platform.invokeMethod('clearCookies');
    } catch (e) {
      // If platform channel fails, ignore error (may not be supported on some devices)
      // On iOS, this error should not occur as we have implemented the platform channel
      print('Platform channel not available: $e');
    }
  }

  Future<void> _initializeWebView() async {
    print('🚀 [OAuthWebView] Initializing WebView...');
    print('   Auth URL: ${widget.authUrl}');
    print('   Redirect URI: ${widget.redirectUri}');
    
    // Clear cookies before creating WebView to ensure a fresh session each time
    // Note: On iOS, clearing cookies also clears cache and local storage
    try {
      await _clearCookies();
      print('✅ [OAuthWebView] Cookies cleared before WebView creation');
      // Give some time for the clear operation to complete
      await Future.delayed(const Duration(milliseconds: 100));
    } catch (e) {
      print('⚠️ [OAuthWebView] Error clearing cookies: $e');
    }

    // Create platform-specific WebView configuration
    late final PlatformWebViewControllerCreationParams params;
    if (WebViewPlatform.instance is WebKitWebViewPlatform) {
      params = WebKitWebViewControllerCreationParams(
        allowsInlineMediaPlayback: true,
        mediaTypesRequiringUserAction: const <PlaybackMediaTypes>{},
      );
    } else {
      params = AndroidWebViewControllerCreationParams();
    }

    final controller = WebViewController.fromPlatformCreationParams(params)
      ..setJavaScriptMode(JavaScriptMode.unrestricted)
      ..setUserAgent('Mozilla/5.0 (Linux; Android 10) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.120 Mobile Safari/537.36')
      ..setNavigationDelegate(
        NavigationDelegate(
          onNavigationRequest: (NavigationRequest request) {
            print('🔀 [OAuthWebView] Navigation request: ${request.url}');
            print('   Is main frame: ${request.isMainFrame}');
            
            // Intercept callback URL
            final uri = Uri.tryParse(request.url);
            if (uri != null) {
              final redirectUri = Uri.parse(widget.redirectUri);
              if (uri.scheme == redirectUri.scheme && uri.host == redirectUri.host) {
                print('🛑 [OAuthWebView] Intercepting redirect URI');
                _handleCallback(request.url);
                return NavigationDecision.prevent;
              }
            }
            print('✅ [OAuthWebView] Allowing navigation');
            return NavigationDecision.navigate;
          },
          onPageStarted: (String url) {
            print('📄 [OAuthWebView] Page started loading: $url');
            if (!_codeReceived) {
              setState(() {
                _isLoading = true;
              });
            }
            _handleCallback(url);
          },
          onPageFinished: (String url) {
            print('✅ [OAuthWebView] Page finished loading: $url');
            if (!_codeReceived) {
              setState(() {
                _isLoading = false;
              });
            }
            _handleCallback(url);
          },
          onWebResourceError: (WebResourceError error) {
            print('❌ [OAuthWebView] WebResourceError:');
            print('   Error code: ${error.errorCode}');
            print('   Description: ${error.description}');
            print('   URL: ${error.url}');
            
            // Ignore deep link errors (this is normal)
            if (error.description.contains('ERR_UNKNOWN_URL_SCHEME')) {
              return;
            }
            
            // Handle network errors
            String errorMessage = 'Loading error';
            if (error.description.contains('ERR_NAME_NOT_RESOLVED')) {
              errorMessage = 'Cannot connect to server, please check network connection\n(If using emulator, ensure emulator has network access)';
            } else if (error.description.contains('ERR_INTERNET_DISCONNECTED')) {
              errorMessage = 'Network connection disconnected, please check network settings';
            } else if (error.description.contains('ERR_TIMED_OUT')) {
              errorMessage = 'Connection timeout, please try again later';
            } else {
              errorMessage = 'Loading error: ${error.description}';
            }
            
            // Show error message to user
            if (mounted && !_codeReceived) {
              setState(() {
                _isLoading = false;
              });
              ScaffoldMessenger.of(context).showSnackBar(
                SnackBar(
                  content: Text(errorMessage),
                  duration: const Duration(seconds: 5),
                  action: SnackBarAction(
                    label: 'Retry',
                    onPressed: () {
                      // Reload page
                      _controller?.reload();
                    },
                  ),
                ),
              );
            }
          },
        ),
      );

    // Platform-specific configuration
    if (controller.platform is AndroidWebViewController) {
      // Android-specific: Clear cache and local storage for private session
      final androidController = controller.platform as AndroidWebViewController;
      await androidController.setMediaPlaybackRequiresUserGesture(false);
      
      // Clear cache and local storage (before loading URL)
      // Note: Clearing operation may affect input focus, so delay clearing
      try {
        // Load page first, then clear cache (to avoid affecting page loading and input)
        Future.delayed(const Duration(seconds: 2), () async {
          try {
            await androidController.clearCache();
            await androidController.clearLocalStorage();
            print('✅ [OAuthWebView] Android: Cache and localStorage cleared for private session');
          } catch (e) {
            print('❌ [OAuthWebView] Error clearing Android cache/localStorage: $e');
          }
        });
      } catch (e) {
        print('❌ [OAuthWebView] Error setting up Android cache clearing: $e');
      }
    } else if (controller.platform is WebKitWebViewController) {
      // iOS-specific: Cache and local storage are already cleared via platform channel
      // The _clearCookies() method called earlier uses WKWebsiteDataStore which clears
      // all website data including cookies, cache, and local storage on iOS
      print('✅ [OAuthWebView] iOS: Cache and localStorage already cleared via platform channel');
    }

    // Set controller first, then load URL
    if (mounted) {
      setState(() {
        _controller = controller;
      });
      print('✅ [OAuthWebView] Controller set in state');
    }

    // Wait a bit to ensure WebView is fully initialized
    print('⏳ [OAuthWebView] Waiting for WebView to initialize...');
    await Future.delayed(const Duration(milliseconds: 500));
    print('✅ [OAuthWebView] WebView initialization wait complete');

    // Load URL
    try {
      final uri = Uri.parse(widget.authUrl);
      print('🌐 [OAuthWebView] Loading URL: ${uri.toString()}');
      print('   Scheme: ${uri.scheme}');
      print('   Host: ${uri.host}');
      print('   Path: ${uri.path}');
      print('   Query: ${uri.query}');
      
      await controller.loadRequest(uri);
      print('✅ [OAuthWebView] URL load request sent successfully');
      
      // Set timeout: If page doesn't load within 15 seconds, show error
      Future.delayed(const Duration(seconds: 15), () {
        if (mounted && _isLoading && !_codeReceived) {
          print('⏰ [OAuthWebView] Timeout: Page did not load within 15 seconds');
          setState(() {
            _isLoading = false;
          });
          ScaffoldMessenger.of(context).showSnackBar(
            const SnackBar(
              content: Text('Page load timeout, please check network connection'),
              duration: Duration(seconds: 3),
            ),
          );
        }
      });
    } catch (e, stackTrace) {
      print('❌ [OAuthWebView] Error loading URL: $e');
      print('   Stack trace: $stackTrace');
      if (mounted) {
        setState(() {
          _isLoading = false;
        });
        ScaffoldMessenger.of(context).showSnackBar(
          SnackBar(
            content: Text('Failed to load page: $e'),
            duration: const Duration(seconds: 3),
          ),
        );
      }
    }
  }

  void _handleCallback(String url) {
    if (_codeReceived) return;

    final uri = Uri.tryParse(url);
    if (uri != null) {
      final redirectUri = Uri.parse(widget.redirectUri);
      if (uri.scheme == redirectUri.scheme && uri.host == redirectUri.host) {
        final code = uri.queryParameters['code'];
        final error = uri.queryParameters['error'];

        if (error != null) {
          if (mounted) {
            ScaffoldMessenger.of(context).showSnackBar(
              SnackBar(content: Text('Login error: $error')),
            );
            Navigator.pop(context);
          }
          return;
        }

        if (code != null) {
          _codeReceived = true;
          setState(() {
            _isLoading = false;
          });
          // Delay a bit before closing to ensure state update
          Future.delayed(const Duration(milliseconds: 100), () {
            if (mounted) {
              widget.onCodeReceived(code);
            }
          });
        }
      }
    }
  }

  @override
  void dispose() {
    // Clean up resources
    _controller = null;
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Login with 42'),
      ),
      body: _controller == null
          ? const Center(
              child: CircularProgressIndicator(strokeWidth: 2),
            )
          : Stack(
              children: [
                WebViewWidget(controller: _controller!),
                if (_isLoading)
                  const Center(
                    child: CircularProgressIndicator(strokeWidth: 2),
                  ),
              ],
            ),
    );
  }
}

