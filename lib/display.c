#include <stdio.h>
#include "display.h"
#include "string.h"

void printBlueString(char * input){
    int i;
    for(i = 0; i<string_length(input);++i){
        printf("%s%c", BLUE, input[i]);
    }
    printf("%s", NORMAL);
}
void printGrayString(char * input){
    int i;
    for(i = 0; i<string_length(input);++i){
        printf("%s%c", GRAY, input[i]);
    }
    printf("%s", NORMAL);
}

void printLogo(){
    printGrayString("................................  "); printBlueString(" .:^~!!~^:. "); printGrayString("  ............\n");
    printGrayString(".............................. "); printBlueString(" .!YB#&@@@@@&B57: ");  printGrayString(" ..........\n");
    printGrayString("............................. ");printBlueString(".J#@@@@@@@@@@@@@@&Y:"); printGrayString(" .........\n");
    printGrayString("............................ ");printBlueString("^B@@@@@@@@@@@&P55B@@&!"); printGrayString("     ....\n");
    printGrayString("........................... ");printBlueString(":#@@@@@@@@@@@G::^Y^?@@@?~^"); printGrayString("......\n");
    printGrayString(".    ....................   ");printBlueString("5@@@@@@@@@@@@5 7GB~~@@@@@@&B?."); printGrayString(" .\n");
    printBlueString(" :~:.                    ");printBlueString(":7G@@@@@@@@@@@@@@G?7?5&@@@@@@G!."); printGrayString(" ..\n");
    printBlueString(" .Y&BG5J?7!~^^^::^^^~!?YG&@@@@@@@@@@@@@@@@@@@@@@@@@@G! "); printGrayString("  ...\n");
    printGrayString(".  ");printBlueString("J@@@@@@@@@@&&&&@@@@@@@@BPY?77?5B@@@@@@@@@@@@@@@@#. "); printGrayString("......\n");
    printGrayString("..  ");printBlueString("7&@@@@@@@@@@@@@@@&GY!^.       .~P@@@@@@@@@@@@@@P "); printGrayString(".......\n");
    printGrayString(".... ");printBlueString("^G@@@@@@@@@@@&P7:  "); printGrayString("   .......  ");printBlueString(" Y@@@@@@@@@@@@@7"); printGrayString(" .......\n");
    printGrayString("..... ");printBlueString(".?#@@@@@@@@B: "); printGrayString("  .............. ");printBlueString(":&@@@@@@@@@@@P"); printGrayString(" ........\n");
    printGrayString("...... ");printBlueString(" :J&@@@@@@@G?^  "); printGrayString("  ........... ");printBlueString("!@@@@@@@@@@@P."); printGrayString(" ........\n");
    printGrayString("........ ");printBlueString(" :?B@@@@@@@&GJ~.           !#@@@@@@@@@@J."); printGrayString(" .........\n");
    printGrayString(".......... ");printBlueString(" .~5#@@@@@@@@#PJ!^:..:~?G@@@@@@@@@@P^ "); printGrayString(" ..........\n");
    printGrayString("............  ");printBlueString(" .~?PB&@@@@@@@@&##&@@@@@@@@@@#Y^ "); printGrayString(" ............\n");
    printGrayString("...............   ");printBlueString(" .:~7JP#&@@@@@@@@@@@@#PJ~. "); printGrayString(" ..............\n");
    printGrayString("...................   ");printBlueString("   .^~7?JJY#5?7~!5!  "); printGrayString(" ................\n");
    printGrayString(".........................  ");printBlueString("  .:^57     .?Y^  "); printGrayString(" ..............\n");

    printBlueString("   ____     _   _    ____           ____               ____\n");     
    printBlueString("U | __\")uU |\"|u| |U |  _\"\\ u     U | __\")u    ___   U |  _\"\\ u \n");     
    printBlueString(" \\|  _ \\/ \\| |\\| | \\| |_) |/      \\|  _ \\/   |_\"_|   \\| |_) |/ \n");     
    printBlueString("  | |_) |  | |_| |  |  _ <         | |_) |    | |     |  _ <   \n");     
    printBlueString("  |____/  <<\\___/   |_| \\_\\        |____/   U/| |\\u   |_| \\_\\  \n");     
    printBlueString(" _|| \\\\_ (__) )(    //   \\\\_      _|| \\\\_.-,_|___|_,-.//   \\\\_  \n");     
    printBlueString("(__) (__)    (__)  (__)  (__)    (__) (__)\\_)-' '-(_/(__)  (__) \n");     
}