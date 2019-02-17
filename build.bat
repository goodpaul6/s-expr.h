@echo off
set CURR_DIR=%cd%

if not defined DevEnvDir (
    call "%VS_CMD_LINE_BUILD_PATH%" x64
)

cd /d %CURR_DIR%

SET opts= -Zi /GL /MP4 /W3 /EHsc /Fetest.exe /D_CRT_SECURE_NO_WARNINGS /FC /std:c++latest
SET sources=..\test_sexpr.c

pushd bin
	cl %opts% %sources%
popd
