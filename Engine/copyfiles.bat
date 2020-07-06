@echo off
echo Duplicador de Archivos para el .exe by Franco Vega

set targetdir=%~1
set solutiondir=%~2
set config=%3

echo Copiando librerias dinamicas

echo 1 = Debug
echo 2 = Release

IF %config% == "1" (

XCOPY "%solutiondir%lib\glfw\glfw3.dll" "%targetdir%" /E /Y /S
XCOPY "%solutiondir%lib\assimp\lib\assimp-vc141-mt.dll" "%targetdir%" /E /Y /S
XCOPY "%solutiondir%lib\freetype\lib\freetype.dll" "%targetdir%" /E /Y /S

) ELSE IF %config% == "2" (

XCOPY "%solutiondir%lib\glfw\glfw3.dll" "%targetdir%" /E /Y /S
XCOPY "%solutiondir%lib\assimp\lib\assimp-vc141-mt.dll" "%targetdir%" /E /Y /S
XCOPY "%solutiondir%lib\freetype\lib\freetype.dll" "%targetdir%" /E /Y /S

)

echo Copia de Archivos terminado!