# SimulatorController
依賴
===========================
Qt (測試版本: Desktop Qt 5.11.2 MSVC2017 64bit<br>
Visual Studio 2017 (測試版本: Visual Studio Community 2017 15.8.5)<br>
Detours (https://github.com/Microsoft/Detours)<br>

編譯
===========================
順序 Hook -> SimulatorControllerLibrary -> SimulatorSupport

Hook
---------------------------
更改 dllmain.cpp 裡面的 detours 相關設定<br>

SimulatorControllerLibrary
---------------------------

SimulatorSupport
---------------------------
更改 mylabel.cpp 裡面的 SimulatorControllerLibrary 相關設定<br>

執行準備
===========================
1.使用 setdll -d:Hook.dll C:\Program Files\dnplayerext2\LdBoxHeadless.exe<br>
2.將 Hook.dll 以及依賴的檔案放到 C:\Program Files\dnplayerext2<br>
3.將 SimulatorControllerLibrary.dll 放到 SimulatorSupport.exe 旁邊<br>
4.執行雷電模擬器<br>
5.執行SimulatorSupport.exe<br>

[Demo](https://drive.google.com/file/d/1_znAu_drjWsEqBHu3eO-ip2B9i40yGgj/view?usp=sharing)
