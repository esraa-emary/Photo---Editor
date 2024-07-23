// Purpose: Photo Editor.
// Description: This program applies some effects to photos.
// Author: Esraa Emary Abd Elsalam.
// version: 4.
//========================================================================================================================================//

#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <regex>
#include <windows.h>
#include "Image_Class.h"
using namespace std;

// Save the effect in a new photo or the same one.
void how_to_save(Image &image, string &photo){
    cout << "\n----------------------------------------------------------------------" << endl << endl;
    cout << "Do you want to save the effect in a new photo or replace the base ?\n[1] New photo.\n[2] Replace the base.\nChoice: ";
    while (true)
    {
        string choice;
        getline(cin, choice);

        // Save the effect in a new photo.
        if(choice == "1"){
            string new_name;
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "Remember that:" << endl;
            cout << "The new file name must be one of the following format.\n";
            cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
            cout << "Please enter the new file name:\n--> ";
            getline(cin, new_name);

            // Check the validity of the new file name.
            while(new_name.size() < 5 || ((new_name.substr(new_name.size() - 5 , 5) != ".jpeg") && (new_name.substr(new_name.size() - 4 , 4) != ".jpg") && (new_name.substr(new_name.size() - 4 , 4) != ".png") && (new_name.substr(new_name.size() - 4 , 4) != ".bmp"))){
                cout << "\n----------------------------------------------------------------------" << endl << endl;
                cout << "Invalid new file name.\n";
                cout << "\n----------------------------------------------------------------------" << endl << endl;
                cout << "Remember that:" << endl;
                cout << "The new file name must be one of the following format.\n";
                cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
                cout << "Please enter a valid new file name:\n--> ";
                getline(cin, new_name);
            }
            image.saveImage(new_name);
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "Photo has been saved successfully." << endl;
            break;
        }
        
        // Save the effect in the same photo.
        else if(choice == "2"){
            image.saveImage(photo);
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "Photo has been saved successfully." << endl;
            break;
        }
        
        // Invalid choice.
        else{
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "Please enter a valid choice:\n-->" << endl;   
            continue;
        }
    }
}

// Save the effect in a new photo only.
void how_to_save2(Image &image){
    string new_name;
    cout << "\n----------------------------------------------------------------------" << endl << endl;
    cout << "Remember that:" << endl;
    cout << "The new file name must be one of the following format.\n";
    cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
    cout << "Please enter the new file name:\n--> ";
    getline(cin, new_name);

    // Check the validity of the new file name.
    while(new_name.size() < 5 || ((new_name.substr(new_name.size() - 4 , 4) != "jpeg") && (new_name.substr(new_name.size() - 3 , 3) != "jpg") && (new_name.substr(new_name.size() - 3 , 3) != "png") && (new_name.substr(new_name.size() - 3 , 3) != "bmp"))){
        cout << "\n----------------------------------------------------------------------" << endl << endl;
        cout << "Remember that:" << endl;
        cout << "The new file name must be one of the following format.\n";
        cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
        cout << "Please enter a valid new file name:\n--> ";
        getline(cin, new_name);
    }
    image.saveImage(new_name);
    cout << "\n----------------------------------------------------------------------" << endl << endl;
    cout << "Photo has been saved successfully." << endl;
}

// Get the image from the user to apply the filter.
string load(string &name){
    while (true) {
        cout << endl;
        try {
        Image image(name);
        cout << "----------------------------------------------------------------------" << endl << endl;
        cout << "Photo Loaded Successfuly.\n";
        return name;
        }
        catch (invalid_argument) {
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "Please enter a valid file name:\n--> ";
            getline(cin, name);
        }
    }
}

// ========================================================== Main Functions ========================================================== //

// ========================================================== Filter 1 (Grayscale Conversion) ========================================================== //
Image Grayscale_Conversion(Image &image){
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned  int avg = 0;                                                  // Initialize average value.
            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k);                                              // Accumulate pixel values.
            }
            avg /= 3;                                                               // Calculate average.
            image(i, j, 0) = avg;                                                   // Set all channels to the average value.
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }
    return image;
}

// ========================================================== Filter 2 (Darken and Lighten Image) ========================================================== //
Image Darken_and_Lighten(Image &image){
    while (true)
    {
        cout << "\n----------------------------------------------------------------------" << endl << endl;
        cout << "Do you want to darken or lighten the image ?\n[1] Darken The Image.\n[2] Lighten The Image.\n[3] Back.\nChoice: ";
        string choice2;
        getline(cin, choice2);

        // Darken The Image.
        if (choice2 ==  "1"){
            float darken = 0.5;                                                   // Initialize darken value.
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        image(i, j, k) *= darken;                                 // Change pixel values.
                    }
                }
            }
            return image;
        }

        // Lighten The Image.
        else if(choice2 == "2"){
            float lighten = 1.5;                                                // Initialize lighten value.
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        int val = image(i, j, k) * lighten;                     // Change pixel values.
                        if (val > 255)                                          // Check if channel value exceeds 255.
                            (image(i, j, k) = 255);
                        else
                            image(i, j, k) = val;
                    }
                }
            }
            return image;
        }

        // Back to the main menu.
        else if (choice2 =="3")
            break;

        else{
            cout << "Please enter a valid choice." << endl;   
            continue;
        }
    }
    return image;
}

// ========================================================== Filter 3 (Detect_Image_Edges) ========================================================== //
Image Detect_Image_Edges(Image &image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            unsigned int avg = 0;  // Initialize average value.
            for (int k = 0; k < 3; k++) {
                avg += image(i, j, k);  // Accumulate pixel values.
            }

            avg /= 3;  // Calculate average.
            int val;

            if (avg > 127) {
                val = 255;
            } else {
                val = 0;
            }

            // Set all channels to either 0 or 255 (to obtain black and white only)
            image(i, j, 0) = val;
            image(i, j, 1) = val;
            image(i, j, 2) = val;
        }
    }

    for (int i = 0; i < image.width; i++) {
        bool flag = false;
        bool flag2 = false;
        for (int j = 1; j < image.height-1; j++) {        
            if (j > 0 && image(i, j - 1, 0) == 255 && image(i, j, 0) == 0 && !flag) {
                flag2 = false;
                flag = true;
                image(i, j, 0) = 0;
                image(i, j, 1) = 0;
                image(i, j, 2) = 0;
            }

            else if (j < image.width - 1 && image(i, j, 0) == 0 && image(i, j + 1, 0) == 255 && !flag2){
                flag = false;
                flag2 = true;
                image(i, j, 0) = 0;
                image(i, j, 1) = 0;
                image(i, j, 2) = 0;
            }

            else{
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 255;
            }
        }
    }
    return image;
}            

// ========================================================== Filter 4 (Natural sunlight) ========================================================== //
Image Natural_sunlight(Image &image){
    for(int i = 0; i < image.width; i++) {
        for(int j = 0; j < image.height; j++) {
            if (image(i, j, 1) <= 220) image(i, j, 1) += 35;  // Check for underflow
            else image(i, j, 1) = 255;

            if (image(i, j, 0) <= 220) image(i, j, 0) += 35;  // Check for underflow
            else image(i, j, 0) = 255;

            if (image(i, j, 2) >= 20) image(i, j, 2) -= 20;  // Check for underflow
            else image(i, j, 2) = 0;
        }
    }
    return image;
}

// ========================================================== Filter 5 (Purple Image) ========================================================== //
Image Purple_Image(Image &image){
    for(int i = 0; i < image.width; i++) {
        for(int j = 0; j < image.height; j++) {
            if (image(i, j, 0) <= 240) image(i, j, 0) += 15;  // Check for overflow
            else image(i, j, 0) = 255;
            
            if (image(i, j, 2) <= 230) image(i, j, 2) += 25;  // Check for overflow
            else image(i, j, 2) = 255;
            
            if (image(i, j, 1) >= 40) image(i, j, 1) -= 40;  // Check for underflow
            else image(i, j, 1) = 0;
        }
    }
    return image;
}

// ========================================================== Filter 6 (Infrared Photography) ========================================================== //
Image Infrared_Photography(Image &image){
    for(int i=0; i<image.width; i++){
        for(int j=0; j<image.height; j++){
            for(int k=0; k<3; k++){
                image(i, j, k) = 255 - image(i, j, k);                          // Change pixel values.
                image(i, j, 0) = 255;
            }
        }  
    }
    return image;
}

//================================================================= Main Program ==============================================================//

int main(){
    // Welcome message and brief lines about our application.
    cout << "#==================== Welcome to our application ====================#" << endl << endl;
    cout << "---> This application takes any photo and applies some filters in it." << endl;
    cout << "---> To apply filters in a photo it must be in one of these formats:" << endl;
    cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
    
    int count = 0;
    string name;
    Image image;
    bool flag = false;
    
    while (true){
        cout << "\n----------------------------------------------------------------------" << endl << endl;
        cout << "What do you want to do ?\n"<< "[1]  Load a new image.\n" << "[2]  Grayscale Conversion.\n" << "[3]  Darken and Lighten Image.\n" << "[4] Detect Image Edges.\n" 
            << "[5] Natural sunlight.\n" << "[6] Purple Image.\n" << "[7] Infrared Photography.\n" <<"[8] Save the image.\n" << "[9] Exit.\n"<< "Choice: ";
        string choice1;
        getline(cin, choice1);

        bool filter = true;
        // Check that the user enrered an image first.
        if (count == 0 && (choice1 == "2" || choice1 == "3" || choice1 == "4" || choice1  == "5" || choice1  == "6" || choice1  == "7" || 
            choice1  == "8" || choice1  == "9" || choice1  == "10" || choice1  == "11" || choice1  == "12" || choice1  == "13" || 
            choice1  == "14" || choice1  == "15" || choice1  == "16" || choice1  == "17")){
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "Please load an image first.\n";
            filter = false;
            continue;
        }

        // Loading the image.
        if (choice1 == "1"){
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "Remember that:" << endl;
            cout << "The file name must be at one of the following format.\n";
            cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
            cout << "Please enter the file name:\n--> ";
            string photo_name;
            getline(cin, photo_name);
            name = photo_name;
            name = load(name);
            Image image1 (name);
            image = image1;
            count ++;
            filter = false;
        }

        // Applying filter 1 (Grayscale Conversion).
        else if (choice1 == "2"){
            image = Grayscale_Conversion(image);
        }

        // Applying filter 2 (Darken and Lighten Image).
        else if (choice1 == "3"){
            image = Darken_and_Lighten(image);
        }

        // Applying filter 3 (Detect Image Edges).
        else if (choice1 == "4"){
            image = Detect_Image_Edges(image);
        }

        // Applying filter 4 (Natural sunlight).
        else if (choice1 == "5"){
            image = Natural_sunlight(image);
        }

        // Applying filter 5 (Purple Image).
        else if (choice1 == "6"){
            image = Purple_Image(image);
        }

        // Applying filter 6 (Infrared Photography).
        else if (choice1 == "7"){
            image = Infrared_Photography(image);
        }

        // Save the image.
        else if (choice1 == "8"){
            filter = false;
            if (flag){
                how_to_save2(image);
                flag = false;
            }
            else
                how_to_save(image, name);
        }

        // Exit the application.
        else if (choice1 =="9")
            break;

        // Invalid choice.
        else{
            filter = false;
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "Please enter a valid choice." << endl;   
            continue;
        }

        if (filter) {
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "- Filter has been applied succesfully!\n";
            Sleep(1000);    // Wait a second to allow user to read the message
        }
    }
    cout << "\n----------------------------------------------------------------------" << endl << endl;
    cout << "#===== Thanks for using our application =====#" << endl;
    return 0;
}
