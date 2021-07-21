REM Server Build
call %LLC_UNREAL_SOURCE%\Engine\Build\BatchFiles\RunUAT.bat BuildCookRun -project="%~dp0LowLightCombat.uproject" -build -cook -cookall -compressed -stage -noclient -server -serverplatform=Linux -serverconfig=Development -pak -archive -archivedirectory="%~dp0Build"
REM Full build
call %LLC_UNREAL_SOURCE%\Engine\Build\BatchFiles\RunUAT.bat BuildCookRun -project="%~dp0LowLightCombat.uproject" -build -cook -cookall -compressed -stage -platform=Linux -clientconfig=Development -pak -archive -archivedirectory="%~dp0Build"