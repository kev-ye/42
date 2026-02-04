import 'package:http/http.dart' as http;
import 'dart:convert';
import 'package:flutter_secure_storage/flutter_secure_storage.dart';
import 'package:flutter_dotenv/flutter_dotenv.dart';

// API management class
class IntraApi {
  static String get uid => dotenv.get('INTRA_UID');
  static String get secret => dotenv.get('INTRA_SECRET');
  static String get redirectUri => dotenv.get('INTRA_REDIRECT_URI');
  static const String authUrl = 'https://api.intra.42.fr/oauth/authorize';
  static const String tokenUrl = 'https://api.intra.42.fr/oauth/token';
  static const String apiBase = 'https://api.intra.42.fr/v2';

  final storage = const FlutterSecureStorage();

  // Generate authorization URL
  String getAuthorizationUrl() {
    final params = {
      'client_id': uid,
      'redirect_uri': redirectUri,
      'response_type': 'code',
    };
    return Uri.parse(authUrl).replace(queryParameters: params).toString();
  }

  // Exchange authorization code for token
  Future<bool> exchangeCodeForToken(String code) async {
    try {
      print('🔐 [Token Management] Exchanging authorization code for token...');
      print('   Request URL: $tokenUrl');
      print('   Request body: grant_type=authorization_code&client_id=$uid&client_secret=***&code=$code&redirect_uri=$redirectUri');
      
      final response = await http.post(
        Uri.parse(tokenUrl),
        body: {
          'grant_type': 'authorization_code',
          'client_id': uid,
          'client_secret': secret,
          'code': code,
          'redirect_uri': redirectUri,
        },
      );

      print('📡 [Token Management] Response received:');
      print('   Status Code: ${response.statusCode}');
      print('   Headers: ${response.headers}');
      print('   Body: ${response.body}');

      if (response.statusCode == 200) {
        final data = json.decode(response.body) as Map<String, dynamic>;
        final accessToken = data['access_token'] as String;
        final refreshToken = data['refresh_token'] as String?;
        final expiresIn = data['expires_in'] as int;
        // Use created_at timestamp (if exists) or current time to calculate expiration
        final createdAt = data['created_at'] != null
            ? DateTime.fromMillisecondsSinceEpoch((data['created_at'] as int) * 1000)
            : DateTime.now();
        final expiresAt = createdAt.add(Duration(seconds: expiresIn));

        await storage.write(key: 'access_token', value: accessToken);
        await storage.write(key: 'expires_at', value: expiresAt.toIso8601String());
        if (refreshToken != null) {
          await storage.write(key: 'refresh_token', value: refreshToken);
          print('✅ [Token Management] Refresh token saved');
        }

        print('✅ [Token Management] Token obtained successfully');
        print('   Token expires in: ${expiresIn ~/ 60} minutes');
        print('   Token preview: ${accessToken.substring(0, 20)}...');
        return true;
      } else {
        print('❌ [Token Management] Token exchange failed: ${response.statusCode}');
      }
    } catch (e) {
      print('❌ [Token Management] Token exchange error: $e');
    }
    return false;
  }

  // Refresh access token using refresh token
  Future<bool> refreshToken() async {
    try {
      final refreshToken = await storage.read(key: 'refresh_token');
      if (refreshToken == null) {
        print('❌ [Token Management] No refresh token available');
        return false;
      }

      print('🔄 [Token Management] Refreshing access token...');
      final response = await http.post(
        Uri.parse(tokenUrl),
        body: {
          'grant_type': 'refresh_token',
          'client_id': uid,
          'client_secret': secret,
          'refresh_token': refreshToken,
        },
      );

      print('📡 [Token Management] Refresh response:');
      print('   Status Code: ${response.statusCode}');
      print('   Body: ${response.body}');

      if (response.statusCode == 200) {
        final data = json.decode(response.body) as Map<String, dynamic>;
        final accessToken = data['access_token'] as String;
        final newRefreshToken = data['refresh_token'] as String?;
        final expiresIn = data['expires_in'] as int;
        final createdAt = data['created_at'] != null
            ? DateTime.fromMillisecondsSinceEpoch((data['created_at'] as int) * 1000)
            : DateTime.now();
        final expiresAt = createdAt.add(Duration(seconds: expiresIn));

        await storage.write(key: 'access_token', value: accessToken);
        await storage.write(key: 'expires_at', value: expiresAt.toIso8601String());
        if (newRefreshToken != null) {
          await storage.write(key: 'refresh_token', value: newRefreshToken);
        }

        print('✅ [Token Management] Token refreshed successfully');
        print('   Token expires in: ${expiresIn ~/ 60} minutes');
        return true;
      } else {
        print('❌ [Token Management] Token refresh failed: ${response.statusCode}');
        // If refresh fails, clear tokens
        await storage.delete(key: 'access_token');
        await storage.delete(key: 'refresh_token');
        await storage.delete(key: 'expires_at');
      }
    } catch (e) {
      print('❌ [Token Management] Token refresh error: $e');
    }
    return false;
  }

  // Get valid token
  // Automatically refreshes token if expired and refresh token is available
  // Returns null if token is expired and cannot be refreshed, need to re-authenticate
  Future<String?> getValidToken() async {
    String? token = await storage.read(key: 'access_token');
    String? expiresAtStr = await storage.read(key: 'expires_at');

    if (token != null && expiresAtStr != null) {
      final expiry = DateTime.parse(expiresAtStr);
      final timeUntilExpiry = expiry.difference(DateTime.now());
      
      if (DateTime.now().isBefore(expiry.subtract(const Duration(minutes: 5)))) {
        // Token is still valid, reuse existing token
        print('✅ [Token Management] Reusing existing token');
        print('   Token expires in: ${timeUntilExpiry.inMinutes} minutes');
        print('   Token preview: ${token.substring(0, 20)}...');
        return token;
      } else {
        // Token is expiring soon or expired, try to refresh
        print('⚠️ [Token Management] Token expired or expiring soon');
        print('   Time until expiry: ${timeUntilExpiry.inMinutes} minutes');
        print('   Attempting to refresh token...');
        
        final refreshed = await refreshToken();
        if (refreshed) {
          // Get the new token
          token = await storage.read(key: 'access_token');
          if (token != null) {
            print('✅ [Token Management] Token refreshed, using new token');
            return token;
          }
        } else {
          print('❌ [Token Management] Failed to refresh token, need to re-authenticate');
          // Clear expired tokens
          await storage.delete(key: 'access_token');
          await storage.delete(key: 'expires_at');
        }
      }
    } else {
      print('⚠️ [Token Management] No token found');
    }
    return null;
  }

  // Check if logged in
  Future<bool> isLoggedIn() async {
    final token = await getValidToken();
    return token != null;
  }

  // Logout
  Future<void> logout() async {
    await storage.deleteAll();
    print('✅ [Token Management] Logged out, all tokens cleared');
  }

  // Get current user information
  Future<Map<String, dynamic>?> getCurrentUser() async {
    print('👤 [API Call] Getting current user info...');
    final token = await getValidToken();
    if (token == null) {
      print('❌ [API Call] No valid token available');
      return null;
    }

    print('📡 [API Call] Making request with token: ${token.substring(0, 20)}...');
    try {
      final response = await http.get(
        Uri.parse('$apiBase/me'),
        headers: {'Authorization': 'Bearer $token'},
      );

      if (response.statusCode == 200) {
        print('✅ [API Call] User info retrieved successfully');
        return json.decode(response.body) as Map<String, dynamic>;
      } else if (response.statusCode == 401) {
        print('⚠️ [API Call] Token expired or invalid, attempting to refresh...');
        // Try to refresh token
        final refreshed = await refreshToken();
        if (refreshed) {
          // Retry the request with new token
          final newToken = await storage.read(key: 'access_token');
          if (newToken != null) {
            print('🔄 [API Call] Retrying request with refreshed token');
            final retryResponse = await http.get(
              Uri.parse('$apiBase/me'),
              headers: {'Authorization': 'Bearer $newToken'},
            );
            if (retryResponse.statusCode == 200) {
              print('✅ [API Call] User info retrieved successfully after token refresh');
              return json.decode(retryResponse.body) as Map<String, dynamic>;
            }
          }
        }
        print('❌ [API Call] Failed to refresh token, need to re-authenticate');
      } else {
        print('❌ [API Call] Failed to get user info: ${response.statusCode}');
      }
    } catch (e) {
      print('❌ [API Call] Error: $e');
    }
    return null;
  }

  // Search for user
  Future<Map<String, dynamic>?> searchUser(String login) async {
    print('🔍 [API Call] Searching for user: $login');
    final token = await getValidToken();
    if (token == null) {
      print('❌ [API Call] No valid token available');
      return {'error': 'Not authenticated'};
    }

    print('📡 [API Call] Making request with token: ${token.substring(0, 20)}...');
    try {
      final response = await http.get(
        Uri.parse('$apiBase/users/$login'),
        headers: {'Authorization': 'Bearer $token'},
      );

      if (response.statusCode == 200) {
        print('✅ [API Call] User found successfully');
        return json.decode(response.body) as Map<String, dynamic>;
      } else if (response.statusCode == 404) {
        print('⚠️ [API Call] User not found');
        return {'error': 'User not found'};
      } else if (response.statusCode == 401) {
        print('⚠️ [API Call] Token expired or invalid, attempting to refresh...');
        // Try to refresh token
        final refreshed = await refreshToken();
        if (refreshed) {
          // Retry the request with new token
          final newToken = await storage.read(key: 'access_token');
          if (newToken != null) {
            print('🔄 [API Call] Retrying request with refreshed token');
            final retryResponse = await http.get(
              Uri.parse('$apiBase/users/$login'),
              headers: {'Authorization': 'Bearer $newToken'},
            );
            if (retryResponse.statusCode == 200) {
              print('✅ [API Call] User found successfully after token refresh');
              return json.decode(retryResponse.body) as Map<String, dynamic>;
            }
          }
        }
        return {'error': 'Token expired. Please re-authenticate.'};
      }
    } catch (e) {
      print('❌ [API Call] Network error: $e');
      return {'error': 'Network error'};
    }
    return null;
  }
}

