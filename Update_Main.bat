@echo off
echo Do you want to procceed with an update to your LOCAL repository? (Y/N)
SET /P CHOICE=
if /I "%CHOICE%" EQU "Y" goto YES

if /I "%CHOICE%" EQU "N" goto NO

:YES
echo Updating current repository...

git pull https://git.sg.digipen.edu/projects/team_little_match_f24 main

echo Update completed.

pause

exit

:NO
echo Update cancelled.
pause
exit