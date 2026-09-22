# HelloQt 计算器

## 📖 项目简介

这是我在学习 Qt 过程中完成的第一个图形界面项目——一个基于 Qt Widgets 的简易计算器。项目完全使用 C++ 代码手写界面，没有使用 Qt Designer 拖控件，并实现了一个支持运算符优先级的四则运算表达式求值功能。

## ✨ 功能特性

- **纯代码构建界面**：所有按钮和显示框均通过 C++ 代码创建，使用 `QGridLayout` 进行网格布局。
- **四则运算**：支持加（+）、减（-）、乘（*）、除（/）以及等号（=）计算。
- **运算符优先级**：乘除优先于加减，通过 `QStack<double>` 实现表达式求值。
- **除零保护**：当除数为 0 时，程序不会崩溃，会忽略该次除法操作。
- **清除功能**：按 `C` 键可将当前输入重置为 `0`。
- **结果展示**：上方输入框显示当前表达式，下方只读框显示计算结果。
- **界面自适应**：按钮大小随窗口缩放自动调整（`QSizePolicy::Expanding`），按钮字体大小设为 20 号。

## 🛠️ 技术栈

- **语言**：C++
- **框架**：Qt 6 (Qt Widgets)
- **构建工具**：qmake
- **核心类**：`QApplication`、`QMainWindow`、`QWidget`、`QGridLayout`、`QPushButton`、`QLineEdit`、`QStack`、`QFont`

## 🚀 如何运行

1. 确保已安装 Qt 6（包含 MinGW 编译器）。
2. 克隆本仓库到本地：
   ```bash
   git clone https://github.com/Shimizu-Haruka/Qt-Calculator.git
   ```
3. 使用 Qt Creator 打开 `HelloQt.pro` 文件。
4. 配置构建套件（Desktop Qt 6.x MinGW 64-bit）。
5. 点击运行（或按 `Ctrl+R`）。

## 📂 项目结构

```
HelloQt/
├── main.cpp            # 程序入口，创建 QApplication 和主窗口
├── mainwindow.h        # 主窗口类声明，包含计算相关函数
├── mainwindow.cpp      # 主窗口实现，界面搭建、信号槽连接及计算逻辑
├── HelloQt.pro         # qmake 工程文件
└── README.md           # 本文件
```

## 🧠 核心实现简述

- **界面搭建**：在 `MainWindow` 构造函数中创建所有按钮和输入框，通过 `QGridLayout` 指定每个控件的位置。
- **信号槽连接**：使用 lambda 表达式捕获按钮和输入框指针，统一处理所有按钮的点击事件。
- **表达式计算**：`calculate()` 函数遍历输入字符串，利用 `QStack<double>` 和 `operatorCompare()` 实现运算符优先级计算。
- **状态管理**：通过判断输入框当前文本是否为 `"0"` 来决定是追加数字还是替换。


## 📅 更新日志

### 2026-09-20
- 完成计算器基本功能：四则运算、运算符优先级、除零保护、清除（C）。
- 使用 `QGridLayout` 手写界面，所有按钮统一连接信号槽。
- 上传至 GitHub。

### 2026-09-21
- 添加历史记录功能：使用 `QListWidget` 显示每次计算的表达式与结果。
- 添加“清除记录”按钮，一键清空历史。

### 2026-09-22
- 添加侧栏历史面板，支持展开/收起动画（`QPropertyAnimation` + `QEasingCurve::OutCubic`）。
- 添加“show/hide”切换按钮，控制历史面板的显示与隐藏。
- 修复 `calculate` 中多个独立 `if` 导致的分支判断问题，改为 `else if`。
- 优化界面布局：主区域与历史面板使用 `QHBoxLayout` 分栏。
