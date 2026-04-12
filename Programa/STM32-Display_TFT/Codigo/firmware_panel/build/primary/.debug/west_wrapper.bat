@echo off
REM Wrapper script to run west commands out of Zephyr workbench environment
REM This script is auto-generated -- do not edit

REM Set environment variables
set ZEPHYR_BASE=d:\aguat\Documents\GitHub\STM32\zephyrProject\deps\zephyr
set ZEPHYR_PROJECT_DIRECTORY=d:\aguat\Documents\GitHub\STM32\zephyrProject


REM Source environment and execute West
call C:\Users\aguat\.zinstaller\env.bat && west %*
