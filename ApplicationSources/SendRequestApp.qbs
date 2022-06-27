import qbs.FileInfo

QtApplication {
    Depends { name: "Qt.widgets" }
    Depends { name: "Qt.network" }

    cpp.defines: [
        // You can make your code fail to compile if it uses deprecated APIs.
        // In order to do so, uncomment the following line.
        //"QT_DISABLE_DEPRECATED_BEFORE=0x060000" // disables all the APIs deprecated before Qt 6.0.0
    ]

    files: [
        "main.cpp",
    ]
    Group {
        name: "MainWindow"
        files: [
            "mainwindow.cpp",
            "mainwindow.h",
            "mainwindow.ui",
        ]
    }
    Group {
        name: "SettingsWindow"
        files: [
            "settingwindow.cpp",
            "settingwindow.h",
            "settingwindow.ui",
        ]
    }

    install: true
    installDir: qbs.targetOS.contains("qnx") ? FileInfo.joinPaths("/tmp", name, "bin") : base
}
