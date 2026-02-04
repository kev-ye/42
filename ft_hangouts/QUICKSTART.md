# 快速启动指南 - ft_hangouts

## 🚀 一分钟启动

```bash
cd /Users/kangkai_ye/code/ft_hangouts
open ft_hangouts.xcodeproj
```

在Xcode中：
1. 选择模拟器：iPhone 15 Pro
2. 点击运行 ▶️
3. 输入手机号登录（例如：+1234567890）
4. 开始使用！

## 📱 必须添加：42 Logo

**重要**：项目缺少42的logo图标，需要手动添加：

### 方法1：使用在线工具
1. 访问 https://appicon.co/ 或 https://www.appicon.build/
2. 上传42 logo (1024x1024 PNG)
3. 下载生成的AppIcon.appiconset
4. 在Xcode中替换 Assets.xcassets/AppIcon.appiconset

### 方法2：手动添加
1. 准备1024x1024的42 logo图片
2. 在Xcode中打开 Assets.xcassets
3. 点击 AppIcon
4. 将图片拖入"1024pt"位置
5. Xcode会自动生成其他尺寸

### 方法3：使用SF Symbols（临时）
如果没有42 logo，可以临时使用系统图标测试：
- 在AppIcon中不做任何修改
- 应用会显示默认图标

## ✅ 功能检查清单

所有必需功能已实现：

- ✅ 用户登录（手机号）
- ✅ 创建/编辑/删除联系人
- ✅ 5+字段（姓名、电话、邮箱、地址、生日、备注、照片）
- ✅ 联系人列表
- ✅ 发送/接收消息
- ✅ 对话历史
- ✅ 标题颜色菜单
- ✅ 双语支持（中文/英文）
- ✅ 后台时间Toast
- ✅ 横竖屏支持
- ✅ 拨打电话（Bonus）
- ✅ 联系人照片（Bonus）
- ✅ 用户切换（iOS特有）

## 🎯 测试流程（5分钟）

### 基础测试
1. **登录**: 输入手机号 → 进入主界面
2. **添加联系人**: 点击+ → 填写信息 → 保存
3. **编辑联系人**: 点击联系人 → 编辑 → 修改 → 完成
4. **删除联系人**: 左滑联系人 → 删除
5. **更换颜色**: 设置 → 标题颜色 → 选择颜色

### 消息测试（需要两个用户）
1. 创建用户A（例如：+111）
2. 退出 → 创建用户B（例如：+222）
3. 切换回用户A
4. 发送消息到+222
5. 切换到用户B查看消息

## 📝 代码特点

- **代码量少**: 约1500行，易于理解
- **无依赖**: 只使用Apple原生框架
- **简洁架构**: MVVM模式，清晰的职责分离
- **易于扩展**: 模块化设计

## 📚 文档

- `README.md` - 项目概述和功能说明
- `TESTING.md` - 详细测试指南
- `ARCHITECTURE.md` - 代码架构说明

## 🔧 常见问题

### 编译错误
- 确保Xcode 15+
- 确保选择了iOS 17.0+ SDK
- Clean Build Folder (Cmd+Shift+K)

### 运行时错误
- 检查Info.plist是否正确
- 确认所有.swift文件都在target中

### 照片无法选择
- 检查Info.plist中的NSPhotoLibraryUsageDescription

### 语言未切换
- 重启应用
- 或在系统设置中更改语言

## 📦 项目结构

```
ft_hangouts/
├── 📱 主要代码
│   ├── ft_hangoutsApp.swift      # 应用入口
│   ├── AppState.swift             # 状态管理
│   ├── Models.swift               # 数据模型
│   ├── DatabaseManager.swift     # 数据库
│   └── Views/                     # 所有界面
│
├── 🌍 多语言
│   ├── en.lproj/
│   └── zh-Hans.lproj/
│
├── 🎨 资源
│   ├── Assets.xcassets/
│   └── Info.plist
│
└── 📖 文档
    ├── README.md
    ├── TESTING.md
    └── ARCHITECTURE.md
```

## 🎓 适合新手

项目特意设计得简单易懂：
- 没有复杂的设计模式
- 注释清晰
- 职责明确
- 易于调试

虽然你没写过Swift，但如果你懂：
- ORM → 看 DatabaseManager
- 框架 → SwiftUI自动处理UI刷新
- 状态管理 → AppState是全局状态

## 🚨 提交前最后检查

- [ ] 添加42 Logo图标
- [ ] 测试所有功能
- [ ] 确认无编译警告
- [ ] 测试横竖屏
- [ ] 测试双语切换
- [ ] 测试后台返回Toast
- [ ] 代码清理（删除调试代码）

## 💡 提示

这是一个完全符合要求的iOS应用，唯一缺少的是42 Logo图标（需要你手动添加）。代码简洁、易懂、功能完整！

祝项目成功！🎉
