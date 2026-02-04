# ft_hangouts - iOS Contact & SMS Management App

一个简洁的iOS联系人和短信管理应用，使用SwiftUI和SQLite开发。

## 功能特性

### 核心功能
✅ **用户管理**
- 使用手机号码登录
- 自动创建用户
- 支持多用户切换

✅ **联系人管理**
- 创建联系人（包含5个以上详细信息：姓名、电话、邮箱、地址、生日、备注、照片）
- 编辑联系人
- 删除联系人
- 联系人列表展示
- 支持联系人照片

✅ **短信功能**
- 发送短信到已注册用户
- 查看对话历史
- 清晰的发送者/接收者界面
- 消息列表

✅ **应用设置**
- 双语支持（中文/英文）
- 自定义标题栏颜色
- 用户切换
- 后台时间显示（Toast提示）

✅ **其他特性**
- 横屏和竖屏支持
- 拨打电话功能
- SQLite数据持久化
- 无第三方库依赖

## 项目结构

```
ft_hangouts/
├── ft_hangoutsApp.swift          # 应用入口
├── ContentView.swift              # 主视图
├── AppState.swift                 # 应用状态管理
├── Models.swift                   # 数据模型
├── DatabaseManager.swift          # SQLite数据库管理
├── Localization.swift            # 多语言支持
├── Views/
│   ├── LoginView.swift           # 登录界面
│   ├── MainTabView.swift         # 主标签栏
│   ├── ContactListView.swift    # 联系人列表
│   ├── AddContactView.swift     # 添加联系人
│   ├── ContactDetailView.swift  # 联系人详情
│   ├── MessagesListView.swift   # 消息列表
│   ├── NewMessageView.swift     # 新消息
│   ├── ChatView.swift           # 聊天界面
│   └── SettingsView.swift       # 设置界面
├── en.lproj/
│   └── Localizable.strings      # 英文翻译
├── zh-Hans.lproj/
│   └── Localizable.strings      # 中文翻译
├── Assets.xcassets/              # 资源文件
├── Info.plist                    # 应用配置
└── ft_hangouts.xcodeproj/       # Xcode项目文件
```

## 技术栈

- **语言**: Swift 5.0
- **框架**: SwiftUI
- **数据库**: SQLite3
- **最低支持**: iOS 17.0
- **开发工具**: Xcode 15+

## 安装和运行

1. **打开项目**
   ```bash
   cd ft_hangouts
   open ft_hangouts.xcodeproj
   ```

2. **运行应用**
   - 在Xcode中选择目标设备（iPhone模拟器或真机）
   - 点击运行按钮或按 `Cmd + R`

3. **首次使用**
   - 输入手机号码创建/登录用户
   - 开始添加联系人和发送消息

## 使用说明

### 用户系统
由于iOS限制无法访问系统短信，本应用实现了一个独立的用户系统：
- 每个用户通过手机号码标识
- 只能向已在应用中注册的用户发送消息
- 可以在设置中切换用户

### 添加联系人
1. 进入"联系人"标签
2. 点击右上角"+"按钮
3. 填写联系人信息（姓名和电话为必填项）
4. 可选择添加照片
5. 点击"保存"

### 发送消息
1. 方式一：从联系人详情页点击"发送消息"
2. 方式二：从"消息"标签点击新消息按钮
3. 输入接收者手机号码（必须是已注册用户）
4. 输入消息内容
5. 点击发送

### 更改主题颜色
1. 进入"设置"标签
2. 点击"标题颜色"
3. 选择喜欢的颜色
4. 点击"完成"

### 切换语言
1. 进入"设置"标签
2. 在"语言"部分选择语言
3. 应用会立即更新（部分界面可能需要重启应用）

## 数据库结构

### Users 表
- `id`: 主键
- `phone_number`: 手机号码（唯一）
- `created_at`: 创建时间

### Contacts 表
- `id`: 主键
- `user_id`: 所属用户ID
- `name`: 姓名
- `phone_number`: 电话号码
- `email`: 邮箱
- `address`: 地址
- `birthday`: 生日
- `notes`: 备注
- `photo_data`: 照片数据
- `created_at`: 创建时间

### Messages 表
- `id`: 主键
- `sender_id`: 发送者ID
- `receiver_id`: 接收者ID
- `content`: 消息内容
- `timestamp`: 时间戳
- `is_read`: 是否已读

## 关键特性说明

### 后台时间显示
应用进入后台时会保存当前时间，返回前台时会显示Toast提示。这个功能通过监听 `UIApplication` 的通知实现：
- `willResignActiveNotification`: 保存时间
- `didBecomeActiveNotification`: 显示Toast

### 横竖屏支持
应用支持所有方向（竖屏、横屏左、横屏右），在 `Info.plist` 中配置。

### 无第三方库
整个应用不使用任何第三方库，仅使用Apple原生框架：
- SwiftUI（界面）
- SQLite3（数据库）
- PhotosUI（照片选择）

## 待添加42 Logo

你需要手动添加42的logo图标：
1. 准备1024x1024的42 logo图片
2. 在Xcode中打开 `Assets.xcassets`
3. 点击 `AppIcon`
4. 将图片拖入对应位置

或者使用在线工具生成：
- https://appicon.co/
- https://www.appicon.build/

## 注意事项

1. **真机测试**: 如需在真机上测试，需要配置开发者证书
2. **照片权限**: 首次使用照片功能会请求相册权限
3. **用户数据**: 数据存储在应用沙盒中，卸载应用会清除所有数据
4. **消息系统**: 这是一个模拟的短信系统，不会发送真实SMS

## 开发者

学生项目 - 42 School

## 许可证

Educational Use Only
