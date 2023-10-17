//Write an abstract class MediaSegment for representation of a media segment. In the class you need to store information for:
//•	title (array of maximum 100 characters)
//•	 author (array of maximum 100 characters)
//•	 duration in seconds (positive integer)
//•	 size of the record in megabytes (positive integer)
//For the class implement the necessary constructors and methods for the program to work according to the calls in the main function.
//From the class MediaSegment, derive two separate classes, one for audio and one for video recordings. In the class AudioRecording additionally, you need to store information for:
//•	the format of the audio record (one of the values: mp3, wav, ogg and flac)
//•	the number of channels (variable of type short)
//For the class AudioRecording implement the necessary constructors/methods and implement a method price that calculates the price of the audio record in the following way:
//A product of the duration and number of channels is calculated. If the format is flac then the calculated product from step 1 is increased by 50%.
//Overload the operator << that will print the audio recording in the following format:
//Title - Author - Duration - Size - Price
//In the class VideoRecording additionally, you need to store information for:
//•	the width of the video recording (positive integer)
//•	the compression format of the video recording (one of the values: x264, Theora, AV1)
//For the class VideoRecording implement the necessary constructors/methods and implement a method price that will calculate the price of the video record in the following way:
//If the width is less or equal to 1920, the price is 100 euros per second. If the width is greater than 1920, the price is 170 euros per second. If the compression is x264 then the calculated price from the first step is increased by 50%. If the compression is Theora, the price from the first step is reduced by 10%.
//Overload the operator << that will print the video recording in the following format:
//Title - Author - Duration - size - dimension – price
//Create a class MusicVideo that is derived from the classes AudioRecording and VideoRecording. In this class, you need to store additional information for:
//•	the date of publication (array of characters in the format ddmmgggg)
//Implement a method price for the calculation of the price of a music video. The price is calculated as the sum of the price of the audio and the video recordings. If the publication date is after 2010, the price is additionally increased by 30%.
//Overload the operator << that will print the music video in the following format:
//Title - Author - Date of publication - Duration – Price
//Implement a global function total_price that has two arguments: an array of pointers of type MediaSegment and their count. The function should return the total price of all media segments.
//Implement a global function cheapest_music_video that has two arguments: an array of pointers of type MediaSegment and their count. The result of the function should be the cheapest music video from the received media segments.


#include <iostream>
#include <cstring>
using namespace std;

class MediaSegment{
protected:
    char title[100];
    char author[100];
    int duration;
    int size;
public:
    MediaSegment(char *title="", char *author="", int duration=0, int size=0){
        strcpy(this->title,title);
        strcpy(this->author,author);
        this->duration=duration;
        this->size=size;
    }
    virtual float price()=0;
};

//=============================================================================================================//

class AudioRecording:virtual public MediaSegment{
protected:
    int format;
    // 0 - mp3
    // 1 - wav
    // 2 - ogg
    // 3 - flac
    short channels;
public:
    AudioRecording(char *title="", char *author="", int duration=0, int size=0, short format=0, short channels=0):
    MediaSegment(title,author,duration,size),format(format),channels(channels){}

    float price() override {
        float p=float (duration)*channels;
        if(format==3){
            return p*1.5;
        }
        return p;
    }
    friend ostream &operator<<(ostream &out, AudioRecording &a){
        out<<a.title<<" - "<<a.author<<" - "<<a.duration<<" - "<<a.size<<" - "<<a.price()<<endl;
        return out;
    }

};

//======================================================================================================================//

class VideoRecording:virtual public MediaSegment{
protected:
    int width;
    int compression;
    // VideoCompression:
    // 0 - x264
    // 1 - Theora
    // 2 - AV1
public:
    VideoRecording(char *title="", char *author="", int duration=0, int size=0, int width=0, int compression=0):
            MediaSegment(title,author,duration,size),width(width),compression(compression){}

    float price() override {
        float p;
        if(width<=1920){
            p=100*duration;
        } else{
            p=170*duration;
        }

        if(compression==0){
            p=p*1.5;
        } else if(compression==1){
            p=p*0.9;
        }
        return p;
    }
    friend ostream &operator<<(ostream &out, VideoRecording &a){
        out<<a.title<<" - "<<a.author<<" - "<<a.duration<<" - "<<a.size<<" - "<<a.width<<" - "<<a.price()<<endl;
        return out;
    }
};


//======================================================================================================================//


class MusicVideo:public AudioRecording,public VideoRecording{
private:
    char date[9];
public:
    MusicVideo(char *title="", char *author="", int duration=0, int size=0, short format=0, short channels=0, int width=0, int compression=0, char *date=""):
            MediaSegment(title,author,duration,size), AudioRecording(title,author,duration,size,format,channels),
            VideoRecording(title,author,duration,size,width,compression){
        strcpy(this->date,date);
    }
    int getYear(){
        int year=0;
        for(int i=4 ; i<8 ; i++){
            year=year*10+(date[i]-'0');;
        }
        return year;
    }
    float price() override {
        float p=AudioRecording::price()+VideoRecording::price();
        if(getYear()>2010){
            p=p*1.3;
        }
        return p;
    }
    friend ostream &operator<<(ostream &out, MusicVideo &a){
        out<<a.title<<" - "<<a.author<<" - "<<a.date<<" - "<<a.duration<<" - "<<a.price()<<endl;
        return out;
    }
};

//=====================================================================================================================

float total_price(MediaSegment **p, int n){
    float sum=0;
    for(int i=0 ; i<n ; i++){
        sum+=p[i]->price();
    }
    return sum;
}

//====================================================================================================================

 MusicVideo *cheapest_music_video(MediaSegment **p, int n){
    MusicVideo *tmp,*cheapest;
    int flag=1;
    for(int i=0 ; i<n ; i++){
        tmp=dynamic_cast<MusicVideo *>(p[i]);
        if(tmp!= nullptr){
            if(flag){
                cheapest=tmp;
                flag=0;
            } else if(tmp->price()<cheapest->price()){
                cheapest=tmp;
            }
        }
    }
     return cheapest;
}

int main() {

    int test_case_num;
    cin >> test_case_num;


    // for MediaSegment
    char title[100];
    char author[1000];
    unsigned int size;
    unsigned int duration;


    // for AudioRecording
    //-------------------
    unsigned short channels;

    // AudioFormat:
    // 0 - mp3
    // 1 - wav
    // 2 - ogg
    // 3 - flac
    unsigned short format;


    // for VideoRecording
    //-------------------
    unsigned short width;

    // VideoCompression:
    // 0 - x264
    // 1 - Theora
    // 2 - AV1
    int compression;


    // for MusicVideo
    //-------------------
    char publication_date[9];


    if (test_case_num == 1) {
        cout << "Testing class AudioRecording and operator<<" << std::endl;
        cin.get();
        cin.getline(title, 100);
        cin.getline(author, 100);
        //cin.get();
        cin >> duration >> size;
        cin >> format >> channels;

        AudioRecording a(title, author, duration, size, format, channels);

        cout << a;

    } else if (test_case_num == 2) {
        cout << "Testing class VideoRecording and operator<<" << std::endl;
        cin.get();
        cin.getline(title, 100);
        cin.getline(author, 100);
        //cin.get();
        cin >> duration >> size;
        cin >> width >> compression;

        VideoRecording v(title, author, duration, size, width, compression);

        cout << v;

    } else if (test_case_num == 3) {
        cout << "Testing class MusicVideo and operator<<" << std::endl;

        cin.get();
        cin.getline(title, 100);
        cin.getline(author, 100);
        //cin.get();
        cin >> duration >> size;

        cin >> format >> channels;
        cin >> width >> compression;

        cin.get();
        cin.getline(publication_date, 9);
        MusicVideo mv(title, author, duration, size, format, channels, width, compression, publication_date);

        cout << mv;
    } else if (test_case_num == 4) {
        cout << "Testing function: total_price " << std::endl;

        MediaSegment **m;

        int num_media_segments;
        cin >> num_media_segments;

        // 1 - AudioRecording
        // 2 - VideoRecording
        // 3 - MusicVideo
        short media_type;

        m = new MediaSegment *[num_media_segments];

        for (int i = 0; i < num_media_segments; i++) {

            cin >> media_type;

            cin.get();
            cin.getline(title, 100);
            cin.getline(author, 100);
            //cin.get();
            cin >> duration >> size;

            switch (media_type) {
                case 1:
                    cin >> format >> channels;
                    m[i] = new AudioRecording(title, author, duration, size, format, channels);
                    break;
                case 2:
                    cin >> width >> compression;
                    m[i] = new VideoRecording(title, author, duration, size, width, compression);
                    break;
                case 3:
                    cin >> format >> channels;
                    cin >> width >> compression;
                    cin.get();
                    cin.getline(publication_date, 9);
                    m[i] = new MusicVideo(title, author, duration, size, format, channels, width, compression,
                                          publication_date);
                    break;
            }
        }

        //for (int i=0;i<num_media_segments; i++){
        //    cout << *m[i];
        //}

        cout << "Total PRC is: " << total_price(m, num_media_segments);

        delete[] m;

    } else if (test_case_num == 5) {
        cout << "Testing function: cheapest_music_video " << std::endl;

        MediaSegment **m;

        int num_media_segments;
        cin >> num_media_segments;

        // 1 - AudioRecording
        // 2 - VideoRecording
        // 3 - MusicVideo
        short media_type;

        m = new MediaSegment *[num_media_segments];

        for (int i = 0; i < num_media_segments; i++) {

            cin >> media_type;

            cin.get();
            cin.getline(title, 100);
            cin.getline(author, 100);
            //cin.get();
            cin >> duration >> size;

            switch (media_type) {
                case 1:
                    cin >> format >> channels;
                    m[i] = new AudioRecording(title, author, duration, size, format, channels);
                    break;
                case 2:
                    cin >> width >> compression;
                    m[i] = new VideoRecording(title, author, duration, size, width, compression);
                    break;
                case 3:
                    cin >> format >> channels;
                    cin >> width >> compression;
                    cin.get();
                    cin.getline(publication_date, 9);
                    m[i] = new MusicVideo(title, author, duration, size, format, channels, width, compression,
                                          publication_date);
                    break;
            }
        }

        cout << cheapest_music_video(m, num_media_segments);

        delete[] m;
    }

    return 0;
}