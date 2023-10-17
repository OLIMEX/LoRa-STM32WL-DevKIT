If you have errors compiling the project, try the following:

In the Project Explorer right-click over the name of the project and go to "Properties" at the bottom;
- New window will pop up and under "C/C++ Build select Settings";
- Go under "MCU GCC Compiler" and select "Miscellaneous";
- Add new flag from the small green plus sign named "Add..";
- add "-fcommon" and save and "Apply and Close".

Then clean the project and then build it. There should be a few warnings that can be ignored but now the project will compile and work fine.

For more info read here for a lot of people and projects that had same problem:

https://community.st.com/t5/stm32cubeide-mcus/multiple-definition-error-after-stm32cubeide-1-9-0-update/td-p/130147

Alternatively, just use older version of STM32CubeIDE. Previously I used 1.10.0 without issues.
