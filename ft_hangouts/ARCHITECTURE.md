# 代码架构说明

## 设计理念

本项目采用简洁的MVVM架构，代码量最少化，便于理解和维护。

## 核心组件

### 1. 数据层 (Models & Database)

#### Models.swift
定义三个核心数据模型：
- `User`: 用户（id, 手机号, 创建时间）
- `Contact`: 联系人（包含7个字段）
- `Message`: 消息（发送者、接收者、内容等）

#### DatabaseManager.swift
单例模式的数据库管理器：
- SQLite3原生API（无ORM）
- 三张表：users, contacts, messages
- 所有CRUD操作都封装在此
- 线程安全的数据库操作

**关键方法**：
```swift
// 用户
getOrCreateUser(phoneNumber:) -> User

// 联系人
createContact(_:) -> Contact
getContacts(forUserId:) -> [Contact]
updateContact(_:)
deleteContact(_:)

// 消息
sendMessage(from:to:content:) -> Message?
getMessages(between:and:) -> [Message]
getRecentConversations(forUserId:) -> [(user, lastMessage)]
```

### 2. 状态管理 (AppState)

#### AppState.swift
全局状态管理（ObservableObject）：
- `currentUser`: 当前登录用户
- `headerColor`: 标题栏颜色
- `showBackgroundToast`: 显示后台Toast
- `backgroundMessage`: Toast消息内容

**职责**：
- 用户登录/登出
- 颜色主题持久化
- 后台时间记录和显示
- 跨视图状态共享

### 3. 视图层 (Views)

采用声明式SwiftUI，视图自动响应状态变化。

#### 登录流程
```
LoginView
  ↓ (输入手机号)
MainTabView (三个标签)
```

#### 主界面结构
```
MainTabView
├── ContactListView (联系人列表)
│   ├── AddContactView (添加)
│   └── ContactDetailView (详情/编辑)
│       └── ChatView (发消息)
├── MessagesListView (消息列表)
│   ├── NewMessageView (新消息)
│   └── ChatView (对话)
└── SettingsView (设置)
    ├── ColorPickerView (颜色选择器)
    └── UserSwitchView (用户切换)
```

### 4. 多语言支持

#### Localization.swift
简单的String扩展：
```swift
extension String {
    var localized: String {
        return NSLocalizedString(self, comment: "")
    }
}
```

使用方式：
```swift
Text("contacts".localized)  // 自动根据系统语言显示
```

## 关键技术点

### 1. SQLite集成
```swift
// 直接使用C API
import SQLite3

var db: OpaquePointer?
sqlite3_open(path, &db)
sqlite3_prepare_v2(db, sql, -1, &statement, nil)
sqlite3_step(statement)
sqlite3_finalize(statement)
```

### 2. 后台时间检测
```swift
// 监听应用状态
NotificationCenter.default.publisher(for: UIApplication.willResignActiveNotification)
NotificationCenter.default.publisher(for: UIApplication.didBecomeActiveNotification)

// 保存和读取时间
UserDefaults.standard.set(Date(), forKey: "backgroundTime")
```

### 3. 照片选择
```swift
// PhotosUI框架
import PhotosUI

PhotosPicker(selection: $selectedPhoto, matching: .images) {
    Text("选择照片")
}

// 异步加载
Task {
    if let data = try? await selectedPhoto?.loadTransferable(type: Data.self) {
        photoData = data
    }
}
```

### 4. 颜色持久化
```swift
// 将Color编码为可存储的格式
struct CodableColor: Codable {
    var red, green, blue, opacity: Double
    
    init(color: Color) {
        let uiColor = UIColor(color)
        // 提取RGBA值
    }
}
```

### 5. 横竖屏支持
在Info.plist中配置：
```xml
<key>UISupportedInterfaceOrientations</key>
<array>
    <string>UIInterfaceOrientationPortrait</string>
    <string>UIInterfaceOrientationLandscapeLeft</string>
    <string>UIInterfaceOrientationLandscapeRight</string>
</array>
```

## 数据流

### 创建联系人流程
```
1. 用户在AddContactView填写信息
2. 点击保存 → saveContact()
3. DatabaseManager.createContact() → SQLite INSERT
4. onSave回调 → ContactListView.loadContacts()
5. 数据库读取 → 更新UI列表
```

### 发送消息流程
```
1. 用户在ChatView输入消息
2. 点击发送 → sendMessage()
3. 检查接收者是否存在
4. DatabaseManager.sendMessage() → SQLite INSERT
5. 消息追加到本地messages数组
6. SwiftUI自动刷新UI
```

### 用户切换流程
```
1. SettingsView → UserSwitchView
2. 显示所有用户列表
3. 选择用户 → appState.setCurrentUser()
4. 保存到UserDefaults
5. 整个应用重新加载（因为currentUser是@Published）
```

## 文件依赖关系

```
ft_hangoutsApp.swift (入口)
  ├── AppState (全局状态)
  └── ContentView
        ├── LoginView (未登录)
        └── MainTabView (已登录)
              ├── ContactListView
              ├── MessagesListView
              └── SettingsView

Models.swift (数据模型)
  └── DatabaseManager.swift (数据库操作)

Localization.swift (独立工具)
```

## 性能优化

1. **懒加载**：使用`LazyVStack`和`List`，只渲染可见项
2. **数据库索引**：虽然简单，但查询使用了WHERE和ORDER BY优化
3. **状态最小化**：只在必要时更新状态，避免过度渲染
4. **照片压缩**：可以在生产环境中添加图片压缩

## 可扩展性

### 添加新功能
1. **群组聊天**：在数据库添加groups表，修改Message模型
2. **语音消息**：添加audioData字段，使用AVFoundation
3. **云同步**：集成CloudKit或自建后端API

### 代码约定
- 所有数据库操作在DatabaseManager中
- 所有状态在AppState或View的@State中
- 视图只负责展示和用户交互
- 业务逻辑在对应的方法中

## 调试技巧

### 查看数据库
```swift
// 在DatabaseManager的init中打印路径
let fileURL = try! FileManager.default
    .url(for: .documentDirectory, in: .userDomainMask, appropriateFor: nil, create: false)
    .appendingPathComponent("ft_hangouts.sqlite")
print("Database path: \(fileURL.path)")
```

然后使用DB Browser for SQLite查看。

### 查看日志
在关键位置添加：
```swift
print("✅ Contact created: \(contact.name)")
print("❌ Failed to send message")
```

### 重置应用数据
删除应用重装，或在代码中：
```swift
UserDefaults.standard.removePersistentDomain(forName: Bundle.main.bundleIdentifier!)
// 删除数据库文件
```

## 常见问题解决

### Q: 编译错误 "Module not found"
A: 确保import语句正确，所有文件都添加到target

### Q: 界面不更新
A: 检查@Published, @State, @ObservedObject是否正确使用

### Q: 数据库查询为空
A: 检查SQL语法，确认表已创建，数据已插入

### Q: 照片不显示
A: 检查Info.plist权限，确认photoData不为nil

## 项目统计

- **Swift文件数**: 16个
- **总代码行数**: ~1500行
- **无第三方依赖**: ✅
- **最低iOS版本**: 17.0
- **支持设备**: iPhone & iPad

## 下一步改进建议

1. **单元测试**: 添加XCTest测试数据库操作
2. **错误处理**: 更完善的错误提示和恢复机制
3. **动画效果**: 添加视图转场动画
4. **无障碍**: 支持VoiceOver和Dynamic Type
5. **性能监控**: 使用Instruments分析性能瓶颈
