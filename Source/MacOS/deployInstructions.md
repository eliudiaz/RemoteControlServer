Deploy Instructions
===================

If you want to create a dmg file for easy deployment on Mac OS out of the RemoteControlServer.app, follow these steps:

- Download the project source
- Import the project into [Qt Creator](https://www.qt.io/download/)
- Build it
- Open the build directory and run (_Applications/Qt/5.5/clang_64/bin/macdeployqt_)
```
macdeployqt RemoteControlServer.app -dmg
```
- Make dmg pretty


Detailed instructions:
[Deploy Qt applications for Mas OS X](http://dragly.org/2012/01/13/deploy-qt-applications-for-mac-os-x/)