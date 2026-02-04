import Flutter
import UIKit
import WebKit

@main
@objc class AppDelegate: FlutterAppDelegate {
  override func application(
    _ application: UIApplication,
    didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?
  ) -> Bool {
    GeneratedPluginRegistrant.register(with: self)
    
    // 设置平台通道来清除 cookies 和缓存
    guard let controller = window?.rootViewController as? FlutterViewController else {
      return super.application(application, didFinishLaunchingWithOptions: launchOptions)
    }
    
    let cookieChannel = FlutterMethodChannel(
      name: "com.example.swiftcompanion/cookies",
      binaryMessenger: controller.binaryMessenger
    )
    
    cookieChannel.setMethodCallHandler { (call: FlutterMethodCall, result: @escaping FlutterResult) in
      if call.method == "clearCookies" {
        // 清除 WKWebView 的所有 cookies 和缓存
        let dataStore = WKWebsiteDataStore.default()
        let dataTypes = WKWebsiteDataStore.allWebsiteDataTypes()
        
        dataStore.fetchDataRecords(ofTypes: dataTypes) { records in
          dataStore.removeData(ofTypes: dataTypes, for: records) {
            // 清除完成后返回成功
            DispatchQueue.main.async {
              result(true)
            }
          }
        }
      } else {
        result(FlutterMethodNotImplemented)
      }
    }
    
    return super.application(application, didFinishLaunchingWithOptions: launchOptions)
  }
}
