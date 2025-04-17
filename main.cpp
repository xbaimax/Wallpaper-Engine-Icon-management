#include <windows.h>
#include <iostream>
#include <string>
#include <cstdio>


// 修改注册表函数
bool modifyRegistry(bool hide) {
    HKEY hKey;
    const wchar_t* regPath = L"Software\\WallpaperEngine";
    const wchar_t* valueName = L"hideTrayIcon";

    // 打开或创建注册表项
    LONG result = RegOpenKeyExW(HKEY_CURRENT_USER, regPath, 0, KEY_ALL_ACCESS, &hKey);
    if (result != ERROR_SUCCESS) {
        result = RegCreateKeyExW(HKEY_CURRENT_USER, regPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
        if (result != ERROR_SUCCESS) {
            std::wcerr << L"无法打开或创建注册表项。" << std::endl;
            return false;
        }
    }

    // 设置注册表值
    DWORD value = hide ? 1 : 0;
    result = RegSetValueExW(hKey, valueName, 0, REG_DWORD, (const BYTE*)&value, sizeof(DWORD));
    if (result != ERROR_SUCCESS) {
        std::wcerr << L"无法设置注册表值。" << std::endl;
        RegCloseKey(hKey);
        return false;
    }

    RegCloseKey(hKey);
    return true;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    // 输出提示信息
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "Wallpaper Engine托盘图标管理器1.1" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "by：小白初梦" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "此软件完全免费，请勿商用" << std::endl;
    std::cout << "所有付费购买，均是倒卖骗钱" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "托盘图标操作:" << std::endl;
    std::cout << "1. 隐藏托盘图标" << std::endl;
    std::cout << "2. 恢复托盘图标" << std::endl;
    std::cout << "-------------------------------------" << std::endl;    
    std::cout << "请输入操作编号 (1或2): ";

    int choice;
    std::cin >> choice;

    bool hide;
    if (choice == 1) {
        hide = true;
        std::cout << "正在隐藏托盘图标..." << std::endl;
    } else if (choice == 2) {
        hide = false;
        std::cout << "正在恢复托盘图标..." << std::endl;
    } else {
        std::cout << "无效输入，请重新运行程序并输入1或2。" << std::endl;
        while (getchar() != '\n');  // 丢弃所有字符直到换行符
        std::cout << "操作完成，按任意键关闭..." << std::endl;
        getchar();    // 等待用户按回车
        return 1;
    }

    // 修改注册表
    if (modifyRegistry(hide)) {
        std::cout << (hide ? "隐藏托盘图标成功！" : "恢复托盘图标成功！") << std::endl;
        std::cout << "请重新启动Wallpaper Engine使更改生效。" << std::endl;
    } else {
        std::cout << "操作失败。请检查权限或注册表路径是否正确。" << std::endl;
    }
    while (getchar() != '\n');  // 丢弃所有字符直到换行符
    std::cout << "操作完成，按任意键继续..." << std::endl;
    getchar();    // 等待用户按回车
    return 0;
}