/*
 *  Odysseus - a wrapper utility
 *
 *  Copyright (c) 2015 dayt0n
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Birth: 7/6/2015
 *
 */

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

using namespace std;

void mainMenu();
void odysseusLogo();
void menuSelect();
void makeIPSW();
void grabDemBlobs();
void validateBlobs();
void deviceRestore();
void progressUI();
void winChoiceAction();

int main() {
    system("clear");
    mainMenu();
    return 0;
}

void mainMenu()
{
    odysseusLogo();
    printf("\n");
    winChoiceAction();
}

void odysseusLogo ()
{
    double versionNumber;
    versionNumber = 0.01;
    printf("============================================\n");
    cout << "   ____      _         version: " << versionNumber << "        " << endl;
    printf("  / __ \\    | |                             \n");
    printf(" | |  | | __| |_   _ ___ ___  ___ _   _ ___ \n");
    printf(" | |  | |/ _` | | | / __/ __|/ _ \\ | | / __|\n");
    printf(" | |__| | (_| | |_| \\__ \\__ \\  __/ |_| \\__ \\ \n");
    printf("  \\____/ \\__,_|\\__, |___/___/\\___|\\__,_|___/\n");
    printf("                __/ | toolchain by xerub   \n");
    printf("               |___/       utility by dayt0n\n");
    printf("                 Windows version by matteyeux\n");
    printf("============================================\n");
}

void menuSelect()
{
    printf("Do you want to: \n\n");
    printf("1) Make IPSW and prepare kloader\n");
    printf("2) Grab on-device blobs\n");
    printf("3) Validate existing blobs\n");
    printf("4) Restore device to desired firmware\n");
    printf("5) Quit\n\n");
    printf("Selection: ");
}

void winChoiceAction()
{
    int userSelection;
    menuSelect();
    cin >> userSelection;
    switch (userSelection) {
        case 1:
            system("clear");
            odysseusLogo();
            printf("\n");
            makeIPSW();
            break;
        case 2:
            system("clear");
            odysseusLogo();
            printf("\n");
            grabDemBlobs();
            break;
        case 3:
            system("clear");
            odysseusLogo();
            printf("\n");
            validateBlobs();
            break;
        case 4:
            system("clear");
            odysseusLogo();
            printf("\n");
            deviceRestore();
            break;
        case 5:
            break;
        default:
            printf("Invalid input. Try again.\n");
            break;
    }
}

void makeIPSW()
{
    char moarRAM;
    string downloadedIPSW;
    char bareJB;
    string deviceIP;
    char isOTA;
    printf("Are you downgrading via 6.1.3 OTA blob? [y or n]: "); // Just for -bbupdate arg
    cin >> isOTA;
    system("clear");
    printf("Do you have 4GB or more of RAM? [y or n]: ");
    cin >> moarRAM;
    printf("Drag the downloaded iPSW of the iOS version you would like to go to here: ");
    cin.ignore(100,'\n');
    getline(cin, downloadedIPSW);
    printf("\nWould you like to include a barebones jailbreak + SSH with the iPSW (6.1.x only) [y or n]: ");
    cin >> bareJB;
    printf("\nEnter the desired device's local IP address: ");
    cin.ignore(100,'\n');
    getline(cin, deviceIP);
    system("clear");
    if (isOTA == 'n') {
        printf("Grabbing baseband.tar...\n");
        system(("sshtool -s baseband.tar -p 22 "+deviceIP).c_str());
        system("clear");
    printf("Creating iPSW...\n"); // Below: If-ception
    if (moarRAM != 'y')
    {
        if (bareJB != 'y')
        {
            if (ifstream("baseband.tar")) {
                system(("ipsw "+downloadedIPSW+" custom.ipsw baseband.tar").c_str());
            }
            else
                system(("ipsw "+downloadedIPSW+" custom.ipsw").c_str());
        }
        else
        {
            if (ifstream("baseband.tar")) {
                system(("ipsw "+downloadedIPSW+" custom.ipsw baseband.tar ../jb/p0sixspwn.tar ../jb/ssh_small.tar").c_str());
            }
            else
                system(("ipsw "+downloadedIPSW+" custom.ipsw ../jb/p0sixspwn.tar ../jb/ssh_small.tar").c_str());
        }
    }
    else
    {
        if (bareJB != 'y')
        {
            if (ifstream("baseband.tar")) {
                system(("ipsw "+downloadedIPSW+" custom.ipsw -memory baseband.tar").c_str());
            }
            else
                system(("ipsw "+downloadedIPSW+" custom.ipsw -memory").c_str());
        }
        else
        {
            if (ifstream("baseband.tar")) {
                system(("ipsw "+downloadedIPSW+" custom.ipsw -memory baseband.tar ../jb/p0sixspwn.tar ../jb/ssh_small.tar").c_str());
            }
            else
                system(("ipsw "+downloadedIPSW+" custom.ipsw -memory ../jb/p0sixspwn.tar ../jb/ssh_small.tar").c_str());
        }
    }
    }
    else {
        system("clear");
        printf("Creating iPSW...\n");
        if (moarRAM != 'y')
        {
            if (bareJB != 'y')
            {
                system(("ipsw "+downloadedIPSW+" custom.ipsw -bbupdate").c_str());
            }
            else
            {
                system(("ipsw "+downloadedIPSW+" custom.ipsw -bbupdate ../jb/p0sixspwn.tar ../jb/ssh_small.tar").c_str());
            }
        }
        else
        {
            if (bareJB != 'y')
            {
                system(("ipsw "+downloadedIPSW+" custom.ipsw -memory -bbupdate").c_str());
            }
            else
            {
                system(("ipsw "+downloadedIPSW+" custom.ipsw -memory -bbupdate ../jb/p0sixspwn.tar ../jb/ssh_small.tar").c_str());
            }
        }

    }
    if (ifstream("custom.ipsw")) {
        system("clear");
        printf("Extracting PWNed iBSS image...\n");
        system("xpwntool `unzip -j custom.ipsw 'Firmware/dfu/iBSS*' | awk '/inflating/{print $2}'` pwnediBSS");
        system("clear");
        printf("Image extracted. \nYou now have a custom iPSW and PWNed iBSS to kickstart the restore.\n");
    }
    else
        printf("iPSW did not complete creation. Please try again.");
    }

void grabDemBlobs() // This part MAYBE works...
{
    string deviceIP;
    string downloadedBlobIPSW;
    if (ifstream("custom.ipsw"))
    {
        printf("Enter the desired device's local IP address: ");
        cin.ignore(100,'\n');
        getline(cin, deviceIP);
        printf("\nExtracting PWNed iBEC...\n");
        system("mv `unzip -j custom.ipsw 'Firmware/dfu/iBEC*' | awk '/inflating/{print $2}'` pwnediBEC");
        printf("Kloading PWNed iBSS...(might want to CTRL+C if it hangs at the end)\n");
        system(("sshtool -k ../kloader -b pwnediBSS -p 22 "+deviceIP).c_str());
        sleep(10);
        system("clear");
        printf("Unplug and replug the USB cable connected the iDevice. Then, press [Enter].\n");
        cin.ignore();
        system("clear");
        printf("Sending PWNed iBEC...\n");

        system("irecovery -f pwnediBEC"); // Should probably say this now: but in my experience, Linux requires root to access USB. This means that you will have to have an option for OS X and Linux everytime you use a tool like irecovery or idevicerestore that interacts with USB.
        sleep(5);
        printf("Sending payload...\n");
        system("irecovery -f ../payload");
        sleep(3);
        system("irecovery -c \"go blobs\"");
        sleep(3);
        printf("Grabbing blobs...\n");
        system("irecovery -g precious.dump");
        sleep(3);
        if (fstream("precious.dump")) {
            printf("Got blobs. Booting back to userland.\n");
            system("irecovery -c \"reboot\"");
            sleep(1);
        }
        else
        {
            system("irecovery -c \"reboot\"");
            printf("\nFailed to obtain blobs.\n");
            return;
        }

        system("clear");
        printf("Drag the downloaded iPSW of the iOS version that your device is currently on: ");
        cin.ignore(100,'\n');
        getline(cin, downloadedBlobIPSW);
        printf("\nUnpacking dumped blobs...\n");
        system(("ticket precious.dump precious.plist "+downloadedBlobIPSW+" -z").c_str());
        printf("Done grabbing blobs.\n");
    }
    else
    {
        printf("Custom iPSW not found. Please create one first.\n");
        return;
    }
}

void validateBlobs()
{
    char isBlock;
    string meBlob;
    char isXML;
    string downloadedBlobIPSW;
    char validateTU;
    printf("Drag the downloaded iPSW of the iOS version these blobs correspond to here: ");
    cin.ignore(100,'\n');
    getline(cin, downloadedBlobIPSW);
    printf("\nDrag the desired blob here: ");
    getline(cin, meBlob);
    printf("\nIs this a TinyUmbrella \"Block\" SHSH blob? [y or n]: ");
    cin >> isBlock;
    if (isBlock != 'n')
    {
        printf("\nUse SHSHaker to convert blobs (check the README)");
    }
    printf("Is the blob in XML format? [y or n]: ");
    cin >> isXML;
    if (isXML != 'y') /*Did not tested this part, idk if there is plutil in Cygwin or Mingw*/
    {
        system(("zcat "+meBlob+" > XML.shsh").c_str());
        system("plutil -convert xml1 XML.shsh");
        system(("validate XML.shsh "+downloadedBlobIPSW+" -z").c_str());
        printf("\nConverted Blob saved as XML.shsh in Odysseus working directory.\n");
    }
    else
    {
        system(("validate "+meBlob+" "+downloadedBlobIPSW+" -z").c_str());
    }
    printf("\nBlobs validated.\n");
}

void deviceRestore() // This *should* restore the device to the desired firmware, provided blobs are where they should be.
{
    char isReady;
    string deviceIP;
    if (ifstream("custom.ipsw"))
    {
        printf("Preparing to boot PWNed iBSS...\n");
        printf("Enter the desired device's local IP address: ");
        cin.ignore(100,'\n');
        getline(cin, deviceIP);
        system(("sshtool -k ../kloader -b pwnediBSS -p 22 "+deviceIP).c_str());
        sleep(10);
        system("clear");
        odysseusLogo();
        printf("Unplug and replug the USB cable connecting the device. Then, press [Enter].\n");
        cin.ignore();
        system("clear");
        odysseusLogo();
        printf("Are you sure you want to continue? This is the point of no return. [y or n]: ");
        cin >> isReady;
        if (isReady == 'y') {
        progressUI(); // Mainly for more time unless you do decide you don't want to restore.
        sleep(3);
        printf("Initiating Restore...\n"); // I don't check for blobs in this function because idevicerestore does that for me.
        sleep(2);
        system("idevicerestore -d -w custom.ipsw");

        printf("\nRestore Completed. This should have worked if you did everything correctly...\n");
        }
        else
            printf("Ok. Try again when you are ready. No rush :)\n");
    }
    else
        printf("Please create a custom iPSW first.\n\n");
}

void progressUI() // This is just for looks, btw.. But, could be used as a time before the restore starts to change your mind.
{
    system("clear");
    odysseusLogo();
    printf("\nOk... loading restore module...\n");
    printf("[>                  ]\n");
    sleep(1);
    system("clear");
    odysseusLogo();
    printf("\nOk... loading restore module...\n");
    printf("[=>                 ]\n");
    sleep(1);
    system("clear");
    odysseusLogo();
    printf("\nOk... loading restore module...\n");
    printf("[==>                ]\n");
    sleep(1);
    system("clear");
    odysseusLogo();
    printf("\nOk... loading restore module...\n");
    printf("[===>               ]\n");
    sleep(1);
    system("clear");
    odysseusLogo();
    printf("\nOk... loading restore module...\n");
    printf("[====>              ]\n");
    sleep(1);
    system("clear");
    odysseusLogo();
    printf("\nOk... loading restore module...\n");
    printf("[=====>             ]\n");
    sleep(1);
    system("clear");
    odysseusLogo();
    printf("\nOk... loading restore module...\n");
    printf("[======>            ]\n");
    sleep(1);
    system("clear");
    odysseusLogo();
    printf("\nOk... loading restore module...\n");
    printf("[=======>           ]\n");
    sleep(1);
    system("clear");
    odysseusLogo();
    printf("\nOk... loading restore module...\n");
    printf("[========>          ]\n");
    sleep(1);
    system("clear");
    odysseusLogo();
    printf("\nOk... loading restore module...\n");
    printf("[=========>         ]\n");
    sleep(1);
    system("clear");
    odysseusLogo();
    printf("\nOk... loading restore module...\n");
    printf("[==========>        ]\n");
    sleep(1);
    system("clear");
    odysseusLogo();
    printf("\nOk... loading restore module...\n");
    printf("[===========>       ]\n");
    sleep(1);
    system("clear");
    odysseusLogo();
    printf("\nOk... loading restore module...\n");
    printf("[============>      ]\n");
    sleep(1);
    system("clear");
    odysseusLogo();
    printf("\nOk... loading restore module...\n");
    printf("[=============>     ]\n");
    sleep(1);
    system("clear");
    odysseusLogo();
    printf("\nOk... loading restore module...\n");
    printf("[==============>    ]\n");
    sleep(1);
    system("clear");
    odysseusLogo();
    printf("\nOk... loading restore module...\n");
    printf("[===============>   ]\n");
    sleep(2);
    system("clear");
    odysseusLogo();
    printf("\nOk... loading restore module...\n");
    printf("[================>  ]\n");
    sleep(1);
    system("clear");
    odysseusLogo();
    printf("\nOk... loading restore module...\n");
    printf("[=================> ]\n");
    sleep(3);
    system("clear");
    odysseusLogo();
    printf("\nOk... loading restore module...\n");
    printf("[==================>]\n");
    sleep(1);
    system("clear");
    odysseusLogo();
    printf("\nOk... loading restore module...\n");
    printf("[===================]\n");
}

/*
* Credit for the original Odysseus toolchain:
*
* xerub
* iH8sn0w
* winocm
* planetbeing
* libimobiledev
* westbaer
* citrusui
* JonathanSeals
* daytonhasty
*
* “We are Achaians coming from Troy, beaten off our true course by winds from 
* every direction across the great gulf of the open sea, making for home,
* by the wrong way, on the wrong courses. So we have come."
*
*/
