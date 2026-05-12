@echo off
setlocal
chcp 65001 >nul

:: 使用当前关联的 python 确保安装
echo [Checking Dependencies]
python -m pip install pandas openpyxl --user -q

if %ERRORLEVEL% NEQ 0 (
    echo [Error] 无法安装依赖，请检查网络或 Python 安装情况。
    pause
    exit /b
)

echo [Running Script]
python ../Scripts/export_tables.py

echo [Done]
pause