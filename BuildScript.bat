REM Server Build
call %LLC_UNREAL_SOURCE%\Engine\Build\BatchFiles\RunUAT.bat BuildCookRun -project="%~dp0LowLightCombat.uproject" -build -cook -cookall -compressed -stage -noclient -server -serverplatform=Win64 -serverconfig=Shipping -pak -archive -archivedirectory="%~dp0Build"
REM Client Build
REM call %LLC_UNREAL_SOURCE%\Engine\Build\BatchFiles\RunUAT.bat BuildCookRun -project="%~dp0LowLightCombat.uproject" -build -cook -cookall -compressed -stage -noserver -client -platform=Win64 -clientconfig=Shipping -pak -archive -archivedirectory="%~dp0Build"
REM Full build
call %LLC_UNREAL_SOURCE%\Engine\Build\BatchFiles\RunUAT.bat BuildCookRun -project="%~dp0LowLightCombat.uproject" -build -cook -cookall -compressed -stage -platform=Win64 -clientconfig=Shipping -pak -archive -archivedirectory="%~dp0Build"
REM Linux Server Build
call %LLC_UNREAL_SOURCE%\Engine\Build\BatchFiles\RunUAT.bat BuildCookRun -project="%~dp0LowLightCombat.uproject" -build -cook -cookall -compressed -stage -noclient -server -serverplatform=Linux -serverconfig=Shipping -pak -archive -archivedirectory="%~dp0Build"
REM Client Build
REM call %LLC_UNREAL_SOURCE%\Engine\Build\BatchFiles\RunUAT.bat BuildCookRun -project="%~dp0LowLightCombat.uproject" -build -cook -cookall -compressed -stage -noserver -client -platform=Linux -clientconfig=Shipping -pak -archive -archivedirectory="%~dp0Build"
REM Linux Full build
call %LLC_UNREAL_SOURCE%\Engine\Build\BatchFiles\RunUAT.bat BuildCookRun -project="%~dp0LowLightCombat.uproject" -build -cook -cookall -compressed -stage -platform=Linux -clientconfig=Shipping -pak -archive -archivedirectory="%~dp0Build"