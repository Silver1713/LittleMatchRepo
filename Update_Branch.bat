@echo off


:START
echo Remote Branch List:

git branch -r

:INPUT
SET /P BRANCH=Enter the branch name you want to update:

git rev-parse --verify %branch% >nul 2>&1
if %errorlevel%==0 (
    echo Branch '%branch%' exists locally, checking it out...
    git checkout %branch%
    goto UPDATE
)

git ls-remote --heads origin %BRANCH% >nul 2>&1

if %errorlevel% NEQ 0 (
    echo Invalid branch name. Please try again.
    goto INPUT
)

:UPDATE

echo Updating current repository on branch %BRANCH%...

git checkout -b %BRANCH% origin/%BRANCH%

git pull https://git.sg.digipen.edu/projects/team_little_match_f24 %BRANCH%

echo Update completed.

pause

exit